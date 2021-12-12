#include "defs.h"
#include "data.h"
#include "decl.h"

//AST 를 바탕으로 어셈블리 코드 생성
static int genAST(struct ASTnode *n) {
	int leftreg, rightreg;

	// 왼쪽, 오른쪽 subtree 값을 변수에 저장
	if (n->left)
		leftreg = genAST(n->left);
	if (n->right)
		rightreg = genAST(n->right);

	switch(n->op) {
		// op 이 덧셈인 경우
		case A_ADD:
			return cgadd(leftreg, rightreg);
		// op 이 곱셈인 경우
		case A_MULTIPLY:
			return cgmul(leftreg, rightreg);
		// op이 정수인 경우
		case A_INTLIT:
			return cgload(n->intvalue);
		default:
			fprintf(stderr, "Unknown AST operator %d\n", n->op);
			exit(1);
	}
}


// 코드 생성하는 함수:
void generatecode(struct ASTnode *n) {
	int reg;
	cgpreamble();
	reg = genAST(n);
	cgprintint(reg);
	cgpostamble();
	register_count();
}
