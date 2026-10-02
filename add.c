#include "apc.h"
#include <stdio.h>
#include <stdlib.h>

static int dl_append(Dlist **head, Dlist **tail, int data) 
{
    Dlist *node = (Dlist *)malloc(sizeof(Dlist));
    if (!node) return FAILURE;
    node->data = data;
    node->next = NULL;
    node->prev = *tail;
    if (*tail) 
    {
        (*tail)->next = node;
    } 
    else 
    {
        *head = node;   /* list was empty */
    }
    *tail = node;
    return SUCCESS;
}

int addition(Dlist **head1, Dlist **tail1,Dlist **head2, Dlist **tail2,Dlist **headR, Dlist **tailR)
{
    (void)tail1;
    (void)tail2;
    Dlist *p1 = *head1;
    Dlist *p2 = *head2;
    int carry = 0;
    *headR = NULL;
    *tailR = NULL;

    while (p1 || p2 || carry) 
    {
        int d1 = p1 ? p1->data : 0;
        int d2 = p2 ? p2->data : 0;
        int sum = d1 + d2 + carry;
        int digit = sum % 10;
        carry = sum / 10;

        if (dl_append(headR, tailR, digit) != SUCCESS) 
        {
            dl_delete_list(headR, tailR);
            return FAILURE;
        }
        if (p1) p1 = p1->next;
        if (p2) p2 = p2->next;
    }
    return SUCCESS;
}
