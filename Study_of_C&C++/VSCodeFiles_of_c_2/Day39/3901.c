#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

typedef struct LinkedList
{
    Node *head;
} LinkedList;

LinkedList *create()
{
    LinkedList *list = (LinkedList *)malloc(sizeof(LinkedList));
    list->head = NULL;
    return list;
}

LinkedList *append(LinkedList *list, int data)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    if (list->head == NULL)
    {
        list->head = node;
    }
    else
    {
        Node *temp = list->head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = node;
    }
    return list;
}

LinkedList *delete(LinkedList *list, int data)
{
    if (list->head == NULL)
    {
        return list;
    }
    if (list->head->data == data)
    {
        Node *temp = list->head;
        list->head = list->head->next;
        free(temp);
        return list;
    }
    Node *temp = list->head;
    while (temp->next != NULL)
    {
        if (temp->next->data == data)
        {
            Node *del = temp->next;
            temp->next = del->next;
            free(del);
            return list;
        }
        temp = temp->next;
    }
    return list;
}

// 按序合并两个有序链表，将list_b合并到list_a中
LinkedList *merge(LinkedList *list_a, LinkedList *list_b)
{
    // 如果list_b为空，直接返回list_a
    if (list_b->head == NULL)
    {
        return list_a;
    }
    
    // 如果list_a为空，将list_b的所有节点移动到list_a
    if (list_a->head == NULL)
    {
        list_a->head = list_b->head;
        list_b->head = NULL;
        return list_a;
    }
    
    // 创建一个虚拟头节点，简化合并逻辑
    Node dummy;
    dummy.next = NULL;
    Node *current = &dummy;
    
    Node *ptr_a = list_a->head;
    Node *ptr_b = list_b->head;
    
    // 合并两个有序链表
    while (ptr_a != NULL && ptr_b != NULL)
    {
        if (ptr_a->data <= ptr_b->data)
        {
            current->next = ptr_a;
            ptr_a = ptr_a->next;
        }
        else
        {
            current->next = ptr_b;
            ptr_b = ptr_b->next;
        }
        current = current->next;
    }
    
    // 连接剩余的节点
    if (ptr_a != NULL)
    {
        current->next = ptr_a;
    }
    else
    {
        current->next = ptr_b;
    }
    
    // 更新list_a的头节点
    list_a->head = dummy.next;
    
    // 清空list_b的头节点（节点已经被移动到list_a）
    list_b->head = NULL;
    
    return list_a;
}

// 集合化
LinkedList *set(LinkedList *list)
{
    if (list->head == NULL)
    {
        return list;
    }
    Node *temp = list->head;
    while (temp->next != NULL)
    {
        if (temp->data == temp->next->data)
        {
            Node *duplicate = temp->next;
            temp->next = duplicate->next;
            free(duplicate);
        }
        else
        {
            temp = temp->next;
        }
    }
    return list;
}

LinkedList *clear(LinkedList *list)
{
    if (list->head == NULL)
    {
        return list;
    }
    Node *temp = list->head;
    while (temp != NULL)
    {
        Node *del = temp;
        temp = temp->next;
        free(del);
    }
    list->head = NULL;
    return list;
}

void print(LinkedList *list)
{
    if (list->head == NULL)
    {
        printf("NULL\n");
        return;
    }
    Node *temp = list->head;
    while (temp != NULL)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main()
{
    LinkedList *la = create();
    for (int i = 1; i <= 5; i++)
        append(la, i);

    LinkedList *lb = create();
    for (int i = 2; i <= 10; i += 2)
        append(lb, i);

    print(la);
    print(lb);

    LinkedList *lm = create();
    // 先将la的内容复制到lm中
    Node *temp = la->head;
    while (temp != NULL)
    {
        append(lm, temp->data);
        temp = temp->next;
    }
    // 然后将lb合并到lm中
    merge(lm, lb);
    set(lm);
    clear(la);
    print(lm);

    clear(lb);
    append(lb, 2);
    append(lb, 6);
    append(lb, 8);
    append(lb, 9);
    append(lb, 11);
    append(lb, 15);
    append(lb, 20);
    print(lb);

    LinkedList *lc = create();
    // 先将la的内容复制到lc中（此时la已经被清空）
    temp = la->head;
    while (temp != NULL)
    {
        append(lc, temp->data);
        temp = temp->next;
    }
    // 然后将lb合并到lc中
    merge(lc, lb);
    print(lc);
    return 0;
}