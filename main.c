/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AI Assistant                               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023-11-10                            #+#    #+#               */
/*   Updated: 2023-11-10                           ###   ########.fr         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

size_t ft_strlen(const char *s);

void test_strlen(const char *str)
{
    size_t original = strlen(str);
    size_t mine = ft_strlen(str);
    
    printf("文字列: \"%s\"\n", str);
    printf("元のstrlen: %zu\n", original);
    printf("ft_strlen: %zu\n", mine);
    printf("結果: %s\n\n", (original == mine) ? "OK" : "KO");
}

int main(void)
{
    printf("===== ft_strlen テスト =====\n");
    
    // テストケース
    test_strlen("");
    test_strlen("Hello");
    test_strlen("Hello, World!");
    test_strlen("42Tokyo");
    test_strlen("あいうえお");  // 日本語文字列 (マルチバイト文字)
    test_strlen("1234567890123456789012345678901234567890");  // 長い文字列
    
    return (0);
} 