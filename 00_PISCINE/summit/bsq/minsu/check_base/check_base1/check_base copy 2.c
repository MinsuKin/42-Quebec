#include <stdio.h>               
#include <string.h>                        // 문자열 처리함수를 위한 헤더파일
 
int main()
{
    char animal[9][28] = {
        "...........................", 
        "....o......................", 
        "............o..............", 
        "...........................", 
        "....o......................",     // 배열의 선언과 초기화
        "...............o...........", 
        "...........................", 
        "......o..............o.....", 
        "..o.......o................"
    };
    int i;                             // 반복 제어변수
    int count;                         // 문자열의 개수를 저장할 변수
    int total;                         // 배열의 전체 크기를 저장할 변수
    int stored=0;                      // 문자열이 저장된 크기를 저장할 변수
    double waste;                      // 낭비되는 공간의 크기를 저장할 변수
 
    total=sizeof(animal);                     // 배열 전체의 크기 계산
    count=sizeof(animal)/sizeof(animal[0]);   // 전체 크기를 한 행의 크기로 나누면
    printf("%d\n", total);
                                              // 문자열의 개수를 구할 수 있다.
    for(i=0; i<count; i++){               // 문자열의 개수만큼 반복
        printf("%s\n", animal[i]);         // 문자열 출력
        stored += (strlen(animal[i])+1);  //문자열의 길이를 계산하여 누적, 
                                          //이때 널문자까지 포함해야 한다.
    }                                                   
 
    waste=total-stored;                              // 낭비되는 기억공간 계산
    printf("낭비되는 기억공간의 비율 : %.2lf%% ", waste/total*100 );                                                                                 // 낭비되는 비율을 계산하여 출력한다.
 
    return 0;
}