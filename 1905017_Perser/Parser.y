%{
  #include <bits/stdc++.h>
  #include "symbolTable.h"
  using namespace std;


  int yyparse(void);
  int yylex(void);
  extern FILE *yyin;
  extern int yylineno;
  bool isErrorHasOccured=false;
  int extraInt=0;

  symbolTable st=symbolTable(30);
  
  int errorCount = 0;
  ofstream errorFile;
  vector<symbolInfo*>* functionParamList = NULL;
  int paramDeclineNo;
  ofstream parseTree;

  /*void dfs(symbolInfo* symbol){
    if(symbol->childList.size()==0) 
      {
        parseTree << symbol->getType() + " "+ symbol->getName() + "<Line: "<< symbol->getStartLine() <<"-"<<symbol->getEndLine()<<">"<<endl;
        return;
      }

    parseTree << symbol->getType() + " "+ symbol->getName() + "<Line: " << symbol->getStartLine()<<"-"<<symbol->getEndLine()<<">"<<endl;

    for(int i=0;i<symbol->childList.size();i++){
      dfs(symbol->childList[i]);
    }    

  }*/

  void dfs(symbolInfo* symbol,int space){
    parseTree << symbol->getType() +" : " + symbol->getName();
    if(symbol->childList.size()==0){
      parseTree << "\t" <<"<Line: "<<symbol->getStartLine()<<">"<<endl;
    }
    else {
      parseTree << " \t" << "<Line: "<<symbol->getStartLine()<<"-"<<symbol->getEndLine()<<">"<<endl;
    }

    for(int i=0; i<symbol->childList.size();i++){
        for(int j=0;j<space;j++){
          parseTree<<" ";
        }
        dfs(symbol->childList[i],space+1);
    }
  }

  void yyerror(const char* s){
		
  }

  void debuggerFlag(){
    cout<<"The debuggerFlag is here ------------------------------------------------"<<endl;
  }

  void writeErrorFile(string str, int n=-1){
    int lineNo;
    if(n==-1){
      lineNo=yylineno;
    }else{
      lineNo=n;
    }
    
    //Line# 20: Redefinition of parameter 'a'
    string s="Line# "+to_string(lineNo)+": "+str;
    //string s="Error at line "+ to_string(lineNo) +": "+str+"\n";
    //errorFile<<"Error at line "<<n<<": "<<str<<"\n"<<endl;
    errorFile<<s<<endl;
    //cout<<s<<endl;
    errorCount++;
  }

  void writeLogFile(string str1,string str2){
    cout<<str1<<" : "<<str2<<endl;
  }

  void declareFuncParamList(vector<symbolInfo*>* &symbolList, int lineNo=yylineno){
    if(symbolList == NULL){
      return;
    }

    for(symbolInfo* si : *symbolList){
      string dataType=si->getDataTypeOrReturnType();
      string name = si->getName();
      int lineno = yylineno;

      if(dataType == "void"){
        writeErrorFile("Function parameter cannot be void");
        continue;
      }

      if(st.insert(name,"ID")){
        symbolInfo* info=st.LookUp(name);
        info->setDataTypeOrReturnType(dataType);
        continue;
      }

      //writeErrorFile("Multiple declaration of "+name+" in parameter",lineNo);
      writeErrorFile((string)"Redefinition of parameter '"+(string)name+(string)"'",lineNo);

    }
    symbolList->clear();
  }




  void declareFunction(string funcName, string returnType, vector<symbolInfo*>* paramList= NULL , int lineNo=yylineno){
    bool isInserted = st.insert(funcName, "FUNCTION");

    symbolInfo* si = st.LookUp(funcName);

    if(isInserted){
      si->setIsVariableOrFunction(2);
      si->setDataTypeOrReturnType(returnType);

      if(paramList != NULL){
        for(symbolInfo* para : *paramList){
          si->parameters.push_back({para->getDataTypeOrReturnType(),para->getName()});
        }
      }
    }
    else{
      if(si->getIsVariableOrFunction()== 2){
        writeErrorFile((string)"redeclaration of '"+(string)funcName+(string)"'", lineNo);
        return ;
      }
    }
  }

  bool checkVoidFunction(symbolInfo *a, symbolInfo *b){
    if(a->getDataTypeOrReturnType()=="void" || b->getDataTypeOrReturnType()=="void"){
      writeErrorFile("Void cannot be used in expression ");
      return true;
    }
    return false;
  }

  string typeCasting(symbolInfo *a, symbolInfo *b){
    if(a->getDataTypeOrReturnType() == b->getDataTypeOrReturnType()){
      return a->getDataTypeOrReturnType();
    }

    if(a->getDataTypeOrReturnType()=="int" && b->getDataTypeOrReturnType()=="float"){
      return "float";
    }

    if(a->getDataTypeOrReturnType()=="float" && b->getDataTypeOrReturnType()=="int"){
      return "float";
    }

    if(a->getDataTypeOrReturnType()=="void")
      return b->getDataTypeOrReturnType();
    else 
      return a->getDataTypeOrReturnType();
  }

  void defineFunction(string functionName, string returnType, int lineNo=yylineno, vector<symbolInfo*>* parameterList=NULL){
    symbolInfo* info= st.LookUp(functionName);

    if(info == NULL){
      st.insert(functionName,"FUNCTION");
      info = st.LookUp(functionName);
    }else{
      if(info->getIsVariableOrFunction() == 2){
        if(info->getDataTypeOrReturnType() != returnType){
          writeErrorFile((string)"Conflicting types for '"+(string)functionName+(string)"'",lineNo);
          return;
        }

        vector<pair<string,string>> paramsInDefine = info->parameters;

        int paramCount=0;
        if(parameterList==NULL) paramCount=0;
        else paramCount=parameterList->size();

        if(paramsInDefine.size()!= paramCount){
          //writeErrorFile("Numbers of arguments doesnt match declaration of function "+functionName,lineNo);
          writeErrorFile((string)"Conflicting types for '"+(string)functionName+(string)"'",lineNo);
          return;
        } 
        if(parameterList != NULL){

          vector<symbolInfo*> paramList= *parameterList;
          for(int i=0;i<paramsInDefine.size();i++){

            if(paramsInDefine[i].first != paramList[i]->getDataTypeOrReturnType()){
              writeErrorFile((string)"Conflicting argument types for '"+(string)functionName+(string)"'",lineNo);
              return;
            }
          }
        }
      }else{
        if(info->getIsVariableOrFunction()==1)
          writeErrorFile((string)"'"+(string)functionName+(string)"' redeclared as different kind of symbol");
        return;
      }
    }

    if(info->getIsVariableOrFunction() == 3){
      writeErrorFile((string)"redefinition of '"+(string)functionName+(string)"'",lineNo);
      return;
    }


    info->setIsVariableOrFunction(3);
    info->setReturnType(returnType);
    info->parameters=vector<pair<string,string>> ();

    if(parameterList != NULL){
      for(symbolInfo* si : *parameterList){

        /*for(auto x: info->parameters){
          if(x.second == si->getName()){
            writeErrorFile("Redefinition of parameter "+si->getName());
            return;
          }
        }*/
        info->parameters.push_back({si->getDataTypeOrReturnType(), si->getName()});
      }
    }
  }

  void callFunction(symbolInfo* &func, vector<symbolInfo*>* args=NULL){
    string funcName=func->getName();
    symbolInfo* info=st.LookUp(funcName);

    if(info==NULL){
      writeErrorFile((string)"Undeclared function '"+(string)funcName+(string)"'");
      return;
    }

    if(!info->isItFunction()){
      writeErrorFile((string)"'"+(string)funcName+(string)"' is not a function");
      return;
    }
    func->setDataTypeOrReturnType(info->getDataTypeOrReturnType());

    if(info->getIsVariableOrFunction() != 3){
      writeErrorFile((string)"Function '"+(string)funcName+(string)"' is not defined");
      return;
    }

    vector<pair<string,string>> params=info->parameters;

    int paramCount=0;
    if(args == NULL ) paramCount=0;
    else paramCount=args->size();

    if(params.size() != paramCount){
      //writeErrorFile("Total number of arguments mismatch in function "+funcName);
      if(params.size()> paramCount){
        writeErrorFile((string)"Too few arguments to function '"+(string)funcName+(string)"'");
      }
      else{
        writeErrorFile((string)"Too many arguments to function '"+(string)funcName+(string)"'");
      }
      return;
    } 

    if(args != NULL){
      vector<symbolInfo*> argList= *args;

      bool isOkay=true;
      
      for(int i=0;i<params.size();i++){
        if(params[i].first != argList[i]->getDataTypeOrReturnType()){
          //writeErrorFile(to_string(i+1)+"th argument mismatch in function "+funcName);
          isOkay=false;
          //debuggerFlag();
          //cout<<params[i].first<<"   "<<argList[i]->getDataTypeOrReturnType()<<endl;
          writeErrorFile((string)"Type mismatch for argument "+(string)to_string(i+1)+(string)" of '"+(string)funcName+(string)"'");
        }
      }
      if(!isOkay) return;
    }
  }
%}

