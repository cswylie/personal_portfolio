#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <inttypes.h>
#include <stdbool.h>
#include <time.h>
#include <sys/stat.h>
#include <string.h>
#include <gmp.h>
#include "numtheory.h"
#include "randstate.h"
#include "rsa.h"

#define OPTIONS "b:i:n:d:s:vh"

int main(int argc, char **argv) {
    int opt = 0;
    mpz_t p, q, e, n, d, user, sign;
    mpz_inits(p, q, e, n, d, user, sign, NULL);
    uint64_t minbits = 1024; //default values already asigned
    uint64_t bittarget;
    uint64_t iter = 50;
    uint64_t itertarget;
    FILE *pbfile;
    FILE *pvfile;
    char *pubfile = "rsa.pub";
    char *privfile = "rsa.priv";
    uint64_t seed = time(NULL);
    uint64_t seedtarget;
    int verbose = 0; //verbose starts off
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
            case 'b':
                bittarget = strtoul(optarg, NULL, 10);
                if (bittarget > 0) {
                    minbits = bittarget;
                }
                else {
                    return 1;
                }
                break;
            case 'i':
                itertarget = strtoul(optarg, NULL, 10);
                if (itertarget > 0) {
                    iter = itertarget;
                }
                else {
                    return 1;
                }
                break;
            case 'n':
                pubfile = optarg;
                break;
            case 'd':
                privfile = optarg;
                break;
            case 's':
                seedtarget = strtoul(optarg, NULL, 10);
                if (seedtarget > 0 && seedtarget < 10000000000) {
                    seed = seedtarget;
                }
                else {
                    return 1;
                }
                break;
            case 'v':
                verbose = 1;
                break;
            case 'h':
                fprintf(stderr, "Usage: ./keygen [options]\n");
                fprintf(stderr, "  ./keygen generates a public / private key pair, placing the keys into the public and private\n  key files as specified below. The keys have a modulus (n) whose length is specified in\n  the program options.\n");
                fprintf(stderr, "    -s <seed>   : Use <seed> as the random number seed. Default: time()\n");
                fprintf(stderr, "    -b <bits>   : Public modulus n must have at least <bits> bits. Default: 1024\n");
                fprintf(stderr, "    -i <iters>  : Run <iters> Miller-Rabin iterations for primality testing. Default: 50\n");
                fprintf(stderr, "    -n <pbfile> : Public key file is <pbfile>. Default: rsa.pub\n");
                fprintf(stderr, "    -d <pvfile> : Private key file is <pvfile>. Default: rsa.priv\n");
                fprintf(stderr, "    -v          : Enable verbose output.\n");
                fprintf(stderr, "    -h          : Display program synopsis and usage.\n");
                return 0;
                break;
        }
    }
    pbfile = fopen(pubfile, "w");
    if (pbfile == NULL) { //open and check if there is an error
        fprintf(stderr, "File not valid\n");
        return 1;
    } //print error message if unable to open files
    pvfile = fopen(privfile, "w");
    if (pvfile == NULL) {
        fprintf(stderr, "File not valid\n");
        return 1;
    }
    int filedesc = fileno(pvfile);
    fchmod(filedesc, 0600); //make private file only accesible to the user
    randstate_init(seed);
    rsa_make_pub(p, q, n, e, minbits, iter); //generate public key
    rsa_make_priv(d, e, p, q); //generate private key
    char *username = getenv("USER"); //get username from currently logged in user
    mpz_set_str(user, username, 62); //set username to mpz
    rsa_sign(sign, user, d, n); //calculate signature
    rsa_write_pub(n, e, sign, username, pbfile); //write to pub and priv
    rsa_write_priv(n, d, pvfile);
    if (verbose == 1) { //verbose output
        gmp_fprintf(stderr, "username: %s\n", username); 
        gmp_fprintf(stderr, "user signature (%lu bits): %Zd\n", mpz_sizeinbase(sign, 2), sign);
        gmp_fprintf(stderr, "p (%lu bits): %Zd\n", mpz_sizeinbase(p, 2), p);
        gmp_fprintf(stderr, "q (%lu bits): %Zd\n", mpz_sizeinbase(q, 2), q);
        gmp_fprintf(stderr, "n - modulus (%lu bits): %Zd\n", mpz_sizeinbase(n, 2), n);
        gmp_fprintf(stderr, "e - public exponent (%lu bits): %Zd\n", mpz_sizeinbase(e, 2), e);
        gmp_fprintf(stderr, "d - private exponent (%lu bits): %Zd\n", mpz_sizeinbase(d, 2), d);
    }
    fclose(pbfile);
    fclose(pvfile);
    randstate_clear();
    mpz_clears(p, q, e, n, d, user, sign, NULL);
    return 0;
}

