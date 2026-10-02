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
static int copy_list(Dlist *src, Dlist **head, Dlist **tail)
{
    *head = NULL;
    *tail = NULL;
    while (src)
    {
        if (dl_append(head, tail, src->data) != SUCCESS)
            return FAILURE;
        src = src->next;
    }
    return SUCCESS;
}
static int is_zero(Dlist *head)
{
    return (head->data == 0 && head->next == NULL);
}
int division(Dlist **head1, Dlist **tail1,Dlist **head2, Dlist **tail2,Dlist **headR, Dlist **tailR)
{
    (void)tail1;
    (void)tail2;
    *headR = NULL;
    *tailR = NULL;
    if (is_zero(*head2))
    {
        printf("Division by zero not possible\n");
        return FAILURE;
    }
    int sign;
    Dlist *tempDividendH = NULL;
    Dlist *tempDividendT = NULL;
    copy_list(*head1, &tempDividendH, &tempDividendT);
    int count = 0;
    while (1)
    {
        Dlist *tempResultH = NULL;
        Dlist *tempResultT = NULL;
        subtraction(&tempDividendH,&tempDividendT,head2,tail2,&tempResultH,&tempResultT,&sign);
        if (sign == -1)
        {
            dl_delete_list(&tempResultH, &tempResultT);
            break;
        }
        dl_delete_list(&tempDividendH, &tempDividendT);
        tempDividendH = tempResultH;
        tempDividendT = tempResultT;
        count++;
    }
    dl_append(headR, tailR, count);
    dl_delete_list(&tempDividendH, &tempDividendT);
    return SUCCESS;
}