%union{
  symbolInfo* symbol;
}

%token<symbol> IF ELSE FOR WHILE DO BREAK INT CHAR FLOAT DOUBLE VOID RETURN SWITCH CASE DEFAULT CONTINUE

%token<symbol> ADDOP MULOP RELOP LOGICOP INCOP DECOP ASSIGNOP NOT LPAREN RPAREN LCURL RCURL LSQUARE RSQUARE COMMA SEMICOLON

%token<symbol> CONST_INT CONST_FLOAT CONST_CHAR  LOWER_THAN_ELSE ID


%type <symbol> factor term unary_expression simple_expression rel_expression logic_expression expression
%type <symbol> expression_statement statements compound_statement
%type <symbol> type_specifier var_declaration func_declaration unit program 
%type <symbol> declaration_list parameter_list argument_list arguments 
%type <symbol> start func_definition statement variable

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%%
start : program {
   $$=new symbolInfo("program","start",$1->getStartLine(),$1->getEndLine());
   $$->childList.push_back($1);
   writeLogFile("start","program");
   st.printAllScopeTable();
   st.exitScope();
   cout<<"Total Lines: "<<yylineno<<endl;
   cout<<"Total Errors; "<<errorCount<<endl;
   //parseTree<<"it has opened"<<endl;
   dfs($$,1);
}
;

program : program unit {
  $$ = new symbolInfo("program unit","program",$1->getStartLine(),$2->getEndLine());
  $$->childList.push_back($1);
  $$->childList.push_back($2);
  writeLogFile("program","program unit");
  $$->necessaryList=$1->necessaryList;
}
| unit{
  $$ = new symbolInfo("unit","program",$1->getStartLine(),$1->getEndLine());
  $$->childList.push_back($1);
  writeLogFile("program","unit");
  $$->necessaryList=$1->necessaryList;
}
;


unit : var_declaration{
  $$ = new symbolInfo("var_declaration","unit",$1->getStartLine(),$1->getEndLine());
  $$-> childList.push_back($1);
  $$->necessaryList=$1->necessaryList;
  writeLogFile("unit","var_declaration");
  
}
| func_declaration {
  $$ = new symbolInfo("func_declaration","unit",$1->getStartLine(),$1->getEndLine());
  $$-> childList.push_back($1);
  $$->necessaryList=$1->necessaryList;
  writeLogFile("unit","func_declaration");
  
}
| func_definition {
  $$ = new symbolInfo("func_definition","unit",$1->getStartLine(),$1->getEndLine());
  $$-> childList.push_back($1);
  $$->necessaryList=$1->necessaryList;
  writeLogFile("unit","func_definition");
}
;

