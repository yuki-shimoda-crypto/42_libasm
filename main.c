#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

size_t ft_strlen(const char *s);
char *ft_strcpy(char *dst, const char *src);
int ft_strcmp(const char *s1, const char *s2);
ssize_t ft_write(int fd, const void *buf, size_t count);
ssize_t ft_read(int fd, void *buf, size_t count);
char *ft_strdup(const char *s);

void test_strlen(const char *str)
{
    size_t original = strlen(str);
    size_t mine = ft_strlen(str);
    
    printf("文字列: \"%s\"\n", str);
    printf("元のstrlen: %zu\n", original);
    printf("ft_strlen: %zu\n", mine);
    printf("結果: %s\n\n", (original == mine) ? "OK" : "KO");
}

void test_strcpy(const char *src)
{
    char *dst1 = malloc(strlen(src) + 1);
    char *dst2 = malloc(strlen(src) + 1);
    
    if (!dst1 || !dst2) {
        printf("メモリ割り当てエラー\n");
        free(dst1);
        free(dst2);
        return;
    }
    
    char *ret1 = strcpy(dst1, src);
    char *ret2 = ft_strcpy(dst2, src);
    
    printf("コピー元: \"%s\"\n", src);
    printf("元のstrcpy: \"%s\"\n", dst1);
    printf("ft_strcpy: \"%s\"\n", dst2);
    printf("コピー元とコピー先が同じ: %s\n", strcmp(dst1, dst2) == 0 ? "OK" : "KO");
    printf("戻り値が正しい: %s\n\n", (ret1 == dst1 && ret2 == dst2) ? "OK" : "KO");
    
    free(dst1);
    free(dst2);
}

void test_strcmp(const char *s1, const char *s2)
{
    int original = strcmp(s1, s2);
    int mine = ft_strcmp(s1, s2);
    
    // 完全一致をチェック
    int exact_match = (original == mine);
    
    printf("文字列1: \"%s\"\n", s1);
    printf("文字列2: \"%s\"\n", s2);
    printf("元のstrcmp: %d\n", original);
    printf("ft_strcmp: %d\n", mine);
    printf("完全一致: %s\n\n", exact_match ? "OK" : "KO");
}

void test_write_normal()
{
    char buffer[] = "Hello, World!\n";
    size_t len = strlen(buffer);
    
    printf("--- 通常のwriteテスト ---\n");
    printf("標準出力(1)に書き込み:\n");
    
    ssize_t original = write(1, buffer, len);
    ssize_t mine = ft_write(1, buffer, len);
    
    printf("元のwrite戻り値: %zd\n", original);
    printf("ft_write戻り値: %zd\n", mine);
    printf("結果: %s\n\n", (original == mine) ? "OK" : "KO");
    
    // ファイルへの書き込みテスト
    char filename[] = "test_write.txt";
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    
    if (fd < 0) {
        perror("open");
        return;
    }
    
    printf("ファイルに書き込み:\n");
    
    original = write(fd, buffer, len);
    close(fd);
    
    fd = open(filename, O_WRONLY | O_APPEND, 0644);
    mine = ft_write(fd, buffer, len);
    close(fd);
    
    printf("元のwrite戻り値: %zd\n", original);
    printf("ft_write戻り値: %zd\n", mine);
    printf("結果: %s\n\n", (original == mine) ? "OK" : "KO");
    
    // ファイルの内容確認
    fd = open(filename, O_RDONLY);
    char read_buffer[100] = {0};
    ssize_t read_bytes = read(fd, read_buffer, sizeof(read_buffer) - 1);
    close(fd);
    
    printf("ファイルの内容: %s", read_buffer);
    printf("ファイルに正しく書き込まれた: %s\n\n", (read_bytes == (ssize_t)(len * 2)) ? "OK" : "KO");
    
    // 後片付け
    unlink(filename);
}

