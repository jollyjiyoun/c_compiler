#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

// token 종류 정의 - +, *, 정수
enum {
	T_PLUS, T_STAR, T_INTLIT
};

// token 구조체 정의
struct token {
	int token;
	int intvalue;
};
