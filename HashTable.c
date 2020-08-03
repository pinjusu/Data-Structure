#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/*******************************************************************************************************/
struct node{
	int key;
	char *string;
	struct node *next;
};

struct hash{
	struct node **array;
	int NodeSize;
	int maxSize;
};

# define initial(head) struct hash *head; initialVal(head)
# define initialVal(head) \
do { \
    head=(struct hash *)malloc(sizeof(struct hash)); \
	head->NodeSize=0; \
	head->maxSize=5; \
	head->array=(struct node **)malloc(sizeof(struct node *)*(head->maxSize)); \
	memset(head->array,0,sizeof(struct node *)*(head->maxSize)); \
}while(0)

int hashFunction(struct hash *head,int key){
	return key%head->maxSize;
}
void Rehashing(struct hash *head,int originSize){
	struct node **newArray=(struct node **)malloc(sizeof(struct node *)*(head->maxSize));
	memset(newArray,0,sizeof(struct node *)*(head->maxSize));

	for(int i=0;i<originSize;i++){
		while(head->array[i]){
			struct node *RNode=head->array[i];
			head->array[i]=RNode->next;

			int Index=hashFunction(head,RNode->key);
			RNode->next=newArray[Index];
			newArray[Index]=RNode;
		}
	}

	free(head->array);
	head->array=newArray;
}

void TableDoubling(struct hash *head){
	head->maxSize=head->maxSize*2;
	Rehashing(head,head->maxSize/2);
}

void TableShrinking(struct hash *head){
	head->maxSize=head->maxSize/2;
	Rehashing(head,head->maxSize*2);
}
/*******************************************************************************************************/

/**API*/
void insert(struct hash *head,int key,char *string){
	if((head->NodeSize+1) == head->maxSize)
		TableDoubling(head);

	int Index=hashFunction(head,key);

	struct node *newNode=(struct node *)malloc(sizeof(struct node));
	newNode->key=key;
	newNode->string=string;

	newNode->next=head->array[Index];
	head->array[Index]=newNode;
	head->NodeSize=head->NodeSize+1;
}

bool delete(struct hash *head,int key){
	if((head->NodeSize-1) < head->maxSize/4)
		TableShrinking(head);

	int Index=hashFunction(head,key);

	struct node **traverse=&head->array[Index];
	while(*traverse){
		if((*traverse)->key==key){
			struct node *deletenode=*traverse;
			*traverse=(*traverse)->next;

			free(deletenode);
			head->NodeSize=head->NodeSize-1;
			return true;
		}
		traverse=&(*traverse)->next;
	}
	return false;
}

char *search(struct hash *head,int key){
	int Index=hashFunction(head,key);

	struct node *traverse=head->array[Index];
	while(traverse){
		if(traverse->key==key){
			return traverse->string;
		}
		traverse=traverse->next;
	}
	return NULL;
}


void display(struct hash *head){
	for(int i=0;i<head->maxSize;i++){
		printf("The chain from index %d:\n",i);

		struct node *traverse=head->array[i];
		while(traverse){
			printf("Key: %d Val: %s\n",traverse->key,traverse->string);
			traverse=traverse->next;
		}
		printf("\n");
	}
}

void freeHash(struct hash *head){
	for(int i=0;i<head->maxSize;i++){
		struct node *traverse=head->array[i];
		while(traverse){
			struct node *temp=traverse;
			traverse=traverse->next;
			free(temp);
		}
	}
}

/**
 * Your hash will be instantiated and called as such:
 * initial(head);
 
 * add the new node with key and val, 63 is key and "banana" is string val.
 * insert(head,63,"banana");
 
 * delete the node with key from the tree. 63 is the key.
 * bool successOrNot = delete(head,63);
 
 * search the val with corresponding key.
 * search(head,63);
 * If there has a node with the same key, the API will return the val.
 * If not, return NULL.
 
 * display the whole hash table:
 * display(head);
 
 * free the whole hash table:
 * freeHash(head);
*/


int main(){
	initial(head);

	insert(head,63,"banana");
	insert(head,14,"apple");
	insert(head,15,"carrot");
	insert(head,5,"potato");
	insert(head,107,"coffee");
	display(head);

	char *searchS=NULL;

	searchS=search(head,63);
	if(searchS!=NULL){
		delete(head,63);
		printf("After delete %s:\n",searchS);
		display(head);
	} else{
		printf("There is no val for 63");
	}

	searchS=search(head,15);
	if(searchS!=NULL){
		delete(head,15);
		printf("After delete %s:\n",searchS);
		display(head);
	} else{
		printf("There is no val for 15");
	}

	searchS=search(head,5);
	if(searchS!=NULL){
		delete(head,5);
		printf("After delete %s:\n",searchS);
		display(head);
	} else{
		printf("There is no val for 5");
	}

	searchS=search(head,107);
	if(searchS!=NULL){
		delete(head,107);
		printf("After delete %s:\n",searchS);
		display(head);
	} else{
		printf("There is no val for 107");
	}

	freeHash(head);
}
