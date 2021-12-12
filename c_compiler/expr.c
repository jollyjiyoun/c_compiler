#include "defs.h"
#include "data.h"
#include "decl.h"

// scanner에서 생성한 op 토큰(+, *)을 AST 노드에 매핑시키는 함수
int arithop(int tok) {
	switch(tok) {
		case T_PLUS:
			return A_ADD;
		case T_STAR:
			return A_MULTIPLY;
		default:
			fprintf(stderr, "unknown token in arithop() on line %d\n", Line);
			exit(1);
	}
}

// input 토큰이 op 토큰이 아니라 정수로 들어오는 경우
static struct ASTnode *primary(void) {
	struct ASTnode *n;

	switch(Token.token) {
		// 들어오는 토큰값이 정수인 경우, leaf node로 생성
		case T_INTLIT:
			n = mkastleaf(A_INTLIT, Token.intvalue);
			printf("made token leaf %d\n", Token.intvalue);
			// 다음 토큰 스캔
			scan(&Token);
			return n;
		default:
			fprintf(stderr, "syntax error on line %d\n", Line);
			exit(1);
	}
}


struct ASTnode *additive_expr(void);


struct ASTnode *multiplicative_expr(void) {
	struct ASTnode *left, *right;
	int tokentype;

	// scan 한 현재 토큰이 정수인 경우, leaf 노드 생성
	left = primary();

	// primary() 에서 새로 스캔한 토큰 type 저장
	tokentype = Token.token;

	// 토큰이 end of file 인 경우 left 을 return 한다.
	if(tokentype == T_EOF)
		return left;
	
	// 현재의 op 토큰이 곱셈(*)인 경우
	while(tokentype == T_STAR) {
		// 다음 토큰을 스캔한다.
		scan(&Token);
		// 스캔한 정수 토큰을 leaf 노드로 생성
		right = primary();

		// 위에서 정의한 left 토큰, right 토큰을 현재의 토큰 타입으로 묶어서 left 에 넘겨준다.
		left = mkastnode(arithop(tokentype), left, right, 0);

		tokentype = Token.token;
		//새로 스캔한 토큰이 end of file 인 경우 멈춘다.
		if(tokentype == T_EOF)
			break;
	}

	//left 토큰, right 토큰을 묶은 left tree 를 반환한다.
	return left;
}


// root 가 + 인 AST tree 생성
struct ASTnode *additive_expr(void) {
	struct ASTnode *left, *right;
	int tokentype;

	// 현재 node 의 op type가 + 인 경우, left 및 right에 우선권을 준다.
	left = multiplicative_expr();
	
	tokentype = Token.token;
	//end of file 접근하면 left 만 반환한다.
	if(tokentype ==T_EOF)
		return left;

	while(1) {
		scan(&Token);
	
		// 현재 node 의 op type가 + 인 경우, left 및 right에 우선권을 준다.	
		right = multiplicative_expr();
		// left, right subtree 을 + 로 연결한다.
		left = mkastnode(arithop(tokentype), left, right, 0);

		tokentype = Token.token;

		if(tokentype == T_EOF)
			break;

	}

	return left;
}

		


//root 가 op 토큰인 AST tree 생성
struct ASTnode *binexpr(void) {
	// 낮은 우선순위 tree로 시작한다.
	return additive_expr();
}

