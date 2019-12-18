
# include <iostream>
# include <stdlib.h>
using namespace std;

struct EdgeType                                     //关于图中边的信息的结构体

{

	int from, to;

	int Weight;

};

struct EdgeGraph                                    //关于整个图中顶点、边的所有信息，需要将前面边的结构体内容导入此结构体

{

	int Vertex[100];                            //顶点数组，假设最大顶点数和边数不超过100

	EdgeType Edge[100];                         //边信息的结构体数组

	int VertexNum, EdgeNum;                     //顶点数、边数

};

void Create(struct EdgeGraph *MyEdgeGraph);         //构造图的函数函数

void WayToAchieve(struct EdgeGraph *MyEdgeGraph);   //算法实现函数

int FindRoot(int Parent[],int v);                   //寻找各连通分量根的函数

int main()

{

	EdgeGraph MyEdgeGraph;

	Create(&MyEdgeGraph);

	WayToAchieve(&MyEdgeGraph);

	system("pause");

	return 0;

}

void Create(struct EdgeGraph *MyEdgeGraph)

{

	int Vertex, Edge;

	cout << "请输入无向图的顶点数：" << endl;

	cin >> Vertex;

	cout << "请输入无向图的边数：" << endl;

	cin >> Edge;

	cout << "请依次输入每个边所依附的两个顶点和边的权值：" << endl;

	EdgeType *MyEdge = new EdgeType[Edge];             //申请用户要求数量的边信息结构体数组

	for (int i = 0; i < Edge; i++) {                   //边结构体数组的初始化

		cin >> MyEdge[i].from >> MyEdge[i].to >> MyEdge[i].Weight;

	}

	for (int i = 0; i < Edge; i++) {                   //依据各边的权值进行重新排序

		for (int j = i + 1; j < Edge; j++) {

			if (MyEdge[i].Weight > MyEdge[j].Weight) {

				EdgeType Temp;

				Temp = MyEdge[i];

				MyEdge[i] = MyEdge[j];

				MyEdge[j] = Temp;

			}

		}

	}

	(*MyEdgeGraph).VertexNum = Vertex;

	(*MyEdgeGraph).EdgeNum = Edge;

	for (int i = 0; i < Edge; i++) {

		(*MyEdgeGraph).Edge[i] = MyEdge[i];                //将边的信息结构体导入图的信息结构体

	}

	for (int i = 0; i < Vertex; i++) {

		(*MyEdgeGraph).Vertex[i] = i;                     //初始化图结构体的顶点数组

	}
	delete MyEdge;

}

void WayToAchieve(struct EdgeGraph *MyEdgeGraph)

{

	int num = 0, i = 0,v1,v2;

	int *root = new int[(*MyEdgeGraph).VertexNum];        //创建辅助函数并初始化

	for (int i = 0; i < (*MyEdgeGraph).VertexNum; i++) {

		root[i] = -1;

	}

	for (num = 0, i = 0; i < (*MyEdgeGraph).EdgeNum; i++) {      //依次对每个边进行遍历，num记录输出边的个数

		v1 = FindRoot(root,(*MyEdgeGraph).Edge[i].from);    //分别寻找v1,v2所在连通分量的根

		v2 = FindRoot(root, (*MyEdgeGraph).Edge[i].to);

		if (v1 != v2) {                                     //如果所在不同的连通分量就合并

			cout << "("<<(*MyEdgeGraph).Edge[i].from<<","<<(*MyEdgeGraph).Edge[i].to<<")" << endl;

			root[v2] = v1;                                 //合并

			num++;                                         //记录选择边的个数

			if (num == (*MyEdgeGraph).VertexNum - 1) {     //如果选择的边次数等于顶点数-1则证明最小树已经生成，结束函数调用

                delete root;
				return;

			}

		}
	}

}

int FindRoot(int Parent[], int v)

{

	int v1 = v;

	while (Parent[v1] > -1) {         //沿着连通分量路径不停循环找根

		v1 = Parent[v1];

	}

	return v1;

}
