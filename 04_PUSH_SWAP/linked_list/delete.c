# include <stdio.h>
# include <stdlib.h>


struct NODE
{
    struct NODE *next;
    int data;
};

void addFirst(struct NODE *target, int data)
{
    struct NODE *newNode = malloc(sizeof(struct NODE));
    newNode->next = target->next;
    newNode->data = data;

    target->next = newNode;
}

void removeNode(struct NODE *target)
{
    struct NODE *removeNode = target->next;
    target->next = removeNode->next;

    free(removeNode);
}

int main()
{
    struct NODE *head = malloc(sizeof(struct NODE));

    head->next = NULL;

    addFirst(head, 10);
    addFirst(head, 20);
    addFirst(head, 30);

    removeNode(head);

    struct NODE *curr = head->next;
    while (curr != NULL)
    {
        printf("%d\n", curr->data);
        curr = curr->next;
    }

    curr = head->next;      //save the address of the fisrt node on visiting linked list pointer
    while (curr != NULL)
    {
        struct NODE *next = curr->next;
        free(curr);
        curr = next;
    }

    free(head);

    return 0;
}