func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON {
  $$ = new symbolInfo("type_specifier ID LPAREN parameter_list RPAREN SEMICOLON","func_declaration",$1->getStartLine(),$6->getEndLine());
  $$-> childList.push_back($1);
  $$-> childList.push_back($2);
  $$-> childList.push_back($3);
  $$-> childList.push_back($4);
  $$-> childList.push_back($5);
  $$-> childList.push_back($6);

  declareFunction($2->getName(),$1->getDataTypeOrReturnType(),&($4->necessaryList));

  writeLogFile("func_declaration","type_specifier ID LPAREN parameter_list RPAREN SEMICOLON");
  
}
| type_specifier ID LPAREN RPAREN SEMICOLON {
  $$ = new symbolInfo("type_specifier ID LPAREN RPAREN SEMICOLON","func_declaration",$1->getStartLine(),$5->getEndLine());
  $$-> childList.push_back($1);
  $$-> childList.push_back($2);
  $$-> childList.push_back($3);
  $$-> childList.push_back($4);
  $$-> childList.push_back($5);

  declareFunction($2->getName(),$1->getDataTypeOrReturnType()); 
  writeLogFile("func_declaration","type_specifier ID LPAREN RPAREN SEMICOLON");
  
}
;

func_definition : type_specifier ID LPAREN parameter_list RPAREN{defineFunction($2->getName(),$1->getDataTypeOrReturnType(),yylineno,&($4->necessaryList));} compound_statement{
  $$ = new symbolInfo("type_specifier ID LPAREN parameter_list RPAREN compound_statement","func_definition",$1->getStartLine(),$7->getEndLine());
  $$-> childList.push_back($1);
  $$-> childList.push_back($2);
  $$-> childList.push_back($3);
  $$-> childList.push_back($4);
  $$-> childList.push_back($5); 
  $$->childList.push_back($7);
  writeLogFile("func_definition","type_specifier ID LPAREN parameter_list RPAREN compound_statement");

}
| type_specifier ID LPAREN RPAREN{defineFunction($2->getName(),$1->getDataTypeOrReturnType(),yylineno);} compound_statement {
  $$ = new symbolInfo("type_specifier ID LPAREN RPAREN compound_statement","func_definition",$1->getStartLine(),$6->getEndLine());
  $$-> childList.push_back($1);
  $$-> childList.push_back($2);
  $$-> childList.push_back($3);
  $$-> childList.push_back($4);
  $$-> childList.push_back($6); 
  writeLogFile("func_definition","type_specifier ID LPAREN RPAREN compound_statement");
  //parseTree<<"it has opened "<<$$->getName()<<endl;
  
}
| type_specifier ID LPAREN error{
  if(!isErrorHasOccured){
    isErrorHasOccured=true;
    writeErrorFile("Syntax error at parameter list of function definition",yylineno);
    cout<<"Error at line no "<<yylineno<<" :syntax error"<<endl;
    //functionParamList.clear();
  }} RPAREN{isErrorHasOccured=false;} compound_statement{

    writeLogFile("func_definition","type_specifier ID LPAREN parameter_list RPAREN compound_statement");

    $$=new symbolInfo("type_specifier ID LPAREN parameter_list RPAREN compound_statement","func_definition",$1->getStartLine(),$8->getEndLine());

    $$->childList.push_back($1);
    $$->childList.push_back($2);
    $$->childList.push_back($3);
    $$->childList.push_back(new symbolInfo("error","parameter_list",$3->getEndLine(),$6->getStartLine()));
    $$->childList.push_back($6);
    $$->childList.push_back($8);

    isErrorHasOccured=false;
  }
;

parameter_list : parameter_list COMMA type_specifier ID {
 $$ = new symbolInfo("parameter_list COMMA type_specifier ID","parameter_list",$1->getStartLine(),$4->getEndLine());
 $$->childList.push_back($1);
 $$->childList.push_back($2);
 $$->childList.push_back($3);
 $$->childList.push_back($4);

 $1->necessaryList.push_back(new symbolInfo($4->getName(),"",$3->getDataTypeOrReturnType()));
 $$->necessaryList=$1->necessaryList; 

 functionParamList = &($1->necessaryList);
 paramDeclineNo=yylineno;
 writeLogFile("parameter_list","parameter_list COMMA type_specifier ID");
 
}
| parameter_list COMMA type_specifier{
  $$=new symbolInfo("parameter_list COMMA type_specifier","parameter_list",$1->getStartLine(),$3->getEndLine());
  $$->childList.push_back($1);
  $$->childList.push_back($2);
  $$->childList.push_back($3);

  $1->necessaryList.push_back(new symbolInfo($3->getName(),"",$3->getDataTypeOrReturnType()));
  $$->necessaryList=$1->necessaryList;

  functionParamList = &($1->necessaryList);
  paramDeclineNo=yylineno;
  writeLogFile("parameter_list","parameter_list COMMA type_specifier");
  //parseTree<<"it has opened "<<$$->getName()<<endl;
}
| type_specifier ID {
  $$=new symbolInfo("type_specifier ID","parameter_list",$1->getStartLine(),$2->getEndLine());
  $$->childList.push_back($1);
  $$->childList.push_back($2);

  $$->necessaryList.push_back(new symbolInfo($2->getName(),"",$1->getDataTypeOrReturnType()));
  
  functionParamList = &($$->necessaryList);
  paramDeclineNo=yylineno;
  writeLogFile("parameter_list","type_specifier ID");
}
| type_specifier{
  $$=new symbolInfo("type_specifier","parameter_list",$1->getStartLine(),$1->getEndLine());
  $$->childList.push_back($1);
  $$->necessaryList.push_back(new symbolInfo($1->getName(),"",$1->getDataTypeOrReturnType()));
  //$$->necessaryList.push_back($1);
  writeLogFile("parameter_list","type_specifier");
}
;

