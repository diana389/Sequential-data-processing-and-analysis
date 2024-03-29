#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define abs(a) (a) < 0 ? -(a) : (a)

typedef struct Node
{
    int timestamp, ok;
    double value;
    struct Node *next;
    struct Node *prev;
} Node, *TNode;

typedef struct
{
    TNode first;
    TNode last;
} DoubleList, *DList;

void print(DList list)
{
    TNode p = list->first;

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
    TNode new_node = (TNode)malloc(sizeof(struct Node));

    new_node->value = val;
    new_node->timestamp = time;

    new_node->next = NULL;

    if (list->first == NULL)
    {
        new_node->prev = NULL;
        list->first = new_node;
        list->last = new_node;

        return;
    }

    new_node->prev = list->last;
    list->last->next = new_node; 
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
    if (list->first == NULL || del == NULL)
        return;

    if (list->first == del)
        list->first = del->next;

    if (del->next != NULL)
        del->next->prev = del->prev;

    if (del->prev != NULL)
        del->prev->next = del->next;

    free(del);
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

        if (dif >= 100 && dif <= 1000)
        {
            p->timestamp = (double)(p->timestamp + p->prev->timestamp) / 2;
            p->value = (double)(p->value + p->prev->value) / 2;
        }
    }
}

void insertAfter(TNode prev_node, int new_timestamp, double new_value)
{
    if (prev_node == NULL)
        return;

    TNode new_node = (TNode)malloc(sizeof(Node));

    new_node->value = new_value;
    new_node->timestamp = new_timestamp;

    new_node->next = prev_node->next;
    prev_node->next = new_node;
    new_node->prev = prev_node;

    if (new_node->next != NULL)
        new_node->next->prev = new_node;
}

void c(DList list, int *npairs)
{
    TNode p, left1, left2, left3, right1, right2, right3;
    double C, f, w03 = (double)0.1 / 1.425, w13 = (double)0.325 / 1.425, w23 = (double)1 / 1.425;
    int new_timestamp;

    for (p = list->first; p->next != NULL; p = p->next)
    {
        int dif = abs(p->next->timestamp - p->timestamp);

        if (dif >= 1000)
        {
            new_timestamp = p->timestamp + 200;
            left1 = p->prev->prev;
            left2 = p->prev;
            left3 = p;
            right1 = p->next->next->next;
            right2 = p->next->next;
            right3 = p->next;

            while (new_timestamp < right3->timestamp)
            {
                C = (double)(new_timestamp - left3->timestamp) / (right3->timestamp - left3->timestamp);
                f = (1 - C) * (left1->value * w03 + left2->value * w13 + left3->value * w23) + C * (right1->value * w03 + right2->value * w13 + right3->value * w23);

                insertAfter(p, new_timestamp, f);

                (*npairs)++;
                p = p->next;
                new_timestamp = p->timestamp + 200;
            }
        }
    }
}

int st(DList list, int delta)
{
    sort(list);

    TNode p = list->first;
    int start = floor(p->value), end = start + delta, k, ok = 1;

    while (ok == 1)
    {
        k = 0;
        while (p->value >= start && p->value <= end && ok == 1)
        {
            k++;
            if (p->next != NULL)
                p = p->next;
            else
                ok = 0;
        }
        if (k > 0)
            printf("[%d, %d] %d\n", start, end, k);
        start += delta;
        end += delta;
    }
    return 1;
}

int main(int argc, char **argv)
{
    int npairs, i, arg, ok = 0;
    DList list = (DList)malloc(sizeof(DoubleList));
    double val;
    int time;
    list->first = NULL;
    list->last = NULL;

    scanf("%d", &npairs);

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
        if (strcmp(argv[arg], "--c") == 0)
        {
            c(list, &npairs);
            continue;
        }
        if (strstr(argv[arg], "--st") != NULL)
        {
            int delta = 0;
            for (i = 4; i < strlen(argv[arg]); i++)
                delta = delta * 10 + (argv[arg][i] - '0');
            ok = st(list, delta);
            continue;
        }
    }

    if (ok == 0)
    {
        printf("%d\n", npairs);
        print(list);
    }

    free_list(list, npairs);
    return 0;
}