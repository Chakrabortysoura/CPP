#include <iostream>
#include <string.h>
using namespace std;
int compare_need(int *curinst,int *need,int n,int m){
    //n signifying which process' need to check and m beeing the number of reosurces
    int counter=1;
    for(int i=0;i<m;i++){
        if(*(curinst+i)<*(need+n*m+i)){
            counter=0;
        }
    }
    return counter;
}
int main(){
    int n,m;
    int *Toinst,*allocation,*max,*Curinst,*need;
    cout<<"The number of processes:";
    cin>>n; 
    cout<<"The number of resources: ";
    cin>>m; 
    Toinst=new int[m];
    Curinst=new int[m];
    cout<<"Give the number of instances for the resources: \n";
    for(int i=0;i<m;i++){
        cin>>*(Toinst+i);
    }
    allocation=new int[n*m];
    need=new int[n*m];
    max=new int[n*m];
    cout<<"Start giving the max resource requirements for the processes:\n";
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>*(max+i*m+j);
            // *(finish+(i*m)+j)=0;
        }
    }
    cout<<"Start giving the current allocation of the resource instances for the processes:\n";
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>*(allocation+i*m+j);
            *(need+i*m+j)=*(max+i*m+j)-*(allocation+i*m+j);
        }
    }
    for(int j=0;j<m;j++){
        *(Curinst+j)=*(Toinst+j);
        for(int i=0;i<n;i++){
            *(Curinst+j)-=*(allocation+i*m+j);
        }
    }
    cout<<"\n";
    int counter=0, finish[n];
    memset(finish,0,sizeof(finish));
    for(int i=1;i<=n;i++){
        for(int j=0;j<n;j++){
            if(*(finish+j)==0 && compare_need(Curinst,need,j,m)){
                // cout<<"Encoutered a match: "<<j+1<<"\n";
                for(int k=0;k<m;k++){
                    *(Curinst+k)=(*(Curinst+k))+(*(allocation+j*m+k));
                }
                *(need+j*m)=-1;
                *(finish+j)=i;
                counter++;
                //the resource curinst after the allocation of this new process.
                for(int k=0;k<m;k++){
                    cout<<*(Curinst+k)<<" ";
                }cout<<"\n";
                break;
            }
        }
    }
    if(counter<n){
        cout<<"The system in not in a safe state."<<counter<<"\n";
    }
    else{
        cout<<"The system is in a safe state.\n";
        cout<<"The safe sequence :";
        for(int i=1;i<=n;i++){
           for(int j=0;j<n;j++){
                if(*(finish+j)==i){
                    cout<<j+1<<",";
                        break;
                }
           }
            // cout<<*(finish+i-1)<<",";
        }
        cout<<"\n";
    }
    return 0;
}