void test_write_error()
{
    char buffer[] = "Error test";
    size_t len = strlen(buffer);
    
    printf("--- エラーケースのwriteテスト ---\n");
    
    // 無効なファイルディスクリプタ
    printf("無効なファイルディスクリプタに書き込み:\n");
    
    errno = 0;
    ssize_t original = write(-1, buffer, len);
    int original_errno = errno;
    
    errno = 0;
    ssize_t mine = ft_write(-1, buffer, len);
    int mine_errno = errno;
    
    printf("元のwrite戻り値: %zd, errno: %d (%s)\n", original, original_errno, strerror(original_errno));
    printf("ft_write戻り値: %zd, errno: %d (%s)\n", mine, mine_errno, strerror(mine_errno));
    printf("結果: %s\n\n", (original == mine && original_errno == mine_errno) ? "OK" : "KO");
    
    // 無効なバッファポインタ
    printf("無効なバッファポインタで書き込み:\n");
    
    errno = 0;
    original = write(1, NULL, len);
    original_errno = errno;
    
    errno = 0;
    mine = ft_write(1, NULL, len);
    mine_errno = errno;
    
    printf("元のwrite戻り値: %zd, errno: %d (%s)\n", original, original_errno, strerror(original_errno));
    printf("ft_write戻り値: %zd, errno: %d (%s)\n", mine, mine_errno, strerror(mine_errno));
    printf("結果: %s\n\n", (original == mine && original_errno == mine_errno) ? "OK" : "KO");
}

void test_read_normal()
{
    // テスト用のファイルを作成
    char filename[] = "test_read.txt";
    char content[] = "This is a test file for ft_read function.";
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    
    if (fd < 0) {
        perror("open for write");
        return;
    }
    
    write(fd, content, strlen(content));
    close(fd);
    
    printf("--- 通常のreadテスト ---\n");
    
    // 標準的なread操作のテスト
    fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("open for read");
        unlink(filename);
        return;
    }
    
    char buffer1[100] = {0};
    char buffer2[100] = {0};
    
    // 最初の10バイトを読み込む
    lseek(fd, 0, SEEK_SET);
    ssize_t original = read(fd, buffer1, 10);
    
    // ファイルポインタを先頭に戻す
    lseek(fd, 0, SEEK_SET);
    ssize_t mine = ft_read(fd, buffer2, 10);
    
    close(fd);
    
    printf("部分読み込み (10バイト):\n");
    printf("元のread: \"%.*s\", 戻り値: %zd\n", (int)original, buffer1, original);
    printf("ft_read: \"%.*s\", 戻り値: %zd\n", (int)mine, buffer2, mine);
    printf("結果: %s\n\n", (original == mine && strncmp(buffer1, buffer2, original) == 0) ? "OK" : "KO");
    
    // ファイル全体を読み込む
    fd = open(filename, O_RDONLY);
    memset(buffer1, 0, sizeof(buffer1));
    memset(buffer2, 0, sizeof(buffer2));
    
    original = read(fd, buffer1, sizeof(buffer1) - 1);
    
    // ファイルポインタを先頭に戻す
    lseek(fd, 0, SEEK_SET);
    mine = ft_read(fd, buffer2, sizeof(buffer2) - 1);
    
    close(fd);
    
    printf("ファイル全体読み込み:\n");
    printf("元のread: \"%s\", 戻り値: %zd\n", buffer1, original);
    printf("ft_read: \"%s\", 戻り値: %zd\n", buffer2, mine);
    printf("結果: %s\n\n", (original == mine && strcmp(buffer1, buffer2) == 0) ? "OK" : "KO");
    
    // 後片付け
    unlink(filename);
}

void test_read_error()
{
    char buffer[100] = {0};
    
    printf("--- エラーケースのreadテスト ---\n");
    
    // 無効なファイルディスクリプタ
    printf("無効なファイルディスクリプタから読み込み:\n");
    
    errno = 0;
    ssize_t original = read(-1, buffer, sizeof(buffer) - 1);
    int original_errno = errno;
    
    errno = 0;
    ssize_t mine = ft_read(-1, buffer, sizeof(buffer) - 1);
    int mine_errno = errno;
    
    printf("元のread戻り値: %zd, errno: %d (%s)\n", original, original_errno, strerror(original_errno));
    printf("ft_read戻り値: %zd, errno: %d (%s)\n", mine, mine_errno, strerror(mine_errno));
    printf("結果: %s\n\n", (original == mine && original_errno == mine_errno) ? "OK" : "KO");
}

