#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>
#define MAX_VERTEX_NUM 100
#define max 65536

typedef struct 
{
	int distance;
	int cost;
}EDG;

typedef struct 
{
	int n;
	int e;
	int vexs[MAX_VERTEX_NUM];
	EDG edges[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
}MGraph;

void shortpat_FLOYED(MGraph *mg);
MGraph *creat_MGraph();//建立邻接矩阵

void main()
{
	int m,n;
	MGraph *mg;
	mg=creat_MGraph();//建立邻接矩阵
	printf("请输入要求的两个顶点的序号：");
	scanf("%d%d",&m,&n);
	shortpat_FLOYED(mg);
	printf("顶点%d与顶点%d的最短路径的距离：%d花费为：%d\n",m,n,mg->edges[m][n].distance,mg->edges[m][n].cost);
	printf("程序结束\n");
}

void shortpat_FLOYED(MGraph *mg)
{
	int i,j,k;
	for(k=1;k<=mg->n;k++)
		for(i=1;i<=mg->n;i++)
			for(j=1;j<=mg->n;j++)
			{
				if(mg->edges[i][k].distance+mg->edges[k][j].distance<mg->edges[i][j].distance)
				{
					mg->edges[i][j].distance=mg->edges[i][k].distance+mg->edges[k][j].distance;
					mg->edges[i][j].cost=mg->edges[i][k].cost+mg->edges[k][j].cost;
				}
				else if(mg->edges[i][k].distance+mg->edges[k][j].distance==mg->edges[i][j].distance)
				{
					if(mg->edges[i][k].cost+mg->edges[k][j].cost<mg->edges[i][j].cost)
						
						mg->edges[i][j].cost=mg->edges[i][k].cost+mg->edges[k][j].cost;
					
				}
				else 
					;//空语句
			}
}

MGraph *creat_MGraph()//建立邻接矩阵
{
	int i,j,k,n,e,d,c;
	MGraph *mg=malloc(sizeof(MGraph));
	printf("请输入顶点的个数：");
	scanf("%d",&n);
	printf("请输入边的条数：");
	scanf("%d",&e);
	mg->n=n;
	mg->e=e;
	getchar();
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++)
		{
			mg->edges[i][j].distance=max;//初始化邻接矩阵表示的所有边
			mg->edges[i][j].cost=max;
		}
		printf("请输入边的信息:\n");
		for(i=1;i<=e;i++)
		{
			scanf("%d%d%d%d",&j,&k,&d,&c);
			mg->edges[j][k].distance=d;
			mg->edges[j][k].cost=c;
			mg->edges[k][j].distance=d;
			mg->edges[k][j].cost=c;//标记存在的边
		}
		return mg;//返回邻接矩阵的首地址
}
