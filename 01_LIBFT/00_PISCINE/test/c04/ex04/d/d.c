#include <stdio.h>
#define MAX_LENGTH     64

int main()
{
	char str[MAX_LENGTH], check_char;
	int i;

	printf("문자열을 입력하시오 : ");
	scanf_s("%s", str, MAX_LENGTH - 1);
	check_char = str[0];
	printf("연속된 문자가 있는지 체크 -> ");
	for (i = 1; str[i] != 0; i++) {
		if (check_char != str[i]) {
			check_char = str[i];
		} else {
			printf("연속된 문자가 있습니다 : %c\n", check_char);
			break;
		}
	}
	if (str[i] == 0) printf("연속된 문자가 없습니다!\n");

	return 0;
}