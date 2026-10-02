#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "apc.h"
static void str_to_list(const char *s, Dlist **head, Dlist **tail)
{
    *head = NULL;
    *tail = NULL;
    size_t len = strlen(s);
    for (size_t i = 0; i < len; i++)
    {
        if (s[i] < '0' || s[i] > '9')
            continue;
        Dlist *node = malloc(sizeof(Dlist));
        if (!node)
            return;
        node->data = s[i] - '0';
        node->next = NULL;
        node->prev = *tail;
        if (*tail)
            (*tail)->next = node;
        else
            *head = node;

        *tail = node;
    }
    Dlist *cur = *head;
    Dlist *prev = NULL;
    while (cur)
    {
        Dlist *next = cur->next;
        cur->next = prev;
        cur->prev = next;
        prev = cur;
        cur = next;
    }
    *head = prev;
    *tail = *head;
    if (*tail)
    {
        while ((*tail)->next)*tail = (*tail)->next;
    }
}
static void print_result(Dlist *tail)
{
    if (!tail)
    {
        printf("0\n");
        return;
    }
    Dlist *temp = tail;
    while (temp)
    {
        printf("%d", temp->data);
        temp = temp->prev;
    }
    printf("\n");
}

int main(void)
{
    char expr[256];
    printf("Enter expression (example: 123+456 or 135-65 or 12*5 or 10/2 or 5^2): ");
    if (!fgets(expr, sizeof(expr), stdin))
    {
        printf("Input error\n");
        return EXIT_FAILURE;
    }
    expr[strcspn(expr, "\r\n")] = '\0';
    char *opPos = NULL;
    if (expr[0] == '-')
        opPos = strpbrk(expr + 1, "+-*/^");
    else
        opPos = strpbrk(expr, "+-*/^");
    if (!opPos)
    {
        printf("Invalid expression\n");
        return EXIT_FAILURE;
    }
    char operator = *opPos;
    *opPos = '\0';
    char *left = expr;
    char *right = opPos + 1;
    int leftNeg = (left[0] == '-');
    int rightNeg = (right[0] == '-');
    if (leftNeg) left++;
    if (rightNeg) right++;
    Dlist *h1 = NULL, *t1 = NULL, *h2 = NULL, *t2 = NULL, *hR = NULL, *tR = NULL;
    str_to_list(left, &h1, &t1);
    str_to_list(right, &h2, &t2);

    int sign = 1; 
    switch(operator)
    {
        /* Addition */
        case '+':
            if (!leftNeg && !rightNeg)
            {
                addition(&h1,&t1,&h2,&t2,&hR,&tR);
                print_result(tR);
            }
            else if (leftNeg && rightNeg)
            {
                addition(&h1,&t1,&h2,&t2,&hR,&tR);
                printf("-");
                print_result(tR);
            }
            else if (leftNeg && !rightNeg)
            {
                subtraction(&h2,&t2,&h1,&t1,
                         &hR,&tR,&sign);

                if(sign == -1)
                    printf("-");

                print_result(tR);
            }
            else
            {
                subtraction(&h1,&t1,&h2,&t2,&hR,&tR,&sign);

                if(sign == -1)
                    printf("-");

                print_result(tR);
            }
            break;
        /* Subtraction */
        case '-':
            if(leftNeg && !rightNeg)
            {
                addition(&h1,&t1,&h2,&t2,&hR,&tR);
                printf("-");
                print_result(tR);
            }
            else if(!leftNeg && rightNeg)
            {
                addition(&h1,&t1,&h2,&t2,&hR,&tR);
                print_result(tR);
            }
            else
            {
                subtraction(&h1,&t1,&h2,&t2,&hR,&tR,&sign);
                if(sign == -1)
                    printf("-");

                print_result(tR);
            }
            break;
        /* Multiplication */
        case '*':
        {
            int resultNeg = leftNeg ^ rightNeg;
            if (multiplication(&h1, &t1, &h2, &t2, &hR, &tR) != SUCCESS)
            {
                printf("Multiplication error\n");
                return EXIT_FAILURE;
            }
            if (resultNeg && tR != NULL)
            {
                Dlist *temp = tR;
                int isZero = 1;
                while (temp)
                {
                    if (temp->data != 0)
                    {
                        isZero = 0;
                        break;
                    }
                    temp = temp->prev;
                }
                if (!isZero)
                {
                    printf("-");
                }
            }
            print_result(tR);
            break;
        }
        /* Division */
        case '/':
        {
            int resultNeg = leftNeg ^ rightNeg;
            if (division(&h1, &t1, &h2, &t2, &hR, &tR) != SUCCESS)
            {
                printf("Division error\n");
                return EXIT_FAILURE;
            }
            if (resultNeg && tR != NULL)
            {
                Dlist *temp = tR;
                int isZero = 1;
                while (temp)
                {
                    if (temp->data != 0)
                    {
                        isZero = 0;
                        break;
                    }
                    temp = temp->prev;
                }
                if (!isZero)
                {
                    printf("-");
                }
            }
            print_result(tR);
            break;
        }
        /* Power */
        case '^':
        {
            int resultNeg = 0;
            if (leftNeg)
            {
                Dlist *temp = h2;
                int exponent = 0;
                while (temp)
                {
                    exponent = exponent * 10 + temp->data;
                    temp = temp->next;
                }
                if (exponent % 2 != 0)
                    resultNeg = 1;
            }
            if (power(&h1, &t1, &h2, &t2, &hR, &tR) != SUCCESS)
            {
                printf("Power error\n");
                return EXIT_FAILURE;
            }
            if (resultNeg)
            {
                printf("-");
            }
            print_result(tR);
            break;
        }
        default:
            printf("Unsupported operator\n");
            break;
    }
    dl_delete_list(&h1, &t1);
    dl_delete_list(&h2, &t2);
    dl_delete_list(&hR, &tR);
    return EXIT_SUCCESS;
}
