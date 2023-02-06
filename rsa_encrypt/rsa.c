#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <gmp.h>
#include "randstate.h"
#include "numtheory.h"

void rsa_make_pub(mpz_t p, mpz_t q, mpz_t n, mpz_t e, uint64_t nbits, uint64_t iters) { //unknown if it works, check random() implementation
    mpz_t leastcm, tmp, tmp2, tmpp, tmpq;
    mpz_inits(leastcm, tmp, tmp2, tmpp, tmpq, NULL);
    uint64_t pbits, qbits;
    while (1) { //nbits is a uint64_t
        pbits = random() % (((3*nbits)/4)-(nbits/4)); //pbits = random number in the range (nbits/4 -- (3*nbits)/4)
	pbits += (nbits/4);
	qbits = nbits-pbits; //qbits is whatever is left, so pbits and qbits add up to nbits
	make_prime(p, pbits, iters); //make p and q, and their product n
	make_prime(q, qbits, iters);
	mpz_mul(n, p, q);
	if (mpz_sizeinbase(n, 2) >= nbits) { //log2(n) >= nbits
	    break;
	}
    } //lcm works for large prime numbers
    mpz_sub_ui(tmpp, p, 1); //tmpp = p -1
    mpz_sub_ui(tmpq, q, 1); //tmpq = q -1
    mpz_mul(tmp, tmpp, tmpq); //tmp = (p-1)*(q-1)
    gcd(tmp2, tmpp, tmpq); //tmp2 = gcd(tmpp, tmpq)
    mpz_fdiv_q(leastcm, tmp, tmp2); //lcm = (p-1)(q-1)/gcd(p-1, q-1)
    while (1) {
        mpz_urandomb(tmp, state, nbits); //tmp = random number of nbits
        gcd(tmp2, tmp, leastcm); //tmp2 = gcd(tmp, leastcm)
        if (mpz_cmp_ui(tmp2, 1) == 0) {
            mpz_set(e, tmp); //set e to the randomly generated number
            break;
        }
    }
    mpz_clears(leastcm, tmp, tmp2, tmpp, tmpq, NULL);
}

void rsa_write_pub(mpz_t n, mpz_t e, mpz_t s, char username[], FILE *pbfile) { //files should be opened and closed in main
    gmp_fprintf(pbfile, "%Zx\n%Zx\n%Zx\n%s\n", n, e, s, username);
}

void rsa_read_pub(mpz_t n, mpz_t e, mpz_t s, char username[], FILE *pbfile) {
    gmp_fscanf(pbfile, "%Zx\n%Zx\n%Zx\n%s\n", n, e, s, username);
}

void rsa_make_priv(mpz_t d, mpz_t e, mpz_t p, mpz_t q) {
    mpz_t tmp, tmp2, tmpp, tmpq, leastcm;
    mpz_inits(tmp, tmp2, tmpp, tmpq, leastcm, NULL);
    mpz_sub_ui(tmpp, p, 1); //tmp = p-1
    mpz_sub_ui(tmpq, q, 1); //tmpq = q-1
    mpz_mul(tmp, tmpp, tmpq); //tmp = (p-1)*(q-1)
    gcd(tmp2, tmpp, tmpq); //tmp2 = gcd(p-1, q-1)
    mpz_fdiv_q(leastcm, tmp, tmp2); //lcm = tmp/tmp2
    mod_inverse(d, e, leastcm);
    mpz_clears(tmp, tmp2, tmpp, tmpq, leastcm, NULL);
}

void rsa_write_priv(mpz_t n, mpz_t d, FILE *pvfile) {
    gmp_fprintf(pvfile, "%Zx\n%Zx\n", n, d);
}

void rsa_read_priv(mpz_t n, mpz_t d, FILE *pvfile) {
    gmp_fscanf(pvfile, "%Zx\n%Zx\n", n, d);
}

void rsa_encrypt(mpz_t c, mpz_t m, mpz_t e, mpz_t n) {
    pow_mod(c, m, e, n);
}

void rsa_encrypt_file(FILE *infile, FILE *outfile, mpz_t n, mpz_t e) {
    mpz_t m, c;
    mpz_inits(m, c, NULL); //assuming that infile and outfile will be opened and closed in main
    uint64_t k = (mpz_sizeinbase(n, 2)-1)/8;
    uint8_t *block = (uint8_t *) malloc(k * sizeof(uint8_t));
    block[0] = 0xFF;
    uint64_t j;
    while (1) { //read from file until you reach the end
        j = fread(&block[1], 1, k-1, infile); //read k-1 bytes and put it in block[1], if k-1 bytes isn't available, it will simply read all up to that point and reach EOF
        mpz_import(m, j+1, 1, 1, 1, 0, block);// j is in bytes, and the size is thus 1=8bits, add 1 to make it the total number k bytes
        rsa_encrypt(c, m, e, n);
        gmp_fprintf(outfile, "%Zx\n", c);
        if(feof(infile)) { //reach end of file (EOF)
            break;
        }
    }
    free(block);
    mpz_clears(m, c, NULL);
}

void rsa_decrypt(mpz_t m, mpz_t c, mpz_t d, mpz_t n) {
    pow_mod(m, c, d, n);
}

void rsa_decrypt_file(FILE *infile, FILE *outfile, mpz_t n, mpz_t d) { //files will have been opened in main, and closed after the function is called
    mpz_t c, m;
    mpz_inits(c, m, NULL);
    uint64_t k = (mpz_sizeinbase(n, 2)-1)/8;
    uint64_t j = 1;
    uint8_t *block = (uint8_t *) malloc(k * sizeof(uint8_t));
    while(1) {
        gmp_fscanf(infile, "%Zx\n", c);
        rsa_decrypt(m, c, d, n); //decrypt c
        mpz_export(block, &j, 1, 1, 1, 0, m); //export m into block
        fwrite(&block[1], 1, j-1, outfile);
        if(feof(infile)) {
            break;
        }
    }
    free(block);
    mpz_clears(c, m, NULL);
}

void rsa_sign(mpz_t s, mpz_t m, mpz_t d, mpz_t n) {
    pow_mod(s, m, d, n);
}

bool rsa_verify(mpz_t m, mpz_t s, mpz_t e, mpz_t n) {
    mpz_t t;
    mpz_init(t);
    pow_mod(t, s, e, n);
    if (mpz_cmp(m, t) == 0) {
        return true;
    }
    else {
        return false;
    }
    mpz_clear(t);
}