compound_statement : LCURL{st.EnterScope(); st.printAllScopeTable();  declareFuncParamList(functionParamList, paramDeclineNo);} statements RCURL {
  $$=new symbolInfo("LCURL statements RCURL","compound_statement",$1->getStartLine(),$4->getEndLine());
  $$->childList.push_back($1);
  $$->childList.push_back($3);
  $$->childList.push_back($4);
  $$->necessaryList=$1->necessaryList;

  
  st.printAllScopeTable();
  st.exitScope();
  writeLogFile("compound_statement","LCURL statements RCURL");
  //parseTree<<"it has opened "<<$$->getName()<<endl;
}
| LCURL{st.EnterScope();} RCURL {
  $$=new symbolInfo("LCURL RCURL","compound_statement",$1->getStartLine(),$3->getEndLine());
  $$->childList.push_back($1);
  $$->childList.push_back($3);
  st.printAllScopeTable();
  st.exitScope();
  writeLogFile("compound_statement","LCURL RCURL");
  //parseTree<<"it has opened "<<$$->getName()<<endl;
}
;

var_declaration : type_specifier declaration_list SEMICOLON {
  $$=new symbolInfo("type_specifier declaration_list SEMICOLON","var_declaration",$1->getStartLine(),$3->getEndLine());
  $$->childList.push_back($1);
  $$->childList.push_back($2);
  $$->childList.push_back($3);
  
  for(symbolInfo* si : $2->necessaryList){
    if($1->getDataTypeOrReturnType() == "void"){
      writeErrorFile((string)"Variable or field '"+(string)si->getName()+(string)"' declared void");
    }

    bool isInserted = st.insert(si->getName(),si->getType());

    
    if(!isInserted){
      if(si->getIsVariableOrFunction()!=1)
        writeErrorFile((string)"'"+(string)si->getName()+(string)"' redeclared as different kind of symbol");

      symbolInfo* temp=st.LookUp(si->getName());
      if(si->getIsVariableOrFunction()==1 && si->getDataTypeOrReturnType() != temp->getDataTypeOrReturnType()){
        writeErrorFile((string)"Conflicting types for'"+(string)si->getName()+(string)"'");
      }
    }else{
      symbolInfo* temp = st.LookUp(si->getName());
      temp->setDataTypeOrReturnType($1->getDataTypeOrReturnType());

      if(si->isItArray()){
          temp->sizeOfArray=si->sizeOfArray;
      }
    }
  }

  writeLogFile("var_declaration","type_specifier declaration_list SEMICOLON");
  //parseTree<<"it has opened "<<$$->getName()<<endl;
}
| type_specifier error{
  if(!isErrorHasOccured){
    isErrorHasOccured=true;
    cout<<"Error at line no "<<yylineno<<" : syntax error"<<endl;
    writeErrorFile("Syntax error at declaration list of variable declaration",yylineno);
    writeLogFile("var_declaration","type_specifier declaration_list SEMICOLON");
    extraInt=yylineno;
  }
}SEMICOLON{
    $$=new symbolInfo("type_specifier declaration_list SEMICOLON","var_declaration",$1->getStartLine(),$4->getEndLine());
    $$->childList.push_back($1);
    $$->childList.push_back(new symbolInfo("error","declaration_list",extraInt,extraInt));
    $$->childList.push_back($4);

    isErrorHasOccured=false;
    extraInt=0;
}
;

type_specifier : INT {
  $$=new symbolInfo("INT","type_specifier",$1->getStartLine(),$1->getEndLine());
  $$->childList.push_back($1);
  $$->setDataTypeOrReturnType("int");
  writeLogFile("type_specifier","INT");
  //parseTree<<"it has opened "<<$$->getName()<<endl;
}
| FLOAT {
  $$=new symbolInfo("FLOAT","type_specifier",$1->getStartLine(),$1->getEndLine());
  $$->childList.push_back($1);
  $$->setDataTypeOrReturnType("float");
  writeLogFile("type_specifier","FLOAT");
  //parseTree<<"it has opened "<<$$->getName()<<endl;
}
| VOID {
  $$=new symbolInfo("VOID","type_specifier",$1->getStartLine(),$1->getEndLine());
  $$->childList.push_back($1);
  $$->setDataTypeOrReturnType("void");
  writeLogFile("type_specifier","VOID");
  //parseTree<<"it has opened "<<$$->getName()<<endl;
}
;

declaration_list : declaration_list COMMA ID {
  $$ = new symbolInfo("declaration_list COMMA ID", "declaration_list",$1->getStartLine(),$3->getEndLine());
  $$->childList.push_back($1);
  $$->childList.push_back($2);
  $$->childList.push_back($3);
  $1->necessaryList.push_back($3);
  $$->necessaryList=$1->necessaryList;
  writeLogFile("declaration_list","declaration_list COMMA ID");

}
| declaration_list COMMA ID LSQUARE CONST_INT RSQUARE {
  $$ = new symbolInfo("declaration_list COMMA ID LSQUARE CONST_INT RSQUARE", "declaration_list",$1->getStartLine(),$6->getEndLine());
  $$->childList.push_back($1);
  $$->childList.push_back($2);
  $$->childList.push_back($3);
  $$->childList.push_back($4);
  $$->childList.push_back($5);
  $$->childList.push_back($6);

  $3->sizeOfArray=$5->getName();
  $1->necessaryList.push_back($3);
  $$->necessaryList=$1->necessaryList;
  writeLogFile("declaration_list","declaration_list COMMA ID LSQUARE CONST_INT RSQUARE");
}
| ID {
  $$= new symbolInfo("ID","declaration_list",$1->getStartLine(),$1->getEndLine());
  $$->childList.push_back($1);
  writeLogFile("declaration_list","ID");
  $$->necessaryList.push_back($1);
}
| ID LSQUARE CONST_INT RSQUARE {
  $$ = new symbolInfo("ID LSQUARE CONST_INT RSQUARE","declaration_list",$1->getStartLine(),$4->getEndLine());
  $$->childList.push_back($1);
  $$->childList.push_back($2);
  $$->childList.push_back($3);
  $$->childList.push_back($4);
  writeLogFile("declaration_list","ID LSQUARE CONST_INT RSQUARE");
  $$->necessaryList.push_back($1);
  $1->sizeOfArray=$3->getName();
  //parseTree<<"it has opened "<<$$->getName()<<endl;
}
;

