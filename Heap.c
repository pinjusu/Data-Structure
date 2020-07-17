#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/************************************************************************************************************************************************************************************************************************************/
typedef struct {
    int *HeapArray; 
    int HeapCapacity;
    int HeapSize;
    bool MinHeapOrNot;
} Heap;

void checkSize(int **array,int size,int *capacity){
    if(size==*capacity){
        *array=(int *)realloc(*array,(size) * 2 *sizeof(int));
        *capacity=*capacity * 2;
    }
}

int compare(int *a,int *b,bool MinOrMax){
    if((MinOrMax && *a>*b) || (!MinOrMax && *a<*b)){
        int temp=*a;
        *a=*b;
        *b=temp;
        return 1;
    }
    return 0;
}

void DecreaseKey(int *array,int size,bool MinOrMax){
    int children=size, parent=children/2;
    while( parent>=1 && compare( array+(parent-1), array+(children-1), MinOrMax ) ){
        children=parent;
        parent=children/2;
    }
}

void addNumIntoHeap(int *array,int *size,bool MinOrMax,int data){
    array[*size] = data;
    (*size)++;
    DecreaseKey(array,*size,MinOrMax);
}

void Heapify(int *array,int size,bool MinOrMax){
    int parent=1, children=2*parent;
    while(children<=size){
        if(children+1 <= size){
            if ( (MinOrMax && array[children-1] > array[children]) ||(!MinOrMax && array[children-1] < array[children]) )
                children=children+1;
        }
        if(!compare( array+(parent-1), array+(children-1), MinOrMax ))
            break;
        parent=children;
        children=2*parent;
    }
}

int removeNumFromHeap(int *array,int *size,bool MinOrMax){
    int MaxorMinNum = array[0];
    array[0]=array[*size-1];
    *size=*size - 1;
    Heapify(array,*size,MinOrMax);
    return MaxorMinNum;
}
/************************************************************************************************************************************************************************************************************************************/

/** Initialize your data structure here. */
/** MinHeapOrNot is set to one, and create the min heap*/ 
Heap* HeapCreate(bool MinHeapOrNot) {
    Heap *mf=(Heap *)malloc(sizeof(Heap));
    mf->HeapArray=(int *)malloc(sizeof(int));
    mf->HeapSize=0;
    mf->HeapCapacity=1;
    mf->MinHeapOrNot=MinHeapOrNot;
    return mf;
}

/** Inserts a num into the data structure. */
void HeapAddNum(Heap* mf, int num){

    checkSize(&mf->HeapArray,mf->HeapSize,&mf->HeapCapacity);
    addNumIntoHeap(mf->HeapArray,&mf->HeapSize,mf->MinHeapOrNot,num);
}

/** Get and Remove the max or min num from heap.*/
int HeapGetMaxOrMin(Heap* mf){
    return removeNumFromHeap(mf->HeapArray,&mf->HeapSize,mf->MinHeapOrNot);
}

/** Output the element in the heap*/
void PrintHeap(Heap* mf){
    for (int i = 0; i < mf->HeapSize;i++)
        printf("%d's element:%d\n", i + 1, mf->HeapArray[i]);
    printf("Total Size: %d\n", mf->HeapSize);
}

/** Deallocates memory previously allocated for the data structure. */
void HeapFree(Heap* mf) {
    if (mf == NULL) return;
    if (mf->HeapArray) free(mf->HeapArray);
    free(mf);
}

/**
 * Your Heap struct will be instantiated and called as such:
 * Heap* MinHeap = HeapCreate(1); -> Min Heap
 * Heap* MaxHeap = HeapCreate(0); -> Max Heap
 
 * Heap* obj = HeapCreate(1);
 
 * HeapAddNum(obj, num);
 
 * double param_2 = HeapFindMedian(obj);
 
 * HeapFree(obj);
*/

int main(){
    Heap* obj = HeapCreate(1);
    HeapAddNum(obj, 1);
    HeapAddNum(obj, 2);
    HeapAddNum(obj, 3);
    HeapAddNum(obj, 0);

    PrintHeap(obj);
    int min=HeapGetMaxOrMin(obj);
    printf("%d\n",min);
    PrintHeap(obj);
}