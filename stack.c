#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*******************************************************************************************************/
# define initial(head) struct stack *head=NULL

struct stack{
    int val;
    struct stack *next;
};
/*******************************************************************************************************/

/**API*/
int pop(struct stack **head){
    if(*head==NULL)
        return NULL;
    struct stack *temp=*head;
    int data=temp->val;
    *head=(*head)->next;
    free(temp);
    return data;
}
void push(struct stack **head, int data){
    struct stack *node=(struct stack *)malloc(sizeof(struct stack));
    node->val=data;
    node->next=*head;
    *head=node;
}
void release(struct stack *head){
    while(head){
        struct stack *temp=head;
        head=head->next;
        free(temp);
    }
}
bool isempty(struct stack *head){
    return head==NULL;
}

/**
 * Your stack struct will be instantiated and called as such:
 * initial(head);
 
 * add the new node, for example: number 7.
 * push(&head,7);
 
 * pop the last node from the tree.
 * int num = pop(&head); //num=7;
 
 * free the whole stack:
 * freeTree(head);
*/

int main(){
    initial(head);
    push(&head,5);
    push(&head,6);
    push(&head,7);
    int num=pop(&head);
    release(head);
}