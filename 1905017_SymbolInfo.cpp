#include <bits/stdc++.h>
using namespace std;

int num=0;
class symbolInfo
{
private:
    string name;
    string type;
public:
    symbolInfo* next;

    symbolInfo()
    {
        next=NULL;
    }
    symbolInfo(string name,string type)
    {
        this->name=name;
        this->type=type;
        next=NULL;
    }

    void setName(string name)
    {
        this->name=name;
    }
    void setType(string name)
    {
        this->type=type;
    }

    string getName()
    {
        return name;
    }
    string getType()
    {
        return type;
    }
};
bool isNull(symbolInfo* ptr)
{
    if(ptr==NULL)
        return true;
    else return false;
}
class scopeTable
{
    public:
        int id;
        int n;
        symbolInfo** table;
        scopeTable* parentScope;

    scopeTable(int n)
    {
        this->n=n;
        table=new symbolInfo*[n];
        for(int i=0;i<n;i++)
        {
            table[i]=NULL;
        }
    }
    int hashFunction(string str)
    {
        unsigned int hash=0;
        unsigned int i=0;
        unsigned int len=str.length();

        for(int i=0;i<len;i++)
        {
            hash=(str[i])+(hash<<6)+(hash<<16)-hash;
            hash=hash%n;
        }

        return (hash%n);
    }

    bool insert(string name,string type)
    {
        int i=1;
        symbolInfo* temp=new symbolInfo(name,type);
        int bucketNumber = hashFunction(temp->getName());
        symbolInfo* prev,*curr;
        prev=NULL;
        curr=table[bucketNumber];
        //cout<<"here"<<endl;
        /*while(!isNull(curr))
        {
            i++;
            prev=curr;
            if(curr->getName() == temp->getName())
            {
                cout<<"\t'"<<name<<"' "<<"already exists in the current ScopeTable"<<endl;
                return false;
            }
            curr=curr->next;
        }*/

        if(LookUp(temp->getName(),true))
        {
            cout<<"\t'"<<name<<"' "<<"already exists in the current ScopeTable"<<endl;
                return false;
        }
        else
        {
           while(!isNull(curr))
            {
                i++;
                prev=curr;
                curr=curr->next;
            }
        }

        if(isNull(curr))
        {
            curr=temp;
            if(isNull(prev))
                table[bucketNumber]=curr;
            else
                prev->next=curr;

            cout<<"\tInserted in ScopeTable# "<<id<<" at position "<<bucketNumber+1<<", "<<i<<endl;
            return true;
        }
    }

    symbolInfo* LookUp(string name,bool isInsideAfunction)
    {
        int i=0;
        int bucketNumber=hashFunction(name);
        symbolInfo* curr=table[bucketNumber];

        while(!isNull(curr))
        {
            i++;
            if(curr->getName()==name )
                {
                    if(!isInsideAfunction)
                        cout<<"\t'"<<name<<"' "<<"found in ScopeTable# "<<id<<" at position "<<bucketNumber+1<<", "<<i<<endl;
                    return curr;
                }
            else
                curr=curr->next;
        }
        //cout<<"'"<<name<<"'"<<" not found in any of the ScopeTables"<<endl;
        return NULL;
    }

