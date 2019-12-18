#include<stdio.h>
#include<stdlib.h>
#define MAX 10
#define INIFINITY 65535
#define TRUE 1
#define FALSE 0
typedef int Boole;  //布尔类型 存储TRUE FALSE
Boole visited[MAX];    //访问标志数组

//邻接表结点定义
typedef int VertexType;  //顶点数据类型
typedef int EdgeType;    //边上的权值类型

typedef struct EdgeNode  //边表结点   存储边表信息
{
	int adjvex;		    //邻接点域，存储该顶点对应的下标
	EdgeType weight;	//权值
	struct EdgeNode *next;	//链域，指向下一个邻接点
}EdgeNode;

typedef struct VertexNode   //顶点表结点
{
	VertexType data;      //顶点域，存储顶点信息
	EdgeNode *firstedge;	//边表头指针，指向此顶点的第一个邻接点
}VertexNode,AdjList[MAX];


typedef struct
{
	AdjList adjList;
	int numVertexes,numEdges;   //图中当前顶点数和边数
}GraphAdjList,*GraphAdj;


typedef struct LoopQueue{ //定义循环队列结构体
	int data[MAX];
	int front;
	int rear;   //注意每次队尾标记指向最后一个元素的下一个位置
}Queue, *LQueue;

void InitQueue(LQueue &Q){  //初始化队列
	Q->front = Q->rear = 0;
}

bool QueueisFull(LQueue &Q){ //判断队列是否满了
	if((Q->rear + 1) % MAX == Q->front){
		return true;  //已满
	}
	else{
		return false;
	}
}

bool QueueisEmpty(LQueue &Q){//判断队列是否为空
	if(Q->front == Q->rear){
		return true;
	}
	return false;
}


void EnQueue(LQueue &Q, int i){ //入队列
	if(!QueueisFull(Q)){
		Q->data[Q->rear] = i;
		Q->rear = (Q->rear + 1) % MAX;  //队尾指针后移
	}
}

void DeQueue(LQueue &Q, int *k){ //出队列
	if(!QueueisEmpty(Q)){
		*k = Q->data[Q->front];
		Q->front = (Q->front + 1) % MAX;
	}
}


/*邻接表创建*/
void create(GraphAdj G)
{
	int i,j,k,t;
	EdgeNode *e;
	printf("输入顶点数和边数:");
	scanf("%d%d",&G->numVertexes,&G->numEdges);
	//getchar();  						//注意要清除缓冲
	for(i=0;i<G->numVertexes;i++)          //建立顶点表
	{
		G->adjList[i].data=i;           //输入顶点表，序号从0依次
		G->adjList[i].firstedge=NULL; 		//将边表置空
	}
	for(k=0;k<G->numEdges;k++)             //建立边表
	{
		printf("输入边(Vi,Vj)上的顶点序号:");
		scanf("%d%d%d",&i,&j,&t);
		/*使用头插法加入边表结点*/
		e=(EdgeNode *)malloc(sizeof(EdgeNode));   //生成结点

		e->adjvex=j;
		e->next=G->adjList[i].firstedge;
		e->weight=t;
		G->adjList[i].firstedge=e;

		e=(EdgeNode *)malloc(sizeof(EdgeNode));   //生成结点

		e->adjvex=i;
		e->next=G->adjList[j].firstedge;
		e->weight=t;
		G->adjList[j].firstedge=e;
	}
	printf("\n");
}


/*邻接表的深度优先递归*/
void DFS(GraphAdj G,int i)
{
	EdgeNode *p;
	visited[i]=TRUE;         		//访问过了该顶点，标记为TRUE
	printf("\t%c",G->adjList[i].data);
	p=G->adjList[i].firstedge;     //让p指向边表第一个结点
	while(p)                      //在边表内遍历
	{
		if(!visited[p->adjvex])    //对未访问的邻接顶点递归调用
			DFS(G,p->adjvex);
		p=p->next;
	}
 }

 //邻接表的深度遍历操作

void DFSTraverse(GraphAdj G)
{
	int i;
	for(i=0;i<G->numVertexes;i++)
		visited[i]=FALSE;       //初始设置为未访问
	for(i=0;i<G->numVertexes;i++)
		if(!visited[i])       //对未访问的顶点调用DFS，若是连通图只会执行一次
			DFS(G,i);
}

/*广度优先遍历*/
void BFS(GraphAdj G){

	Queue *Q =(LQueue)malloc(sizeof(Queue));
	for(int i = 0; i < G->numVertexes; i++){
		visited[i] = FALSE;
	}
	InitQueue(Q);  //初始化队列
	for(int i = 0; i < G->numVertexes; i++){
		visited[i] = TRUE;
		printf("\t%c", G->adjList[i].data);
		EnQueue(Q, i);

		while(!QueueisEmpty(Q)){
			DeQueue(Q, &i);  //这里不断的修改i的值！！
			EdgeNode *e = G->adjList[i].firstedge;  //i顶点的邻接链表的第一个结点
			while(e){//e存在时，将e的所有邻接点加入队列,也就是遍历i的所有邻接点
				if(!visited[e->adjvex]){ // adjvex是e所表示的结点下标
					visited[e->adjvex] = TRUE;
					printf("\t%c", G->adjList[e->adjvex].data);
					EnQueue(Q, e->adjvex); //将该结点入队
				}
				e = e->next; //遍历i的下一个邻接点
			}
		}
	}
}

int main()
{
	GraphAdjList G;
	create(&G);
	printf("深度优先遍历为：");
	DFSTraverse(&G);
	printf("\n");
	printf("广度优先遍历为：");
	BFS(&G);
	printf("\n图遍历完毕");
	return 0;
 }
