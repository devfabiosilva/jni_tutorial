#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

#define WELCOME_MSG "Welcome. This is a JNI example"
#define HELLO_GUEST_MSG "Hello %s this is a JNI example test. Have a nice day ;)"

const char *welcome();
int hello_guest_dynamic(char **, const char *);
double add_two_numbers(double, double);
double sub_two_numbers(double, double);
double mult_two_numbers(double, double);
double *div_two_numbers(double *, double);
unsigned long int random_longint();

