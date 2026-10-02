#include "apc.h"
#include <stdio.h>
#include <stdlib.h>

int addition(Dlist **head1, Dlist **tail1,
             Dlist **head2, Dlist **tail2,
             Dlist **headR, Dlist **tailR);

int subtraction(Dlist **head1, Dlist **tail1,
                Dlist **head2, Dlist **tail2,
                Dlist **headR, Dlist **tailR,
                int *sign);

int multiplication(Dlist **head1, Dlist **tail1,
                  Dlist **head2, Dlist **tail2,
                  Dlist **headR, Dlist **tailR);

int division(Dlist **head1, Dlist **tail1,
            Dlist **head2, Dlist **tail2,
            Dlist **headR, Dlist **tailR);

int power(Dlist **head1, Dlist **tail1,
          Dlist **head2, Dlist **tail2,
          Dlist **headR, Dlist **tailR);

int dl_insert_first(Dlist **head, Dlist **tail, int data)
{
    Dlist *node = (Dlist *)malloc(sizeof(Dlist));
    if (!node) return FAILURE;
    node->data = data;
    node->prev = NULL;
    node->next = *head;
    if (*head) (*head)->prev = node;
    *head = node;
    if (*tail == NULL) *tail = node;
    return SUCCESS;
}

int dl_delete_first(Dlist **head, Dlist **tail)
{
    if (!head || !*head) return FAILURE;
    Dlist *tmp = *head;
    *head = tmp->next;
    if (*head) (*head)->prev = NULL;
    else *tail = NULL;
    free(tmp);
    return SUCCESS;
}

int dl_delete_list(Dlist **head, Dlist **tail)
{
    while (*head) 
    {
        dl_delete_first(head, tail);
    }
    return SUCCESS;
}

void print_list(Dlist *head)
{
    printf("[ ");
    for (Dlist *cur = head; cur; cur = cur->next) 
    {
        printf("%d ", cur->data);
    }
    printf("]\n");
}
