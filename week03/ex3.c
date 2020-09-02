#include <stdio.h>
#include <stdlib.h>

struct Node{
    int val;
    struct Node* next;
};


struct Node *get_node(){
    struct Node *ret = (struct Node*)malloc(sizeof(struct Node));
    ret->next = NULL;
    ret->val = -1;
    return ret;
}

struct linked_list{
    struct Node *head;
    int size;
};

struct Node *get_linked_list(){
    struct linked_list *ret = (struct linked_list*)malloc(sizeof(struct linked_list));
    ret->head = get_node();
    ret->size = 0;
    return ret;
}

void print_list(struct linked_list *linkedList){
    struct Node *head = linkedList->head;
    while (head->next != NULL){
        head = head->next;
        printf("%d ", head->val);
    }
    puts("");
}

void insert_node(struct linked_list *linkedList, int newVal, int index){
    if (index < 0){
        printf("Invalid insertion! Index %d out of bounds\n", index);
        return;
    }
    int i;
    struct Node *head = linkedList->head;
    struct Node *cur = head;
    for (i = 0; i < index; i++){
        if (cur->next == NULL){
            break;
        }
        cur = cur->next;
    }
    if (i != index){
        printf("Invalid insertion! Index %d out of bounds\n", index);
        return;
    }
    linkedList->size++;
    struct Node *newNode = get_node();
    newNode->val = newVal;
    newNode->next = cur->next;
    cur->next = newNode;
}

void delete_node(struct linked_list *linkedList, int delVal){
    struct Node *head = linkedList->head;
    struct Node *cur = head;
    int i;
    for (i = 0; i < linkedList->size; i++) {
        if (cur->next->val == delVal) {
            break;
        }
        cur = cur->next;
    }
    if (i == linkedList->size){
        printf("The element %d is not in the list!\n", delVal);
        return;
    }
    linkedList->size--;
    struct Node *temp = cur->next;
    cur->next = cur->next->next;
    free(temp);
}

int main() {
    struct linked_list *list = get_linked_list();
    for (int i = 0; i < 10; i++){
        insert_node(list, i, i);
        print_list(list);
    }
    insert_node(list, 14, -1);
    for (int i = 0; i < 5; i++){
        insert_node(list, i, i + 13);
        print_list(list);
    }
    for (int i = 4; i < 10; i++){
        delete_node(list, i);
        print_list(list);
    }
    for (int i = 4; i < 10; i++){
        delete_node(list, i);
        print_list(list);
    }
    for (int i = 0; i < 4; i++){
        delete_node(list, i);
        print_list(list);
    }
    for (int i = 0; i < 10; i++){
        insert_node(list, i, i);
        print_list(list);
    }
    for (int i = 4; i < 10; i++){
        delete_node(list, i);
        print_list(list);
    }
    for (int i = 0; i < 4; i++){
        delete_node(list, i);
        print_list(list);
    }
    return 0;
}