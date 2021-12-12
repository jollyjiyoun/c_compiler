#include "defs.h"
#include "data.h"
#include "decl.h"

// input 파일에서 한 character 씩 읽어오기
static int next(void) {
	int c;
	
	// input stream 에서 너무 많이 읽은 경우
	if (Putback) {
		c = Putback;
		Putback = 0;
		return c;
	}
	
	// input 파일에서 한 character 읽기
	c = fgetc(Infile);
	
	// 개행문자 받은 경우 line 변수 증가 (디버깅 위함)
	if ('\n' == c) {
		Line++;
	}

	return c;
}

// 너무 많이 읽어서 putback 하고 싶은 character를 Putback 변수에 저장
static void putback(int c) {
	Putback = c;
}

// 공백 문자 모두 skip 하고 공백이 아닌 문자만 읽음
static int skip(void) {
	int c;

	c = next();
	while(' ' == c || '\t' == c || '\n' == c || '\r' == c || '\f' == c) {
		c = next();
	}
	
	return c;
}

// c 가 digit(0-9) 인 경우, int 로 전환 / digit 아닌 경우 -1 return
static int chrpos(char *s, int c) {
        char *p;

        // 문자열 s ("0123456789") 에서 c가 포함된 위치 return
        // c가 문자열에 포함되어 있지 않으면 NULL return
        p = strchr(s, c);

        return (p? p-s : -1);
}

// digit(0-9) 를 scan 하는 경우, digit이 끝날때까지 다음 character 읽고 int 로 변경
static int scanint(int c) {
        int k, val = 0;

        // next()로 얻은 character가 digit(0-9) 인 경우, int 변환 후 기존 val 변수에 누적해서 더하기
        while((k = chrpos("0123456789", c)) >= 0) {
                val = val * 10 +k;
                c = next();
        }

        // next()로 얻은 character가 digit(0-9)가 아닌 경우, putback에 전달
        putback(c);

        return val;

}

// lexical scanner 구현
// input 파일에서 공백 제외한 다음 character 를 읽어오고 (scan)
// 토큰 구조체 생성하는 작업 (tokenize)
int scan(struct token *t) {
	int c;
	
	// 공백 아닌 다음 character 가져옴
	c = skip();
	
	switch (c) {
		case EOF:
			// 토큰을 찾지 못한 경우 0 return
			return t->token = T_EOF;
		case '+':
			t->token = T_PLUS;
			break;
		case '*':
			t->token = T_STAR;
			break;
		default:
			if(isdigit(c)) {
				t->intvalue = scanint(c);
				t->token = T_INTLIT;
				break;
			}
			
			// valid한 token 이 아닌 경우, 비정상 exit
			printf("Unrecognised character %c on line %d\n", c, Line);
			exit(1);
	}
	
	// 토큰을 찾은 경우 1 return
	return 1;
}	
