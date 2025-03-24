; int ft_strcmp(const char *s1, const char *s2);
; rdi: 第1引数 - 比較する1つ目の文字列へのポインタ (s1)
; rsi: 第2引数 - 比較する2つ目の文字列へのポインタ (s2)
; rax: 戻り値 - 比較結果（s1 < s2: 負の値、s1 == s2: 0、s1 > s2: 正の値）

section .text
global ft_strcmp

ft_strcmp:
    push rbp                ; ベースポインタを保存
    mov rbp, rsp            ; 新しいベースポインタを設定

    xor rcx, rcx            ; カウンタを0に初期化

compare_loop:
    movzx rax, byte [rdi + rcx]    ; s1から1バイト読み取る (符号なし拡張)
    movzx rdx, byte [rsi + rcx]    ; s2から1バイト読み取る (符号なし拡張)

    ; 両方の文字を比較
    cmp rax, rdx                  ; 現在の文字を比較
    jne end_comparison            ; 不一致なら差分を返して終了

    ; どちらかがnullかチェック
    cmp rax, 0                    ; s1の文字がnullか確認
    je end_comparison             ; nullなら（同じ文字列か長さ違い）終了

    inc rcx                       ; カウンタをインクリメント
    jmp compare_loop              ; ループを続ける

end_comparison:
    sub rax, rdx                  ; 差分を計算（rax - rdx = s1文字 - s2文字）

    mov rsp, rbp                  ; スタックポインタを復元
    pop rbp                       ; ベースポインタを復元
    ret                           ; 関数から戻る 
