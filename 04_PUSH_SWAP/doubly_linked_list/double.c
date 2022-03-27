# include <stdio.h>
# include <stdlib.h>

typedef int element;
// 이중 연결리스트 노드 타입
typedef struct NODE {
	element data;
	struct NODE *prev;
	struct NODE *next;
}NODE;
// 이중 연결리스트 초기화
void init(NODE *phead) {
	phead->prev = phead;
	phead->next = phead;
}
// 이중 연결리스트 상태 출력
void print_list(NODE *phead) {
	NODE *p;
	for (p = phead->next; p != phead; p = p->next) {
		printf("<-| |%d| |-> ", p->data);
	}
	printf("\n");
}
// 새로운 데이터를 노드 before의 오른쪽에 삽입
void insert(NODE *before, element data) {
	NODE *newnode = (NODE*)malloc(sizeof(NODE));
	newnode->data = data;
	newnode->prev = before;
	newnode->next = before->next;
	before->next->prev = newnode;
	before->next = newnode;
}
// 노드 removed를 삭제
void delete(NODE *head, NODE *removed) {
	if (removed == head) return;
	head->next = removed->next;
	removed->next->prev = removed->prev;
	free(removed);
}
// 메인
int main(void) {
	NODE *head = (NODE *)malloc(sizeof(NODE));
    // struct NODE *head = malloc(sizeof(struct NODE));
	init(head);
	printf("추가 단계\n");
	for (int i = 0; i < 5; i++) {
		insert(head, i);
		print_list(head);
	}
	printf("\n삭제 단계\n");
	for (int i = 0; i < 5; i++) {
		print_list(head);
		delete(head, head->next);
	}
	free(head);
	return 0;
}