statements : statement {
  $$=new symbolInfo("statement","statements",$1->getStartLine(),$1->getEndLine());
  $$->childList.push_back($1);

  $$->necessaryList=$1->necessaryList;
  writeLogFile("statements","statement");
  //parseTree<<"it has opened "<<$$->getName()<<endl;
}
| statements statement {
  $$=new symbolInfo("statements statement","statements",$1->getStartLine(),$2->getEndLine());
  $$->childList.push_back($1);
  $$->childList.push_back($2);

  $$->necessaryList=$1->necessaryList;
  writeLogFile("statements","statements statement");
  //parseTree<<"it has opened "<<$$->getName()<<endl;
}
;

statement : var_declaration {
  $$=new symbolInfo("var_declaration","statement",$1->getStartLine(),$1->getEndLine());
  $$->childList.push_back($1);

  $$->necessaryList=$1->necessaryList;
  writeLogFile("statement","var_declaration");
  //parseTree<<"it has opened "<<$$->getName()<<endl;
}
| expression_statement {
  $$=new symbolInfo("expression_statement","statement",$1->getStartLine(),$1->getEndLine());
  $$->childList.push_back($1);
  $$->necessaryList=$1->necessaryList;
  writeLogFile("statement","expression_statement");
  //parseTree<<"it has opened "<<$$->getName()<<endl;
}
| compound_statement {
  $$=new symbolInfo("compound_statement","statement",$1->getStartLine(),$1->getEndLine());
  $$->childList.push_back($1);
  $$->necessaryList=$1->necessaryList;
  writeLogFile("statement","compound_statement");
  //parseTree<<"it has opened "<<$$->getName()<<endl;
}
| FOR LPAREN expression_statement expression_statement expression RPAREN statement{
  $$= new symbolInfo("FOR LPAREN expression_statement expression_statement expression RPAREN statement","statement",$1->getStartLine(),$7->getEndLine());
  $$->childList.push_back($1);
  $$->childList.push_back($2);
  $$->childList.push_back($3);
  $$->childList.push_back($4);
  $$->childList.push_back($5);
  $$->childList.push_back($6);
  $$->childList.push_back($7);
  $$->necessaryList=$1->necessaryList;
  writeLogFile("statement","FOR LPAREN expression_statement expression_statement expression RPAREN statement");
  //parseTree<<"it has opened "<<$$->getName()<<endl;
}
| IF LPAREN expression RPAREN statement %prec LOWER_THAN_ELSE {
  $$=new symbolInfo("IF LPAREN expression RPAREN statement","statement",$1->getStartLine(),$5->getEndLine());
  $$->childList.push_back($1);
  $$->childList.push_back($2);
  $$->childList.push_back($3);
  $$->childList.push_back($4);
  $$->childList.push_back($5);

  $$->necessaryList=$1->necessaryList;
  writeLogFile("statement","IF LPAREN expression RPAREN statement");
  //$$->childList.push_back($6);
  //parseTree<<"it has opened "<<$$->getName()<<endl;
}
| IF LPAREN expression RPAREN statement ELSE statement {
  $$=new symbolInfo("IF LPAREN expression RPAREN statement ELSE statement","statement",$1->getStartLine(),$7->getEndLine());
  $$->childList.push_back($1);
  $$->childList.push_back($2);
  $$->childList.push_back($3);
  $$->childList.push_back($4);
  $$->childList.push_back($5);
  $$->childList.push_back($6);
  $$->childList.push_back($7);

  $$->necessaryList=$1->necessaryList;
  writeLogFile("statement","IF LPAREN expression RPAREN statement ELSE statement");
  //parseTree<<"it has opened "<<$$->getName()<<endl;
}
| WHILE LPAREN expression RPAREN statement {
  $$=new symbolInfo("WHILE LPAREN expression RPAREN statement","statement",$1->getStartLine(),$5->getEndLine());
  $$->childList.push_back($1);
  $$->childList.push_back($2);
  $$->childList.push_back($3);
  $$->childList.push_back($4);
  $$->childList.push_back($5);

  $$->necessaryList=$1->necessaryList;
  writeLogFile("statement","WHILE LPAREN expression RPAREN statement");
  //parseTree<<"it has opened "<<$$->getName()<<endl;
}

| RETURN expression SEMICOLON {
  $$=new symbolInfo("RETURN expression SEMICOLON","statement",$1->getStartLine(),$3->getEndLine());
  $$->childList.push_back($1);
  $$->childList.push_back($2);
  $$->childList.push_back($3);

  $$->necessaryList=$1->necessaryList;
  writeLogFile("statement","RETURN expression SEMICOLON");
  //parseTree<<"it has opened "<<$$->getName()<<endl;
}
;

