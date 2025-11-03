#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

typedef struct Node
{
    int data;
    struct Node *next;
} Node, *LinkList;

void freeList(LinkList L)
{
    Node *current = L;
    Node *nextNode;
    while (current != NULL)
    {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }
}

void createList(LinkList *L, int arr[], int n)
{
    *L = (LinkList)malloc(sizeof(Node));
    if (*L == NULL)
    {
        perror("为头节点分配内存失败");
        exit(EXIT_FAILURE);
    }
    (*L)->next = NULL;
    Node *current = *L;
    for (int i = 0; i < n; i++)
    {
        Node *newNode = (Node *)malloc(sizeof(Node));
        if (newNode == NULL)
        {
            perror("为新节点分配内存失败");
            freeList(*L); // 清理已分配的内存
            exit(EXIT_FAILURE);
        }
        newNode->data = arr[i];
        newNode->next = NULL;
        current->next = newNode;
        current = newNode;
    }
}

// 函数：打印链表
void printList(LinkList L, const char *name)
{
    printf("%s = ", name);
    Node *current = L->next;
    while (current != NULL)
    {
        printf("%d", current->data);
        if (current->next != NULL)
        {
            printf(",");
        }
        current = current->next;
    }
    printf("\n");
}

// 算法2.1的实现: 将Lb中不存在于La的元素插入到La中
void unionList(LinkList La, LinkList Lb)
{
    Node *pa = La->next;
    Node *pb = Lb->next;
    Node *prev_pa = La;

    while (pa != NULL && pb != NULL)
    {
        if (pa->data < pb->data)
        {
            prev_pa = pa;
            pa = pa->next;
        }
        else if (pa->data > pb->data)
        {
            Node *newNode = (Node *)malloc(sizeof(Node));
            if (newNode == NULL)
            {
                perror("在 unionList 中分配内存失败");
                return;
            }
            newNode->data = pb->data;
            newNode->next = pa;
            prev_pa->next = newNode;
            prev_pa = newNode;
            pb = pb->next;
        }
        else
        { // pa->data == pb->data
            prev_pa = pa;
            pa = pa->next;
            pb = pb->next;
        }
    }
    // 如果Lb还有剩余元素，将它们附加到La的末尾
    if (pb != NULL)
    {
        prev_pa->next = pb;
    }
    // Lb的头节点现在是孤立的，其节点已成为La的一部分。
    // 我们将Lb的头节点的next设置为空，表示它已被消耗。
    Lb->next = NULL;
}

// 算法2.2的修改版: 合并两个有序链表La和Lb到Lc
void mergeList(LinkList La, LinkList Lb, LinkList *Lc)
{
    *Lc = (LinkList)malloc(sizeof(Node));
    if (*Lc == NULL)
    {
        perror("为Lc头节点分配内存失败");
        exit(EXIT_FAILURE);
    }
    (*Lc)->next = NULL;
    Node *pc = *Lc;
    Node *pa = La->next;
    Node *pb = Lb->next;

    // 这个合并操作重用了La和Lb的节点
    while (pa != NULL && pb != NULL)
    {
        if (pa->data <= pb->data)
        {
            pc->next = pa;
            pc = pa;
            pa = pa->next;
        }
        else
        {
            pc->next = pb;
            pc = pb;
            pb = pb->next;
        }
    }
    pc->next = (pa != NULL) ? pa : pb;

    // 将原始列表标记为空，因为它们的节点现在在Lc中
    La->next = NULL;
    Lb->next = NULL;
}

// 函数：删除有序链表中的重复元素
void deduplicateList(LinkList L)
{
    if (L == NULL || L->next == NULL)
        return;
    Node *current = L->next;
    while (current != NULL && current->next != NULL)
    {
        if (current->data == current->next->data)
        {
            Node *temp = current->next;
            current->next = temp->next;
            free(temp); // 释放重复的节点
        }
        else
        {
            current = current->next;
        }
    }
}

int main()
{
    // 设置控制台输出代码页为UTF-8以正确显示中文字符
    SetConsoleOutputCP(65001);

    // 初始数据
    int arr_a[] = {1, 2, 3, 4, 5};
    int arr_b[] = {2, 4, 6, 8, 10};
    LinkList La, Lb;
    createList(&La, arr_a, 5);
    createList(&Lb, arr_b, 5);

    printf("初始链表:\n");
    printList(La, "La");
    printList(Lb, "Lb");
    printf("\n");

    // (1) 执行算法2.1
    unionList(La, Lb);
    printf("(1) 算法 2.1 执行后:\n");
    printList(La, "new La");
    printf("\n");
    // Lb的节点现在在La中，释放Lb的孤立头节点
    free(Lb);

    // (2) 修改Lb并与新的La合并
    int arr_b_new[] = {2, 6, 8, 9, 11, 15, 20};
    LinkList Lb_new, Lc;
    createList(&Lb_new, arr_b_new, 7);

    int arr_a_new[] = {1, 2, 3, 4, 5, 6, 8, 10};
    LinkList La_new;
    createList(&La_new, arr_a_new, 8);

    printf("(2) 准备合并的链表:\n");
    printList(La_new, "La_new");
    printList(Lb_new, "Lb_new");

    mergeList(La_new, Lb_new, &Lc);
    printf("合并后:\n");
    printList(Lc, "Lc");
    printf("\n");
    // La_new和Lb_new已被消耗，释放它们的孤立头节点
    free(La_new);
    free(Lb_new);

    // (3) 从Lc中删除重复元素
    deduplicateList(Lc);
    printf("(3) 删除重复元素后:\n");
    printList(Lc, "Lc_deduplicated");
    printf("\n");

    // 释放所有分配的内存
    printf("正在释放内存...\n");
    freeList(La); // 释放第一个列表
    freeList(Lc); // 释放最终合并和去重后的列表
    printf("内存已释放。\n");

    return 0;
}