#include <stdio.h>
#include <stdlib.h>

typedef struct node* nodep;
typedef struct node
{
    int val;
    nodep link;
}node;

void insert(nodep* first, int score);
void listprint(nodep first);
void ddel(nodep* first, nodep trail, nodep x);
void oddel(nodep* first);

int main()
{
    FILE* fp = fopen("input.txt", "r");
    int val;
    nodep first = NULL;
    while (!feof(fp))
    {
        fscanf_s(fp, "%d", &val);
        insert(&first, val);
    }
    listprint(first);
    oddel(&first);
    listprint(first);
    nodep temp = first;
    nodep trail = NULL;
    while (temp != NULL)
    {
        ddel(&first, trail, temp);
        temp = first;
    }

}

void insert(nodep* first, int score) {
    nodep temp = malloc(sizeof(*temp));
    temp->val = score;
    temp->link = NULL;
    nodep* curr = first;
    while (*curr && (*curr)->val < score) {
        curr = &(*curr)->link; //curr를 링크필드의 주소로 이동시키고
    }

    temp->link = *curr;
    *curr = temp; // 그 주소의 값을 참조해 변경해준다.
}

void listprint(nodep first)
{
    nodep curr = first;
    for (; curr; curr = curr->link)
    {
        printf("(%p, %d, %p)\n", curr, curr->val, curr->link);
    }
}

void ddel(nodep* first, nodep trail, nodep x)
{
    if (trail)
        trail->link = x->link;
    else
        *first = x->link;
}

void oddel(nodep* first)
{
    nodep cur = *first;
    nodep pre = NULL;

    while (cur)
    {
        if (cur->val % 2 == 1)
        {
            nodep temp = cur;
            cur = cur->link;
            ddel(first, pre, temp);
        }
        else
        {
            pre = cur;
            cur = cur->link;
        }
    }
    printf("after delete odd num\n\n");
}