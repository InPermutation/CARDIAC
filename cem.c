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
		assert( (val / 100) == 8);
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
	printf("%03hd\n", val);
}

void fetch() {
	ir = get_mem(pc);
}
void advance() {
	pc++;
}
void execute() {
	switch(ir / 100) {
		default:
			printf("FAIL decode, ir=");
			output(ir);
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
