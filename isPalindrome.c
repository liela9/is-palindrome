#include <stdio.h>
#include <stdlib.h>

typedef enum { false, true } bool;

typedef struct ListNode {
    int val;
    struct ListNode* next;
} ListNode;

typedef struct list {
    struct ListNode* head;
    struct ListNode* tail;
} list;

static int list_count;

struct ListNode* reverseList(struct ListNode* head) {
    struct ListNode *curr, *next = NULL, *prev = NULL;

    curr = head;
    while (curr) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}

struct ListNode* copyList(struct ListNode* head) {
    if (head == NULL) {
        return NULL;
    } else {
        struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));

        newNode->val = head->val;
        newNode->next = copyList(head->next);

        return newNode;
    }
}

bool isPalindrome(struct ListNode* head) {
    struct ListNode* rev;
    int i = 0;

    rev = (struct ListNode*)malloc(sizeof(struct ListNode));
    if (!rev) {
        printf("Memory allocation failed\n");
        return false;
    }

    rev = reverseList(copyList(head));

    while (i < list_count) {
        if (rev->val == head->val) {
            rev = rev->next;
            head = head->next;
            i++;
            list_count--;
        } else
            return false;
    }

    free(rev);
    return true;
}

void sddToList(struct list* myList, int val) {
    struct ListNode* node;

    node = (struct ListNode*)malloc(sizeof(struct ListNode));
    if (!node) {
        printf("Memory allocation failed\n");
        return;
    }

    list_count++;
    node->val = val;
    node->next = NULL;

    if (myList->head == NULL) {
        myList->head = node;
        myList->tail = node;
    } else {
        myList->tail->next = node;
        myList->tail = node;
    }
}

void freeList(struct list* myList) {
    struct ListNode* temp;

    while (myList->head) {
        temp = temp->next;
        temp = myList->head;
        myList->head = myList->head->next;
        free(temp);
    }
    free(myList);
}

int main() {
    struct list* myList;

    myList = (struct list*)malloc(sizeof(struct list));
    if (!myList) {
        printf("Memory allocation failed\n");
        exit(0);
    }

    myList->head = NULL;
    myList->tail = NULL;

    sddToList(myList, 1);
    sddToList(myList, 2);

    if (isPalindrome(myList->head))
        printf("1");
    else
        printf("0");

    freeList(myList);

    return 0;
}
