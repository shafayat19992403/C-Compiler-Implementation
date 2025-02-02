%option noyywrap

%x STRING
/*%x SINGLE_LINE_COMMENT*/
/*%x MULTI_LINE_COMMENT*/

%{
  #include <bits/stdc++.h>
  #include "symbolTable.h"
  using namespace std;

  ofstream tokenout;

  symbolTable st(10);
  bool isMultiLineString=false;

  string getEscapeChar(char ch){
	if(ch=='n')
		return "\n";
	else if(ch=='t')
		return "\t";
	else if(ch=='\\')
		return "\\";
	else if(ch=='\'')
		return "\'";
	else if(ch=='a')
		return "\a";
	else if(ch=='f')
		return "\f";
	else if(ch=='r')
	return "\r";
	else if(ch=='b')
		return "\b";
	else if(ch=='v')
		return "\v";
	else if(ch=='0')
		return "\0";
	else if(ch=='\"')
		return "\"";
	else return "Nothing";
}

string str;
string str2;
int startLine;
int line_count=1;
int error_count=0;


void PrintLogFile(int line, string token,string lexeme, bool IsNewline=true){
  /*int l=lexeme.size();
  if(lexeme[l-1]=='\n')
    lexeme[l-1]='\0';*/

  cout<<"Line# "<<line<<": Token <" << token << "> Lexeme " << lexeme <<" found";
  if(IsNewline) cout<<endl;
}

void PrintLogFileError(int line,string error,string lexeme,bool IsNewline=true){
  /*Error at line# 1: TOO_MANY_DECIMAL_POINTS 1.2.345*/
  error_count++;
  cout<<"Error at line# "<<line<<": "<<error<<" "<<lexeme;
  if(IsNewline) cout<<endl;

}

void PrintTokenFile(string token, string lexeme){
  tokenout<<"<" << token <<", "<<lexeme<<">"<<endl;
}
void PrintTokenFile(string token){
  tokenout<< "<" <<token << "> "<<endl;
}


%}

/*pattern=======================*/

WHITESPACE [ \t\f\r\v]+
DIGIT [0-9]
LETTER [a-zA-Z]
LETTER_ [a-zA-Z_]
ESCAPE_CHAR [nt\\'afrbv0]
EXPONENT [eE][+-]?{DIGIT}+
NEWLINE (\r)?\n
CONST_INT [0-9]+
CONST_FLOAT {DIGIT}*(\.{DIGIT}+)?{EXPONENT}?
CONST_CHAR \'[^\\\n\r]\'
CONST_ESCAPE_CHAR \'\\[nt\\'afrbv0]\'
INDENTIFIER [a-zA-Z_][a-zA-Z0-9_]*
SINGLE_COMMENT \/\/(.|(\\{NEWLINE}))*
MULTI_COMMENT (\/\*)([^\*]|\*[^\/])*(\*\/) 

/*ERRORS=========================================================*/
TOO_MANY_DECIMAL_POINTS {DIGIT}*(\.{DIGIT}*)+(\.{DIGIT}*)+{EXPONENT}?
ILLFORMED_NUMBER {DIGIT}*[Ee][+-]?{DIGIT}*(\.{DIGIT}*)+
INVALID_ID_SUFFIX_NUM_PREFIX {CONST_FLOAT}+{INDENTIFIER}+
MULTICHAR_CONST_CHAR \'.[^\'\r\n]+\'
EMPTY_CONST_CHAR \'\'
UNFINISHED_CONST_CHAR \'(\\\')?[^\'\r\n]
UNFINISHED_COMMENT (\/\*)([^\*]|\*[^\/])*



%%
{WHITESPACE} {}
{NEWLINE} {line_count++;}

if {
  string token="IF";
  string keyword="if";
  PrintLogFile(line_count, token, keyword);
  PrintTokenFile(token,keyword);
}

else {
  string token="ELSE";
  string keyword="else";
  PrintLogFile(line_count, token, keyword);
  PrintTokenFile(token,keyword);
}

for {
  string token="FOR";
  string keyword="for";
  PrintLogFile(line_count, token, keyword);
  PrintTokenFile(token,keyword);
}

while {
  string token="WHILE";
  string keyword="while";
  PrintLogFile(line_count, token, keyword);
  PrintTokenFile(token,keyword);
}

do {
  string token="DO";
  string keyword="do";
  PrintLogFile(line_count, token, keyword);
  PrintTokenFile(token,keyword);
}

break {
  string token="BREAK";
  string keyword="break";
  PrintLogFile(line_count, token, keyword);
  PrintTokenFile(token,keyword);
}

int {
  string token="INT";
  string keyword="int";
  PrintLogFile(line_count, token, keyword);
  PrintTokenFile(token,keyword);
}

