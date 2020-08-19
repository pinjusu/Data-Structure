#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

# define Initial(array,arraySize,initVal) \
do { \
	array=(int *)malloc(sizeof(int)*arraySize); \
	for(int i=0;i<arraySize;i++) \
		array[i]=initVal; \
} while(0)

# define InitialGraph(Graph) \
do { \
	Graph.minV=INT_MAX; \
	Graph.maxV=INT_MIN; \
	Graph.graphArrayCurSize=0; \
	Graph.graphArrayMaxSize=1; \
	Graph.graphArray=(int **)malloc(sizeof(int *)); \
} while(0)

# define InitialBFSData(bfsdata) \
do { \
	bfsdata.firstnode=0; \
	bfsdata.parents=NULL; \
	bfsdata.level=NULL; \
	bfsdata.Adj=NULL; \
} while(0)

#define DEBUG 1

struct graph{
	int minV;
	int maxV;
	int **graphArray;
	int graphArrayCurSize;
	int graphArrayMaxSize;
};

struct node{
	int val;
	struct node *next;
};

struct BFSData{
	int firstnode;
	int *parents;
	int *level;
	struct node **Adj;
};

void alignment(int **Array, int rowSize, int minNode){
	for(int i=0;i<rowSize;i++){
		for(int j=0;j<2;j++)
			Array[i][j]=Array[i][j]-minNode;
	}
}

void CrateGraph(struct node *** AdjPtr, int **graph, int rowSize, int Size){
	*AdjPtr=(struct node**)malloc(sizeof(struct node *)*(Size));
	memset(*AdjPtr,0,(Size)*sizeof(struct node*));

	for(int i=0;i<rowSize;i++){
		struct node *newnode=(struct node *)malloc(sizeof(struct node));
		newnode->val=graph[i][1];

		newnode->next=(*AdjPtr)[graph[i][0]];
		(*AdjPtr)[graph[i][0]]=newnode;

	}
}

void BFSAlgorithmn(struct node **Adj,int *parents,int *level,int arraySize,int firstnode){
	int *Queue=(int *)malloc(sizeof(int)*arraySize);
	Queue[0]=firstnode;
	level[firstnode]=0;

	int minn=0, maxn=1;
	while(minn!=maxn){
		int tempmaxNode=maxn;
		for(; minn<tempmaxNode;minn++){
			struct node *tempAdj=Adj[Queue[minn]];
			while(tempAdj){
				int nodeVal=tempAdj->val;
				tempAdj=tempAdj->next;

				if(level[nodeVal]==-1){
					level[nodeVal]=level[Queue[minn]]+1;
					parents[nodeVal]=Queue[minn];
					Queue[maxn++]=nodeVal;
				}
			}
		}
	}
	free(Queue);
}

void backOrigin(int *array,int arraySize, int minNode){
	for(int i=0;i<arraySize;i++)
		array[i]=minNode+array[i];
}

void Insert(struct graph *Graph,int x,int y){
	int xymin,xymax;
	if(x>y){
		xymax=x;
		xymin=y;
	}else{
		xymax=y;
		xymin=x;
	}

	Graph->minV=Graph->minV>xymin?xymin:Graph->minV;
	Graph->maxV=Graph->maxV<xymax?xymax:Graph->maxV;

	if(Graph->graphArrayMaxSize==Graph->graphArrayCurSize){
		Graph->graphArrayMaxSize=Graph->graphArrayMaxSize*2;
		Graph->graphArray=(int **)realloc(Graph->graphArray,Graph->graphArrayMaxSize*sizeof(int *));
	}
	int *newNode=(int *)malloc(sizeof(int)*2);
	newNode[0]=x; newNode[1]=y;
	Graph->graphArray[Graph->graphArrayCurSize++]=newNode;
}

void BFS(struct graph *Graph, struct BFSData *bfsdata, int firstnode){

	bfsdata->firstnode=firstnode;

	alignment(Graph->graphArray,Graph->graphArrayCurSize,Graph->minV);

	int arraySize=Graph->maxV-Graph->minV+1, initVal=Graph->minV-1;
	CrateGraph(&bfsdata->Adj,Graph->graphArray,Graph->graphArrayCurSize,arraySize);

	Initial(bfsdata->parents,arraySize,initVal);
	Initial(bfsdata->level,arraySize,-1);

	BFSAlgorithmn(bfsdata->Adj,bfsdata->parents,bfsdata->level,arraySize,bfsdata->firstnode-Graph->minV);

	backOrigin(bfsdata->parents,arraySize,Graph->minV);
}

void printBFS(struct graph *Graph, struct BFSData *bfsdata){
	printf("from %d to all the nodes in the graph\n",bfsdata->firstnode);

	int arraySize=Graph->maxV-Graph->minV+1;

	for(int i=0;i<arraySize;i++){
		if(bfsdata->level[i]==-1 || bfsdata->level[i]==0)
			continue;
		printf("node: %d path len: %d parent: %d\n",i+Graph->minV,bfsdata->level[i],bfsdata->parents[i]);
	}
}
void FreeBFS(struct graph *Graph, struct BFSData *bfsdata){
	for(int i=0;i<Graph->graphArrayCurSize;i++)
		free(Graph->graphArray[i]);
	free(Graph->graphArray);

	free(bfsdata->parents);
	free(bfsdata->level);

	int arraySize=Graph->maxV-Graph->minV+1;

	for(int i=0;i<arraySize;i++){
		struct node *tempAdj=bfsdata->Adj[i];
		while(tempAdj){
			struct node *freeTemp=tempAdj;
			tempAdj=tempAdj->next;
			free(freeTemp);
		}
	}
	free(bfsdata->Adj);
}

int main(){
	struct graph Graph;
	InitialGraph(Graph);

	struct BFSData bfsdata;
	InitialBFSData(bfsdata);

	Insert(&Graph,-1,1);Insert(&Graph,-1,2);Insert(&Graph,-1,3);
	Insert(&Graph,1,-1);Insert(&Graph,1,4);
	Insert(&Graph,2,-1);Insert(&Graph,2,4);Insert(&Graph,2,5);Insert(&Graph,2,6);Insert(&Graph,2,7);
	Insert(&Graph,3,-1);Insert(&Graph,3,7);
	Insert(&Graph,4,1);Insert(&Graph,4,2);Insert(&Graph,4,5);
	Insert(&Graph,5,2);Insert(&Graph,5,4);Insert(&Graph,5,-2);
	Insert(&Graph,6,2);Insert(&Graph,6,7);Insert(&Graph,6,-2);
	Insert(&Graph,7,2);Insert(&Graph,7,3);Insert(&Graph,7,6);
	Insert(&Graph,-2,5);Insert(&Graph,-2,6);

	BFS(&Graph,&bfsdata,-1);

	#if (DEBUG == 1)
	printBFS(&Graph,&bfsdata);
	#endif

	FreeBFS(&Graph,&bfsdata);
}