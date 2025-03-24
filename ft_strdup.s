; char *ft_strdup(const char *s);
; rdi: 第1引数 - 複製する元の文字列へのポインタ (s)
; rax: 戻り値 - 複製された新しい文字列へのポインタ、失敗時はNULL

extern malloc
extern __errno_location

section .text
global ft_strdup
extern ft_strlen
extern ft_strcpy

ft_strdup:
    push rbp                ; ベースポインタを保存
    mov rbp, rsp            ; 新しいベースポインタを設定
    push rdi                ; 元の文字列ポインタを保存

    ; 文字列の長さを計算
    call ft_strlen          ; ft_strlen(rdi)を呼び出し、結果はraxに格納される
    
    ; malloc用に長さ+1（NULL終端用）を計算
    inc rax                 ; 長さに1を加える（NULL終端のため）
    
    ; メモリ割り当て
    mov rdi, rax            ; 第1引数: 割り当てるバイト数
    call malloc wrt ..plt   ; malloc(rdi)を呼び出し
    
    ; mallocの戻り値をチェック
    test rax, rax           ; rax（mallocの戻り値）が0かチェック cmpより早い
    jz error_handler        ; 0の場合はエラー処理へ
    
    ; mallocが成功した場合：文字列をコピー
    mov rdi, rax            ; 第1引数: コピー先（新しいメモリ）
    pop rsi                 ; 第2引数: コピー元（元の文字列）
    call ft_strcpy          ; ft_strcpy(rdi, rsi)を呼び出し
    
    ; 関数を終了
    mov rsp, rbp            ; スタックポインタを復元
    pop rbp                 ; ベースポインタを復元
    ret                     ; 戻り値はraxに既に格納されている

error_handler:
    ; mallocエラー時の処理
    ; エラーコードENOMEM（12）をレジスタにセット
    mov r11, 12             ; r11にENOMEM（12：メモリ不足エラー）をセット
    
    ; errnoのアドレスを取得し、そこにエラーコードを設定
    push r11                ; r11を保存（関数呼び出しによって変わる可能性があるため）
    call __errno_location wrt ..plt ; errnoのアドレスを取得（PIE対応）
    pop r11                 ; r11を復元
    
    mov [rax], r11          ; errno変数にエラー番号を設定
    
    xor rax, rax            ; raxを0にクリア（NULLを返す）
    
    pop rdi                 ; スタックバランスを維持するため
    mov rsp, rbp            ; スタックポインタを復元
    pop rbp                 ; ベースポインタを復元
    ret                     ; 戻り値としてNULL（0）を返す 