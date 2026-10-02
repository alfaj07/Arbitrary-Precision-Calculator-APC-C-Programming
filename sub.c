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


static int compare(Dlist *head1, Dlist *head2)
{
    int len1 = 0, len2 = 0;

    Dlist *p1 = head1;
    Dlist *p2 = head2;

    while (p1)
    {
        len1++;
        p1 = p1->next;
    }

    while (p2)
    {
        len2++;
        p2 = p2->next;
    }

    if (len1 > len2)
        return 1;

    if (len1 < len2)
        return -1;

    while (head1->next)
        head1 = head1->next;

    while (head2->next)
        head2 = head2->next;

    while (head1 && head2)
    {
        if (head1->data > head2->data)
            return 1;
        if (head1->data < head2->data)
            return -1;
        head1 = head1->prev;
        head2 = head2->prev;
    }

    return 0;
}

int subtraction(Dlist **head1, Dlist **tail1,
             Dlist **head2, Dlist **tail2,
             Dlist **headR, Dlist **tailR,
             int *sign)
{
    (void)tail1;
    (void)tail2;
    Dlist *p1;
    Dlist *p2;
    int borrow = 0;
    *headR = NULL;
    *tailR = NULL;
    int cmp = compare(*head1, *head2);
    if (cmp == 0)
    {
        dl_append(headR, tailR, 0);
        *sign = 1;
        return SUCCESS;
    }
    if (cmp < 0)
    {
        p1 = *head2;
        p2 = *head1;
        *sign = -1;
    }
    else
    {
        p1 = *head1;
        p2 = *head2;
        *sign = 1;
    }
    while (p1)
    {
        int d1 = p1->data;
        int d2 = p2 ? p2->data : 0;
        int diff = d1 - d2 - borrow;
        if (diff < 0)
        {
            diff += 10;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }
        if (dl_append(headR, tailR, diff) != SUCCESS)
        {
            dl_delete_list(headR, tailR);
            return FAILURE;
        }
        p1 = p1->next;

        if (p2)
            p2 = p2->next;
    }
    while (*tailR != *headR && (*tailR)->data == 0)
    {
        Dlist *temp = *tailR;
        *tailR = (*tailR)->prev;
        (*tailR)->next = NULL;
        free(temp);
    }

    return SUCCESS;
}