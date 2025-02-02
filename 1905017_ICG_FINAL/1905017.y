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


  vector<symbolInfo*> ListOfGlobalVar;
  bool isItGlobal=true;
  ofstream assemblyOut;
  bool isNegative=false;
  int level=0;
  int offset=0;
  //vector<pair<symbolInfo*, symbolInfo*> > parametersInFunction;
  vector<symbolInfo*> parametersInFunction;
  
  string returnLevel="";
  int sizeOfParametersInFunction=0;


  void startAssemble(symbolInfo*);
  void funcDefinition(symbolInfo*);
  void compoundStatement(symbolInfo*);
  void statements(symbolInfo*);
  void statement(symbolInfo*);
  void ifElseFunction(symbolInfo*,string);
  void statement(symbolInfo*);
  void expressionStatement(symbolInfo*);
  void expression(symbolInfo*);
  void logicExpression(symbolInfo*);
  void relExpression(symbolInfo*);
  void simpleExpression(symbolInfo*);
  void term(symbolInfo*);
  void unaryExpression(symbolInfo*);
  void factor(symbolInfo*);
  void argumentList(symbolInfo*);
  void arguments(symbolInfo*);
  void declarationList(symbolInfo*);

  string createLevel(){
    level++;
    return "L"+to_string(level);
  }

  void printNewLineAssemblyCode(){
        assemblyOut<<"new_line proc\n"<<"\tpush ax\n"<<"\tpush dx\n"<<"\tmov ah,2\n"<<"\tmov dl,cr\n"<<"\tint 21h\n";
        assemblyOut<<"\tmov ah,2\n"<<"\tmov dl,lf\n"<<"\tint 21h\n"<<"\tpop dx\n"<<"\tpop ax\n"<<"\tret\n";
        assemblyOut<<"new_line endp"<<endl;
  }

  void printOutputAssemblyCode(){
        assemblyOut<<"print_output proc  ;print what is in ax\n";

            assemblyOut<<"\tpush ax\n"<<"\tpush bx\n"<<"\tpush cx\n"<<"\tpush dx\n"<<"\tpush si\n"<<"\tlea si,number\n";
            assemblyOut<<"\tmov bx,10\n"<<"\tadd si,4\n"<<"\tcmp ax,0\n"<<"\tjnge negate\n"<<"\tprint:\n"<<"\txor dx,dx\n";
            assemblyOut<<"\tdiv bx\n"<< "\tmov [si],dl\n"<<"\tadd [si],'0'\n"<<"\tdec si\n"<<"\tcmp ax,0\n"<<"\tjne print\n";
            assemblyOut<<"\tinc si\n"<<"\tlea dx,si\n"<<"\tmov ah,9\n"<<"\tint 21h\n"<<"\tpop si\n"<<"\tpop dx\n";
            assemblyOut<<"\tpop cx\n"<<"\tpop bx\n"<<"\tpop ax\n"<<"\tret\n"<<"\tnegate:\n"<<"\tpush ax\n"<<"\tmov ah,2\n"<<"\tmov dl,'-'\n";
            assemblyOut<<"\tint 21h\n"<<"\tpop ax\n"<<"\tneg ax\n"<<"\tjmp print\n";
        assemblyOut<<"print_output endp"<<endl;
    }
    void initialCodesOfStart(){
      assemblyOut<<".MODEL SMALL"<<endl<<".STACK 1000H"<<endl<<".Data"<<endl<<"\tCR EQU 0DH"<<endl;
      assemblyOut<<"\tLF EQU 0AH"<<endl<<"\tnumber DB \"00000$\""<<endl;
    }

    void startAssemble(symbolInfo* si){
      isItGlobal=false;
      vector<symbolInfo*> listOfUnit;
      assemblyOut.open("assemblt.txt");
      initialCodesOfStart();
      symbolInfo* temp=si->childList[0];

      for(;temp->childList.size()==2;){
        listOfUnit.push_back(temp->childList[1]);
        temp=temp->childList[0];
      }

      listOfUnit.push_back(temp->childList[0]);

      assemblyOut<<"\t\t;declaring global variables"<<endl;

      for(symbolInfo* var: ListOfGlobalVar){
        if(var->isItArray()){
          assemblyOut<<"\t"<<var->getName()<<" DW "<<var->sizeOfArray<<" DUP (0000H)"<<endl;
        }else{
          assemblyOut<<"\t"<<var->getName()<<" DW 1 DUP (0000H)"<<endl;
        }
      }

      assemblyOut<<".CODE"<<endl;
      

      for(symbolInfo* unit:listOfUnit){
        //if(unit==NULL) errorFile<<"jhamela"<<endl;
        if(unit->getName()=="func_definition")
          {
            funcDefinition(unit->childList[0]);
          }
      }

      printNewLineAssemblyCode();
      printOutputAssemblyCode();

      assemblyOut<<"END main"<<endl;
      //st.printAllScopeTable();

    }

    void varDeclaration(symbolInfo* si){
      assemblyOut<<"\t\t;variable declared"<<endl;

      declarationList(si->childList[1]);
    }

    void declarationList(symbolInfo* si){
        if(isItGlobal){
            return;
        }
        if(si->childList.size()==1){
          assemblyOut<<"\tSUB SP, 2"<<endl;
            offset+=2;

            si->childList[0]->offset=offset;

            st.insert(*(si->childList[0]));

            
        }
        else if(si->childList.size()==3){
           assemblyOut<<"\tSUB SP, 2"<<endl;
            offset+=2;
            si->childList[2]->offset=offset;
            st.insert(*(si->childList[2]));
           
            declarationList(si->childList[0]);
        }
        else if(si->childList.size()==4){
            string strTemp=si->childList[0]->sizeOfArray;
            int temp=stoi(strTemp);
            offset=offset+ 2*temp ;
            (si->childList[0])->offset=offset;
            st.insert(*(si->childList[0]));
            assemblyOut<<"\tSUB SP, "<<2*stoi((si->childList[0])->sizeOfArray)<<endl;
            
        }
        else if(si->childList.size() == 6){
            offset=offset+2*stoi((si->childList[2])->sizeOfArray);

            (si->childList[2])->offset=offset;

            st.insert(*(si->childList[2]));

            assemblyOut<<"\tSUB SP, "<<2*stoi(si->childList[2]->sizeOfArray)<<endl;
            declarationList(si->childList[0]);
        }
    }

    void funcDefinition(symbolInfo* si){
      bool hasParam=false;
      bool isMain=false;
      offset=-2;
      string name=si->childList[1]->getName();
      assemblyOut<<"\t\t;function definition"<<endl;
      assemblyOut<<name<<" PROC"<<endl;
      if(name=="main"){
            isMain=true;
        }

        if(si->childList.size()==6){
          hasParam=true;
        }

        if(isMain){
          assemblyOut<<"\tMOV AX, @DATA"<<endl;
          assemblyOut<<"\tMOV DS, AX"<<endl;
        }

        if(hasParam){
         // parametersInFunction = si->childList[3]->parameters;
         
         //functionParamList= &(si->childList[3]->necessaryList)
         *functionParamList = (si->childList[3]->necessaryList);

         errorFile<<si->childList[3]->necessaryList.size()<<endl;

          for(symbolInfo* i: *functionParamList){
            //assemblyOut<<"is inside"<<endl;
            offset=offset-2;
            i->offset=offset;
            //assemblyOut<<i->getName()<<" "<<i->offset<<endl;
            
          }
        }

        offset=0;
        if(functionParamList==NULL){
          sizeOfParametersInFunction=0;
        }else{
          sizeOfParametersInFunction = functionParamList->size();
        }
        
        assemblyOut<<"\t\t;pushing base pointer"<<endl<<"\tPUSH BP"<<endl<<"\tMOV BP, SP"<<endl;
        returnLevel=createLevel();

        if(hasParam){
            compoundStatement(si->childList[5]);
        }
        else{
            compoundStatement(si->childList[4]);
        }

        assemblyOut<<returnLevel<<":"<<"\t\t;returning from function"<<endl;
        assemblyOut<<"\tMOV SP, BP "<<endl;
        assemblyOut<<"\tPOP BP"<<endl;

        if(isMain){
            assemblyOut<<"\tMOV AX, 4CH"<<endl;
            assemblyOut<<"\tINT 21H"<<endl;
        }
        else{

            if(sizeOfParametersInFunction>0){

              int t=sizeOfParametersInFunction*2;
              assemblyOut<<"\tRET "<<t<<endl;

            }
            else{
                assemblyOut<<"\tRET"<<endl;
            }
            sizeOfParametersInFunction=0;
        }

        assemblyOut<<name<<" ENDP"<<endl;
        offset=0;

    }

  

    void compoundStatement(symbolInfo* si){
      bool hasStatement=false;
      int functionParamListSize;
      if(si->childList.size()==3){
          hasStatement=true;
      }


      if(functionParamList==NULL){
        functionParamListSize=0;
      }else{
        functionParamListSize=functionParamList->size();
      }


      if(hasStatement){
        st.EnterScope();
        if(functionParamListSize!=0){
          for(symbolInfo* x: *functionParamList){
            st.insert(*x);
          }
          functionParamList->clear();
        }
        statements(si->childList[1]);
        st.exitScope();
      }
      else{
        st.EnterScope();
        st.exitScope();
      }
    }

    void statements(symbolInfo* si){
        if(si->childList.size()==1){
          statement(si->childList[0]);
        }
        else if(si->childList.size()==2){
          statements(si->childList[0]);
          statement(si->childList[1]);
        }
    }
    void printLNHelper(symbolInfo* si){
        assemblyOut<<"\t\t;Line no "<<si->getStartLine()<<endl;
            string variableName=si->childList[2]->getName();
            symbolInfo* si1=st.LookUp(variableName);
            string variableName1="";

            if(si1->offset==0){
                variableName1=si1->getName();
            }

            else if(si1->offset > 0){
                variableName1="[BP-"+to_string(si1->offset)+"]";
            }

            else if(si1->offset < 0){
                variableName1="[BP+"+to_string((si1->offset)*(-1))+"]";
            }

            assemblyOut<<"\t\t;calling println function"<<endl;
            assemblyOut<<"\tMOV AX, "<<variableName1<<endl;
            assemblyOut<<"\tCALL print_output"<<endl;
	          assemblyOut<<"\tCALL new_line"<<endl;
    }
    void ifLRPARENhelper(symbolInfo* si){
            assemblyOut<<"\t\t;Line no "<<si->getStartLine()<<endl<<"\t\t;if else statement"<<endl;
            expression(si->childList[2]);
            string nextLevel=createLevel();
            assemblyOut<<"\tPOP AX"<<endl<<"\tCMP AX, 0"<<endl<<"\tJE "<<nextLevel<<endl;
            statement(si->childList[4]);
            assemblyOut<<nextLevel<<":"<<endl;
    }
    void ifLRPARENhelperWithElse(symbolInfo* si){
            assemblyOut<<"\t\t;Line no "<<si->getStartLine()<<endl;
            assemblyOut<<"\t\t;if else statement"<<endl;
            expression(si->childList[2]);

            string levelOne=createLevel();
            string levelZero=createLevel();
            string nextLevel=createLevel();

            assemblyOut<<"\tPOP AX"<<endl<<"\tCMP AX, 0"<<endl<<"\tJNE "<<levelOne<<endl<<"\tJMP "<<levelZero<<endl;
            assemblyOut<<levelOne<<":"<<endl;
            statement(si->childList[4]);

            assemblyOut<<"\tJMP "<<nextLevel<<endl;
            assemblyOut<<levelZero<<":"<<endl;
            ifElseFunction(si->childList[6], nextLevel);
            assemblyOut<<nextLevel<<":"<<endl;
    }

    void forLoopHelper(symbolInfo* si){
            assemblyOut<<"\t\t;Line no "<<si->getStartLine()<<endl<<"\t\t;for initialization"<<endl;
            expressionStatement(si->childList[2]);
      
            string levelStart=createLevel();
            string levelEnd=createLevel();

            assemblyOut<<levelStart<<":"<<"\t\t;for loop start"<<endl;
            expressionStatement(si->childList[3]);
           
            assemblyOut<<"\tCMP AX, 0"<<endl<<"\tJE "<<levelEnd<<endl;
            statement(si->childList[6]);
            expression(si->childList[4]);

            assemblyOut<<"\tPOP AX"<<endl<<"\tJMP "<<levelStart<<endl;

            assemblyOut<<levelEnd<<":"<<endl;
            
    }
    void whileLoopHelper(symbolInfo* si){
            assemblyOut<<"\t\t;Line no "<<si->getStartLine()<<endl;

            string levelStart=createLevel();
            string levelEnd=createLevel();

            assemblyOut<<levelStart<<":"<<"\t\t;while loop start"<<endl;
            expression(si->childList[2]);


            assemblyOut<<"\tPOP AX"<<endl<<"\tCMP AX, 0"<<endl<<"\tJE "<<levelEnd<<endl;
            statement(si->childList[4]);
            
            assemblyOut<<"\tJMP "<<levelStart<<endl<<levelEnd<<":"<<endl;

    }
    void statement(symbolInfo* si){
      //assemblyOut<<si->getName()<<endl;
        if(si->getName()=="var_declaration"){

          assemblyOut<< "\t\t;Line no "<<si->getStartLine()<<endl;

          varDeclaration(si->childList[0]);
        }

        else if(si->getName()=="expression_statement"){

          assemblyOut<<"\t\t;Line no "<<si->getStartLine()<<endl;

          expressionStatement(si->childList[0]);
        }

        else if(si->getName()=="PRINTLN LPAREN ID RPAREN SEMICOLON"){
            printLNHelper(si);
        }
        else if(si->getName()=="compound_statement"){
            compoundStatement(si->childList[0]);
        }
        else if(si->getName()=="RETURN expression SEMICOLON"){
            assemblyOut<<"\t\t;Line no "<<si->getStartLine()<<endl;
            expression(si->childList[1]);
            assemblyOut<<"\tPOP AX"<<endl;
            assemblyOut<<"\tJMP "<<returnLevel<<endl;
        }

         else if(si->getName()=="IF LPAREN expression RPAREN statement"){
            ifLRPARENhelper(si);
        }

        else if(si->getName()=="IF LPAREN expression RPAREN statement ELSE statement"){
            ifLRPARENhelperWithElse(si);
        }
         else if(si->getName()=="FOR LPAREN expression_statement expression_statement expression RPAREN statement"){
            forLoopHelper(si);
        }

         else if(si->getName()=="WHILE LPAREN expression RPAREN statement"){
            
            whileLoopHelper(si);
        }

    }

    void ifElseFunction(symbolInfo* si, string nextLevel){
     
        if(si->getName()=="IF LPAREN expression RPAREN statement ELSE statement"){
            expression(si->childList[2]);
            string levelZero=createLevel();
            string levelOne=createLevel();
            assemblyOut<<"\tPOP AX"<<endl<<"\tCMP AX, 0"<<endl<<"\tJNE "<<levelOne<<endl<<"\tJMP "<<levelZero<<endl;
            assemblyOut<<levelOne<<":"<<endl;
            statement(si->childList[4]);
            assemblyOut<<"\tJMP "<<nextLevel<<endl;
            assemblyOut<<levelZero<<":"<<endl;
            ifElseFunction(si->childList[6], nextLevel);
        }
        else if(si->getName()=="IF LPAREN expression RPAREN statement"){
            expression(si->childList[2]);
            assemblyOut<<"\tPOP AX"<<endl<<"\tCMP AX, 0"<<endl<<"\tJE "<<nextLevel<<endl;
            statement(si->childList[4]);
        }
        else{
            statement(si);
        }
    }

    void expressionStatement(symbolInfo* si){
        if(si->childList.size() == 2){
            expression(si->childList[0]);
            assemblyOut<<"\tPOP AX"<<endl;
        }
    }

  int offsetChecker(symbolInfo* si){
    if(si->offset==0) return 0;
    else if(si->offset>1) return 1;
    else return -1;
  }

  void expression(symbolInfo* si){
        if(si->childList.size()== 3){
            string variableName1="";
            
            if((si->childList[0])->childList.size()== 1){
                
                string variableName=((si->childList[0])->childList[0])->getName();
                
                errorFile<<variableName<<endl;
                symbolInfo* si1=st.LookUp(variableName);

              
                int offset=offsetChecker(si1);
                if(offset==0){
                  variableName1=si1->getName();
                }else if(offset==1){
                  variableName1="[BP-"+to_string(si1->offset)+"]";
                }else if(offset==-1){
                  variableName1="[BP+"+to_string((si1->offset)*(-1))+"]";
                }

            }

            else{
                string variableName=((si->childList[0])->childList[0])->getName();
                
                symbolInfo* si1=st.LookUp(variableName);
                expression((si->childList[0])->childList[2]);
                
                assemblyOut<<"\tPOP SI"<<endl;
                assemblyOut<<"\tSHL SI, 1"<<endl;
                int offset=offsetChecker(si1);

                if(offset==0){
                    variableName1=si1->getName()+"[SI]";
                }

                else if(offset==1){
                    
                    assemblyOut<<"\tNEG SI"<<endl;
                    assemblyOut<<"\tADD SI, "<<si1->offset<<endl;
                    variableName1="BP[SI]";
                }

                else if(offset==-1){
                    assemblyOut<<"\tSUB SI, "<<si1->offset<<endl;
                    variableName1="BP[SI]";
                }
            }

            logicExpression(si->childList[2]);
            assemblyOut<<"\tPOP AX"<<endl;
            assemblyOut<<"\tMOV "<<variableName1<<", AX"<<endl;
            assemblyOut<<"\tPUSH AX"<<endl;
        }

        else{
            logicExpression(si->childList[0]);
        }

    }
  
  void logicExpressionHelper(string levelZero,string levelOne,string nextLevel){
                assemblyOut<<"\tPOP AX"<<endl<<"\tCMP AX, 0"<<endl<<"\tJE "<<levelZero<<endl;
                assemblyOut<<levelOne<<":"<<endl;
                assemblyOut<<"\tMOV AX, 1"<<endl<<"\tPUSH AX"<<endl<<"\tJMP "<<nextLevel<<endl;
                assemblyOut<<levelZero<<":"<<endl<<"\tMOV AX, 0"<<endl<<"\tPUSH AX"<<endl;
                assemblyOut<<nextLevel<<":"<<endl;
  }
  void logicExpressionHelperTwo(string levelZero,string levelOne,string nextLevel){
                assemblyOut<<"\tPOP AX"<<endl<<"\tCMP AX, 0"<<endl<<"\tJNE "<<levelOne<<endl;
                assemblyOut<<levelZero<<":"<<endl;
                assemblyOut<<"\tMOV AX, 0"<<endl<<"\tPUSH AX"<<endl<<"\tJMP "<<nextLevel<<endl;
                assemblyOut<<levelOne<<":"<<endl;
                assemblyOut<<"\tMOV AX, 1"<<endl<<"\tPUSH AX"<<endl;
                assemblyOut<<nextLevel<<":"<<endl;
  }

   void logicExpression(symbolInfo* si){
        if(si->childList.size() == 1){
            relExpression(si->childList[0]);
        }
        else{
            relExpression(si->childList[0]);
            string levelZero=createLevel();
            string levelOne=createLevel();
            string nextLevel=createLevel();
            assemblyOut<<"\tPOP AX"<<endl;
            assemblyOut<<"\tCMP AX, 0"<<endl;
            if((si->childList[1])->getName()=="||"){
                assemblyOut<<"\tJNE "<<levelOne<<endl;
                relExpression(si->childList[2]);
                logicExpressionHelper(levelZero,levelOne,nextLevel);   
            }

            else if((si->childList[1])->getName() == "&&"){
                assemblyOut<<"\tJE "<<levelZero<<endl;
                relExpression(si->childList[2]);
                logicExpressionHelperTwo(levelZero,levelOne,nextLevel);
            }
        }
    }
  void relExpressionHelper(string levelZero,string levelOne,string nextLevel){
           assemblyOut<<"\tJMP "<<levelZero<<endl;
            assemblyOut<<levelOne<<":"<<endl;
            assemblyOut<<"\tMOV AX, 1"<<endl<<"\tPUSH AX"<<endl<<"\tJMP "<<nextLevel<<endl;
            assemblyOut<<levelZero<<":"<<endl;
            assemblyOut<<"\tMOV AX, 0"<<endl<<"\tPUSH AX"<<endl;
            assemblyOut<<nextLevel<<":"<<endl;
  }

   void relExpressionPrintJMP(symbolInfo* si,string levelZero,string levelOne,string nextLevel){
        string jump;
            if(si->childList[1]->getName() == "<"){
                jump="\tJL ";
                
            }
            else if(si->childList[1]->getName()== "<="){
                jump="\tJLE ";
                
            }
            else if(si->childList[1]->getName() == ">"){
                jump="\tJG ";

            }
            else if(si->childList[1]->getName()== ">="){
              jump="\tJGE ";
                
            }
            else if(si->childList[1]->getName() == "=="){
              jump="\tJE ";
               
            }
            else if(si->childList[1]->getName() == "!="){
              jump="\tJNE ";
                
            }
            assemblyOut<<jump<<levelOne<<endl;
   }
   void relExpression(symbolInfo* si){
        if(si->childList.size()==1){
            simpleExpression(si->childList[0]);
        }
        else{
            simpleExpression(si->childList[0]);
            simpleExpression(si->childList[2]);
            string levelZero=createLevel();
            string levelOne=createLevel();
            string nextLevel=createLevel();
           
            assemblyOut<<"\tPOP DX"<<endl;
            assemblyOut<<"\tPOP AX"<<endl;
            assemblyOut<<"\tCMP AX, DX"<<endl;

            
            relExpressionPrintJMP(si,levelZero,levelOne,nextLevel);

            relExpressionHelper(levelZero,levelOne,nextLevel);
            
        }
    }

  void simpleExpression(symbolInfo* si){
        bool isOnlyTerm=false;
         if(si->childList.size() == 1){
            isOnlyTerm=true;
        }
        if(isOnlyTerm){
            term(si->childList[0]);
        }
        else{
            simpleExpression(si->childList[0]);
            term(si->childList[2]);
            assemblyOut<<"\tPOP DX"<<endl<<"\tPOP AX"<<endl;
            string op;
            if((si->childList[1])->getName() == "+"){
                op="ADD";
            }else{
                op="SUB";
            }
            
             assemblyOut<<"\t"<<op<<" AX, DX"<<endl;
            assemblyOut<<"\tPUSH AX"<<endl;
        }
    }

    void term(symbolInfo* si){
      bool isOnlyUnary=false;
      if(si->childList.size() == 1){
            isOnlyUnary=true;
      }
        if(isOnlyUnary){
            unaryExpression((si->childList)[0]);
        }
        else{
            term((si->childList)[0]);
            unaryExpression((si->childList)[2]);
            assemblyOut<<"\tPOP CX"<<endl<<"\tPOP AX"<<endl<<"\tCWD"<<endl;
            string op;
            string reg;

            if((si->childList)[1]->getName() == "*"){
                op="MUL";
                reg="AX";
            }

            else if((si->childList[1])->getName() == "/"){
                op="DIV";
                reg="AX";
            }

            else if((si->childList[1])->getName() == "%"){
               op="DIV";
               reg="DX";
            }

            assemblyOut<<"\t"<<op<<" CX"<<endl<<"\tPUSH "<<reg<<endl;
        }
    }

    void unaryExpressionHelper(int levelZero,int levelOne,int nextLevel){
            assemblyOut<<"\tPOP AX"<<endl<<"\tCMP AX, 0"<<endl<<"\tJE "<<levelOne<<endl;
            assemblyOut<<"\tJMP "<<levelZero<<endl<<levelOne<<":"<<endl<<"\tMOV AX, 1"<<endl<<"\tPUSH AX"<<endl;
            assemblyOut<<"\tJMP "<<nextLevel<<endl;
            assemblyOut<<levelZero<<":"<<endl<<"\tMOV AX, 0"<<endl;
            assemblyOut<<"\tPUSH AX"<<endl;
            assemblyOut<<nextLevel<<":"<<endl;
    }

    void unaryExpression(symbolInfo* si){
        if(si->childList.size() == 1){
            factor((si->childList)[0]);
        }

        else if(si->getName() == "ADDOP unary_expression"){
            if(si->childList[0]->getName() == "-"){
                isNegative=true;
            }

            unaryExpression(si->childList[1]);
        }

        else if(si->getName() == "NOT unary_expression"){
            unaryExpression(si->childList[1]);
            string levelZero=createLevel();
            string levelOne=createLevel();
            string nextLevel=createLevel();
        }
    }
    void factorVariableHelper(symbolInfo* si){
      string variableName1="";
            if((si->childList[0])->childList.size() == 1){
                string variableName=((si->childList[0])->childList[0])->getName();
                symbolInfo* si1=st.LookUp(variableName);
                
                
                int offset=offsetChecker(si1);
                if(offset == 0){
                    variableName1=si1->getName();
                }
                else if(offset == 1){
                    variableName1= "[BP-"+to_string(si1->offset)+"]" ;
                }
                else if(offset == -1){
                    variableName1="[BP+"+to_string((si1->offset)*(-1))+"]";
                }
            }
            else{
                string variableName=(si->childList[0]->childList[0])->getName();
                symbolInfo* si1=st.LookUp(variableName);
                expression((si->childList[0])->childList[2]);
                assemblyOut<<"\tPOP SI"<<endl<<"\tSHL SI, 1"<<endl;

                int offset=offsetChecker(si1);
                if(offset == 0){
                    variableName1=si1->getName()+"[SI]";
                }

                else if(offset == 1){
                    assemblyOut<<"\tNEG SI"<<endl<<"\tADD SI, "<<si1->offset<<endl;
                    variableName1="BP[SI]";
                }

                else if(offset == -1){
                    assemblyOut<<"\tSUB SI, "<<si1->offset<<endl;
                    variableName1="BP[SI]";
                }
            }
            assemblyOut<<"\tMOV AX, "<<variableName1<<endl;
            if(isNegative){
                assemblyOut<<"\tNEG AX"<<endl;
                isNegative=false;
            }
            assemblyOut<<"\tPUSH AX"<<endl;
    }

    void factorVariableIncopHelper(symbolInfo* si,bool isIncop){
        string variableName1="";

            if((si->childList[0])->childList.size() == 1){

                string variableName=((si->childList[0])->childList[0])->getName();

                symbolInfo* si1=st.LookUp(variableName);

                
                int offset=offsetChecker(si1);
                
                if(offset == 0){
                    variableName1=si1->getName();
                   

                }

                else if(offset == 1){
                    variableName1="[BP-"+to_string(si1->offset)+"]";
                    
                }

                else if(offset == -1){
                    
                    variableName1="[BP+"+to_string((si1->offset)*(-1))+"]";
                }
            }

            else{
                string variableName=((si->childList[0])->childList[0])->getName();
                symbolInfo* si1=st.LookUp(variableName);
                expression((si->childList[0])->childList[2]);

                assemblyOut<<"\tPOP SI"<<endl<<"\tSHL SI, 1"<<endl;

                int offset=offsetChecker(si1);
                if(offset == 0){

                    variableName1=si1->getName()+"[SI]";
                }

                else if(offset == 1){
                    assemblyOut<<"\tNEG SI"<<endl;
                    assemblyOut<<"\tADD SI, "<<si1->offset<<endl;
                    variableName1="BP[SI]";
                }

                else if(offset == -1){
                    assemblyOut<<"\tSUB SI, "<<si1->offset<<endl;
                    variableName1="BP[SI]";
                }
            }

            assemblyOut<<"\tMOV AX, "<<variableName1<<endl;
            if(isNegative){
                assemblyOut<<"\tNEG AX"<<endl;
                isNegative=false;
            }
            assemblyOut<<"\tPUSH AX"<<endl;
            if(isIncop){
                assemblyOut<<"\tINC AX"<<endl;
            }else{
              assemblyOut<<"\tDEC AX"<<endl;
            }
            
            assemblyOut<<"\tMOV "<<variableName1<<", AX"<<endl;
    }

    void factor(symbolInfo* si){
      if(si->childList[0]->getType() =="CONST_INT"){
        string temp=si->childList[0]->getName();
        assemblyOut<<"\tMOV AX, ";
        assemblyOut<<temp<<endl;
        if(isNegative){
          isNegative=false;
          assemblyOut<<"\tNEG AX"<<endl;
        }
        assemblyOut<<"\tPUSH AX"<<endl;
      }
      else if(si->childList[0]->getType() == "CONST_FLOAT"){
            string temp=si->childList[0]->getName();
            assemblyOut<<"\tMOV AX, ";
            assemblyOut<<temp<<endl;
            if(isNegative){
                isNegative=false;
                assemblyOut<<"\tNEG AX"<<endl;
                
            }
            assemblyOut<<"\tPUSH AX"<<endl;
        }

        else if(si->getName() == "variable"){
            factorVariableHelper(si);
        }

      else if(si->getName() == "variable INCOP"){
            
            factorVariableIncopHelper(si,true);
        }

        else if(si->getName() == "variable DECOP"){

            factorVariableIncopHelper(si,false);
        }

        else if(si->getName() == "LPAREN expression RPAREN"){
            expression(si->childList[1]);
        }

        else if(si->getName() == "ID LPAREN argument_list RPAREN"){
            argumentList(si->childList[2]);
            string temp=(si->childList[0])->getName();
            assemblyOut<<"\tCALL "<<temp<<endl<<"\tPUSH AX"<<endl;
        }
        
     }
    void argumentList(symbolInfo* si){

        if(si->getName() == "arguments"){

            arguments(si->childList[0]);

        }

    }

    void argumentsHelperOne(symbolInfo* si){logicExpression(si->childList[2]);arguments(si->childList[0]);}
    void argumentsHelperTwo(symbolInfo* si){logicExpression(si->childList[0]);}
    void arguments(symbolInfo* si){
        if(si->getName() == "arguments COMMA logic_expression"){
            argumentsHelperOne(si);
        }

        else if(si->getName() == "logic_expression"){
            argumentsHelperTwo(si);
        }
    }

  void dfsUnU(symbolInfo* symbol){
    if(symbol->childList.size()==0) 
      {
        parseTree << symbol->getType() + " "+ symbol->getName() + "<Line: "<< symbol->getStartLine() <<"-"<<symbol->getEndLine()<<">"<<endl;
        return;
      }

    parseTree << symbol->getType() + " "+ symbol->getName() + "<Line: " << symbol->getStartLine()<<"-"<<symbol->getEndLine()<<">"<<endl;

    for(int i=0;i<symbol->childList.size();i++){
      //dfs(symbol->childList[i]);
    }    

  }

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

  void debuggerFlagUpdated(){
      /*symbolInfo* isInsertable=st.LookUp(name);
      if(isInsertable==NULL){
        st.insert(name,"ID");
        symbolInfo* isInsertable=st.LookUp(name);
        isInsertable->setDataTypeOrReturnType(dataType);
        continue;
      }else{
        errorFile<<isInsertable->getName()<<endl;
        errorFile<<st.curScopeTable->id<<endl;
      }*/
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
      
      /*symbolInfo* isInsertable=st.LookUp(name);
      if(isInsertable==NULL){
        st.insert(name,"ID");
        symbolInfo* isInsertable=st.LookUp(name);
        isInsertable->setDataTypeOrReturnType(dataType);
        continue;
      }else{
        errorFile<<isInsertable->getName()<<endl;
        errorFile<<st.curScopeTable->id<<endl;
      }*/

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
        //----
        info->parametersAsSi.push_back(si);
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

%token<symbol> CONST_INT CONST_FLOAT CONST_CHAR  LOWER_THAN_ELSE ID PRINTLN


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
   startAssemble($$);
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

func_definition : type_specifier ID LPAREN parameter_list RPAREN{errorFile<<$4->necessaryList.size()<<"From funcDecBisonButAir"<<endl; defineFunction($2->getName(),$1->getDataTypeOrReturnType(),yylineno,&($4->necessaryList)); } compound_statement{
  $$ = new symbolInfo("type_specifier ID LPAREN parameter_list RPAREN compound_statement","func_definition",$1->getStartLine(),$7->getEndLine());
  $$-> childList.push_back($1);
  $$-> childList.push_back($2);
  $$-> childList.push_back($3);
  $$-> childList.push_back($4);
  $$-> childList.push_back($5); 
  $$->childList.push_back($7);
  errorFile<<$4->necessaryList.size()<<"From funcDecBison"<<endl;
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
  vector<symbolInfo*> temp=$1->necessaryList;
 functionParamList = &temp;
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

  //functionParamList = &($1->necessaryList);
  vector<symbolInfo*> temp=$1->necessaryList;
  functionParamList = &temp;
  paramDeclineNo=yylineno;
  writeLogFile("parameter_list","parameter_list COMMA type_specifier");
  //parseTree<<"it has opened "<<$$->getName()<<endl;
}
| type_specifier ID {
  $$=new symbolInfo("type_specifier ID","parameter_list",$1->getStartLine(),$2->getEndLine());
  $$->childList.push_back($1);
  $$->childList.push_back($2);

  $$->necessaryList.push_back(new symbolInfo($2->getName(),"",$1->getDataTypeOrReturnType()));
  
  vector<symbolInfo*> temp=$$->necessaryList;
  functionParamList = &temp;
  //functionParamList = &($$->necessaryList);
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

compound_statement : LCURL{ st.EnterScope(); st.printAllScopeTable();  declareFuncParamList(functionParamList, paramDeclineNo);} statements RCURL {
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

  if(st.curScopeTable->id == 1){
    ListOfGlobalVar.push_back($3);
  }

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

  if(st.curScopeTable->id == 1){
    ListOfGlobalVar.push_back($3);
  }
}
| ID {
  $$= new symbolInfo("ID","declaration_list",$1->getStartLine(),$1->getEndLine());
  $$->childList.push_back($1);
  writeLogFile("declaration_list","ID");
  $$->necessaryList.push_back($1);

  if(st.curScopeTable->id == 1){
    ListOfGlobalVar.push_back($1);
  }
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
  if(st.curScopeTable->id == 1){
    ListOfGlobalVar.push_back($1);
  }
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
| PRINTLN LPAREN ID RPAREN SEMICOLON {
  $$=new symbolInfo("PRINTLN LPAREN ID RPAREN SEMICOLON","statement",$1->getStartLine(),$5->getEndLine());
  $$->childList.push_back($1);
  $$->childList.push_back($2);
  $$->childList.push_back($3);
  $$->childList.push_back($4);
  $$->childList.push_back($5);

  bool isInserted = st.LookUp($3->getName());

  if(!isInserted){
    writeErrorFile("Undeclared variable "+$3->getName());
  }
  $$->necessaryList=$1->necessaryList;
  writeLogFile("statement","PRINTLN LPAREN ID RPAREN SEMICOLON");
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