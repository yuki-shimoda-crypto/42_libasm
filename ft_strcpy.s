; char *ft_strcpy(char *dst, const char *src);
; rdi: 第1引数 - コピー先の文字列へのポインタ (dst)
; rsi: 第2引数 - コピー元の文字列へのポインタ (src)
; rax: 戻り値 - コピー先の文字列へのポインタ (dst)

section .text
    global ft_strcpy

ft_strcpy:
    push rbp                ; ベースポインタを保存
    mov rbp, rsp            ; 新しいベースポインタを設定
    
    mov rax, rdi            ; 戻り値用にdstポインタを保存
    
    ; 引数チェック
    cmp rdi, 0              ; dstがNULLかチェック
    je end
    cmp rsi, 0              ; srcがNULLかチェック
    je end
    
    xor rcx, rcx            ; カウンタを0に初期化
    
copy_loop:
    mov dl, byte [rsi + rcx]    ; srcから1バイト読み取る
    mov byte [rdi + rcx], dl    ; dstに1バイト書き込む
    
    cmp dl, 0                   ; コピーした文字がヌル終端文字かチェック
    je end                      ; ヌル文字ならコピー終了
    
    inc rcx                     ; カウンタをインクリメント
    jmp copy_loop               ; ループを続ける
    
end:
    ; raxにはすでにdstポインタが格納されている
    
    mov rsp, rbp                ; スタックポインタを復元
    pop rbp                     ; ベースポインタを復元
    ret                         ; 関数から戻る 
    