expression_statement : SEMICOLON {
  $$=new symbolInfo("SEMICOLON","expression_statement",$1->getStartLine(),$1->getEndLine());
  $$->childList.push_back($1);

  $$->necessaryList.push_back(new symbolInfo($1->getName(),$1->getType()));
  writeLogFile("expression_statement","SEMICOLON");
  //parseTree<<"it has opened "<<$$->getName()<<endl;

}
| expression SEMICOLON {
  $$=new symbolInfo("expression SEMICOLON","expression_statement",$1->getStartLine(),$2->getEndLine());
  $$->childList.push_back($1);
  $$->childList.push_back($2);

  $$->necessaryList=$1->necessaryList;
  writeLogFile("expression_statement","expression SEMICOLON");
  //parseTree<<"it has opened "<<$$->getName()<<endl;

}
| error{if(!isErrorHasOccured){
  extraInt=yylineno;
  isErrorHasOccured=true;
}}SEMICOLON{
  writeLogFile("expression_statement","expression SEMICOLON");
  writeErrorFile("Syntax error at expression of expression statement",extraInt);

  $$=new symbolInfo("expression SEMICOLON","expression_statement",$3->getStartLine(),$3->getEndLine());

  $$->childList.push_back( new symbolInfo("error","expression",extraInt,extraInt));
  $$->childList.push_back($3);

  extraInt=0;
  isErrorHasOccured=false;
}
;

variable : ID {
  $$ = new symbolInfo("ID","variable",$1->getStartLine(),$1->getEndLine());
  $$->childList.push_back($1);

  symbolInfo *si = st.LookUp($1->getName());

  if(si != NULL){
    if(si->isItArray()){
      //writeErrorFile("Type mismatch, "+si->getName()+" is an array");
    }
    $$->necessaryList.push_back($1);
    $$->necessaryList[0]->setDataTypeOrReturnType(si->getDataTypeOrReturnType());
  }else{
    writeErrorFile((string)"Undeclared variable '"+(string)$1->getName()+(string)"'");
    $$->necessaryList.push_back($1);
    $$->necessaryList[0]->setDataTypeOrReturnType("");
  }

  
  writeLogFile("variable","ID");
  //parseTree<<"it has opened "<<$$->getName()<<endl;

}
| ID LSQUARE expression RSQUARE {
  $$ = new symbolInfo("ID LSQUARE expression RSQUARE","variable",$1->getStartLine(),$4->getEndLine());
  $$->childList.push_back($1);
  $$->childList.push_back($2);
  $$->childList.push_back($3);
  $$->childList.push_back($4);

  symbolInfo *si = st.LookUp($1->getName());
  if(si != NULL){
    $1->setDataTypeOrReturnType(si->getDataTypeOrReturnType());

    if(!si->isItArray()){
      writeErrorFile((string)"'"+(string)$1->getName()+(string)"' is not an array");
    }
    if($3->necessaryList[0]->getDataTypeOrReturnType()!="int"){
      writeErrorFile("Array subscript is not an integer");
    }
  }
  else{
    writeErrorFile((string)"Undeclared variable '"+(string)$1->getName()+(string)"'");
  }

  //string name=$1->getName()+"["+$3->getName()+"]";
  //$1->setName("");
  $$->necessaryList.push_back($1);
  writeLogFile("variable","ID LSQUARE expression RSQUARE");
  //parseTree<<"it has opened "<<$$->getName()<<endl;

}
;

expression : logic_expression{
  $$ = new symbolInfo("logic_expression","expression",$1->getStartLine(),$1->getEndLine());
  $$->childList.push_back($1);
  $$->necessaryList=$1->necessaryList;
  writeLogFile("expression","logic_expression");
  //parseTree<<"it has opened "<<$$->getName()<<endl;

}
| variable ASSIGNOP logic_expression{
  $$ = new symbolInfo("variable ASSIGNOP logic_expression","expression",$1->getStartLine(),$3->getEndLine());
  $$->childList.push_back($1);
  $$->childList.push_back($2);
  $$->childList.push_back($3);

  $$->necessaryList=$1->necessaryList;
  /*if(!checkVoidFunction($1->necessaryList[0],$3->necessaryList[0])){
    $$->necessaryList[0]->setDataTypeOrReturnType(typeCasting($1->necessaryList[0],$3->necessaryList[0]));
  }else{
    if($1->necessaryList[0]->getDataTypeOrReturnType()!="void"){
      $$->necessaryList[0]->setDataTypeOrReturnType($3->necessaryList[0]->getDataTypeOrReturnType());
    }
    else{
      $$->necessaryList[0]->setDataTypeOrReturnType($1->necessaryList[0]->getDataTypeOrReturnType());
    }
  }*/
  checkVoidFunction($1->necessaryList[0],$3->necessaryList[0]);

  if($1->necessaryList[0]->getDataTypeOrReturnType()=="int" && $3->necessaryList[0]->getDataTypeOrReturnType()=="float"){
    writeErrorFile("Warning: possible loss of data in assignment of FLOAT to INT");
  }
  $$->necessaryList[0]->setDataTypeOrReturnType(typeCasting($1->necessaryList[0],$3->necessaryList[0]));
  writeLogFile("expression","variable ASSIGNOP logic_expression");
  //parseTree<<"it has opened "<<$$->getName()<<endl;

}
;

logic_expression : rel_expression {
  $$ = new symbolInfo("rel_expression","logic_expression",$1->getStartLine(),$1->getEndLine());
  $$->childList.push_back($1);
  $$->necessaryList=$1->necessaryList;
  writeLogFile("logic_expression","rel_expression");
  //parseTree<<"it has opened "<<$$->getName()<<endl;

}
| rel_expression LOGICOP rel_expression {
  $$ = new symbolInfo("rel_expression LOGICOP rel_expression","logic_expression",$1->getStartLine(),$3->getEndLine());
  $$->childList.push_back($1);
  $$->childList.push_back($2);
  $$->childList.push_back($3);

  
  
  $$->necessaryList=$1->necessaryList;
  $$->necessaryList[0]->setDataTypeOrReturnType("int");
  writeLogFile("logic_expression","rel_expression LOGICOP rel_expression");
  //parseTree<<"it has opened "<<$$->getName()<<endl;

}
;

