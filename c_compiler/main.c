#include "defs.h"
#define extern_
#include "data.h"
#undef extern_
#include "decl.h"
#include <errno.h>

char *tokstr[] = {"+", "*", "intlit"};

//전역 변수 초기화 
static void init() {
	Line = 1;
	Putback = '\n';
}

// input 파일에서 모든 토큰을 차례로 scan
// 새 토큰이 있는 동안 해당 토큰의 정보 print
static void scanfile() {
        struct token T;

        while(scan(&T)) {
                printf("Token %s", tokstr[T.token]);
                if(T.token == T_INTLIT)
                        printf(", value %d", T.intvalue);
                printf("\n");
        }
}

int main(int argc, char *argv[]) {

	// input 으로 들어온 arg 개수가 2개가 아닌 경우 비정상 exit
	if(argc != 2) {
		fprintf(stderr, "Usage: %s infile\n", argv[0]);
		return 1;
	}

	// 전역변수 초기화
	init();

	// 파일을 열고 Infile 변수에 저장
	// 파일이 열리지 않는 경우 에러 메세지 표시 
	if((Infile = fopen(argv[1], "r")) == NULL) {
		fprintf(stderr, "Unable to open %s: %s\n", argv[1], strerror(errno));
		exit(1);
	}

	scanfile();

	return 0;

}

