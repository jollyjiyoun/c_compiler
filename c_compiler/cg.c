#include "defs.h"
#include "data.h"
#include "decl.h"

static int freereg[4];
static char *reglist[4] = {"%r8", "%r9", "%r10", "%r11"};
static int used_reg_count[4];


// 모든 register 를 사용 가능하다는 flag 붙인다.
void freeall_registers(void) {
	freereg[0] = freereg[1] = freereg [2] = freereg[3] = 1;
}

//register 사용 개수 파악하는 변수 초기화
void used_reg_init (void) {
	used_reg_count[0] = used_reg_count[1] = used_reg_count[2] = used_reg_count[3] = 0;
}

// 사용 가능한 register (flag = 1) 를 찾으면 해당 register의 번호를 반환한다.
static int alloc_registers(void) {

	for(int i = 0; i<4; i++) {
		if (freereg[i]) {
			freereg[i] = 0;
			used_reg_count[i] = 1;
			return i;
		}
	}
	
	//register가 없는 경우 
	fprintf(stderr, "out of registers\n");
	exit(1);
}


// 사용을 완료한 register 를 반환한다.
static void free_register(int reg) {
	//비우려는 register 가 사용중이 아닌 경우
	if (freereg[reg] != 0) {
		fprintf(stderr, "Cannot free register %d\n", reg);
		exit(1);
	}
	
	// register를 사용 가능하도록 flag = 1 로 둔다.
	freereg[reg] = 1;
}


//register 설정 초기화
void cgpreamble() {
	//모든 register를 사용 가능하도록 flag 설정한다.
	freeall_registers();

	used_reg_init();

	// 함수의 초기화값 print
	fputs(
		"main:\n"
		"\tpushq\t%rbp\n"
		"\tmovq %rsp, rbp\n",
	Outfile);
}


// register 사용 완료한 후에 print하는 함수
void cgpostamble() {
	fputs(
		"\tmovl $0, %eax\n"
		"\tpopq %rbp\n"
		"\tret\n",
	Outfile);
}


// value 값에 register 하나를 할당한다.
int cgload(int value) {

	// 새 register 하나를 설정해준다.
	int r = alloc_registers();
	fprintf(Outfile, "\tmovq\t$%d, %s\n", value, reglist[r]);
	return r;
}


// 두 값을 더할때, 하나의 register에만 두 값이 저장되므로 나머지 하나의 register는 free한다.
int cgadd(int r1, int r2) {
	fprintf(Outfile, "\taddq\t%s, %s\n", reglist[r1], reglist[r2]);
	free_register(r1);
	return r2;
}


// 두 값을 곱할때, 하나의 register에만 두 값이 저장되므로 나머지 하나의 register는 free한다.
int cgmul(int r1, int r2) {
	fprintf(Outfile, "\timulq\t%s, %s\n", reglist[r1], reglist[r2]);
	free_register(r1);
	return r2;
}


//printint 를 호출한다.
void cgprintint(int r) {
	fprintf(Outfile, "\tmovq\t%s, %%rdi\n", reglist[r]);
	//fprintf(Outfile, "\tcall\tprintint\n");
	free_register(r);
}

//사용된 register 개수 출력
void register_count() {
	int reg_count = 0;
	for(int i=0; i<sizeof(used_reg_count); i++) {
		if (used_reg_count[i] == 1) {
			reg_count +=1;
		}
	}

	fprintf(Outfile, "\n사용된 register 개수: %d 개\n", reg_count);
}