rel_expression : simple_expression{
  $$ = new symbolInfo("simple_expression","rel_expression",$1->getStartLine(),$1->getEndLine());
  $$->childList.push_back($1);
  $$->necessaryList=$1->necessaryList;
  writeLogFile("rel_expression","simple_expression");
  //parseTree<<"it has opened "<<$$->getName()<<endl;

}
| simple_expression RELOP simple_expression{
  $$ = new symbolInfo("simple_expression RELOP simple_expression","rel_expression",$1->getStartLine(),$3->getEndLine());
  $$->childList.push_back($1);
  $$->childList.push_back($2);
  $$->childList.push_back($3);
  $$->necessaryList=$1->necessaryList;
  $$->necessaryList[0]->setDataTypeOrReturnType("int");
  writeLogFile("rel_expression","simple_expression RELOP simple_expression");
  //parseTree<<"it has opened "<<$$->getName()<<endl;

}
;

simple_expression : term {
  $$ = new symbolInfo("term","simple_expression",$1->getStartLine(),$1->getEndLine());
  $$->childList.push_back($1);

  $$->necessaryList=$1->necessaryList;
  writeLogFile("simple_expression","term");
  //parseTree<<"it has opened "<<$$->getName()<<endl;

}
| simple_expression ADDOP term {
  $$ = new symbolInfo("simple_expression ADDOP term","simple_expression",$1->getStartLine(),$3->getEndLine());
  $$->childList.push_back($1);
  $$->childList.push_back($2);
  $$->childList.push_back($3);

  //checkVoidFunction($1,$3);
  $$->necessaryList=$1->necessaryList;
  /*if(!checkVoidFunction($1->necessaryList[0],$3->necessaryList[0])){
    $$->necessaryList[0]->setDataTypeOrReturnType(typeCasting($1->necessaryList[0],$3->necessaryList[0]));
  }else{
    if($1->necessaryList[0]->getDataTypeOrReturnType()!="void"){
      $$->necessaryList[0]->setDataTypeOrReturnType($3->necessaryList[0]->getDataTypeOrReturnType());
    }
    else{
      $$->necessaryList[0]->setDataTypeOrReturnType($1->necessaryList[0]->getDataTypeOrReturnType());
    }
  }*/

  checkVoidFunction($1->necessaryList[0],$3->necessaryList[0]);
  $$->necessaryList[0]->setDataTypeOrReturnType(typeCasting($1->necessaryList[0],$3->necessaryList[0]));
  //$$->necessaryList[0]->setDataTypeOrReturnType(typeCasting($1,$3));
  writeLogFile("simple_expression","simple_expression ADDOP term");
  //parseTree<<"it has opened "<<$$->getName()<<endl;

}
;

term : unary_expression{
  $$ = new symbolInfo("unary_expression","term",$1->getStartLine(),$1->getEndLine());
  $$->childList.push_back($1);
  $$->necessaryList = $1->necessaryList;
  writeLogFile("term","unary_expression");
  //parseTree<<"it has opened "<<$$->getName()<<endl;

}
| term MULOP unary_expression{
  $$ = new symbolInfo("term MULOP unary_expression","term",$1->getStartLine(),$3->getEndLine());
  $$->childList.push_back($1);
  $$->childList.push_back($2);
  $$->childList.push_back($3);

 

  if($2->getName()=="%"){
    if($3->necessaryList[0]->getName()=="0"){
      writeErrorFile("Warning: division by zero i=0f=1Const=0");
    }
    else if($1->necessaryList[0]->getDataTypeOrReturnType()!="int" || $3->necessaryList[0]->getDataTypeOrReturnType()!="int"){
      writeErrorFile("Operands of modulus must be integers ");
    }else{

    }
    $1->necessaryList[0]->setDataTypeOrReturnType("int");
    $3->necessaryList[0]->setDataTypeOrReturnType("int");
  }

  $$->necessaryList=$1->necessaryList;

  /*if(!checkVoidFunction($1->necessaryList[0],$3->necessaryList[0])){
    $$->necessaryList[0]->setDataTypeOrReturnType(typeCasting($1->necessaryList[0],$3->necessaryList[0]));
  }else{
    if($1->necessaryList[0]->getDataTypeOrReturnType()!="void"){
      $$->necessaryList[0]->setDataTypeOrReturnType($3->necessaryList[0]->getDataTypeOrReturnType());
    }
    else{
      $$->necessaryList[0]->setDataTypeOrReturnType($1->necessaryList[0]->getDataTypeOrReturnType());
    }
  }*/
  checkVoidFunction($1->necessaryList[0],$3->necessaryList[0]);
  $$->necessaryList[0]->setDataTypeOrReturnType(typeCasting($1->necessaryList[0],$3->necessaryList[0]));
  //$$->necessaryList[0]->setDataTypeOrReturnType(typeCasting($1,$3));
  
  writeLogFile("term","term MULOP unary_expression");
  //parseTree<<"it has opened "<<$$->getName()<<endl;

}
;

unary_expression : ADDOP unary_expression{
  $$=new symbolInfo("ADDOP unary_expression","unary_expression",$1->getStartLine(),$2->getEndLine());
  $$->childList.push_back($1);
  $$->childList.push_back($2);
  $$->necessaryList=$2->necessaryList;
  //checkVoidFunction($2->necessaryList[0],$2->necessaryList[0]);
  writeLogFile("unary_expression","ADDOP unary_expression");
  //parseTree<<"it has opened "<<$$->getName()<<endl;

}
| NOT unary_expression {
  $$=new symbolInfo("NOT unary_expression","unary_expression",$1->getStartLine(),$2->getEndLine());
  $$->childList.push_back($1);
  $$->childList.push_back($2);
  $$->necessaryList=$2->necessaryList;
  //checkVoidFunction($2->necessaryList[0],$2->necessaryList[0]);
  writeLogFile("unary_expression","NOT unary_expression");
  //parseTree<<"it has opened "<<$$->getName()<<endl;

}
| factor {
  $$=new symbolInfo("factor","unary_expression",$1->getStartLine(),$1->getEndLine());
  $$->childList.push_back($1);
  $$->necessaryList=$1->necessaryList;
  
  
  writeLogFile("unary_expression","factor");
  //parseTree<<"it has opened "<<$$->getName()<<endl;

}
;

