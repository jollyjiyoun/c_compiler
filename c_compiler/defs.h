#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

// token 종류 정의 - +, *, 정수
enum {
	T_EOF, T_PLUS, T_STAR, T_INTLIT
};

// token 구조체 정의
struct token {
	int token;
	int intvalue;
};

// AST 의 노드 정의
enum {
	A_ADD, A_MULTIPLY, A_INTLIT
};

// AST 구조체 정의
struct ASTnode {
	int op;
	struct ASTnode *left;
	struct ASTnode *right;
	int intvalue;
};
