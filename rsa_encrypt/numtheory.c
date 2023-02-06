#include <stdio.h>
#include <stdbool.h>
#include <gmp.h>
#include "randstate.h"

void gcd(mpz_t d, mpz_t a, mpz_t b) { //works
        mpz_t tmp, tmpa, tmpb;
        mpz_inits(tmp, tmpa, tmpb, NULL);
        mpz_set(tmpa, a); //pass by reference instead of pass by value
        mpz_set(tmpb, b);
	while (mpz_cmp_ui(tmpb, 0) != 0) {
	    mpz_set(tmp, tmpb); //tmp = b
	    mpz_mod(tmpb, tmpa, tmpb); //b = a % b
	    mpz_set(tmpa, tmp); //a = tmp
	}
	mpz_set(d, tmpa); //d = a
	mpz_clears(tmp, tmpa, tmpb, NULL);
}

void pow_mod(mpz_t o, mpz_t a, mpz_t d, mpz_t n) { //works
    mpz_t v, p, tmpa, tmpd, tmpn, odd, mul1, mul2; 
    mpz_inits(v, p, tmpa, tmpd, tmpn, odd, mul1, mul2, NULL);
    mpz_set(tmpa, a);
    mpz_set(tmpd, d);
    mpz_set(tmpn, n);
    mpz_set_ui(v, 1); // v = 1
    mpz_set(p, tmpa);//p = a
    while(mpz_cmp_ui(tmpd, 0) > 0) { //d > 0
        mpz_mod_ui(odd, tmpd, 2); //d % 2 ==1
        if (mpz_cmp_ui(odd, 1) == 0) {
            mpz_mul(mul1, v, p); //v = (v*p) % n
            mpz_mod(v, mul1, tmpn);
        }
        mpz_mul(mul2, p, p); //p = (p*p) % n
        mpz_mod(p, mul2, tmpn);
        mpz_fdiv_q_ui(tmpd, tmpd, 2); //d = d/2
    }
    mpz_set(o, v); //o = v
    mpz_clears(v, p, tmpa, tmpd, tmpn, odd, mul1, mul2, NULL);
}

bool is_prime(mpz_t n, uint64_t iters) { //works
    if (mpz_cmp_ui(n, 2) == 0) {
        return true;
    }
    if (mpz_cmp_ui(n, 0) < 0) {
        return false;
    }
    mpz_t tmpy, count, two, j, y, a, i, s, r, mod1, mod2, tmpn, tmpn2, tmps;
    mpz_inits(tmpy, count, two, j, y, a, i, s, r, mod1, mod2, tmpn, tmpn2, tmps, NULL);
    mpz_mod_ui(mod1, n, 2);
    if (mpz_cmp_ui(mod1, 0) == 0) { //if it is even, then it is not a prime number
        return false;
    } 
    mpz_set_ui(two, 2);
    mpz_set_ui(i, 1); //i = 1
    mpz_set_ui(s, 1); //s = 1
    mpz_sub_ui(tmpn, n, 1); //tmpn = n-1
    mpz_sub_ui(tmpn2, n, 3); //tmpn2 = n-3
    mpz_mod(mod1, tmpn, s); //mod1 = n-1 % s
    mpz_set_ui(r, 2); //r =2
    mpz_mod_ui(mod2, r, 2); //mod2 = r % 2
    while(mpz_cmp_ui(mod1, 0) == 0 || mpz_cmp_ui(mod2, 0) == 0) { // loop while n-1 % s == 0 or r % 2 == 0 i.e. r is an even number, i.e. break when r is odd
	mpz_set_ui(tmps, 1); //tmps = 1
	mpz_set_ui(count, 0); // count = 0
	while (mpz_cmp(count, s) < 0){ //tmps = 2^s, i.e. for count = 0; count < s; count +=1
	    mpz_mul_ui(tmps, tmps, 2); 
	    mpz_add_ui(count, count, 1); //count +=1
	}
	mpz_cdiv_q(r, tmpn, tmps); //r = n-1/2^s
	mpz_mod_ui(mod2, r, 2);
	if (mpz_cmp_ui(mod2, 1) == 0) {
	    break;
	}
	mpz_add_ui(s, s, 1); //s += 1
	mpz_mod(mod1, tmpn, s); //mod1 = n-1 % s
    }
    while(mpz_cmp_ui(i, iters) < 0) { //i < iters
        mpz_urandomm(a, state, tmpn2); //choose random number between 2 and n-2, initialized through the function as 0 to n-1
        mpz_add_ui(a, a, 2);
        pow_mod(y, a, r, n); //y = pow_mod(a, r, n)
        if (mpz_cmp_ui(y, 1) != 0 && mpz_cmp(y, tmpn) != 0) { //y != 0 and y != n-1
            mpz_set_ui(j, 1); // j= 1
            mpz_sub_ui(tmps, s, 1); //tmps = s-1
            while (mpz_cmp(j, tmps) <= 0 && mpz_cmp(y, tmpn) != 0) { //j <= s-1 and y != n-1
                mpz_set(tmpy, y);
                pow_mod(y, tmpy, two, n);//pow_mod(y, 2, n)
                if (mpz_cmp_ui(y, 1) == 0){ // y == 1
                    return false;
                }
                mpz_add_ui(j, j, 1); //j += 1
            }
            if (mpz_cmp(y, tmpn) != 0) { //y != n-1
                return false;
            }
        }
        mpz_add_ui(i, i, 1); //i += 1
    }
    mpz_clears(tmpy, count, two, j, y, a, i, s, r, mod1, mod2, tmpn, tmpn2, tmps, NULL);
    return true;
}

