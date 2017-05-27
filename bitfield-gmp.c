#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <gmp.h>
#include <bitfield.h>
#include <bitfield-gmp.h>

#if __BYTE_ORDER == __BIG_ENDIAN

#define ENDIAN 1

#else

#define ENDIAN -1

#endif

struct bitfield {               /* defines a bitfield */
        unsigned long *field;
        int size;
};

void bitfield_to_mpz (mpz_t dst, const struct bitfield *src) {
	/* leading zeroes will be lost */
	int bits = bfsize(src);
	int longs = (bits - 1) / (8 * sizeof(unsigned long)) + 1;
	mpz_import (dst, longs, -1, sizeof(unsigned long), ENDIAN, 0, src->field);
}

void mpz_to_bitfield (struct bitfield *dst, const mpz_t src) {
	int bits_available = bfsize(dst);
	int bits_needed = mpz_sizeinbase (src, 2);
	if (bits_needed != bits_available) {
		bfresize(dst, bits_needed);
		bits_available = bits_needed;
	}
	mpz_export (dst->field, NULL, -1, sizeof(unsigned long), ENDIAN, 0, src);
}
