#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

// The range of a WORD needs to hold -999 to 999, at least 11 bits.
typedef int16_t word_t;
// Accumulator can hold -1998 to 1998, which fits in 12 bits.
typedef int16_t acc_t;

word_t memory[100];
word_t ir;
word_t pc = 0;
acc_t acc;

bool paused = true;

word_t truncate(acc_t a) {
	return a % 1000;
}

word_t get_mem(word_t loc) {
	assert(loc >= 0 && loc <= 99);
	return loc == 0 ? 1 : memory[loc];
}

word_t set_mem(word_t loc, word_t val) {
	assert(loc >= 0 && loc <= 99);
	assert(loc != 0);
	if (loc == 99) {
		assert(val >= 0);
		val = 800 + val % 100;
	}
	memory[loc] = val;
}

word_t input() {
	word_t val;
	scanf("%hd", &val);
	assert(val > -1000 && val < 1000);
	return val;
}

void output(word_t val) {
	if (val >= 0) {
		printf("%03hd\n", val);
	} else {
		printf("-%03hd\n", -val);
	}
}

void fetch() {
	ir = get_mem(pc);
}
void advance() {
	pc++;
}
#define INP 0
#define CLA 1
#define ADD 2
#define TAC 3
#define SFT 4
#define OUT 5
#define STO 6
#define SUB 7
#define JMP 8
#define HRS 9
void execute() {
	assert(ir >= 0);
	uint8_t op = ir / 100;
	uint8_t xy = ir % 100;
#ifdef DEBUG
	fprintf(stderr, "pc=%4hd ir=%4hd op=%4hd xy=%4hd acc=%5hd mem[99]=%5hd\n",
		pc, ir, op, xy, acc, memory[99]);
#endif

	switch (op) {
		case INP:
			set_mem(xy, input());
			break;
		case CLA:
			acc = get_mem(xy);
			break;
		case ADD:
			acc = truncate(acc) + get_mem(xy);
			break;
		case TAC:
			if (truncate(acc) < 0) {
				pc = xy;
			}
			break;
		case OUT:
			output(get_mem(xy));
			break;
		case STO:
			set_mem(xy, truncate(acc));
			break;
		case SUB:
			acc = truncate(acc) - get_mem(xy);
			break;
		case JMP:
			set_mem(99, pc);
			pc = xy;
			break;
		case HRS:
			pc = xy;
			paused = true;
			break;
		default:
			fprintf(stderr, "FAIL decode, ir=%03hd\n", ir);
			exit(1);
	}
}

void step() {
	fetch();
	advance();
	execute();
}

int main(int argc, char** argv) {
	paused = false;
	while (!paused) {
		step();
	}
	return 0;
}