void make_prime(mpz_t p, uint64_t bits, uint64_t iters) { //works, double check how the bits are calculated
    mpz_t tmp, count;
    mpz_inits(tmp, count, NULL);
    mpz_set_ui(tmp, 1);
    while (mpz_cmp_ui(count, bits) < 0) { //while count < bits; count +=1
        mpz_mul_ui(tmp, tmp, 2);
        mpz_add_ui(count, count, 1);
    }
    mpz_urandomb(p, state, bits); //random from 0 to 2^bits -1
    mpz_add(p, p, tmp); //add an extra 2^bits so that it is at least bits number of bits
    while(is_prime(p, iters) == false) {
        mpz_urandomb(p, state, bits);
    }
    mpz_clears(tmp, count, NULL);
}

void mod_inverse(mpz_t o, mpz_t a, mpz_t n) { //works
    mpz_t r, rprime, t, tprime, q, tmp, tmp2;
    mpz_inits(r, rprime, t, tprime, q, tmp, tmp2, NULL);
    mpz_set(r, n); // r=n
    mpz_set(rprime, a);// rprime = a
    mpz_set_ui(t, 0); //t = 0
    mpz_set_ui(tprime, 1); //tprime = 1
    while(mpz_cmp_ui(rprime, 0) != 0) { //rprime != 0
        mpz_fdiv_q(q, r, rprime); //q = floor(r/rprime)
        mpz_set(tmp, r); //tmp = r
        mpz_set(r, rprime); //r = rprime
        mpz_mul(tmp2, q, rprime); //tmp2 = q * rprime
        mpz_sub(rprime, tmp, tmp2); //rprime = r(tmp) - tmp2
        mpz_set(tmp, t); //tmp = t
        mpz_set(t, tprime); //t = tprime
        mpz_mul(tmp2, q, tprime); //tmp2 = q * tprime
        mpz_sub(tprime, tmp, tmp2); //tprime = t(tmp) - tmp2(q * tprime)
    }
    if (mpz_cmp_ui(r, 1) > 0) {
        mpz_set_ui(o, 0); //return no inverse and set o to 0 to signify that
    }
    else {
        if (mpz_cmp_ui(t, 0) < 0) { //t < 0
	    mpz_add(t, t, n); // t += n
	}
	mpz_set(o, t); //o = t
    }
    mpz_clears(r, rprime, t, tprime, q, tmp, tmp2, NULL);
}

