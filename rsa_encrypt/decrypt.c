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

#define OPTIONS "i:o:n:vh"

int main(int argc, char **argv) {
    int opt = 0;
    mpz_t n, d;
    mpz_inits(n, d, NULL);
    FILE *indecrypt = stdin; //file versions of the strings below and defaults already asigned
    char *infile = "stdin";
    int i = 0;
    FILE *outdecrypt = stdout;
    char *outfile = "stdout";
    int o = 0;
    FILE *pvfile;
    char *privfile = "rsa.priv";
    int v = 0;
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
                privfile = optarg;
                break;
            case 'v':
                v = 1;
                break;
            case 'h': //usage message
                fprintf(stderr, "Usage: ./decrypt [options]\n");
                fprintf(stderr, "  ./decrypt decrypts an input file using the specified private key file,\n  writing the result to the specified output file.\n");
                fprintf(stderr, "    -i <infile> : Read input from <infile>. Default: standard input.\n");
                fprintf(stderr, "    -o <outfile>: Write output to <outfile>. Default: standard output.\n");
                fprintf(stderr, "    -n <keyfile>: Private key is in <keyfile>. Default: rsa.priv.\n");
                fprintf(stderr, "    -v          : Enable verbose output.\n");
                fprintf(stderr, "    -h          : Display program synopsis and usage.\n");
                return 0;
                break;
        }
    }
    pvfile = fopen(privfile, "r"); //open private key
    if (pvfile == NULL) { //open and check if there is an error
        fprintf(stderr, "File not valid\n");
        return 1;
    } //print error message if unable to open files
    rsa_read_priv(n, d, pvfile);
    if (v == 1) {
        gmp_fprintf(stderr, "n - modulus (%lu bits): %Zd\n", mpz_sizeinbase(n, 2), n);
        gmp_fprintf(stderr, "d - private exponent (%lu bits): %Zd\n", mpz_sizeinbase(d, 2), d);
    }
    if (i == 1) {
        indecrypt = fopen(infile, "r"); //read from infile
	if (indecrypt == NULL) {
	    fprintf(stderr, "File not valid\n");
	    return 1;
	}
    }
    if (o == 1) {
	outdecrypt = fopen(outfile, "w");//write to outfile
	if (outdecrypt == NULL) {
            fprintf(stderr, "File not valid\n");
	    return 1;
	}
    }
    rsa_decrypt_file(indecrypt, outdecrypt, n, d);
    fclose(pvfile);
    if (i == 1){
        fclose(indecrypt);
    }
    if (o == 1){
        fclose(outdecrypt);
    }
    mpz_clears(n, d, NULL);
    return 0;
}

