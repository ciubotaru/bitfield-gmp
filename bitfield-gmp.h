#include <gmp.h>
#include <bitfield.h>

#ifndef HAVE_BITFIELD_GMP_H
#define HAVE_BITFIELD_GMP_H

void bitfield_to_mpz (mpz_t dst, const struct bitfield *src);

void mpz_to_bitfield (struct bitfield *dst, const mpz_t src);

#endif
