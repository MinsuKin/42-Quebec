/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 17:11:59 by minkim            #+#    #+#             */
/*   Updated: 2022/04/20 19:53:13 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int main(void)
{
    // char *is_txt = "./test.txt";
    // char *is_exe = "./a.exe";

    // printf("txt읽기: %d\n", access(is_txt, R_OK));
    // printf("txt쓰기: %d\n", access(is_txt, W_OK));
    // printf("txt실행: %d\n", access(is_txt, X_OK));
    // printf("txt존재: %d\n", access(is_txt, F_OK));

    // printf("exe읽기: %d\n", access(is_exe, R_OK));
    // printf("exe쓰기: %d\n", access(is_exe, W_OK));
    // printf("exe실행: %d\n", access(is_exe, X_OK));
    // printf("exe존재: %d\n", access(is_exe, F_OK));

    int errno = 2;

    /* 실행 불가 파일 */
    printf("txt실행: %d\n", access("./test.txt", X_OK));
    printf("%s\n", strerror(errno));

    /* 존재하지 않는 파일 */
    printf("\n존재하지않는 파일: %d\n", access("./empty", R_OK));
    printf("%s\n", strerror(errno));
}