char {
  string token="CHAR";
  string keyword="char";
  PrintLogFile(line_count, token, keyword);
  PrintTokenFile(token,keyword);
}

float {
  string token="FLOAT";
  string keyword="float";
  PrintLogFile(line_count, token, keyword);
  PrintTokenFile(token,keyword);
}

double {
  string token="DOUBLE";
  string keyword="double";
  PrintLogFile(line_count, token, keyword);
  PrintTokenFile(token,keyword);
}

void {
  string token="VOID";
  string keyword="void";
  PrintLogFile(line_count, token, keyword);
  PrintTokenFile(token,keyword);
}

return {
  string token="RETURN";
  string keyword="return";
  PrintLogFile(line_count, token, keyword);
  PrintTokenFile(token,keyword);
}

switch {
  string token="SWITCH";
  string keyword="switch";
  PrintLogFile(line_count, token, keyword);
  PrintTokenFile(token,keyword);
}

case {
  string token="CASE";
  string keyword="case";
  PrintLogFile(line_count, token, keyword);
  PrintTokenFile(token,keyword);
}

default {
  string token="DEFAULT";
  string keyword="default";
  PrintLogFile(line_count, token, keyword);
  PrintTokenFile(token,keyword);
}
continue {
  string token="CONTINUE";
  string keyword="continue";
  PrintLogFile(line_count, token, keyword);
  PrintTokenFile(token,keyword);
}

{CONST_INT} {
  string number = yytext;
  string token = "CONST_INT";
  PrintLogFile(line_count,token,number);
  PrintTokenFile(token,number); 
}

{CONST_FLOAT} {
  string number = yytext;
  string token = "CONST_FLOAT";
  PrintLogFile(line_count,token,number);
  PrintTokenFile(token,number); 
}

{CONST_CHAR} {
  string character=yytext;
  string token="CONST_CHAR";

  
  string ch="";
  ch+=character[1];
  PrintLogFile(line_count, token, ch);
  /*cout<<" --> " << "<" <<token << ", "<<ch<<">" <<endl<<endl;*/
  PrintTokenFile(token,ch);
}

{CONST_ESCAPE_CHAR} {
  string character=yytext;
  string token="CONST_CHAR";

  string ch=getEscapeChar(character[2]);
  PrintLogFile(line_count,token,ch);
  PrintTokenFile(token,ch);
}

"+"|"-" {
  string oprt=yytext;
  string token="ADDOP";
  PrintLogFile(line_count,token,oprt);
  PrintTokenFile(token,oprt);
}
[*/%] {
  string oprt=yytext;
  string token="MULOP";
  PrintLogFile(line_count,token,oprt);
  PrintTokenFile(token,oprt);
}
"++"|"--" {
  string oprt=yytext;
  string token="INCOP";
  PrintLogFile(line_count,token,oprt);
  PrintTokenFile(token,oprt);
}
\<|"<="|\>|">="|"=="|"!=" {
  string oprt=yytext;
  string token="RELOP";
  PrintLogFile(line_count,token,oprt);
  PrintTokenFile(token,oprt);
}
\= {
  string oprt=yytext;
  string token="ASSIGNOP";
  PrintLogFile(line_count,token,oprt);
  PrintTokenFile(token,oprt);
}
"&&"|"||" {
  string oprt=yytext;
  string token="LOGICOP";
  PrintLogFile(line_count,token,oprt);
  PrintTokenFile(token,oprt);
}
\! {
  string oprt=yytext;
  string token="NOT";
  PrintLogFile(line_count,token,oprt);
  PrintTokenFile(token,oprt);
}
\( {
  string oprt=yytext;
  string token="LPAREN";
  PrintLogFile(line_count,token,oprt);
  PrintTokenFile(token,oprt);
}
\) {
  string oprt=yytext;
  string token="RPAREN";
  PrintLogFile(line_count,token,oprt);
  PrintTokenFile(token,oprt);
}
\{ {
  string oprt=yytext;
  string token="LCURL";
  PrintLogFile(line_count,token,oprt);
  PrintTokenFile(token,oprt);
  st.EnterScope();
}
\} {
  string oprt=yytext;
  string token="RCURL";
  PrintLogFile(line_count,token,oprt);
  PrintTokenFile(token,oprt);
  st.exitScope();
}

\[ {
  string oprt=yytext;
  string token="LSQUARE";
  PrintLogFile(line_count,token,oprt);
  PrintTokenFile(token,oprt);
}
\] {
  string oprt=yytext;
  string token="RSQUARE";
  PrintLogFile(line_count,token,oprt);
  PrintTokenFile(token,oprt);
}
\, {
  string oprt=yytext;
  string token="COMMA";
  PrintLogFile(line_count,token,oprt);
  PrintTokenFile(token,oprt);
}
\; {
  string oprt=yytext;
  string token="SEMICOLON";
  PrintLogFile(line_count,token,oprt);
  PrintTokenFile(token,oprt);
}

