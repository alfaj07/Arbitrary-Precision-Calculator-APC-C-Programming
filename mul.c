#include "apc.h"
#include <stdio.h>
#include <stdlib.h>
static int dl_append(Dlist **head, Dlist **tail, int data)
{
    Dlist *node = malloc(sizeof(Dlist));
    if (!node)
        return FAILURE;
    node->data = data;
    node->next = NULL;
    node->prev = *tail;
    if (*tail)
        (*tail)->next = node;
    else
        *head = node;
    *tail = node;
    return SUCCESS;
}
int multiplication(Dlist **head1, Dlist **tail1,Dlist **head2, Dlist **tail2,Dlist **headR, Dlist **tailR)
{
    (void)tail1;
    (void)tail2;
    *headR = NULL;
    *tailR = NULL;
    if (((*head1)->data == 0 && (*head1)->next == NULL) ||((*head2)->data == 0 && (*head2)->next == NULL))
    {
        dl_append(headR, tailR, 0);
        return SUCCESS;
    }
    int size1 = 0;
    int size2 = 0;
    Dlist *p1 = *head1;
    Dlist *p2 = *head2;
    while (p1)
    {
        size1++;
        p1 = p1->next;
    }
    while (p2)
    {
        size2++;
        p2 = p2->next;
    }
    int *result = calloc(size1 + size2, sizeof(int));
    if (!result)
        return FAILURE;
    int i = 0;
    for (p1 = *head1; p1; p1 = p1->next)
    {
        int carry = 0;
        int j = 0;
        for (p2 = *head2; p2; p2 = p2->next)
        {
            int sum = result[i + j] +(p1->data * p2->data) +carry;
            result[i + j] = sum % 10;
            carry = sum / 10;
            j++;
        }
        if (carry)
            result[i + j] += carry;
        i++;
    }
    int size = size1 + size2;
    while (size > 1 && result[size - 1] == 0)
        size--;
    for (i = 0; i < size; i++)
    {
        if (dl_append(headR, tailR, result[i]) != SUCCESS)
        {
            free(result);
            dl_delete_list(headR, tailR);
            return FAILURE;
        }
    }
    free(result);
    return SUCCESS;
}