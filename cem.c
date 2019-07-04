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

int main(int argc, char** argv) {
	return 0;
}
