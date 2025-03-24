#include <stdio.h>
#include <string.h>
#include <stdlib.h>

size_t ft_strlen(const char *s);
char *ft_strcpy(char *dst, const char *src);

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
    
    return (0);
} 