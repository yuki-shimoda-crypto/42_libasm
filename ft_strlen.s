; size_t ft_strlen(const char *s);
; rdi: 第1引数 - 文字列へのポインタ
; rax: 戻り値 - 文字列の長さ

section .text
global ft_strlen

ft_strlen:
    push rbp            ; ベースポインタを保存
    mov rbp, rsp        ; 新しいベースポインタを設定
    
    xor rcx, rcx        ; カウンタを0に初期化
    
    ; 文字列がNULLの場合の処理
    cmp rdi, 0          ; 引数がNULLかチェック
    je end              ; NULLなら終了
    
count_loop:
    cmp byte [rdi + rcx], 0  ; 現在の文字がヌル終端文字かチェック
    je end                   ; ヌル文字なら終了
    inc rcx                  ; カウンタをインクリメント
    jmp count_loop           ; ループを続ける
    
end:
    mov rax, rcx        ; 結果をraxに格納
    
    mov rsp, rbp        ; スタックポインタを復元
    pop rbp             ; ベースポインタを復元
    ret                 ; 関数から戻る 
