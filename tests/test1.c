#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "bitfield-gmp.h"

int main() {
	int i;
	int len = 80;
	char *msg = "Testing bfsub(), bfcat(), bfshift() and bfshift_ip()";
	char *failed = "[FAIL]";
	char *passed = "[PASS]";
	int dots = len - strlen(msg) - 6;       /* 6 is the length of pass/fail string */
	printf("%s", msg);
	for (i = 0; i < dots; i++) printf(".");

	int bits = 80;
	srand((unsigned)time(NULL));
	struct bitfield *input = bfnew(bits);
	for (i = 0; i < bits - 1; i++) if (rand() % 2) bfsetbit(input, i);
	/**
	 * make sure the last bit is set, because in LSB representation of
	 * integer trailing zeroes will be ignored
	**/
	bfsetbit(input, bits - 1);

	mpz_t input_gmp;
	mpz_init(input_gmp);
	bitfield_to_mpz(input_gmp, input);

	struct bitfield *output = bfnew(80);
	mpz_to_bitfield(output, input_gmp);
	int result = bfcmp(input, output, NULL);
	if (result != 0) {
		printf("%s\n", failed);
		return 1;
	}
	printf("%s\n", passed);
	bfdel(input);
	return 0;
}
