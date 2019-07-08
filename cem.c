#include <stdio.h>
#include <assert.h>

short memory[100];
short ir;
short pc;
short acc;

#define truncate(a) (a % 1000)

short get_mem(short loc) {
	assert(loc >= 0 && loc <= 99);
	return loc == 0 ? 1 : memory[loc];
}

void set_mem(short loc, short val) {
	assert(loc >= 1 && loc <= 99);
	if (loc == 99) {
		assert(val >= 0);
		val = 800 + val % 100;
	}
	memory[loc] = val;
}

short input() {
	short val = 0;
	scanf("%hd", &val);
	assert(val > -1000 && val < 1000);
	return val;
}

int step() {
	// fetch
	ir = get_mem(pc);
	// advance
	pc++;
	// decode
	assert(ir >= 0);
	short xy = ir % 100;
#ifdef DEBUG
	fprintf(stderr, "pc=%4hd ir=%4hd xy=%4hd acc=%5hd mem[99]=%5hd\n",
		pc, ir, xy, acc, memory[99]);
#endif
	// execute
	switch (ir / 100) {
		case 0: // INP
			set_mem(xy, input());
			return 1;
		case 1: // CLA
			acc = get_mem(xy);
			return 1;
		case 2: // ADD
			acc = truncate(acc) + get_mem(xy);
			return 1;
		case 3: // TAC
			if (truncate(acc) < 0) {
				pc = xy;
			}
			return 1;
		case 4: // SFT
			while (xy > 10) {
				acc = (acc * 10) % 10000;
				xy -= 10;
			}
			while (xy > 0) {
				acc = acc / 10;
				xy--;
			}
			return 1;

		case 5: // OUT
			xy = get_mem(xy);
			printf(xy >= 0 ? "%03hd\n" : "%04hd\n", xy);
			return 1;
		case 6: // STO
			set_mem(xy, truncate(acc));
			return 1;
		case 7: // SUB
			acc = truncate(acc) - get_mem(xy);
			return 1;
		case 8: // JMP
			set_mem(99, pc);
			pc = xy;
			return 1;
		case 9: // HRS
			pc = xy;
			return 0;
		default:
			fprintf(stderr, "FAIL decode, ir=%03hd\n", ir);
			return -1;
	}
}

int main() {
	while (step() > 0) { }
	return 0;
}
