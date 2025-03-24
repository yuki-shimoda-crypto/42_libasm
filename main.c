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
    
    return (0);
} 