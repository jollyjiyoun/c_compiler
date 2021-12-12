#include "defs.h"
#include "data.h"
#include "decl.h"

//AST op 정의
static char *ASTop[] = {"+", "*"};

//AST의 구조를 파악하고 직접 연산을 수행하는 코드
int interpretAST(struct ASTnode *n) {
	int leftval, rightval;

	//왼쪽의 AST를 재귀적으로 구조 파악 및 연산 수행
	if(n->left)
		leftval = interpretAST(n->left);
	//오른쪽의 AST를 재귀적으로 구조 파악 및 연산 수행
	if(n->right)
		rightval = interpretAST(n->right);

	//정수인 경우
	if(n->op == A_INTLIT)
		printf("int %d\n", n->intvalue);

	//n->op가 정수가 아닌 경우, 왼쪽 노드의 값과 오른쪽 노드의 값을 print한다
	else
		printf("%d %s %d\n", leftval, ASTop[n->op], rightval);


	switch(n->op) {
		//덧셈인 경우 덧셈 연산
		case A_ADD:
			printf("%d + %d = %d\n", leftval, rightval, leftval+rightval);
			return leftval + rightval;
		//곱셈인 경우 곱셈 연산
		case A_MULTIPLY:
			printf("%d * %d = %d\n", leftval, rightval, leftval*rightval);
			return leftval * rightval;
		//정수인 경우, 정수를 반환
		case A_INTLIT:
			return n->intvalue;

		default:
			fprintf(stderr, "Unknown AST operator %d\n", n->op);
			exit(1);
	}
}

		
