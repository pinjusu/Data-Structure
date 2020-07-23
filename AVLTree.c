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
/************************************************************************************************************************************************************************************************************************************/

/** traverse the tree by level*/ 
void printAVLTree(struct AVLTree *head){
    if(!head){
        printf("*******************************\n");
        printf("NULL");
        printf("*******************************\n");
    }
    int headheight = getHeight(head), maxnode = 1;
    while (headheight--)
        maxnode <<= 1;
    struct AVLTree **levelnode = (struct AVLTree **)malloc(sizeof(struct AVLTree *) * maxnode), **nextlevelnode = (struct AVLTree **)malloc(sizeof(struct AVLTree *) * maxnode);
    int levelnodeS = 1, nextlevelnodeS = 1;

    levelnode[0] = head;
    headheight = 1;

    printf("*******************************\n");
    
    while (nextlevelnodeS){
        nextlevelnodeS=0;
        printf("%d's level:\n", headheight++);
        while (levelnodeS--){
            if(levelnode[levelnodeS]){
                printf("%d\t", levelnode[levelnodeS]->key);
                nextlevelnode[nextlevelnodeS++] = levelnode[levelnodeS]->left;
                nextlevelnode[nextlevelnodeS++] = levelnode[levelnodeS]->right;
            } else
                printf("N\t"); //NULL
        }
        printf("\n");
        levelnodeS = nextlevelnodeS;
        struct AVLTree **temp = levelnode;
        levelnode = nextlevelnode;
        nextlevelnode = temp;
    }
    printf("*******************************\n");

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
        if(!head->left && !head->right)
            return NULL;
        else if(!head->right)
            return head->left;
        else if(!head->left)
            return head->right;
        else{
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


/**
 * Your AVL struct will be instantiated and called as such:
 * INIT_AVLTree(tree);
 
 * add the new node, for example: number 7.
 * tree = insert(7,tree);
 
 * delete 7 from the tree.
 * tree = delete(7,tree);
 
 * print the tree, would be like following structure:
 * printAVLTree(tree);
 * 1's level: 7
 * 2's level N N
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
    tree = delete(6,tree);
    printAVLTree(tree);
}