{INDENTIFIER} {
  string id=yytext;
  string token="ID";
  PrintLogFile(line_count,token,id);
  PrintTokenFile(token,id);
  bool hasInserted = st.insert(id,token);
  if(hasInserted) st.printAllScopeTable();
}

\" {
  BEGIN STRING;
  startLine=line_count;
  isMultiLineString=false;
  str.clear();
  //str.append(yytext);
  str2.clear();
  str2.append(yytext);
}

<STRING><<EOF>> {
  //cout<<"Error at line no "<<line_count+1 << ": Unterminated string "<<str2<<endl<<endl;
  PrintLogFileError(line_count+1,"UNFINISHED_STRING",str2);
  str.clear();
  str2.clear();
  BEGIN INITIAL;
  return 0;
}

<STRING>{NEWLINE} {
  //cout<<"Error at line no "<<line_count<<": Unterminated string "<<str2<<endl<<endl;
  PrintLogFileError(line_count,"UNFINISHED_STRING",str2);
  str.clear();
  str2.clear();
  line_count++;
  BEGIN INITIAL;
}

<STRING>\" {
  //str.append(yytext);
  str2.append(yytext);
  if(isMultiLineString)
    tokenout<<"<MULTI LINE STRING, "<<str<<">"<<endl;
  else
    tokenout<<"<SINGLE LINE STRING, "<<str<<">"<<endl;

  if(isMultiLineString)
    PrintLogFile(startLine,"MULTI LINE STRING",str2);
  else 
    PrintLogFile(startLine,"SINGLE LINE STRING",str2);

  startLine=0;
  str.clear();
  str2.clear();
  isMultiLineString=false;
  BEGIN INITIAL;
}

<STRING>((\\){NEWLINE}) {
  line_count++;
  str2.append(yytext);
  isMultiLineString=true;
}
<STRING>(\\[nt\\afrbv0\"\']) {
  str2.append(yytext);
  string temp=getEscapeChar(yytext[1]);
  str.append(temp);
}
<STRING>. {
  str.append(yytext);
  str2.append(yytext);
}

{SINGLE_COMMENT} {
  PrintLogFile(line_count,"SINGLE LINE COMMENT",yytext);

  for(int i=0;i<strlen(yytext);i++){
    if(yytext[i]=='\n'){
      line_count++;
    }
  }
}

{MULTI_COMMENT} {
  PrintLogFile(line_count,"MULTI LINE COMMENT",yytext);

  for(int i=0;i<strlen(yytext);i++){
    if(yytext[i]=='\n'){
      line_count++;
    }
  }
}

{TOO_MANY_DECIMAL_POINTS} {
  PrintLogFileError(line_count,"TOO_MANY_DECIMAL_POINTS",yytext);
}
{ILLFORMED_NUMBER} {
  PrintLogFileError(line_count,"ILLFORMED_NUMBER",yytext);
}
{INVALID_ID_SUFFIX_NUM_PREFIX} {
  PrintLogFileError(line_count,"INVALID_ID_SUFFIX_NUM_PREFIX",yytext);
}
{MULTICHAR_CONST_CHAR} {
  PrintLogFileError(line_count,"MULTICHAR_CONST_CHAR",yytext);
}
{EMPTY_CONST_CHAR} {
  PrintLogFileError(line_count,"EMPTY_CONST_CHAR",yytext);
}
{UNFINISHED_CONST_CHAR} {
  PrintLogFileError(line_count,"UNFINISHED_CONST_CHAR",yytext);
}
{UNFINISHED_COMMENT} {
  for(int i=0;i<strlen(yytext);i++){
    if(yytext[i]=='\n') line_count++;
  }
  PrintLogFileError(line_count,"UNFINISHED_COMMENT",yytext);
}

<<EOF>> {
  st.printAllScopeTable();
  cout<<"Total lines: "<<line_count<<endl;
  cout<<"Total errors: "<<error_count<<endl;
  return 0;
}
. {
  PrintLogFileError(line_count,"UNRECOGNIZED_CHAR",yytext);
}
%%

int main(int argc,char *argv[]){
  if(argc != 2){
    cout<<"Please provide input file name and try again."<<endl;
  }

  FILE *fin= freopen(argv[1],"r",stdin);
  if(fin==nullptr){
    cout<<"Can't open specified file."<<endl;
    return 0;
  }
  tokenout.open("token.txt");
  freopen("log.txt","w",stdout);
  yyin = fin;
  yylex();
  fclose(yyin);
  return 0;
}