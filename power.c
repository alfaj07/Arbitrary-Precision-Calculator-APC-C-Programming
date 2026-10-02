#include "apc.h"
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
int power(Dlist **head1, Dlist **tail1,Dlist **head2, Dlist **tail2,Dlist **headR, Dlist **tailR)
{
    (void)tail1;
    (void)tail2;
    *headR = NULL;
    *tailR = NULL;
    dl_append(headR, tailR, 1);
    Dlist *tempBaseH = NULL;
    Dlist *tempBaseT = NULL;
    copy_list(*head1, &tempBaseH, &tempBaseT);
    Dlist *exp = *head2;
    int exponent = 0;
    if (exp)
        exponent = exp->data;
    while (exponent > 0)
    {
        Dlist *tempH = NULL;
        Dlist *tempT = NULL;
        multiplication(headR,tailR,&tempBaseH,&tempBaseT,&tempH,&tempT);
        dl_delete_list(headR, tailR);
        *headR = tempH;
        *tailR = tempT;
        exponent--;
    }
    dl_delete_list(&tempBaseH, &tempBaseT);
    return SUCCESS;
}