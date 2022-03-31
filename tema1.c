#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define abs(a) (a) < 0 ? -(a) : (a)

typedef struct Node
{
    int timestamp, ok;
    double value;
    struct Node *next; // Pointer to next node in DLL
    struct Node *prev; // Pointer to previous node in DLL
} Node, *TNode;

typedef struct
{
    TNode first;
    TNode last;
} DoubleList, *DList;

void print(DList list)
{
    TNode p = list->first;
    // printf("\nLista:\n");
    if (p == NULL)
        printf("Lista este vida");
    else
    {
        while (p->next != NULL)
        {
            printf("%d %.2lf\n", p->timestamp, p->value);
            p = p->next;
        }
        printf("%d %.2lf\n", p->timestamp, p->value);
    }
}

void free_list(DList list, int npairs)
{
    TNode aux = list->first, p;
    int i;
    for (i = 0; i < npairs; i++)
    {
        p = aux->next;
        free(aux);
        aux = p;
    }
    free(list);
}

void append(DList list, double val, int time)
{
    TNode new_node = (TNode)malloc(sizeof(struct Node)); /* allocate node */

    new_node->value = val; /* put in the data  */
    new_node->timestamp = time;

    /* This new node is going to be the last node, so
          make next of it as NULL*/
    new_node->next = NULL;

    /* If the Linked List is empty, then make the new node as head */
    if (list->first == NULL)
    {
        new_node->prev = NULL;
        list->first = new_node;
        list->last = new_node;

        return;
    }

    /* Make last node as previous of new node */
    new_node->prev = list->last;

    list->last->next = new_node; /* Change the next of last node */

    list->last = new_node;

    return;
}

double average(TNode start)
{
    double avg = 0;
    TNode p = start;
    int i;

    for (i = 0; i < 5; i++)
    {
        avg += p->value;
        p = p->next;
    }
    return (double)avg / 5;
}

double deviation(TNode start, double avg)
{
    double dev = 0;
    TNode p = start;
    int i;

    for (i = 0; i < 5; i++)
    {
        dev += (p->value - avg) * (p->value - avg);
        p = p->next;
    }
    return (double)sqrt(dev / 5);
}

void deleteNode(DList list, TNode del)
{
    /* base case */
    if (list->first == NULL || del == NULL)
        return;

    /* If node to be deleted is head node */
    if (list->first == del)
        list->first = del->next;

    /* Change next only if node to be deleted is NOT the last node */
    if (del->next != NULL)
        del->next->prev = del->prev;

    /* Change prev only if node to be deleted is NOT the first node */
    if (del->prev != NULL)
        del->prev->next = del->next;

    free(del); /* Free the memory occupied by del*/
    return;
}

void init_ok(DList list)
{
    TNode p = list->first;
    if (p != NULL)
    {
        do
        {
            p->ok = 0;
            p = p->next;
        } while (p->next != NULL);
    }
}

void e1(DList list, int *npairs)
{
    int i;
    init_ok(list);
    TNode p = list->first;
    TNode mid = p->next->next;

    for (i = 0; i <= *npairs - 5; i++)
    {
        double avg = average(p);
        double dev = deviation(p, avg);
        // printf("Average: %.2lf; Deviation: %.2lf\n", avg, dev);
        if (mid->value < avg - dev || mid->value > avg + dev)
            mid->ok = 1;
        p = p->next;
        mid = mid->next;
    }

    p = list->first;
    do
    {
        if (p->ok == 1)
        {
            TNode aux = p;
            p = p->next;
            deleteNode(list, aux);
            (*npairs)--;
        }
        else
            p = p->next;

    } while (p->next != NULL);

    // printf("%d\n", *npairs);
    // print(list);
}

void sort(DList list)
{
    int ok = 1;
    double aux;
    TNode p;

    while (ok)
    {
        ok = 0;
        for (p = list->first->next; p != NULL; p = p->next)
            if (p->value < p->prev->value)
            {
                aux = p->value;
                p->value = p->prev->value;
                p->prev->value = aux;
                ok = 1;
            }
    }
}

TNode mini_list(TNode start)
{
    DList mini_lst = (DList)malloc(sizeof(DoubleList));
    mini_lst->first = NULL;
    mini_lst->last = NULL;

    TNode p = start;
    int i;
    for (i = 0; i < 5; i++)
    {
        append(mini_lst, p->value, p->timestamp);
        p = p->next;
    }
    // printf("\n");
    // print(mini_lst);
    sort(mini_lst);

    TNode new_node = (TNode)malloc(sizeof(struct Node));
    new_node->timestamp = mini_lst->first->next->next->timestamp;
    new_node->value = mini_lst->first->next->next->value;

    free_list(mini_lst, 5);
    return new_node;
}

