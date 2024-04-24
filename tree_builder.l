
%{

/**
 * Lexical analysis
 * Authors: Noah Fox and Kaden Papadatos
*/

#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <algorithm>
#include <cstdlib>
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
buildnode                    {yylval.s_val = strdup(yytext);
                                return TKBNODE;}
name                         {yylval.s_val = strdup(yytext);
                                return TKNAME;}
weight                       {yylval.s_val = strdup(yytext);
                                return TKWEIGHT;}
isachildof                   {yylval.s_val = strdup(yytext);
                                return TKISCHILD;}
in                           {yylval.s_val = strdup(yytext);
                                return TKIN;}
for                          {yylval.s_val = strdup(yytext);
                                return TKFOR;}
\"[^\"]*\"                     {yylval.s_val = strdup(yytext);
                                return TKSTRING; }
[ \t\n\f]                   {ACC(yytext[0]); /* Remove tabs/spaces/newlines */}  
[0-9][0-9]*                 {yylval.s_val = strdup(yytext);
                                return TKNUM;}
[a-zA-Z][a-zA-Z_0-9]*    {yylval.s_val = strdup(yytext);
                                  return TKVAR;}
[+{},;=\[\]:]               {return yytext[0];}

%%

