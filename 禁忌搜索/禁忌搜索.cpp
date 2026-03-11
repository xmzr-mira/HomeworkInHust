#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string.h>
#include <time.h>
#include <ctime>
#include <vector>
#include <string.h>

using namespace std;

//to_string方法 
template<typename _T>
string To_string(const _T& t) {
	ostringstream os;
	os << t;
	return os.str();
}

int N_node = 125;
int N_edge = 736;	
int s[125];

//禁忌表 
int tabulist[125];

//增量数组 
int delta[125];

//迭代次数 
int steps=5000;

//二维数组存储边 
int Edge[125][125];

int max_edg=0;
int max_f=0;
int best[125];

//计算增量 
void delta_value(){
	  int num1=0,num2=0;
	
	 for(int i=0;i< N_node;i++)
		{
            num1=num2=0;
    		for(int j=0;j< N_node;j++)
                if((j!=i) &&(Edge[i][j]==1) )
    			{
    				if(s[i]==s[j])
      		   	    	num1++;
    				else
    	 	   			num2++;
    			}
    	delta[i]=num1-num2;
   		}
}

//计算函数值 
int f_value(){
		int f = 0;

		for( int i = 0; i < N_node; i++ )
		{
	
      		for( int j = i+1; j < N_node; j++ )
         		if( (Edge[ i ][ j ] == 1) && (s[ i ] != s[ j ]) )
            		f = f + 1;
            	}		
        return f;

}

void next_step(int cd){
//禁忌步长>0则-1→检查禁忌步长是否为0→为0的找deita最大值→s设为0或1→禁忌步长设为5/10/15/20 
	int flag=0;	
	int max_delta=-125;
	for(int i=0;i<N_node;i++){
	
		if(tabulist[i]>0){
			tabulist[i]-=1;
			
		}
		else if(tabulist[i]==0){
				if(delta[i]>max_delta){
					max_delta=delta[i];
					flag=i;
				}
			}
		} 

	if(s[flag]==0){
		s[flag]=1;
	}
	else {
		s[flag]=0;
	}
	//翻转 
	tabulist[flag]=cd;

}
	
void tabusearch(int cd){
	//函数值 	
	int f;
	
	string filename = "result_steps_" + To_string(cd) + ".txt";
	
	 // 以写模式打开文件
   ofstream FOC;
   FOC.open(filename.c_str());
	
	for (int i=0;i<steps;i++){
		delta_value();
		f=f_value();
		if(f>max_f){
			max_f=f;
			for (int i=0;i<N_node;i++){
				best[i]=s[i];
			}
		}
	FOC<<"迭代次数："<<i<<endl;
	FOC<<"函数值：";
		
	for(int j=0;j<N_node;j++){
		FOC<<s[j];
		}
		FOC<<endl;
 		FOC<<"当前解：";
   		FOC<<f<<endl;
   		FOC<<"最优解：";
		FOC<<max_f<<endl<<endl;
		next_step(cd);
		
	}
	
	FOC<<"\n最终解：";
	for(int i=0;i<N_node;i++){
		FOC<<s[i];
	}
	FOC<<"\n最终函数值：";
	FOC<<f<<endl;
	FOC<<"\n最终最优解：";
	for(int i=0;i<N_node;i++){
		FOC<<best[i];
	}
	FOC<<"\n最终最优函数值：";
	FOC<<max_f<<endl;
	
	cout << filename + "写入完成\n";
	
	FOC.close();// 关闭打开的文件
}

//禁忌搜索 
int main(){
	srand((unsigned)time(NULL));//随机化种子 
	
	ifstream FIC;
    
 char File_Name[] = "dsjc125.1.txt";
 FIC.open(File_Name); //File_Name表示文件名字 如File_Name = "dsjc125.1.txt" 
  if ( FIC.fail() )
  {
           cout << "### Erreur open, File_Name " << File_Name << endl;
           exit(0);
   }
     char StrReading[100];
     FIC >> StrReading;
     if ( FIC.eof() )
     {
           cout << "### Error open, File_Name " << File_Name << endl;
           exit(0);
     }
     
     int x1, x2;
     while ( ! FIC.eof() )
     {
           char bidon[50];
           if ( strcmp(StrReading, "p" )==0 )
           {
              //FIC >> StrReading;
              FIC >> N_node >> N_edge;
              cout << "Number of vertexes = " << N_node << endl;
              
              cout << "Number of edges = " << N_edge << endl;
            
               for ( int x=0; x< N_node; x++ )
			   {
			  		
              	 for ( int y=0; y< N_node; y++ )
				   {
				   
                 	 Edge[x][y] = 0;
                  //cout<<"Edge"<<x<<","<<y<<":"<<Edge[x][y]<<endl;
				  } 
				  }
           }
           
           if ( strcmp(StrReading, "e")==0 )
           {
                 FIC >> x1 >> x2;
                 x1--; x2--;
                 if ( x1<0 || x2<0 || x1>= N_node || x2 >= N_node )
                 {
                       cout << "### Error of node : x1="
                            << x1 << ", x2=" << x2 << endl;
                       exit(0);
                 }
                 Edge[x1][x2]=Edge[x2][x1]=1;
                 max_edg++;
				 
				 }
				 FIC >> StrReading;
			
     }
     FIC.close();	
     //读取文件
	 cout<<"读取成功"<<endl;
	 
	 for( int i = 0; i < N_node; i++ ){
		
 		if(rand()%2==0)
    		s[ i ] = 0;
		else
    		s[ i ] = 1;
 }//初始解 
    
    for( int i = 0; i < N_node; i++ ){
		
 		tabulist[i]=0;
 }
 
 //禁忌CD表初始化（参数代表禁忌长度） 
  
    tabusearch(5);
    tabusearch(10);
    tabusearch(20);
    tabusearch(30);
    tabusearch(40);
    
	return 0;
}



