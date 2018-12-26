#include <iostream>
#include <iomanip>
#include <string>
using namespace std;
class MGraph
{
	public: 
		string vexs[10];//������Ϣ
		int adm[10][10];//�ڽӾ���
		int vertexnum, arcnum;//�������ͱ���
		int p[10][10];//���·������p
		int D[10];//��̾�������D
		int LocateVex(string u)//���ض���u��ͼ�е�λ��
	{
		for(int i=0; i<vertexnum; i++)
			if(vexs[i]==u)
				return i;
				return -1;
	}
void CreateDN()//����������
		{
		string v1, v2; 
		int w;
		
		int i, j, k;
		cout<<"�����붥�����ͱ�����";
		cin>>vertexnum>>arcnum;
 
		cout<<"�����붥�㣺";
		for(i=0; i<vertexnum; i++)
		cin>>vexs[i];
 
		for(i=0; i<10; i++)
			for(j=0; j<10; j++)
				adm[i][j]=65535;
 
		cout<<"������ߺ�Ȩֵ��"<<endl;
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
			final[v]=false;//���ֵ
			D[v]=adm[0][v];//D[]���v0��v����̾��룬��ֵΪv0��v��ֱ�Ӿ���
			for(w=0; w<vertexnum; w++)
				p[v][w]=-1;//��p[][]��ֵΪ-1����û��·��
			if
			
			
			
			(D[v]<65535)//v0��v��ֱ��·��
			{
				p[v][0]=0;//v0��v���·�������ĵ�һ������
				p[v][1]=v;//v0��v���·�������ĵڶ�������
			}
			v++;
		}
	
		D[0]=0;//v0��v0����Ϊ0
		final[0]=true;//v0���㲢��S��
	
	for(i=1; i<vertexnum; i++)//����G.vexnum-1������
	{//��ʼ��ѭ����ÿ�����v0��ĳ������v�����·��������v����S����Ȼ�����p��D
		min=65535;
		for(w=0; w<vertexnum; w++)//�����ж�����
			if(!final[w] && D[w]<min)//��S��֮��(��final[]=false)�Ķ���������v0����Ķ��㣬���丳��v,���븳��min
			{
				v=w;
				min=D[w];
			}
			final[v]=true;//v����S��
			for(w=0; w<vertexnum; w++)//�����²���Ķ��㣬���²���S���Ķ��㵽v0�ľ����·������
			{
				if(!final[w] && min<65535 && adm[v][w]<65535 && (min+adm[v][w]<D[w]))
				{//w ������S����v0->v->w�ľ���<Ŀǰv0->w�ľ���
					D[w]=min+adm[v][w];//����D[w]
					for
					(j=0; j<vertexnum; j++)//�޸�p[w]��v0��w�����Ķ������v0��v���������ж����ټ��϶���w
					{
						p[w][j]=p[v][j];
						if(p[w][j]==-1)//��p[w][]��һ������-1�ĵط����϶���w
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
	cout<<"���·������p[i][j]���£�"<<endl;
	for(i=0; i<vertexnum; i++)
	{
		for(j=0; j<vertexnum; j++)
			cout<<setw(3)<<p[i][j]<<" ";
		cout<<endl;
	}
 
	cout<<vexs[0]<<"������������·��������Ϊ��"<<endl;
	for(i=0; i<vertexnum; i++)
	{
		if(i!=0 && D[i]!=65535)
		{
			cout<<vexs[0]<<"-"<<vexs[i]<<"�����·������Ϊ:"<<D[i];
			cout<<"  ���·��Ϊ��";
			for(j=0; j<vertexnum; j++)
			{
				if(p[i][j]>-1)
					cout<<vexs[p[i][j]]<<" ";
			}
			cout<<endl;			
		}
		else if(D[i]==65535)
			cout<<vexs[0]<<"-"<<vexs[i]<<":"<<"���ɴ��Ŀ����в�����"<<endl;
	}
} 
void Add()
{
	vertexnum++;
	cout<<"������Ҫ���ӵĽڵ�"<<endl;
	string v;
	int w,n,i; 
	cin>>v;
	vexs[vertexnum-1]=v;
	cout<<"��������ָ��ı���"<<endl;
	cin>>n;
	for(int k=0;k<n;k++)
	{ 
		cout<<"���������������Ľڵ��Լ�Ȩֵ"<<endl;
		cin>>v>>w; 
		i=LocateVex(v);
	    adm[vertexnum-1][i]=w; 
	} 
	arcnum+=n;
	cout<<"������ָ����ı���"<<endl;
	cin>>n;
	for(int k=0;k<n;k++)
	{ 
		cout<<"���������������Ľڵ��Լ�Ȩֵ"<<endl;
		cin>>v>>w; 
		i=LocateVex(v);
	    adm[i][vertexnum-1]=w; 
	} 
	arcnum+=n;  

} 
void Delete()
{

	int num=0,i,j,c,y;
	cout<<"������Ҫɾ���Ľڵ�"<<endl;
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
	cout<<"������Ҫ�޸ĵ������ڵ�"<<endl;
	cin>>r>>j;
	cout<<"������Ҫ�޸ĵ�Ȩֵ"<<endl;
	cin>>n;
	i=LocateVex(r);
	k=LocateVex(j);
	adm[i][k]=n;
}
}; 
void run(MGraph &g)
{
	int i; 
	cout<<"****************�Ͻ�˹�����㷨����****************"<<endl;
	cout<<"****************1.�����������*******************"<<endl;
	cout<<"****************2.ɾ��ĳ������*******************"<<endl;
	cout<<"****************3.����ĳ������*******************"<<endl;
	cout<<"*****************4.�޸Ļ���ֵ********************"<<endl;
	cout<<"***********5.��������г��е����·��************"<<endl;
	cout<<"*******************6.�˳�*******************"<<endl;
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
 

