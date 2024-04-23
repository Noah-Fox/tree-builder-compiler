all: tree_builder

tree_builder: tree_builder.tab.c lex.yy.c parse_tree.h
	echo "\nCOMPILING\n"
	g++ -o tree_builder tree_builder.tab.c -ll
	echo "\nCOMPILING SUCCESSFUL\n"

tree_builder.tab.c: tree_builder.y parse_tree.h
	echo "\nBISONING\n"
	bison tree_builder.y
	cat tree_builder.tab.c | sed 's/  __attribute__ ((__unused__))/\/\/ /g' >temp.cc
	mv temp.cc tree_builder.tab.c
	echo "\nBISONING SUCCESSFUL\n"
	
lex.yy.c: tree_builder.l
	echo "\nFLEXING\n"
	flex tree_builder.l
	echo "\nFLEXING SUCCESSFUL\n"
