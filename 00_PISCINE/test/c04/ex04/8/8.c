




#include <stdio.h>
#include <unistd.h>
 
void tooctal(int num);
 
int main() {
    int num;
 
    num = 100;
 
    if (num > 0)
        tooctal(num);
    else
        write(1, "0", 1);
 
    putchar('\n');
 
    return 0;
}
 
void tooctal(int num) {
    if (num > 0) {
        tooctal(num / 8);
        printf("%d", num % 8);
    }
}







