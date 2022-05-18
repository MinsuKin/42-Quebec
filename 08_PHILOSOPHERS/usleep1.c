#include <stdio.h>
#include <unistd.h>

int main()
{
  while (1)
  {
    printf("1초마다 문자열을 출력합니다\n");
    usleep(1000*1000);
  }
}

// ./a.out 으로 실행시 1초마다 메시지가 출력된다.