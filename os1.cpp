#include <iostream>
#include <cstdlib>
#include <string>
const int baseid=rand();
int count=0;
using namespace std;
class process{
    private:
        int pid,burst_time,cpu_burst,io_burst,priority;
        string process_status;
    public:
        process *next;
        process(int id){
            pid=id;
            cpu_burst=rand()%10;
            io_burst=rand()%10;
            priority=0;
            next=NULL;
            burst_time=cpu_burst+io_burst;
            if(cpu_burst>=io_burst){
                process_status="Cpu bound";
            }
            else{
                process_status="IO bound";
            }
        }
        process(process *t){
            int temp;
            string tmp;
            next=NULL;
            temp=pid;
            pid=t->pid;
            t->pid=temp;
            temp=cpu_burst;
            cpu_burst=t->cpu_burst;
            t->cpu_burst=temp;
            temp=io_burst;
            io_burst=t->io_burst;
            t->io_burst=temp;
            tmp=process_status;
            process_status=t->process_status;
            t->process_status=tmp;
            temp=priority;
            priority=t->priority;
            t->priority=temp;
            temp=burst_time;
            burst_time=t->burst_time;
            t->burst_time=temp;
        }
        int get_burst(){
            return burst_time;
        }
        string get_status(){
            return process_status;
        }
        int get_priority(){
            return priority;
        }
        void set_priority(int n){
            priority=n;
        }
        void printdetails(){
            cout<<"Process ID:"<<pid<<"  ";
            cout<<"Total burst time:"<<burst_time<<"\n";
            cout<<"Process Status:"<<process_status<<"  ";
            cout<<"Process Priority:"<<priority<<"\n\n\n";
        }
        void swap(process *t){
            int temp;
            string tmp;
            temp=pid;
            pid=t->pid;
            t->pid=temp;
            temp=cpu_burst;
            cpu_burst=t->cpu_burst;
            t->cpu_burst=temp;
            temp=io_burst;
            io_burst=t->io_burst;
            t->io_burst=temp;
            tmp=process_status;
            process_status=t->process_status;
            t->process_status=tmp;
            temp=priority;
            priority=t->priority;
            t->priority=temp;
            temp=burst_time;
            burst_time=t->burst_time;
            t->burst_time=temp;
        }
};
process* add_process(process *head,process *temp){
    process *t=head;
    if(head==NULL){
        head=temp;
        count++;
        return head;
    }
    while(t->next!=NULL){
        t=t->next;
    }
    t->next=temp;
    return head;
}
void assign_priority(process *head,int count){
    process *t=head;
    for(int i=0;i<count-1;i++){
        t=head;
        for(int j=0;j<count-i-1;j++){
            process *temp=t->next;
            if(t->get_burst()>temp->get_burst()){
                t->swap(temp);
            }
            t=t->next;
        }
    }
    t=head;
    int i=1;
    while(t!=NULL){
        t->set_priority(i);
        i++;
        t=t->next;
    }
}
void printlist(process *head){
    process *temp=head;
    while(temp!=NULL){
        temp->printdetails();
        temp=temp->next;
    }
}
process * readyque(process *head,int size,process *ready){
    process *cpu=NULL,*io=NULL,*t=head;
    int count=1;
    while(t!=NULL){
        if(t->get_status()=="Cpu bound"){
            process *temp=new process(t);
            cpu=add_process(cpu,temp);
        }
        else{
            process *temp=new process(t);
            io=add_process(io,temp);
        }
        t=t->next;
    }
    t=ready;
    while(cpu!=NULL && io!=NULL){
        if(count%3==0){
            process *temp=new process(io);
            ready=add_process(ready,temp);
            io=io->next;
        }
        else{
            process *temp=new process(cpu);
            ready=add_process(ready,temp);
            cpu=cpu->next;
        }
        count++;
    }
    while(cpu!=NULL){
        process *temp=new process(cpu);
        ready=add_process(ready,temp);
        cpu=cpu->next;
    }
    while(io!=NULL){
        process *temp=new process(io);
        ready=add_process(ready,temp);
        io=io->next;
    }
    return ready;
}
int main(){
    process *head=NULL,*ready=NULL,*temp1,*temp2,*temp3;
    int number;
    cout<<"The number of processes to make:";
    cin>>number;
    for(int i=1;i<=number;i++){
        process *temp=new process(baseid+count);
        head=add_process(head,temp);
        count++;
    }
    assign_priority(head,number);
    cout<<"The new state que is=>\n";
    printlist(head);
    ready=readyque(head,number,ready);
    cout<<"The ready que is=>\n";
    printlist(ready);
    return 0;
}