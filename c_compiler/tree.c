#include "defs.h"
#include "data.h"
#include "decl.h"

//AST 노드 생성
struct ASTnode *mkastnode(int op, struct ASTnode *left, struct ASTnode *right, int intvalue) {

	struct ASTnode *n;

	n = (struct ASTnode *) malloc(sizeof(struct ASTnode));
	if(n == NULL) {
		fprintf(stderr, "ASTnode create error in mkastnode()\n");
		exit(1);
	}

	n->op = op;
	n->left = left;
	n->right = right;
	n->intvalue = intvalue;

	return n;
}

//AST 노드 leaf 로 생성
struct ASTnode *mkastleaf(int op, int intvalue) {
	return mkastnode(op, NULL, NULL, intvalue);
}

//AST 노드 왼쪽 child 하나 있는거 생성
struct ASTnode *mkastunary(int op, struct ASTnode *left, int intvalue) {
	return mkastnode(op, left, NULL, intvalue);
}
