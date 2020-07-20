#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*******************************************************************************************************/
struct list_head{
    struct list_head *next, *prev;
};

#define offset(type,member) ((unsigned int) &((type *)0)->member)
#define container_of(ptr, type, member) ({ \
    const typeof( ((type *)0)->member ) *_mptr = (ptr); \
    (type *)( (char *)_mptr - offset(type, member) ); \
})


#define LIST_HEAD_INIT(name) {&(name), &(name)}
#define LIST_HEAD(name) struct list_head name=LIST_HEAD_INIT(name)
#define INIT_LIST_HEAD(ptr)  \
    do                       \
    {                        \
        (ptr)->next = (ptr); \
        (ptr)->prev = (ptr); \
    }while(0)

#define list_for_each(pos, head) for (pos = (head)->next; pos != (head); pos = (pos)->next)
#define list_entry(ptr, type, member) container_of(ptr, type, member);
void _list_add(struct list_head *new_list,struct list_head *prev,struct list_head *next){
    prev->next = new_list;
    new_list->prev = prev;
    next->prev = new_list;
    new_list->next = next;
}
void _list_del(struct list_head *prev,struct list_head *next){
    prev->next = next;
    next->prev = prev;
}
/*******************************************************************************************************/

/**API*/

/** add element behind the head(FILO)*/
void list_add(struct list_head *new_list,struct list_head *head){
    _list_add(new_list, head, head->next);
}

/** add element before the tail(FIFO)*/
void list_add_tail(struct list_head *new_list,struct list_head *head){
    _list_add(new_list, head->prev, head);
}

/** del specific element */
void list_del(struct list_head *element){
    _list_del(element->prev, element->next);
    element->prev = NULL;
    element->next = NULL;
}
/** check if the list is empty or not*/
bool list_empty(struct list_head *head){
    return head->next == head;
}

/**
 * This is the implementation of double linked list from linux kernel.
 * Create a new struct, like following structure.
 
 * struct DemoNode{
 *	int key;
 *	struct list_head list;
 * }; 
 
 * Initial head declaration: LIST_HEAD(obj);
 
 * And you can create a new DemoNode with the linked list by using list_add.
 
 * list_for_each: go thriugh every node.
 
 * list_entry: get DemoNode through linked list.
*/

/** example*/
struct DemoNode{
	int key;
	struct list_head list;
};

int main(){
    LIST_HEAD(obj);

    for (int i = 0; i < 10; i++){
        struct DemoNode *node = (struct DemoNode *)malloc(sizeof(struct DemoNode));
        node->key = i;
        list_add(&node->list,&obj);
    }
    
    struct list_head *pos;
    struct DemoNode *temp;
    
    printf("The element in list: ");
    list_for_each(pos, &obj){
        temp = list_entry(pos, struct DemoNode, list);
        printf("%d\t",temp->key);
    }
    printf("\n");
    
    temp = list_entry(obj.next, struct DemoNode, list);
    list_del(obj.next);
    free(temp);
    
    printf("After deleting the 9,\n");
    list_for_each(pos, &obj){
        temp = list_entry(pos, struct DemoNode, list);
        printf("%d\t",temp->key);
    }
    printf("\n");
    
    struct DemoNode *node = (struct DemoNode *)malloc(sizeof(struct DemoNode));
    node->key = 10;
    list_add_tail(&node->list,&obj);
    
    printf("After addding the 10 in the tail,\n");
    list_for_each(pos, &obj){
        temp = list_entry(pos, struct DemoNode, list);
        printf("%d\t",temp->key);
    }
    printf("\n");
    
    /** free the list*/
    list_for_each(pos, &obj){
        temp = list_entry(pos, struct DemoNode, list);
        free(temp);
    }
}