factor : variable {
  $$=new symbolInfo("variable","factor",$1->getStartLine(),$1->getEndLine());
  $$->childList.push_back($1);
  writeLogFile("factor","variable");
  $$->necessaryList=$1->necessaryList;
  //parseTree<<"it has opened "<<$$->getName()<<endl;

}
| ID LPAREN argument_list RPAREN {
  $$ = new symbolInfo("ID LPAREN argument_list RPAREN","factor",$1->getStartLine(),$4->getEndLine());
  $$->childList.push_back($1);
  $$->childList.push_back($2);
  $$->childList.push_back($3);
  $$->childList.push_back($4);

  callFunction($1,&($3->necessaryList));

  string str;
  symbolInfo* temp=st.LookUp($1->getName());
  if(temp==NULL){
    
    str="";
  }else{
     str=temp->getDataTypeOrReturnType();
  }

  $$->necessaryList.push_back(new symbolInfo("","function",str));

  writeLogFile("factor","ID LPAREN argument_list RPAREN");
  //parseTree<<"it has opened "<<$$->getName()<<endl;

}
| LPAREN expression RPAREN {
  $$ = new symbolInfo("LPAREN expression RPAREN","factor",$1->getStartLine(),$3->getEndLine());
  $$->childList.push_back($1);
  $$->childList.push_back($2);
  $$->childList.push_back($3);
  $$->necessaryList= $2->necessaryList;
  writeLogFile("factor","LPAREN expression RPAREN");
  //parseTree<<"it has opened "<<$$->getName()<<endl;

}
| CONST_INT {
  $$=new symbolInfo("CONST_INT","factor",$1->getStartLine(),$1->getEndLine());
  $$->childList.push_back($1);
  $$->necessaryList.push_back(new symbolInfo($1->getName(),$1->getType(),"int"));
  writeLogFile("factor","CONST_INT");
  //parseTree<<"it has opened "<<$$->getName()<<endl;

}
| CONST_FLOAT {
 $$=new symbolInfo("CONST_FLOAT","factor",$1->getStartLine(),$1->getEndLine());
  $$->childList.push_back($1); 
  $$->necessaryList.push_back(new symbolInfo($1->getName(),$1->getType(),"float"));
  writeLogFile("factor","CONST_FLOAT");
  //parseTree<<"it has opened "<<$$->getName()<<endl;

}
| variable INCOP {
  $$ = new symbolInfo("variable INCOP","factor",$1->getStartLine(),$2->getEndLine());
  $$->childList.push_back($1);
  $$->childList.push_back($2);
  $$->necessaryList=$1->necessaryList;
  writeLogFile("factor","variable INCOP");
  //parseTree<<"it has opened "<<$$->getName()<<endl;

}
|variable DECOP {
  $$ = new symbolInfo("variable DECOP","factor",$1->getStartLine(),$2->getEndLine());
  $$->childList.push_back($1);
  $$->childList.push_back($2);
  $$->necessaryList=$1->necessaryList;
  writeLogFile("factor","variable DECOP");
  //parseTree<<"it has opened "<<$$->getName()<<endl;

}
;

argument_list : arguments {
  $$=new symbolInfo("arguments","argument_list",$1->getStartLine(),$1->getEndLine());
  $$->childList.push_back($1);

  $$->necessaryList=$1->necessaryList;
  writeLogFile("argument_list","arguments");
  //parseTree<<"it has opened "<<$$->getName()<<endl;

}
|{
  /*$$=new symbolInfo("","arguments",$1->getStartLine(),$1->getEndLine());
  $$->childList.push_back($1);*/
}
;

arguments : arguments COMMA logic_expression{
  $$ = new symbolInfo("arguments COMMA logic_expression","arguments",$1->getStartLine(),$3->getEndLine());
  $$->childList.push_back($1);
  $$->childList.push_back($2);
  $$->childList.push_back($3);

  for(symbolInfo* si : $3->necessaryList){
    $1->necessaryList.push_back(si);
  }
  
  $$->necessaryList=$1->necessaryList;
  writeLogFile("arguments","arguments COMMA logic_expression");
  //parseTree<<"it has opened "<<$$->getName()<<endl;
}
| logic_expression {
  $$=new symbolInfo("logic_expression","arguments",$1->getStartLine(),$1->getEndLine());
  $$->childList.push_back($1);
  
  for(symbolInfo* si : $1->necessaryList){
    $$->necessaryList.push_back(si);
  }
  
  //$$->necessaryList.push_back($1);
  writeLogFile("arguments","logic_expression");
  //parseTree<<"it has opened "<<$$->getName()<<endl;
}
;
%%

int main(int argc,char *argv[]){
    if(argc != 2){
        cout<<"Please provide input file name and try again."<<endl;
        return 0;
    }
    FILE *fin = freopen(argv[1], "r", stdin);
    if(fin == nullptr){
        cout<<"Can't open specified file."<<endl;
        return 0;
    }
	cout<<argv[1]<<" opened successfully."<<endl;
	
    parseTree.open("parseTree.txt");
    errorFile.open("errorFile.txt");
    freopen("log.txt", "w", stdout);
    //st.insert("printf","FUNCTION");
    
    // if we don't init the yyin, it will use stdin(console)
    yyin = fin;

    yylineno = 1; // line number starts from 1

    // start scanning the file here
	yyparse();

    fclose(yyin);
    return 0;
}