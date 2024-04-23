/**
 * File: parse_tree.h
 * 
 * Contains class hierarchy for tree_builder language
*/


#include <map>
#include <string>
#include <set>
#include <queue>
#include <algorithm>
#include <iostream>
#include "tree_node.h"

using namespace std;

typedef pair<string,int> intVar;
typedef pair<string,string> stringVar;
typedef map<string,TreeNode> nodeMap;

class NumberExpression {
    public:
        virtual int evaluate_expression(intVar& iv, stringVar& sv, nodeMap& tree) = 0;
};

class NumberConstant: public NumberExpression {
    public:
        NumberConstant(int val){ savedVal = val; }
        virtual int evaluate_expression(intVar& iv, stringVar& sv, nodeMap& tree){ return savedVal; }

    private:
        int savedVal;
};

class NumberVariable: public NumberExpression {
    public: 
        NumberVariable(char* id){ 
            varId = id; 
        }
        void assignVar(intVar& iv){ iv.first = varId; }
        virtual int evaluate_expression(intVar& iv, stringVar& sv, nodeMap& tree){
            if (iv.first == varId){
                return iv.second;
            }
            else {
                return -1;
                //ERROR
            }
        }

    private:
        string varId;
};

class NumberPlusExpression: public NumberExpression {
    public:
        NumberPlusExpression(NumberExpression* l, NumberExpression* r){ left = l; right = r; }
        virtual int evaluate_expression(intVar& iv, stringVar& sv, nodeMap& tree){
            return left -> evaluate_expression(iv,sv,tree) + right -> evaluate_expression(iv,sv,tree);
        }

    private:
        NumberExpression* left;
        NumberExpression* right;
};

class StringExpression {
    public:
        virtual string evaluate_expression(intVar& iv, stringVar& sv, nodeMap& tree) = 0;
};

class StringConstant: public StringExpression {
    public:
        StringConstant(string val){ savedVal = val; }
        virtual string evaluate_expression(intVar& iv, stringVar& sv, nodeMap& tree){ return savedVal; }

    private:
        string savedVal;
};

class StringVariable: public StringExpression {
    public: 
        StringVariable(char* id){ varId = id; }
        void assignVar(stringVar& sv){ sv.first = varId; }
        virtual string evaluate_expression(intVar& iv, stringVar& sv, nodeMap& tree){
            if (sv.first == varId){
                return sv.second;
            }
            else {
                return "";
                //ERROR
            }
        }

    private:
        string varId;
};

class StringPlusExpression: public StringExpression {
    public:
        StringPlusExpression(StringExpression* l, StringExpression* r){ left = l; right = r; }

        virtual string evaluate_expression(intVar& iv, stringVar& sv, nodeMap& tree){
            return left -> evaluate_expression(iv,sv,tree) + right -> evaluate_expression(iv,sv,tree);
        }

    private:
        StringExpression* left;
        StringExpression* right;
};

class StringOfNumber: public StringExpression {
    public:
        StringOfNumber(NumberExpression* n){ numExpr = n; }
        virtual string evaluate_expression(intVar& iv, stringVar& sv, nodeMap& tree){
            return to_string(numExpr -> evaluate_expression(iv, sv, tree));
        }

    private:
        NumberExpression* numExpr;
};

class StringList: public StringExpression {
    public:
        StringList(StringExpression* f, StringList* r){ first = f; rest = r; }
        StringList(StringExpression* f){ first = f; rest = nullptr; }
        virtual string evaluate_expression(intVar& iv, stringVar& sv, nodeMap& tree){
            if (first == nullptr){
                return "";
            }
            string toReturn = first -> evaluate_expression(iv,sv,tree);
            if (toReturn == ""){
                return "";
            }

            if (rest == nullptr){
                first = new StringConstant("");
            }
            else {
                first = new StringConstant(rest -> evaluate_expression(iv,sv,tree));
            }
            return toReturn;
        }

    private:
        StringExpression* first;
        StringList* rest;
};

class Statement {
 public:
  virtual void evaluate_statement(intVar& iv, stringVar& sv, nodeMap& tree) =0;
};

class CompoundStatement: public Statement {
 public:
  CompoundStatement(Statement *first, CompoundStatement *rest) {
    f = first;
    r = rest;
  }
  
  virtual void evaluate_statement(intVar& iv, stringVar& sv, nodeMap& tree) {
    if (f!=nullptr) {
      f->evaluate_statement(iv, sv, tree);
    }
    if (r!=nullptr) {
      r->evaluate_statement(iv, sv, tree);
    }
  }
 private:
  CompoundStatement *r;
  Statement *f;
};


class BuildNodeStatement: public Statement {
    public:
        BuildNodeStatement(StringExpression* n, NumberExpression* w, StringExpression* p){
            name = n;
            weight = w;
            parent = p;
        }

        virtual void evaluate_statement(intVar& iv, stringVar& sv, nodeMap& tree){
            string n = name -> evaluate_expression(iv,sv,tree);
            int w = weight -> evaluate_expression(iv,sv,tree);
            string p = parent -> evaluate_expression(iv,sv,tree);
            TreeNode(n, w, p, tree);
        }

    private:
        StringExpression* name;
        NumberExpression* weight;
        StringExpression* parent;
};

class NumberForStatement: public Statement {
    public:
        NumberForStatement(NumberVariable* n, NumberExpression* s, NumberExpression* e, CompoundStatement* l){
            numVar = n;
            startNum = s;
            endNum = e;
            loopStatement = l;
        }

        virtual void evaluate_statement(intVar& iv, stringVar& sv, nodeMap& tree){
            numVar -> assignVar(iv);
            int start = startNum -> evaluate_expression(iv,sv,tree);
            int end = endNum -> evaluate_expression(iv,sv,tree);
            for (int i = start; i < end; i ++){
                iv.second = i;
                loopStatement -> evaluate_statement(iv,sv,tree);
            }
        }

    private:
        NumberVariable* numVar;
        NumberExpression* startNum;
        NumberExpression* endNum;
        CompoundStatement* loopStatement;
};

class StringForStatement: public Statement {
    public:
        StringForStatement(StringVariable* s, StringList* l, CompoundStatement* ls){
            stringVar = s;
            list = l;
            loopStatement = ls;
        }

        virtual void evaluate_statement(intVar& iv, stringVar& sv, nodeMap& tree){
            stringVar -> assignVar(sv);
            sv.second = list -> evaluate_expression(iv,sv,tree);
            while (sv.second != ""){
                loopStatement -> evaluate_statement(iv,sv,tree);
                sv.second = list -> evaluate_expression(iv,sv,tree);
            }
        }

    private:
        StringVariable* stringVar;
        StringList* list;
        CompoundStatement* loopStatement;
        
};
