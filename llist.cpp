// Jacinto Gomez
// File Processing Payroll
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

template<class T>
class Node{
public:
    Node(){}
    ~Node(){}
    Node<T>* prevnode=nullptr;
    Node<T>* nextnode=nullptr;
    T val;
    Node(T val){
        this->val=val;
    }
};

template<class T>
class List{
public:
    List(){}
    ~List(){}
    Node<T>* head=nullptr;
    Node<T>* tail=nullptr;
    int size=0;
    List(Node<T>* node){
        this->head=node;
        this->tail=node;
        this->size++;
    }
    void addend(Node<T>* node){
        this->tail->nextnode=node;
        node->prevnode=this->tail;
        this->tail=node;
        this->size++;
    }
    void addbeginning(Node<T>* node){
        this->head->prevnode=node;
        node->nextnode=this->head;
        this->head=node;
        this->size++;
    }
    void removeend(){
        this->tail=this->tail->prevnode;
        this->tail->nextnode=nullptr;
        this->size--;
    }
    void printlist(){
        Node<T>* currnode=this->head;
        while(currnode!=nullptr){
            cout<<currnode->val<<" ";
            currnode=currnode->nextnode;
        }
        cout<<endl;
    }
};

class Employee{
public:
    Employee(){};
    int get_id(){return id;}
    int get_workhours(){return workhours;}
    double get_payrate(){return payrate;}
    double get_earned(){return workhours*payrate;}
    string get_name(){return name;}
    void set_id(int i){id=i;}
    void set_workhours(int wh){workhours=wh;}
    void set_payrate(double pr){payrate=pr;}
    void set_earned(double er){earned=er;}
    void set_name(string nm){name=nm;}
    friend ostream& operator <<(ostream& outs,const Employee& em){
        //outs<<em.id<<"\t"<<em.payrate<<"\t"<<em.workhours<<"\t"<<em.earned<<"\t"<<em.name<<endl;
        outs<<em.name<<", $"<<em.earned<<endl;
        return outs;
    }
private:
    int id;
    int workhours;
    double payrate;
    double earned;
    string name;
};

void merge(vector<Employee>& vec,int begin1,int end1,int end2){
    int begin2=end1+1;
    int size1=end1-begin1+1;
    int size2=end2-begin2+1;
    vector<Employee> v1;
    vector<Employee> v2;
    for (int i=0;i<size1;i++){
        v1.push_back(vec[begin1+i]);
    }
    for (int j=0;j<size2;j++){
        v2.push_back(vec[begin2+j]);
    }
    int y=0;
    int z=0;
    int k=begin1;
    while ((size1>y)&&(size2>z)){
        if ((v1[y].get_earned() <= v2[z].get_earned())) {
            vec[k] = v2[z];
            z++;
        } else {
            vec[k] = v1[y];
            y++;
        }
        k++;
    }
    while (y<size1){
        vec[k]=v1[y];
        y++;
        k++;
    }
    while (z<size2){
        vec[k]=v2[z];
        z++;
        k++;
    }
}

void sort(vector<Employee>& sub,int begin,int end){
    if(begin==end){
        return;
    }else{
        int midpoint=(begin+end)/2;
        sort(sub,begin,midpoint);
        sort(sub,midpoint+1,end);
        merge(sub,begin,midpoint,end);
    }
}

void reorder(vector<Employee>& sub){
    int begin=0;
    int end=sub.size()-1;
    sort(sub,begin,end);
}

void openinputfile(ifstream& infile){
    string filename;
    cout<<"Enter filename: ";
    cin>>filename;
    infile.open(filename);
    while (!infile){
        cout<<"File failed ot open!"<<endl;
        cout<<"Enter filename: ";
        cin>>filename;
        infile.clear();
        infile.open(filename);
    }
}

int main(){
    //read info from employee data file
    ifstream infile1;
    openinputfile(infile1);
    Employee temp;
    int tid,tworkhours,tpayrate;
    infile1>>tid>>tpayrate;
    temp.set_id(tid);
    temp.set_payrate(tpayrate);
    infile1.ignore(9999,'\t');
    string tname;
    getline(infile1, tname);
    temp.set_name(tname);
    Node<Employee>* newhead=new Node<Employee>(temp);
    List<Employee>* list=new List<Employee>(newhead);
    list->addend(newhead);
    while (infile1>>tid>>tpayrate){
        temp.set_id(tid);
        temp.set_payrate(tpayrate);
        infile1.ignore(9999,'\t');
        string tname;
        getline(infile1, tname);
        temp.set_name(tname);
        Node<Employee>* newnode=new Node<Employee>(temp);
        list->addend(newnode);
    }

    //read info from hours file
    ifstream infile2;
    openinputfile(infile2);
    while (infile2>>tid>>tworkhours){
        Node<Employee>* here=newhead;
        while (here!=nullptr){
            if (here->val.get_id()==tid){
                double original=here->val.get_workhours();
                here->val.set_workhours(original+tworkhours);
            }
            here=here->nextnode;
        }
    }

    //print linked list results in descending $$ order
    vector<Employee> ev;
    Node<Employee>* here=newhead;
    while (here!=nullptr){
        Employee transfer;
        transfer.set_id(here->val.get_id());
        transfer.set_workhours(here->val.get_workhours());
        transfer.set_payrate(here->val.get_payrate());
        transfer.set_name(here->val.get_name());
        transfer.set_earned(here->val.get_earned());
        ev.push_back(transfer);
        here=here->nextnode;
    }
    reorder(ev);
    cout<<"******* Payroll Information *******"<<endl;
    for (Employee emp:ev){
        cout<<emp;
    }
    cout<<"*********** End Payroll ***********";
    return 0;
}