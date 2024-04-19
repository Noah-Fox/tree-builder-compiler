/**
 * File: parse_tree.h
 * 
 * Contains class hierarchy for tree_builder language
*/


#include <map>
#include <string>
#include <set>
#include <algorithm>
#include <iostream>
#include "tree_node.h"

using namespace std;

typedef pair<string,int> intVar;
typedef pair<string,string> stringVar;
typedef map<string,TreeNode*> nodeMap;

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
        NumberVariable(char* id){ varId = id; }
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
    if (f!=NULL) {
      f->evaluate_statement(iv, sv, tree);
    }
    if (r!=NULL) {
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