void e2(DList list, int *npairs)
{
    TNode p = list->first;
    TNode mid = p->next->next;
    TNode new_node;

    DList new_list = (DList)malloc(sizeof(DoubleList));
    new_list->first = NULL;
    new_list->last = NULL;

    int i;

    for (i = 0; i <= *npairs - 5; i++)
    {
        new_node = mini_list(p);
        // printf("%d %.2lf", new_node->timestamp, new_node->value);
        // printf("\n");

        new_node->next = NULL;

        /* If the Linked List is empty, then make the new node as head */
        if (new_list->first == NULL)
        {
            new_node->prev = NULL;
            new_list->first = new_node;
            new_list->last = new_node;
        }
        else
        {
            /* Make last node as previous of new node */
            new_node->prev = new_list->last;

            new_list->last->next = new_node; /* Change the next of last node */

            new_list->last = new_node;
        }

        p = p->next;
        mid = mid->next;
    }

    // printf("%d\n", *npairs - 4);
    // print(new_list);

    TNode p1, p2;

    p1 = list->first;
    for (p2 = new_list->first; p2 != NULL; p2 = p2->next)
    {
        p1->value = p2->value;
        p1->timestamp = p2->timestamp;
        p1 = p1->next;
    }

    list->last = list->last->prev->prev->prev->prev;
    free(list->last->next->next->next->next);
    free(list->last->next->next->next);
    free(list->last->next->next);
    free(list->last->next);
    list->last->next = NULL;

    *npairs = (*npairs) - 4;

    // printf("%d\n", *npairs);
    // print(list);

    free_list(new_list, *npairs);
}

TNode medie(TNode start)
{
    TNode p = start;
    int i;
    double sum = 0;
    for (i = 0; i < 5; i++)
    {
        sum += p->value;
        p = p->next;
    }

    TNode new_node = (TNode)malloc(sizeof(struct Node));
    new_node->timestamp = start->next->next->timestamp;
    new_node->value = (double)sum / 5;
    return new_node;
}

void e3(DList list, int *npairs)
{
    TNode p = list->first;
    TNode mid = p->next->next;
    TNode new_node;

    DList new_list = (DList)malloc(sizeof(DoubleList));
    new_list->first = NULL;
    new_list->last = NULL;

    int i;

    for (i = 0; i <= *npairs - 5; i++)
    {
        new_node = medie(p);

        new_node->next = NULL;

        if (new_list->first == NULL)
        {
            new_node->prev = NULL;
            new_list->first = new_node;
            new_list->last = new_node;
        }
        else
        {
            new_node->prev = new_list->last;

            new_list->last->next = new_node;

            new_list->last = new_node;
        }

        p = p->next;
        mid = mid->next;
    }

    // printf("%d\n", *npairs - 4);
    // print(new_list);

    TNode p1, p2;

    p1 = list->first;
    for (p2 = new_list->first; p2 != NULL; p2 = p2->next)
    {
        p1->value = p2->value;
        p1->timestamp = p2->timestamp;
        p1 = p1->next;
    }

    list->last = list->last->prev->prev->prev->prev;
    free(list->last->next->next->next->next);
    free(list->last->next->next->next);
    free(list->last->next->next);
    free(list->last->next);
    list->last->next = NULL;

    *npairs = (*npairs) - 4;

    free_list(new_list, *npairs);
}

void u(DList list, int npairs)
{
    TNode p;
    for (p = list->first->next; p != NULL; p = p->next)
    {
        int dif = abs(p->timestamp - p->prev->timestamp);
        //printf("dif:%d\n", dif);
        if (dif >= 100 && dif <= 1000)
        {
            
            p->timestamp = (double)(p->timestamp + p->prev->timestamp) / 2;
            p->value = (double)(p->value + p->prev->value) / 2;
        }
    }
}

int main(int argc, char **argv)
{
    int npairs, i, arg;
    scanf("%d", &npairs);
    DList list = (DList)malloc(sizeof(DoubleList));
    double val;
    int time;
    list->first = NULL;
    list->last = NULL;

    for (i = 0; i < npairs; i++)
    {
        fflush(stdin);
        scanf("%d%lf", &time, &val);
        append(list, val, time);
    }

    for (arg = 0; arg < argc; arg++)
    {
        if (strcmp(argv[arg], "--e1") == 0)
        {
            e1(list, &npairs);
            continue;
        }
        if (strcmp(argv[arg], "--e2") == 0)
        {
            e2(list, &npairs);
            continue;
        }
        if (strcmp(argv[arg], "--e3") == 0)
        {
            e3(list, &npairs);
            continue;
        }
        if (strcmp(argv[arg], "--u") == 0)
        {
            u(list, npairs);
            continue;
        }
    }

    printf("%d\n", npairs);
    print(list);

    free_list(list, npairs);

    return 0;
}

/*
10
1 0.000000
2 0.314159
3 0.628314
4 0.942464
5 −1.743396
6 1.570732
7 1.884844
8 2.198938
9 2.513010
10 2.827057

10
1 0.00
2 0.31
3 0.62
4 0.94
5 −1.74
6 1.57
7 1.88
8 2.19
9 2.51
10 2.82
*/