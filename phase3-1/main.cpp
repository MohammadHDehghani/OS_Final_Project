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
    int size=0;
};

void setVarPage(process* temp_proc,int* temp_size,string var,int varsize,int* page){
    if((*temp_size)<=400){
        temp_proc->var_page[var]=(*page);
    }
    else{
        frame++;
        temp_proc->var_page[var]=++(*page);
        temp_proc->pageTable[(*page)]=frame;
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
    cout <<"Frame Number:" << p->pageTable[p->var_page[var]] << endl;
    cout <<"Offset:" << relativeAddress(p,var) %400 << endl;

}
int main()
{
    int num_of_processes,num_of_vars;
    vector<process> processes;
    cout << "How many process do we have ?\n";
    cin >> num_of_processes;

    while (num_of_processes--) {
        int page=0;
        int temp_size=0;
        process temp_proc;
        temp_proc.pageTable[0]=frame;
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
        for(const auto &x : temp_proc.variables){
            cout << x.first << " " << x.second <<endl;
        }
        for(const auto &x : temp_proc.var_page){
            cout << x.first << " " << x.second <<endl;
        }
        cout << "\n";
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

        for(auto x:processes){
            if(x.name==p){
                cout << "The Ralative Address of " << v << " in Process " << p << " is " << relativeAddress(&x,v);
                logicalAddress(&x,v);
                physicalAddress(&x,v);
                break;
            }
        }

    }
}
