#include <iostream>
#include <iomanip>
#include <string>
using namespace std;
class MGraph
{
	public: 
		string vexs[10];//顶点信息
		int adm[10][10];//邻接矩阵
		int vertexnum, arcnum;//顶点数和边数
		int p[10][10];//最短路径数组p
		int D[10];//最短距离数组D
		int LocateVex(string u)//返回顶点u在图中的位置
	{
		for(int i=0; i<vertexnum; i++)
			if(vexs[i]==u)
				return i;
				return -1;
	}
void CreateDN()//构造有向网
		{
		string v1, v2; 
		int w;
		
		int i, j, k;
		cout<<"请输入顶点数和边数：";
		cin>>vertexnum>>arcnum;
 
		cout<<"请输入顶点：";
		for(i=0; i<vertexnum; i++)
		cin>>vexs[i];
 
		for(i=0; i<10; i++)
			for(j=0; j<10; j++)
				adm[i][j]=65535;
 
		cout<<"请输入边和权值："<<endl;
		for(k=0; k<arcnum; k++)
		{
			cin>>v1>>v2>>w;
			i=LocateVex(v1);
			j=LocateVex(v2);
			adm[i][j]=w;
		}
}
void ShortestPath_DIJ()
{
		int v=0, w, i, j, min;
		bool final[10];
	  
		while(v<vertexnum) 
		{
			final[v]=false;//设初值
			D[v]=adm[0][v];//D[]存放v0到v得最短距离，初值为v0到v的直接距离
			for(w=0; w<vertexnum; w++)
				p[v][w]=-1;//设p[][]初值为-1，即没有路径
			if
			
			
			
			(D[v]<65535)//v0到v有直接路径
			{
				p[v][0]=0;//v0到v最短路径经过的第一个顶点
				p[v][1]=v;//v0到v最短路径经过的第二个顶点
			}
			v++;
		}
	
		D[0]=0;//v0到v0距离为0
		final[0]=true;//v0顶点并入S集
	
	for(i=1; i<vertexnum; i++)//其余G.vexnum-1个顶点
	{//开始主循环，每次求得v0到某个顶点v的最短路径，并将v并入S集，然后更新p和D
		min=65535;
		for(w=0; w<vertexnum; w++)//对所有顶点检查
			if(!final[w] && D[w]<min)//在S集之外(即final[]=false)的顶点中找离v0最近的顶点，将其赋给v,距离赋给min
			{
				v=w;
				min=D[w];
			}
			final[v]=true;//v并入S集
			for(w=0; w<vertexnum; w++)//根据新并入的顶点，更新不在S集的顶点到v0的距离和路径数组
			{
				if(!final[w] && min<65535 && adm[v][w]<65535 && (min+adm[v][w]<D[w]))
				{//w 不属于S集且v0->v->w的距离<目前v0->w的距离
					D[w]=min+adm[v][w];//更新D[w]
					for
					(j=0; j<vertexnum; j++)//修改p[w]，v0到w经过的顶点包括v0到v经过的所有顶点再加上顶点w
					{
						p[w][j]=p[v][j];
						if(p[w][j]==-1)//在p[w][]第一个等于-1的地方加上顶点w
						{
							p[w][j]=w;
							break;
						}
					}					
					
				}
			}
	}	
}
void out()
{
	int i, j;
	cout<<"最短路径数组p[i][j]如下："<<endl;
	for(i=0; i<vertexnum; i++)
	{
		for(j=0; j<vertexnum; j++)
			cout<<setw(3)<<p[i][j]<<" ";
		cout<<endl;
	}
 
	cout<<vexs[0]<<"到各顶点的最短路径及长度为："<<endl;
	for(i=0; i<vertexnum; i++)
	{
		if(i!=0 && D[i]!=65535)
		{
			cout<<vexs[0]<<"-"<<vexs[i]<<"的最短路径长度为:"<<D[i];
			cout<<"  最短路径为：";
			for(j=0; j<vertexnum; j++)
			{
				if(p[i][j]>-1)
					cout<<vexs[p[i][j]]<<" ";
			}
			cout<<endl;			
		}
		else if(D[i]==65535)
			cout<<vexs[0]<<"-"<<vexs[i]<<":"<<"不可达或目标城市不存在"<<endl;
	}
} 
void Add()
{
	vertexnum++;
	cout<<"请输入要增加的节点"<<endl;
	string v;
	int w,n,i; 
	cin>>v;
	vexs[vertexnum-1]=v;
	cout<<"请输入其指向的边数"<<endl;
	cin>>n;
	for(int k=0;k<n;k++)
	{ 
		cout<<"请输入与其相连的节点以及权值"<<endl;
		cin>>v>>w; 
		i=LocateVex(v);
	    adm[vertexnum-1][i]=w; 
	} 
	arcnum+=n;
	cout<<"请输入指向其的边数"<<endl;
	cin>>n;
	for(int k=0;k<n;k++)
	{ 
		cout<<"请输入与其相连的节点以及权值"<<endl;
		cin>>v>>w; 
		i=LocateVex(v);
	    adm[i][vertexnum-1]=w; 
	} 
	arcnum+=n;  

} 
void Delete()
{

	int num=0,i,j,c,y;
	cout<<"请输入要删除的节点"<<endl;
	string v;
	cin>>v;
	for(i=0;i<10;i++)
		if(vexs[i]==v) break;
	for(j=0;j<10;j++) 
	{
		if(adm[j][i]!=65535)
		{
		  	num++;
		  	adm[j][i]=65535;
		}	
		if(adm[i][j]!=65535)
		{
		  	num++;
		  	adm[i][j]=65535;
		}
	}
	arcnum=arcnum-num; 
	i=LocateVex(v);

	
} 
void Modify()
{
	int i,k,n; 
	string r,j;
	cout<<"请输入要修改的两个节点"<<endl;
	cin>>r>>j;
	cout<<"请输入要修改的权值"<<endl;
	cin>>n;
	i=LocateVex(r);
	k=LocateVex(j);
	adm[i][k]=n;
}
}; 
void run(MGraph &g)
{
	int i; 
	cout<<"****************迪杰斯特拉算法课设****************"<<endl;
	cout<<"****************1.构造城市网络*******************"<<endl;
	cout<<"****************2.删除某个城市*******************"<<endl;
	cout<<"****************3.增加某个城市*******************"<<endl;
	cout<<"*****************4.修改弧长值********************"<<endl;
	cout<<"***********5.输出到所有城市的最短路径************"<<endl;
	cout<<"*******************6.退出*******************"<<endl;
	while(cin>>i)
	{
		switch(i)
		{
			case(1):g.CreateDN();break;
			case(2):g.Delete();break;
			case(3):g.Add();break; 
			case(4):g.Modify();break; 
			case(5):g.ShortestPath_DIJ();g.out();break;
			case(6):exit(0); 
		} 
	}
	 
} 
int main()
{
	MGraph g;
	run(g); 
	return 0; 
}
 

