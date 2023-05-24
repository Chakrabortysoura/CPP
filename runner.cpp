#include <iostream>
#include <cstdlib>
#include <string>
#include <unistd.h>
using namespace std;
string extension(char *ar){
    string argument=ar;
    int len=argument.length(),index=argument.find(".");
    argument=argument.substr(index, len-index);
    return argument;
}
int main(int argc,char *argv[]){
    string argument,command="g++ ",ex=extension(argv[1]);
    command=command+argv[1]+" -lm";
    if(system(NULL)!=0){
        cout<<"The file can be executed"<<"\n";
        cout<<"The file to be executed: "<<argv[1]<<"\n";
        string filename=argv[1];
        system(command.c_str());
        cout<<"The file compilation is complete.\n";
        sleep(3);
        system("clear");
        system("./a.out");
    }
    return 0;
}