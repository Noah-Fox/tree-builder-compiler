%start start_var
%token TKBNODE TKNAME TKWEIGHT TKSTRING TKNUM TKISCHILD TKFOR TKVAR TKIN
%token '{' '}' '=' '"' ';' '[' ']' ':' ',' '+'


%{
#include <map>
#include <string>
#include "parse_tree.h"
#include "tree_node.h"

using namespace std;

%}

%union {
  char* s_val;
  NumberExpression *num_ptr;
  StringExpression *string_ptr;
  StringList *string_list;
  Statement *s_ptr;
  CompoundStatement *c_ptr;
}

%{
extern int yylex();
extern void yyerror(char *String);  

#include <iostream>
 using namespace std;

%}

%type <s_val> TKSTRING TKVAR TKNUM
%type <num_ptr> number_expression
%type <string_ptr> string_expression 
%type <string_list> string_list
%type <s_ptr> statement for_statement build_node_statement
%type <c_ptr> prog start_var in_statement

%%
start_var : prog { // At this point, the 
                   // the program is done --- let's evaluate the
                   // program
                   nodeMap tree;
                   TreeNode root("PROGRAM_ROOT", 0, tree);
                   intVar iv;
                   stringVar sv;
                   $$= $1;
                   $1->evaluate_statement(iv,sv,tree);
                   for (size_t i = 0; i < tree["PROGRAM_ROOT"].children.size(); i ++){
                    printTree(tree["PROGRAM_ROOT"].children[i],tree);
                   }

}

prog: statement  prog {$$ = new CompoundStatement($1,$2);}
    | {$$ = NULL;}
    ;
statement: build_node_statement {$$ = $1;}
         | for_statement {$$ = $1;}
         ;
build_node_statement: TKBNODE '{' TKNAME '=' string_expression ';' TKWEIGHT '=' number_expression ';' '}' ';' {
                            $$ = new BuildNodeStatement($5, $9, new StringConstant("PROGRAM_ROOT"));
}
                    | TKBNODE '{' TKNAME '=' string_expression ';' TKWEIGHT '=' number_expression ';' TKISCHILD '=' string_expression ';' '}' ';' {
                            $$ = new BuildNodeStatement($5, $9, $13);
}
                    ;
string_expression: TKSTRING { $$ = new StringConstant($1); }
                 | number_expression { $$ = new StringOfNumber($1); }
                 | string_expression '+' string_expression { $$ = new StringPlusExpression($1,$3); }
                 | TKVAR { $$ = new StringVariable($1); }
                 ;
number_expression: TKNUM { $$ = new NumberConstant(atoi($1)); }
                 | TKVAR { $$ = new NumberVariable($1); }
                 | number_expression '+' number_expression { $$ = new NumberPlusExpression($1, $3); }
                 ;
for_statement: TKFOR TKVAR TKIN '[' number_expression ':' number_expression ']' '{' in_statement '}' ';' {
                    $$ = new NumberForStatement(new NumberVariable($2), $5, $7, $10);
}
             | TKFOR TKVAR TKIN '[' string_list ']' '{' in_statement '}' ';' {
                $$ = new StringForStatement(new StringVariable($2), $5, $8);
             }
             ;
in_statement: build_node_statement in_statement { $$ = new CompoundStatement($1, $2); }
            | { $$ = NULL; }
            ;
string_list: string_expression { $$ = new StringList($1); }
           | string_expression ',' string_list { $$ = new StringList($1, $3); }
           ;




%%
#include "lex.yy.c"

void yyerror(char *error_string)
{
  cout << "Error : " << error_string << "  on line " << line_nmb() << endl;
  exit(-1);
}


main() {
  yyparse();
}
