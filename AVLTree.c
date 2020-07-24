#include <stdio.h>
#include <stdlib.h>

/************************************************************************************************************************************************************************************************************************************/
#define INIT_AVLTree(name) struct AVLTree *name = NULL;
struct AVLTree{
    struct AVLTree *left, *right;
    int height;
    int key;
};

/** create a new node*/
struct AVLTree * create(){
    struct AVLTree * node = (struct AVLTree *)malloc(sizeof(struct AVLTree));
    node->left = NULL;
    node->right = NULL;
    return node;
}

/** get the height of the node in the AVLTree*/
int getHeight(struct AVLTree *node){
    if(!node)
        return -1;
    return node->height;
}

/** update the height of node*/
void UpdateHeight(struct AVLTree *node){
    int leftH = getHeight(node->left), rightH = getHeight(node->right);
    node->height = (leftH > rightH)? leftH + 1 : rightH + 1;
}

/** get the BF by substrating the height right node from left node.*/
int getBalanceFactor(struct AVLTree *node){
    if(!node)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

/** LR */
struct AVLTree *LeftRotation(struct AVLTree *node){
    struct AVLTree *rightNode = node->right;
    node->right = rightNode->left;
    rightNode->left = node;

    UpdateHeight(node);
    UpdateHeight(rightNode);
    return rightNode;
}

/** RR */
struct AVLTree *RightRotation(struct AVLTree *node){
    struct AVLTree *leftNode = node->left;
    node->left = leftNode->right;
    leftNode->right = node;

    UpdateHeight(node);
    UpdateHeight(leftNode);
    return leftNode;
}

/** blance tree if the abs(BF)>1*/
struct AVLTree * BalanceTree(struct AVLTree *node){
    if(getBalanceFactor(node) > 1){
        if(getBalanceFactor(node->left)>=0)
            return RightRotation(node);
        else{
            node->left=LeftRotation(node->left);
            return RightRotation(node);
        }
    } else if(getBalanceFactor(node) < -1){
        if(getBalanceFactor(node->right)<=0)
            return LeftRotation(node);
        else{
            node->right=RightRotation(node->right);
            return LeftRotation(node);
        }
    }
    return node;
}

/** print the tree*/
void print2DUtil(struct AVLTree *head, int space)
{

    space += 10;

    if(head)
        print2DUtil(head->right, space);

    printf("\n");
    for (int i = 10; i < space; i++)
        printf(" ");
    if(head)
        printf("%d\n\n", head->key);
    else
        printf("%c\n\n",'N');

    if(head)
        print2DUtil(head->left, space);
}
/************************************************************************************************************************************************************************************************************************************/

void printAVLTree(struct AVLTree *head){
    printf("*****************************");
    print2DUtil(head,0);
    printf("*****************************\n");
}

/** insert the new node into the AVL tree*/
struct AVLTree * insert(int num,struct AVLTree *head){

    if(!head){
        struct AVLTree *newNode = create();
        newNode->key = num;
        return newNode;
    }

    if(num<head->key)
        head->left = insert(num,head->left);
    else
        head->right = insert(num,head->right);

    UpdateHeight(head);
    head=BalanceTree(head);
    return head;
}

/** delete the node from the AVL tree*/
struct AVLTree * delete(int num,struct AVLTree *head){
    if(!head){
        return NULL;
    }

    if(num<head->key)
        head->left = delete(num,head->left);
    else if(num>head->key)
        head->right = delete(num,head->right);
    else{
        if(!head->left && !head->right){
            free(head);
            return NULL;
        } else if(!head->right){
            struct AVLTree *temp=head->left;
            free(head);
            return temp;
        } else if(!head->left){
            struct AVLTree *temp=head->right;
            free(head);
            return temp;
        } else{
            struct AVLTree *leftmost = head->left;
            while(leftmost->right)
                leftmost = leftmost->right;

            //swap the value
            int dataTemp = leftmost->key;
            leftmost->key = head->key;
            head->key = dataTemp;

            //continue the process
            head->left = delete(num,head->left);
        }
    }
    UpdateHeight(head);
    head=BalanceTree(head);
    return head;
}

void freeTree(struct AVLTree *head){
    if(head){
        freeTree(head->left);
        freeTree(head->right);
        free(head);
    }
}


/**
 * Your AVL struct will be instantiated and called as such:
 * INIT_AVLTree(tree);
 
 * add the new node, for example: number 7.
 * tree = insert(7,tree);
 
 * delete 7 from the tree.
 * tree = delete(7,tree);
 
 * print the tree:
 * printAVLTree(tree);
 
 * free the whole tree:
 * freeTree(tree);
*/

int main(){
    INIT_AVLTree(tree);
    tree = insert(7,tree);
    tree = insert(4,tree);
    tree = insert(3,tree);
    tree = insert(5,tree);
    tree = insert(6,tree);
    printAVLTree(tree);
    tree = delete(4,tree);
    printAVLTree(tree);
    tree = delete(6,tree);
    printAVLTree(tree);
    freeTree(tree);
}
