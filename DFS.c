#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define DEBUG 1

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

# define InitialDFSData(dfsdata) \
do { \
	dfsdata.parents=NULL; \
	dfsdata.color=NULL; \
	dfsdata.discover=NULL; \
	dfsdata.finish=NULL; \
	dfsdata.Adj=NULL; \
} while(0)

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

struct DFSData{
	int *parents;
	int *color;
	int *discover;
	int *finish;
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

void DFSVisit(struct DFSData *dfsdata, int start, int *time){
	dfsdata->color[start]=1;
	dfsdata->discover[start]=++(*time);
	struct node *tempAdj=dfsdata->Adj[start];
	while(tempAdj){
		if(dfsdata->color[tempAdj->val]==0){
			dfsdata->parents[tempAdj->val]=start;
			DFSVisit(dfsdata,tempAdj->val,time);
		}
		tempAdj=tempAdj->next;
	}
	dfsdata->color[start]=2;
	dfsdata->finish[start]=++(*time);
}

void DFSAlgorithmn (struct DFSData *dfsdata,int arraySize){
	int time=0, *timePtr=&time;
	for(int i=0;i<arraySize;i++){
		if(dfsdata->color[i]==0){
			DFSVisit(dfsdata,i,timePtr);
		}
	}
}

void backOrigin(int *array,int arraySize, int minNode){
	for(int i=0;i<arraySize;i++){
		if(array[i]==minNode-1)
			continue;
		array[i]=minNode+array[i];
	}
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

void DFS(struct graph *Graph, struct DFSData *dfsdata){

	alignment(Graph->graphArray,Graph->graphArrayCurSize,Graph->minV);

	int arraySize=Graph->maxV-Graph->minV+1, initVal=Graph->minV-1;
	CrateGraph(&dfsdata->Adj,Graph->graphArray,Graph->graphArrayCurSize,arraySize);

	Initial(dfsdata->parents,arraySize,initVal);
	Initial(dfsdata->color,arraySize,0);
	Initial(dfsdata->discover,arraySize,0);
	Initial(dfsdata->finish,arraySize,0);

	DFSAlgorithmn(dfsdata,arraySize);

	backOrigin(dfsdata->parents,arraySize,Graph->minV);
}

void printDFS(struct graph *Graph, struct DFSData *dfsdata){
	printf("The DFS path for the graph\n");

	int arraySize=Graph->maxV-Graph->minV+1;

	for(int i=0;i<arraySize;i++){
		if(dfsdata->parents[i]==Graph->minV-1)
			printf("Node: %d StartTime: %d EndTime: %d No Parent\n",i+Graph->minV,dfsdata->discover[i],dfsdata->finish[i]);
		else
			printf("Node: %d StartTime: %d EndTime: %d Parent: %d\n",i+Graph->minV,dfsdata->discover[i],dfsdata->finish[i],dfsdata->parents[i]);
	}
}
void FreeDFS(struct graph *Graph, struct DFSData *dfsdata){
	for(int i=0;i<Graph->graphArrayCurSize;i++)
		free(Graph->graphArray[i]);
	free(Graph->graphArray);

	free(dfsdata->parents);
	free(dfsdata->color);
	free(dfsdata->discover);
	free(dfsdata->finish);

	int arraySize=Graph->maxV-Graph->minV+1;

	for(int i=0;i<arraySize;i++){
		struct node *tempAdj=dfsdata->Adj[i];
		while(tempAdj){
			struct node *freeTemp=tempAdj;
			tempAdj=tempAdj->next;
			free(freeTemp);
		}
	}
	free(dfsdata->Adj);
}

int main(){
	struct graph Graph;
	InitialGraph(Graph);

	struct DFSData dfsdata;
	InitialDFSData(dfsdata);

	//-1->1->3->5
	//       3->4
	//0->2
	//6->7
	Insert(&Graph,-1,1);
	Insert(&Graph,0,2);
	Insert(&Graph,1,3);
	Insert(&Graph,2,1);Insert(&Graph,2,5);
	Insert(&Graph,3,4);Insert(&Graph,3,5);
	Insert(&Graph,5,1);
	Insert(&Graph,6,4);Insert(&Graph,6,7);
	Insert(&Graph,7,6);

	DFS(&Graph,&dfsdata);

	#if (DEBUG == 1)
	printDFS(&Graph,&dfsdata);
	#endif

	FreeDFS(&Graph,&dfsdata);
}