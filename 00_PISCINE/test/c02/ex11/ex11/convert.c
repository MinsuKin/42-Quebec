#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int main()
{
    int decimal = 10;                // 10진수 300
    char hexadecimal[20] = { 0, };    // 16진수로 된 문자열을 저장할 배열
    
    int position = 0;
    while (1)
    {
        int mod = decimal % 16;    // 16으로 나누었을 때 나머지를 구함
        if (mod < 10) // 나머지가 10보다 작으면
        {
            // 숫자 0의 ASCII 코드 값 48 + 나머지
            hexadecimal[position] = 48 + mod;
        }
        else    // 나머지가 10보다 크거나 같으면
        {
            // 나머지에서 10을 뺀 값과 영문 대문자 A의 ASCII 코드 값 65를 더함
            hexadecimal[position] = 97 + (mod - 10);
        }

        decimal = decimal / 16;    // 16으로 나눈 몫을 저장

        position++;    // 자릿수 변경

        if (decimal == 0)    // 몫이 0이되면 반복을 끝냄
            break;
    }

    // 배열의 요소를 역순으로 출력
    int i;

    i = position - 1;
    if (hexadecimal[1])
        printf("%c", hexadecimal[0]);
    else
        printf("0");
    while (i >= 0)
    {
        printf("%c", hexadecimal[i]);
        i--;
    }

    printf("\n");

    return 0;
}