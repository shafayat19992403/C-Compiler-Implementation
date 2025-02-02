#pragma once
#include <bits/stdc++.h>
using namespace std;
#define VARIABLE 1
#define FUNCTION_DECLARATION 2
#define FUNCTION_DEFINITION 3

static int num=0;
class symbolInfo
{
private:
    string name;
    string type;
    //symbolInfo* next;

    int startLine,endLine;
    //vector<symbolInfo*> childList;

    string dataTypeOrReturnType;
    int isVariableOrFunction;
    
public:
    symbolInfo* next;
    vector<symbolInfo*> childList;
    vector<symbolInfo*> necessaryList;
    string sizeOfArray;
    vector<pair<string,string>> parameters;
    symbolInfo()
    {
        next=NULL;
    }
    symbolInfo(string name,string type)
    {
        this->name=name;
        this->type=type;
        next=NULL;
        this->dataTypeOrReturnType="";
        this->isVariableOrFunction= VARIABLE;
        this->sizeOfArray="";
        this->parameters.clear();
    }
    symbolInfo(string name, string type, string dataTypeOrReturnType, int infoType = VARIABLE, string arraySize=""){
        this->name=name;
        this->type=type;
        this->next=NULL;
        this->dataTypeOrReturnType=dataTypeOrReturnType;
        this->isVariableOrFunction=infoType;
        this->sizeOfArray=arraySize;
        this->parameters.clear();
        //startLine= start;
        //endLine= end;
    }
    symbolInfo(string name , string type, int start,int end){
        this->name=name;
        this->type=type;
        this->next=NULL;
        this->dataTypeOrReturnType="";
        this->isVariableOrFunction=VARIABLE;
        this->sizeOfArray="";
        this->parameters.clear();
        startLine= start;
        endLine= end;
    }
    symbolInfo(const symbolInfo &s){
        this->name=s.name;
        this->type=s.type;
        this->next=s.next;
        this->dataTypeOrReturnType=s.dataTypeOrReturnType;
        this->isVariableOrFunction=s.isVariableOrFunction;
        this->parameters=s.parameters;
        this->startLine=s.startLine;
        this->endLine=s.endLine;
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

    symbolInfo* getNext(){
        return next;
    }

    void setNext(symbolInfo* next){
        this->next=next;
    }

    void setDataTypeOrReturnType(string d){
        dataTypeOrReturnType=d;
    }

    string getDataTypeOrReturnType(){
        return dataTypeOrReturnType;
    }

    void setIsVariableOrFunction(int info){
        isVariableOrFunction=info;
    }

    int getIsVariableOrFunction(){
        return isVariableOrFunction;
    }

    bool isItArray(){
        if(sizeOfArray=="")
            return false;
        else 
            return true; 
    }

    void setSizeOfArray(int s){
        sizeOfArray=s;
    }
    string getSizeOfArray(){
        return sizeOfArray;
    }

    bool isItFunction(){
        if(isVariableOrFunction==FUNCTION_DECLARATION || isVariableOrFunction==FUNCTION_DEFINITION)
            return true;
        else
            return false;
    }

    void addParameter(string dataType,string paramName){
        parameters.push_back({dataType,paramName});
    }

    void setParameter(vector<pair<string,string>> parameters){
        this->parameters=parameters;
    }

    vector<pair<string,string>> getParameters(){
        return parameters;
    }

    void setReturnType(string dataType){
        this->dataTypeOrReturnType=dataType;
    }

    string getReturnType(){
        return dataTypeOrReturnType;
    }
    int getStartLine(){
        return startLine;
    }
    void setStartLine(int s){
        startLine=s;
    }
    int getEndLine(){
        return endLine;
    }
    void setEndLine(int s){
        endLine=s;
    }

};


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
        unsigned long long hash=0;
        unsigned int i=0;
        unsigned int len=str.length();

        for(int i=0;i<len;i++)
        {
            hash=(str[i])+(hash<<6)+(hash<<16)-hash;
            //hash=hash%n;
        }

        return (hash%n);
    }
    
    bool isNull(symbolInfo* ptr)
    {
        if(ptr==NULL)
            return true;
        else return false;
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
            cout<<"\t"<<name<<" "<<"already exisits in the current ScopeTable"<<endl;
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

            //cout<<"\tInserted in ScopeTable# "<<id<<" at position "<<bucketNumber+1<<", "<<i<<endl;
            return true;
        }
        return false;
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
                    /*if(!isInsideAfunction)
                        cout<<"\t'"<<name<<"' "<<"found in ScopeTable# "<<id<<" at position "<<bucketNumber+1<<", "<<i<<endl;*/
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
            //cout<<"\tNot found in the current ScopeTable"<<endl;
            return false;
        }
        if(curr->getName()==name){
            //cout<<"Found in ScopeTable# "<<id<<" at position "<<bucketNumber<<", "<<i<<endl;
            symbolInfo* temp=curr;
            table[bucketNumber]=curr->next;
            //cout<<"Deleted entry at position "<<bucketNumber<<", "<<i<<endl;
            //cout<<"\tDeleted '"<<temp->getName()<<"'"<<" from ScopeTable# "<<id<<" at position "<<bucketNumber+1<<", "<<i<<endl;
            delete curr;
            return true;
        }

        while(!isNull(curr))
        {
            i++;
            if(curr->getName()==name)
            {
                //cout<<"Found in ScopeTable# "<<id<<" at position "<<bucketNumber<<", "<<i<<endl;
                prev->next=curr->next;
                //curr=prev;
                delete curr;
                curr=prev;
                //cout<<"Deleted entry at position "<<bucketNumber<<", "<<i<<endl;
                //cout<<"\tDeleted '"<<curr->getName()<<"'"<<" from ScopeTable# "<<id<<" at position "<<bucketNumber+1<<", "<<i<<endl;
                return true;
            }
            prev=curr;
            curr=curr->next;
        }
        //cout<<"\tNot found in the current ScopeTable"<<endl;
        return false;
    }
    void print()
    {
        cout<<"\tScopeTable# "<<id<<endl;

        for(int i=0;i<n;i++)
        {
            if(table[i]!=NULL)
                cout<<"\t"<<i+1<<"--> ";
            symbolInfo* temp=table[i];
            while(!isNull(temp)){
                cout<<"<" <<temp->getName() <<","<<temp->getType()<<"> ";
                temp=temp->next;
            }
            delete temp;
            if(table[i]!=NULL)
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
        //cout<<"\tScopeTable# "<<id<<" removed"<<endl;
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
        //cout<<"\tScopeTable# "<<num <<" created"<<endl;

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
        //cout<<"\t'"<<name<<"'"<<" not found in any of the ScopeTables"<<endl;
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
        //cout<<"\tScopeTable# "<<num <<" created"<<endl;
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
