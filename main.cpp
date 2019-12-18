#include<stdio.h>
#include<stdlib.h>
#define MAX 10
#define INIFINITY 65535
#define TRUE 1
#define FALSE 0
typedef int Boole;  //�������� �洢TRUE FALSE
Boole visited[MAX];    //���ʱ�־����

//�ڽӱ��㶨��
typedef int VertexType;  //������������
typedef int EdgeType;    //���ϵ�Ȩֵ����

typedef struct EdgeNode  //�߱���   �洢�߱���Ϣ
{
	int adjvex;		    //�ڽӵ��򣬴洢�ö����Ӧ���±�
	EdgeType weight;	//Ȩֵ
	struct EdgeNode *next;	//����ָ����һ���ڽӵ�
}EdgeNode;

typedef struct VertexNode   //�������
{
	VertexType data;      //�����򣬴洢������Ϣ
	EdgeNode *firstedge;	//�߱�ͷָ�룬ָ��˶���ĵ�һ���ڽӵ�
}VertexNode,AdjList[MAX];


typedef struct
{
	AdjList adjList;
	int numVertexes,numEdges;   //ͼ�е�ǰ�������ͱ���
}GraphAdjList,*GraphAdj;


typedef struct LoopQueue{ //����ѭ�����нṹ��
	int data[MAX];
	int front;
	int rear;   //ע��ÿ�ζ�β���ָ�����һ��Ԫ�ص���һ��λ��
}Queue, *LQueue;

void InitQueue(LQueue &Q){  //��ʼ������
	Q->front = Q->rear = 0;
}

bool QueueisFull(LQueue &Q){ //�ж϶����Ƿ�����
	if((Q->rear + 1) % MAX == Q->front){
		return true;  //����
	}
	else{
		return false;
	}
}

bool QueueisEmpty(LQueue &Q){//�ж϶����Ƿ�Ϊ��
	if(Q->front == Q->rear){
		return true;
	}
	return false;
}


void EnQueue(LQueue &Q, int i){ //�����
	if(!QueueisFull(Q)){
		Q->data[Q->rear] = i;
		Q->rear = (Q->rear + 1) % MAX;  //��βָ�����
	}
}

void DeQueue(LQueue &Q, int *k){ //������
	if(!QueueisEmpty(Q)){
		*k = Q->data[Q->front];
		Q->front = (Q->front + 1) % MAX;
	}
}


/*�ڽӱ���*/
void create(GraphAdj G)
{
	int i,j,k,t;
	EdgeNode *e;
	printf("���붥�����ͱ���:");
	scanf("%d%d",&G->numVertexes,&G->numEdges);
	//getchar();  						//ע��Ҫ�������
	for(i=0;i<G->numVertexes;i++)          //���������
	{
		G->adjList[i].data=i;           //���붥�����Ŵ�0����
		G->adjList[i].firstedge=NULL; 		//���߱��ÿ�
	}
	for(k=0;k<G->numEdges;k++)             //�����߱�
	{
		printf("�����(Vi,Vj)�ϵĶ������:");
		scanf("%d%d%d",&i,&j,&t);
		/*ʹ��ͷ�巨����߱���*/
		e=(EdgeNode *)malloc(sizeof(EdgeNode));   //���ɽ��

		e->adjvex=j;
		e->next=G->adjList[i].firstedge;
		e->weight=t;
		G->adjList[i].firstedge=e;

		e=(EdgeNode *)malloc(sizeof(EdgeNode));   //���ɽ��

		e->adjvex=i;
		e->next=G->adjList[j].firstedge;
		e->weight=t;
		G->adjList[j].firstedge=e;
	}
	printf("\n");
}


/*�ڽӱ��������ȵݹ�*/
void DFS(GraphAdj G,int i)
{
	EdgeNode *p;
	visited[i]=TRUE;         		//���ʹ��˸ö��㣬���ΪTRUE
	printf("\t%c",G->adjList[i].data);
	p=G->adjList[i].firstedge;     //��pָ��߱��һ�����
	while(p)                      //�ڱ߱��ڱ���
	{
		if(!visited[p->adjvex])    //��δ���ʵ��ڽӶ���ݹ����
			DFS(G,p->adjvex);
		p=p->next;
	}
 }

 //�ڽӱ����ȱ�������

void DFSTraverse(GraphAdj G)
{
	int i;
	for(i=0;i<G->numVertexes;i++)
		visited[i]=FALSE;       //��ʼ����Ϊδ����
	for(i=0;i<G->numVertexes;i++)
		if(!visited[i])       //��δ���ʵĶ������DFS��������ͨͼֻ��ִ��һ��
			DFS(G,i);
}

/*������ȱ���*/
void BFS(GraphAdj G){

	Queue *Q =(LQueue)malloc(sizeof(Queue));
	for(int i = 0; i < G->numVertexes; i++){
		visited[i] = FALSE;
	}
	InitQueue(Q);  //��ʼ������
	for(int i = 0; i < G->numVertexes; i++){
		visited[i] = TRUE;
		printf("\t%c", G->adjList[i].data);
		EnQueue(Q, i);

		while(!QueueisEmpty(Q)){
			DeQueue(Q, &i);  //���ﲻ�ϵ��޸�i��ֵ����
			EdgeNode *e = G->adjList[i].firstedge;  //i������ڽ�����ĵ�һ�����
			while(e){//e����ʱ����e�������ڽӵ�������,Ҳ���Ǳ���i�������ڽӵ�
				if(!visited[e->adjvex]){ // adjvex��e����ʾ�Ľ���±�
					visited[e->adjvex] = TRUE;
					printf("\t%c", G->adjList[e->adjvex].data);
					EnQueue(Q, e->adjvex); //���ý�����
				}
				e = e->next; //����i����һ���ڽӵ�
			}
		}
	}
}

int main()
{
	GraphAdjList G;
	create(&G);
	printf("������ȱ���Ϊ��");
	DFSTraverse(&G);
	printf("\n");
	printf("������ȱ���Ϊ��");
	BFS(&G);
	printf("\nͼ�������");
	return 0;
 }
