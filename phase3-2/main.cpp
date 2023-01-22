#include <bits/stdc++.h>
#include <map>
using namespace std;
int frame=0;
class process{
public:
    string name;
    map<string,int> variables;
    map<string,int> var_page;
    map<int,int> pageTable;
    map<int,bool> apBit;
    int size=0;
};
void pagefault(process* p,int lossPage){
    while(true){
        int max=p->pageTable.size()-1;
        int randNum = rand()%(max-0 + 1);
        if(randNum!=lossPage){
            p->pageTable[lossPage]=p->pageTable[randNum];
            p->pageTable[randNum]=-1;
            break;
        }
    }

}
void setVarPage(process* temp_proc,int* temp_size,string var,int varsize,int* page){
    if((*temp_size)<=400){
        temp_proc->var_page[var]=(*page);
    }
    else{
        frame++;
        temp_proc->var_page[var]=++(*page);
        if(frame>9){
            temp_proc->pageTable[(*page)]=-1;
            temp_proc->apBit[(*page)]=false;
        }
        else{
        temp_proc->pageTable[(*page)]=frame;
        temp_proc->apBit[(*page)]=true;
        }
        *temp_size=varsize;
    }

}
int relativeAddress(process* p,string var){
    int tmp=0;
    var.erase(0,3);
    int num=stoi(var);
    for(int i=1;i<num;i++){
        tmp+=p->variables["var"+to_string(i)];
    }
    return tmp;
}

void logicalAddress(process* p,string var){
    cout << "\n\nThe Logical Address of " << var << " in Process " << p->name << " is \n";
    cout <<"Page Number:" << p->var_page[var] << endl;
    cout <<"Offset:" << relativeAddress(p,var) %400 << endl;

}

void physicalAddress(process* p,string var){
    cout << "\n\nThe Physical Address of " << var << " in Process " << p->name << " is \n";
    if(p->pageTable[p->var_page[var]]==-1){
        cout <<"Page Fault"<<endl;
        pagefault(p,p->var_page[var]);
    }
    else{
        cout <<"Frame Number:" << p->pageTable[p->var_page[var]] << endl;
        cout <<"Offset:" << relativeAddress(p,var) %400 << endl;
    }

}
int main()
{
    srand(time(NULL));
    int num_of_processes,num_of_vars;
    vector<process> processes;
    cout << "How many process do we have ?\n";
    cin >> num_of_processes;

    while (num_of_processes--) {
        int page=0;
        int temp_size=0;
        process temp_proc;
        if(frame>9){
            temp_proc.pageTable[0]=-1;
            temp_proc.apBit[0]=false;
        }
        else{
            temp_proc.pageTable[0]=frame;
            temp_proc.apBit[0]=true;
        }
        cout <<"\nProcess Name:";
        cin >> temp_proc.name;

        cout << "How many variable does process" << temp_proc.name << " have ?\n";
        cin >> num_of_vars;

        for(int i=0;i<num_of_vars;i++){
            cout << i<<"'st variable name:";
            string temp_varname;
            cin >> temp_varname;

            cout << "size of "<<i<<"'st variable:";
            int temps;
            cin >> temps;
            temp_proc.size+=temps;
            temp_size+=temps;

            setVarPage(&temp_proc,&temp_size,temp_varname,temps,&page);
            temp_proc.variables[temp_varname]=temps;

        }
//        for(const auto &x : temp_proc.variables){
//            cout << x.first << " " << x.second <<endl;
//        }
        cout << "\n";
        cout << "..Process " << temp_proc.name << " Var To Page...\n\n";
                for(const auto &x : temp_proc.var_page){
                    cout << x.first << " " << x.second <<endl;
                }
                cout<<"\n";
                cout << "\n";
                cout << "..Process " << temp_proc.name << " Page Table...\n\n";
                cout << "#P" << " " << "#F\n";
                for(auto x : temp_proc.pageTable){
                    cout << x.first << " " << x.second << endl;
                }
                cout << "\n";
        processes.push_back(temp_proc);
        frame++;
    }

    while(true){
        cout << "\n\nProcess:";
        string p;
        cin >> p;

        cout << "Variable:";
        string v;
        cin >> v;


        cout << "\n";
        for(auto &x:processes){
            if(x.name==p){

                cout << "\n";
                cout << "..Process " << x.name << " Page Table...\n\n";
                cout << "#P" << " " << "#F\n";
                for(auto x : x.pageTable){
                    cout << x.first << " " << x.second << endl;
                }


                cout << "\n";
                cout << "The Ralative Address of " << v << " in Process " << p << " is " << relativeAddress(&x,v);
                logicalAddress(&x,v);
                physicalAddress(&x,v);
                break;
            }
        }

    }
}