    bool Delete(string name)
    {
        int i=1;
        int bucketNumber=hashFunction(name);
        symbolInfo* curr=table[bucketNumber];
        symbolInfo* prev=NULL;
        if(isNull(curr))
        {
            cout<<"\tNot found in the current ScopeTable"<<endl;
            return false;
        }
        if(curr->getName()==name){
            //cout<<"Found in ScopeTable# "<<id<<" at position "<<bucketNumber<<", "<<i<<endl;
            symbolInfo* temp=curr;
            table[bucketNumber]=curr->next;
            //cout<<"Deleted entry at position "<<bucketNumber<<", "<<i<<endl;
            cout<<"\tDeleted '"<<temp->getName()<<"'"<<" from ScopeTable# "<<id<<" at position "<<bucketNumber+1<<", "<<i<<endl;
            delete temp;
            return true;
        }

        while(!isNull(curr))
        {
            i++;
            if(curr->getName()==name)
            {
                //cout<<"Found in ScopeTable# "<<id<<" at position "<<bucketNumber<<", "<<i<<endl;
                prev->next=curr->next;
                curr=prev;
                delete curr;
                //cout<<"Deleted entry at position "<<bucketNumber<<", "<<i<<endl;
                cout<<"\tDeleted '"<<curr->getName()<<"'"<<" from ScopeTable# "<<id<<" at position "<<bucketNumber+1<<", "<<i<<endl;
                return true;
            }
            prev=curr;
            curr=curr->next;
        }
        cout<<"\tNot found in the current ScopeTable"<<endl;
        return false;
    }
    void print()
    {
        cout<<"\tScopeTable# "<<id<<endl;

        for(int i=0;i<n;i++)
        {
            cout<<"\t"<<i+1<<"--> ";
            symbolInfo* temp=table[i];
            while(!isNull(temp)){
                cout<<"<" <<temp->getName() <<","<<temp->getType()<<"> ";
                temp=temp->next;
            }
            delete temp;
            cout<<endl;
        }
    }

    ~scopeTable()
    {
        for(int i=0;i<n;i++){
            symbolInfo* temp=table[i];
            while(!isNull(temp)){
                symbolInfo* prev=temp;
                temp=temp->next;
                delete prev;
            }
        }
        cout<<"\tScopeTable# "<<id<<" removed"<<endl;
        delete[] table;
    }
};


class symbolTable
{
public:
    int n;

    scopeTable* curScopeTable;

    symbolTable(int n)
    {
        this->n=n;
        curScopeTable=new scopeTable(n);
        curScopeTable->parentScope=NULL;
        num++;
        curScopeTable->id=num;
        cout<<"\tScopeTable# "<<num <<" created"<<endl;

    }


    bool insert(string name,string type)
    {
        bool isInsertable=curScopeTable->insert(name,type);

        return isInsertable;
    }
    bool remove(string name)
    {
        return curScopeTable->Delete(name);
    }

    symbolInfo* LookUp(string name)
    {
        scopeTable* cur=curScopeTable;
        while(cur != NULL)
        {
            symbolInfo* temp=cur->LookUp(name,false);
            if(temp!=NULL){
                return temp;
            }
            else{
                cur=cur->parentScope;
            }
        }
        cout<<"\t'"<<name<<"'"<<" not found in any of the ScopeTables"<<endl;
        return NULL;
    }

    void printCurrentScopeTable()
    {
        //scopeTable* cur=curScopeTable;
        curScopeTable->print();
    }
    void printAllScopeTable()
    {
        scopeTable* cur=curScopeTable;
        while(cur!=NULL)
        {
            cur->print();
            //cout<<endl;
            cur=cur->parentScope;
        }
    }
    void EnterScope()
    {
        scopeTable* newScopeTable= new scopeTable(n);
        newScopeTable->parentScope=curScopeTable;
        curScopeTable=newScopeTable;
        num++;
        newScopeTable->id=num;
        cout<<"\tScopeTable# "<<num <<" created"<<endl;
    }

    void exitScope()
    {
        scopeTable* temp=curScopeTable;
        if(temp->parentScope==NULL)
        {
            cout<<"\tScopeTable# "<<temp->id<<" cannot be removed"<<endl;
            return;
        }
        curScopeTable=curScopeTable->parentScope;
        temp->parentScope=NULL;
        delete temp;
    }
    void cascadeExitScope()
    {
        while(curScopeTable!= NULL)
        {
            scopeTable* temp=curScopeTable;
            curScopeTable=curScopeTable->parentScope;
            temp->parentScope=NULL;
            delete temp;
        }
    }
};