void test_strdup(const char *str)
{
    char *original = strdup(str);
    char *mine = ft_strdup(str);
    
    printf("元の文字列: \"%s\"\n", str);
    printf("strdupの結果: \"%s\"\n", original);
    printf("ft_strdupの結果: \"%s\"\n", mine);
    
    // 内容が同じか確認
    int content_ok;
    
    // ケース1: 両方のポインタが有効で、内容が一致
    if (original && mine) {
        if (strcmp(original, mine) == 0)
            content_ok = 1;
        else
            content_ok = 0;
    }
    // ケース2: 両方とも失敗（NULLを返した）場合も一致とみなす
    else if (!original && !mine) {
        content_ok = 1; // true
    }
    // ケース3: 一方だけ成功、一方だけ失敗
    else {
        content_ok = 0; // false
    }
    
    printf("内容が同じ: %s\n", content_ok ? "OK" : "KO");
    
    // メモリアドレスが異なるか確認
    int address_ok;
    if (original && mine) {
        // 両方とも有効な場合のみアドレス比較
        if (original != mine)
            address_ok = 1;
        else
            address_ok = 0;
        printf("メモリアドレスが異なる: %s\n\n", address_ok ? "OK" : "KO");
    } else {
        // 片方でもNULLならアドレスチェックは実施しない
        printf("メモリアドレスの比較: 不可（片方または両方がNULL）\n\n");
    }
    
    free(original);
    free(mine);
}

int main(void)
{
    printf("===== ft_strlen テスト =====\n");
    
    // strlenのテストケース
    test_strlen("");
    test_strlen("Hello");
    test_strlen("Hello, World!");
    test_strlen("42Tokyo");
    test_strlen("あいうえお");  // 日本語文字列 (マルチバイト文字)
    test_strlen("1234567890123456789012345678901234567890");  // 長い文字列
    
    printf("\n===== ft_strcpy テスト =====\n");
    
    // strcpyのテストケース
    test_strcpy("");
    test_strcpy("Hello");
    test_strcpy("Hello, World!");
    test_strcpy("42Tokyo");
    test_strcpy("あいうえお");  // 日本語文字列 (マルチバイト文字)
    test_strcpy("1234567890123456789012345678901234567890");  // 長い文字列
    
    printf("\n===== ft_strcmp テスト =====\n");
    
    // strcmpのテストケース
    test_strcmp("Hello", "Hello");           // 等しい
    test_strcmp("Hello", "Hellp");           // 1文字違い (o < p)
    test_strcmp("Hellp", "Hello");           // 1文字違い (p > o)
    test_strcmp("Hello", "Hello, World!");   // 前方一致、長さ違い
    test_strcmp("Hello, World!", "Hello");   // 前方一致、長さ違い
    test_strcmp("", "");                     // 空文字列同士
    test_strcmp("", "Hello");                // 片方が空文字列
    test_strcmp("Hello", "");                // 片方が空文字列
    test_strcmp("42Tokyo", "42Tokyp");       // 1文字違い
    test_strcmp("あいうえお", "あいうえお");         // 日本語文字列 同じ
    test_strcmp("あいうえお", "あいうえか");         // 日本語文字列 異なる
    test_strcmp("abc", "ABC");               // 大文字と小文字
    
    printf("\n===== ft_write テスト =====\n");
    test_write_normal();
    test_write_error();
    
    printf("\n===== ft_read テスト =====\n");
    test_read_normal();
    test_read_error();
    
    printf("\n===== ft_strdup テスト =====\n");
    test_strdup("");
    test_strdup("Hello");
    test_strdup("Hello, World!");
    test_strdup("42Tokyo");
    test_strdup("あいうえお");  // 日本語文字列 (マルチバイト文字)
    test_strdup("1234567890123456789012345678901234567890");  // 長い文字列
    
    return (0);
} 