#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <inttypes.h>
#include <stdbool.h>
#include <time.h>
#include <sys/stat.h>
#include <string.h>
#include <limits.h>
#include <gmp.h>
#include "numtheory.h"
#include "randstate.h"
#include "rsa.h"

#define OPTIONS "i:o:n:vh"

int main(int argc, char **argv) {
    int opt = 0;
    mpz_t n, e, s, user;
    mpz_inits(n, e, s, user, NULL);
    FILE *inencrypt = stdin; //default values already asigned
    char *infile = "stdin";
    int i = 0;
    FILE *outencrypt = stdout;
    char *outfile = "stdout";
    int o = 0;
    FILE *pbfile;
    char *pubfile = "rsa.pub";
    char username[LOGIN_NAME_MAX];
    int v = 0; //verbose starts turned off
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch(opt) {
            case 'i':
                i = 1;
                infile = optarg;
                break;
            case 'o':
                o = 1;
                outfile = optarg;
                break;
            case 'n':
                pubfile = optarg;
                break;
            case 'v':
                v = 1;
                break;
            case 'h': //print usage
                fprintf(stderr, "Usage: ./encrypt [options]\n");
                fprintf(stderr, "  ./encrypt encrypts an input file using the specified public key file,\n  writing the result to the specified output file.\n");
                fprintf(stderr, "    -i <infile> : Read input from <infile>. Default: standard input.\n");
                fprintf(stderr, "    -o <outfile>: Write output to <outfile>. Default: standard output.\n");
                fprintf(stderr, "    -n <keyfile>: Public key is in <keyfile>. Default: rsa.pub.\n");
                fprintf(stderr, "    -v          : Enable verbose output.\n");
                fprintf(stderr, "    -h          : Display program synopsis and usage.\n");
                return 0;
                break;
        }
    }
    pbfile = fopen(pubfile, "r");
    if (pbfile == NULL) { //open and check if there is an error
        fprintf(stderr, "File not valid\n");
        return 1;
    } //print error message if unable to open files
    rsa_read_pub(n, e, s, username, pbfile); //causing a seg_fault for some reason
    if (v == 1) {
        gmp_fprintf(stderr, "username: %s\n", username); 
        gmp_fprintf(stderr, "user signature (%lu bits): %Zd\n", mpz_sizeinbase(s, 2), s);
        gmp_fprintf(stderr, "n - modulus (%lu bits): %Zd\n", mpz_sizeinbase(n, 2), n);
        gmp_fprintf(stderr, "e - public exponent (%lu bits): %Zd\n", mpz_sizeinbase(e, 2), e);
    }
    mpz_set_str(user, username, 62); //convert username to an mpz
    if(rsa_verify(user, s, e, n) == false) { //verify the username
        fprintf(stderr, "Username was not valid/did not verify\n");
        return 1;
    }
    if (i == 1) {
        inencrypt = fopen(infile, "r"); //read from infile
        if (inencrypt == NULL) {
            fprintf(stderr, "File not valid\n");
	    return 1;
        }
    }
    if (o == 1) {
        outencrypt = fopen(outfile, "w");//write to outfile
        if (outencrypt == NULL) {
            fprintf(stderr, "File not valid\n");
	    return 1;
        }
    }
    rsa_encrypt_file(inencrypt, outencrypt, n, e);
    fclose(pbfile);
    if (i == 1) {
        fclose(inencrypt);
    }
    if (o ==1) {
        fclose(outencrypt);
    }
    mpz_clears(n, e, s, user, NULL);
    return 0;
}