int main()
{
    freopen("sample_input.txt","r",stdin);
    freopen("sample_output.txt","w",stdout);
    int n;
    cin>>n;
    int cmdNumber=0;
    symbolTable st(n);
    char ch;
    int cnt=0;

    while(true)
    {
        cout<<"Cmd "<<++cmdNumber<<": ";
        cin>>ch;
        //cout<<"Cmd "<<cmdNumber<<": ";
        cout<<ch;
        string str[2];
        //string temp[100]="FAKA";
        if(ch=='I')
        {
            string input;
            int cnt=0;

            getline(cin,input);
            cout<<input<<endl<<"";
            //cout<<'\t';
            stringstream strStream(input);
            string temp;

            while(strStream>>temp){

                if(cnt<2)
                {
                    str[cnt]=temp;
                }
            cnt++;
            }
                if(cnt!=2){
                    cout<<"\tNumber of parameters mismatch for the command "<<ch<<endl;
                }
                else
                    st.insert(str[0],str[1]);
            //bool isInserted
        }
        if(ch=='L')
        {
            //cin>>str[0];

            string input;
            int cnt=0;

            getline(cin,input);
            cout<<input<<endl<<"";
            //cout<<'\t';
            stringstream strStream(input);
            string temp;

            while(strStream>>temp){

                if(cnt<1)
                {
                    str[cnt]=temp;
                }
            cnt++;
            }
                if(cnt!=1){
                    cout<<"\tNumber of parameters mismatch for the command "<<ch<<endl;
                }
                else
                    st.LookUp(str[0]);
        }
        if(ch=='D')
        {
            //cin>>str[0];
            string input;
            int cnt=0;

            getline(cin,input);
            cout<<input<<endl<<"";
            //cout<<'\t';
            stringstream strStream(input);
            string temp;

            while(strStream>>temp){

                if(cnt<1)
                {
                    str[cnt]=temp;
                }
            cnt++;
            }
                if(cnt!=1){
                    cout<<"\tNumber of parameters mismatch for the command "<<ch<<endl;
                }
                else
                    st.remove(str[0]);
        }
        if(ch=='P')
        {
            //char chTwo;
            //cin>>chTwo;
            string input;
            int cnt=0;

            getline(cin,input);
            cout<<input<<endl<<"";
            //cout<<'\t';
            stringstream strStream(input);
            string temp;

            while(strStream>>temp){

                if(cnt<1)
                {
                    str[cnt]=temp;
                }
            cnt++;
            }
                if(cnt!=1){
                    cout<<"\tNumber of parameters mismatch for the command "<<ch<<endl;
                }
                else
                {
                    if(str[0]=="A")
                    {
                        st.printAllScopeTable();
                    }
                    else if(str[0]=="C")
                    {
                        st.printCurrentScopeTable();
                    }
                }

        }
        if(ch=='S')
        {
            string input;
            int cnt=0;

            getline(cin,input);
            cout<<input<<endl<<"";
            //cout<<'\t';
            stringstream strStream(input);
            string temp;

            while(strStream>>temp){

                if(cnt<0)
                {
                    str[cnt]=temp;
                }
            cnt++;
            }
                if(cnt!=0){
                    cout<<"\tNumber of parameters mismatch for the command "<<ch<<endl;
                }
                else
                    st.EnterScope();
        }
        if(ch=='E')
        {
            string input;
            int cnt=0;

            getline(cin,input);
            cout<<input<<endl<<"";
            //cout<<'\t';
            stringstream strStream(input);
            string temp;

            while(strStream>>temp){

                if(cnt<0)
                {
                    str[cnt]=temp;
                }
            cnt++;
            }
                if(cnt!=0){
                    cout<<"\tNumber of parameters mismatch for the command "<<ch<<endl;
                }
                else
                    st.exitScope();
        }
        if(ch=='Q')
        {
            string input;
            int cnt=0;

            getline(cin,input);
            cout<<input<<endl;
            //cout<<'\t';
            stringstream strStream(input);
            string temp;

            while(strStream>>temp){

                if(cnt<0)
                {
                    str[cnt]=temp;
                }
            cnt++;
            }
            if(cnt!=0){
                cout<<"\tNumber of parameters mismatch for the command "<<ch<<endl;
            }
            else
            {
                st.cascadeExitScope();
                break;
            }
        }
    }
}
