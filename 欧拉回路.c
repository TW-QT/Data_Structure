#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#define MAX_VERTEX_NUM 100//顶点的最大个数

typedef struct 
{
	int num;//顶点序号
	//int data;//顶点信息
}VERTEX;//顶点

typedef struct
{
	int n;//顶点个数
	int e;//边的条数
	VERTEX vexs[MAX_VERTEX_NUM];//一维数组储存顶点
	int edges[MAX_VERTEX_NUM][MAX_VERTEX_NUM];//二维数组储存边
}MGraph;//图

int visited[MAX_VERTEX_NUM];//全局变量。在对顶点进行深度优先搜索遍历时的辅助变量数组
int Euleriancycle(MGraph *mg);//判断顶点的度数是否全为偶数，有奇数时输出0，全为偶数时输出1
MGraph *creat_MGraph();//将图转化为邻接矩阵储存起来，返回邻接矩阵的首地址
int  dfs_trave(MGraph *mg);//深度优先搜索遍历
void dfs(MGraph *mg,int i);//深度优先搜索


void main()
{
	int num,m;//num用来接收顶点度数判断的结果，m用来接收图是否为连通图的结果
	MGraph *mg;
	mg=creat_MGraph();//建立邻接矩阵
	//--------------------------------------------------------------------------------------------------------------------------------------
	printf("边的条数%d\n\n\n",mg->e);
	printf("边1 2  为 %d\n\n\n",mg->edges[1][2]);
	printf("边1 3  为 %d\n\n\n",mg->edges[1][3]);
	printf("边2 2  为 %d\n\n\n",mg->edges[2][2]);
	printf("边2 3  为 %d\n\n\n",mg->edges[2][3]);                     //调试、验证
	printf("顶点的个数为 %d\n\n\n",mg->n);
	/*printf("定点1为%d\n\n\n",mg->vexs[1].data);
	printf("定点2为%d\n\n\n",mg->vexs[2].data);
	printf("定点3为%d\n\n\n",mg->vexs[3].data);
	printf("定点4为%d\n\n\n",mg->vexs[4].data);
	printf("定点5为%d\n\n\n",mg->vexs[5].data);//%c时会输出特殊符号*/
	//--------------------------------------------------------------------------------------------------------------------------------------

	num=Euleriancycle(mg);//判断顶点的度数是否全为偶数。全为偶数时num=1；否则num=0
	/*m=dfs_trave(mg);//判断图是否为连通图
	if((num==1)&&(m==1))//如果图是连通图并且所有顶点的度数全为偶数时，改图为欧拉图，存在欧拉回路
		printf("存在欧拉回路！\n");
	else                //否则不是欧拉图，没有欧拉回路
		printf("不存在欧拉回路！\n");
	printf("调用了%d次dfs\n\n",m);//调试...*/
	if(num!=1)
	{
	printf("不存在欧拉图！\n");
	getchar();
	exit(0);
	}
	m=dfs_trave(mg);//判断图是否为连通图
	if(m!=1)
		printf("不存在欧拉图！\n");
	else
		printf("存在欧拉图！\n");
	getch();
}

MGraph *creat_MGraph()//建立邻接矩阵
{
	int i,j,k,n,e;
	//int c;
	MGraph *mg=malloc(sizeof(MGraph));
	printf("请输入顶点的个数：");
	scanf("%d",&n);
	printf("请输入边的条数：");
	scanf("%d",&e);
	mg->n=n;
	mg->e=e;
	getchar();
	/*printf("请输入顶点信息：");
	for(i=1;i<=n;i++)
	{
		scanf("%d",&c);//读入第i个顶点的信息
		mg->vexs[i].data=c;//指定顶点的序号
		mg->vexs[i].num=i;//
	}*/
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++)
			mg->edges[i][j]=0;//初始化邻接矩阵表示的所有边
		printf("请输入边的信息:");
		for(i=1;i<=e;i++)
		{
			scanf("%d%d",&j,&k);
			mg->edges[j][k]=1;mg->edges[k][j]=1;//标记存在的边
		}
		return mg;//返回邻接矩阵的首地址
}

int Euleriancycle(MGraph *mg)//判断是否存在欧拉回路
{
	int i,j,num;
	for(i=1;i<=mg->n;i++)//从第一个顶点开始，判断顶点的度数
	{
		num=0;//初始化每个顶点的度数为0
		for(j=1;j<=mg->n;j++)
		{
			if(mg->edges[i][j]!=0)//如果顶点i到j的边存在度数加1
				num=num+1;
		}
		if(num%2==1)//如果有哪个顶点的度数为奇数，直接退出循环，返回0
			return 0;	
	}
	//if(num%2==1)
	//	return 0;
	//else 
		return 1;//当所有的顶点都判断完成还没有退出本函数说明所有顶点度数均为偶数，返回1
}

int  dfs_trave(MGraph *mg)//深度优先搜索遍历
{
	int i,m=0;
	for(i=1;i<=mg->n;i++)//将辅助变量全部初始化为0，表明顶点没有被访问过
		visited[i]=0;
	for(i=1;i<=mg->n;i++)
		if(visited[i]==0)//对没有访问过的顶点，调用深度优先搜索函数
		{
			dfs(mg,i);//深度优先搜索
			m=m+1;//如果是非连通图，要调用1次以上，m用来记录调用dfs函数的次数
		}
		
		return m;//返回调用dfs函数的次数
}

void dfs(MGraph *mg,int i)//深度优先搜索
{
	int j;
	visited[i]=1;//访问该顶点
	for(j=1;j<=mg->n;j++)
		if((visited[j]==0)&&(mg->edges[i][j]==1))//当顶点没有被访问过并且两顶点存在边
			dfs(mg,j);//对该顶点深度优先搜索
}
