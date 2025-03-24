; ssize_t ft_read(int fd, void *buf, size_t count);
; rdi: 第1引数 - ファイルディスクリプタ (fd)
; rsi: 第2引数 - 読み込むバッファへのポインタ (buf)
; rdx: 第3引数 - 読み込む最大バイト数 (count)
; rax: 戻り値 - 読み込んだバイト数またはエラー時は-1

extern __errno_location

section .text
    global ft_read

ft_read:
    push rbp                ; ベースポインタを保存
    mov rbp, rsp            ; 新しいベースポインタを設定
    
    ; システムコールの準備 (引数は既に正しいレジスタにある)
    mov rax, 0              ; 0 = readシステムコール番号
    syscall                 ; システムコール呼び出し
    
    ; エラーチェック
    cmp rax, 0              ; 負の値はエラー
    jl error_handler        ; エラーの場合、エラーハンドラに
    
    ; 成功時はそのまま値を返す
    mov rsp, rbp            ; スタックポインタを復元
    pop rbp                 ; ベースポインタを復元
    ret                     ; 関数から戻る

error_handler:
    ; システムコールはエラーコードを負の値で返すので、正の値に変換する
    neg rax                 ; エラー値を正の値に変換
    
    ; エラーコードを一時的に保存
    mov r11, rax            ; エラー番号を保存
    
    ; errnoのアドレスを取得し、そこにエラーコードを設定
    push r11                ; r11を保存 関数呼び出しによってレジスタの値が変わる可能性があるため
    call __errno_location wrt ..plt ; errnoのアドレスを取得（PIE対応）
    pop r11                 ; r11を復元
    
    mov [rax], r11          ; errno変数にエラー番号を設定
    
    mov rax, -1             ; 戻り値として-1を返す
    
    mov rsp, rbp            ; スタックポインタを復元
    pop rbp                 ; ベースポインタを復元
    ret                     ; 関数から戻る 