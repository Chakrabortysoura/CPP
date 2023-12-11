#include <iostream>
#include <string.h>
using namespace std;
struct edges{
    int start=0,end=0,weight=0;
};
void kruskal(int n,int v,int *adj){
    struct edges array[n];
    int count=0,k=0,vertices[v];
    memset(vertices,0,sizeof(vertices));
    for(int i=0;i<v;i++){
        for(int j=0;j<v;j++){
            if(*(adj+i*v+j)>0){
                array[k].start=i+1;
                array[k].end=j+1;
                array[k].weight=*(adj+i*v+j);
                k++;
            }
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n-1-i;j++){
            if(array[j].weight>array[j+1].weight){
                struct edges temp;
                temp=array[j];
                array[j]=array[j+1];
                array[j+1]=temp;
            }
        }
    }
    vertices[array[0].start-1]=1;
    vertices[array[0].end-1]=1;
    for(int i=1;i<n;i++){
        if(vertices[array[i].start-1]==1 && vertices[array[i].end-1]==0){
            vertices[array[i].end-1]=1;
        }
        else{
            array[i].weight=0;
        }
    }
    for(int i=0;i<n;i++){
        if(array[i].weight!=0){
            cout<<"Starting: "<<array[i].start<<" Ending: "<<array[i].end<<"\n";
            cout<<"Weight of the edge: "<<array[i].weight<<"\n";
        }
    }
}
void spanningtree(int n,int v,int *adj){
   int vertices[v],k=0,count=0,start;
   cout<<"Starting vertex for the spanning tree: ";
   cin>>start;
   memset(vertices,0,sizeof(vertices));
   vertices[start-1]=1;
   count++;
   do{
        int value=0,starting=0,ending=0;
        for(int i=0;i<v;i++){
            for(int j=0;j<v;j++){
                if(vertices[i]!=0 && vertices[j]==0){
                    if(value==0){
                        starting=i+1;
                        ending=j+1;
                        value=*(adj+i*v+j);
                    }
                    else if(value>*(adj+i*v+j)){
                        starting=i+1;
                        ending=j+1;
                        value=*(adj+i*v+j);
                    }
                }
            }
        }
        if(value>0){
            cout<<"starting : "<<starting<<"Ending: "<<ending<<"\n";
            cout<<"Weight: "<<value<<"\n";
            count++;
            vertices[ending-1]=1;
        }

    }while(count!=v);
}
int main(){
    int v,e;
    cout<<"The number of vertices in the graph: ";
    cin>>v;
    int adj[v][v],spanning[v][v];
    memset(adj, 0, sizeof(adj));
    memset(spanning,0,sizeof(spanning));
    cout<<"How many edges there are in the graph: ";
    cin>>e;
    for(int i=0;i<e;i++){
        int starting,end;
        cout<<"Starting vertex: ";
        cin>>starting;
        cout<<"Ending vertex: ";
        cin>>end;
        cout<<"Weight: ";
        cin>>adj[starting-1][end-1];
    }
    cout<<"The adjacency matrix for the graph is:\n";
    for(int i=0;i<v;i++){
        for(int j=0;j<v;j++){
            cout<<adj[i][j]<<" ";
        }
        cout<<"\n";
    }
    kruskal(e,v,&adj[0][0]);
    return 0;
}
