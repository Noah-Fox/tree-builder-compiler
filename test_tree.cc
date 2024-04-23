/**
 * Test file for using the TreeNode class
*/

#include <iostream>
#include <map>
#include "tree_node.h"

using namespace std;

int main(){
    map<string, TreeNode> nodeMap;

    TreeNode root("root", 1, nodeMap);
    TreeNode a("a", 2, "root", nodeMap);
    TreeNode b("b", 3, "root", nodeMap);
    TreeNode c("c", 4, "a", nodeMap);

    printTree("root", nodeMap);
}
