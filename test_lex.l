
%{

#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <algorithm>
#include <cstdlib>

#define TKBNODE 256
#define TKNAME 257
#define TKWEIGHT 258
#define TKSTRING 259
#define TKNUM 260
#define TKISCHILD 261 
#define TKFOR 262
#define TKVAR 263
#define TKINT 264
#define TKIN 265

using namespace std;


int linecount=1;
int indent;
int n;

void ACC(char c)
{
  if (c == '\n')
    {
      linecount++;
    }
}
int line_nmb()
{
  return linecount;
}

%} 

%%
buildnode                    {
                                return TKBNODE;}
name                         {
                                return TKNAME;}
weight                       {
                                return TKWEIGHT;}
isachildof                   {
                                return TKISCHILD;}
for                          {
                                return TKFOR;}
in                           {
                                return TKIN;}
\"[^\"]*\"                     {
                                return TKSTRING; }
[ \t\n\f]                   {ACC(yytext[0]); /* Remove tabs/spaces/newlines */}  
[0-9][0-9]*                 {
                                return TKNUM;}
[a-zA-Z][a-zA-Z_0-9]*    {
                                  return TKVAR;}
[+{},;=\[\]:]               {return yytext[0];}

%%

int yywrap(){
    return true;
}

int main(){
    vector<int> tokens;
    vector<int> allTokens;
    int token = 0;
    token = yylex();
    while(token){
        allTokens.push_back(token);
        tokens.push_back(token);

        token = yylex();
    }

    ofstream outFile;
    outFile.open("scanner_out.txt");
    if (!outFile.fail()){
        for (size_t i = 0; i < tokens.size(); i ++){
            outFile << tokens[i] << " ";
        }
    }
    outFile.close();
}
