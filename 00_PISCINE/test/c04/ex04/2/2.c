#include <stdio.h>
 
void ToBinary(int num);
 
int main() {
    int num;
 
    printf("input: ");
    scanf("%d", &num);
 
    if (num > 0) {
        ToBinary(num);
    }
    else {
        printf("0");
    }
 
    putchar('\n');
 
    return 0;
}
 
void ToBinary(int num) {
    if (num > 0) {
        ToBinary(num / 2);
        printf("%d", num % 2);
    }
}