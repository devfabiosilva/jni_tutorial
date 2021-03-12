#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

const char *welcome();
int hello_guest_dynamic(char **, const char *);
double add_two_numbers(double, double);
double sub_two_numbers(double, double);
double mult_two_numbers(double, double);
double *div_two_numbers(double *, double);
const char *gen_rand_no_entropy_util(void *, size_t);
const char *random_longint(unsigned long long int *);

