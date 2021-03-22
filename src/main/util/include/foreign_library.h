#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

/**
 * @file
 * @brief Simple JNI example tutorial documentation title
 * @mainpage Overview
 * @details Example JNI (Java Native Interface) tutorial example
 *
 * # Introduction
 *
 * This tutorial is a simple implementation of a compiled native code and its code is accessed by Java VM.
 *
 * Here you will learn how to implement a simple library _*.so_ for UNIX systems or _*.dll_ for Windows systems and access all resources from JNI
 *
 * # Preparing your environment
 *
 * ## Installing your C compiler:
 *
 * ### Linux
 *
 * You must install your gcc, make, ...
 * TODO
 * ### Mac
 *
 * TODO
 *
 * ### Windows
 */

/**
 * @fn welcome
 * @brief Show Welcome message
 * @retval Welcome message string pointer
 */
const char *welcome();

/**
 * @fn int hello_guest_dynamic(char **ret_msg, const char *guest)
 * @brief Welcome message with a cute greeting ;)
 *
 * @param [out] ret_msg The new pointer allocated dynamically in memory
 * @param [in] guest Input text for the cute greeting. It cannot be _NULL_
 *
 * **WARNING**: Pointer _ret_msg_ must be deallocated in memory when it is not used
 *
 * @retval Size of the greeting text string on success or value is less than zero if error occurs
 */
int hello_guest_dynamic(char **, const char *);

/**
 * @fn double add_two_numbers(double a, double b)
 * @brief This stupid function adds two real numbers
 *
 * @param [in] a Double value _a_
 * @param [in] b Double value _b_
 *
 * @retval The sum of _a_ and _b_
 */
double add_two_numbers(double, double);

/**
 * @fn double sub_two_numbers(double a, double b)
 * @brief This stupid function subtracts two real numbers
 *
 * @param [in] a Double value _a_
 * @param [in] b Double value _b_
 *
 * @retval The subtraction of _a_ and _b_
 */
double sub_two_numbers(double, double);

/**
 * @fn double mult_two_numbers(double a, double b)
 * @brief This stupid function multiplies two real numbers
 *
 * @param [in] a Double value _a_
 * @param [in] b Double value _b_
 *
 * @retval The multiplication of _a_ and _b_
 */
double mult_two_numbers(double, double);

/**
 * @fn double *div_two_numbers(double *a, double b)
 * @brief This stupid function divides two real numbers
 *
 * @param [in] a Double value _a_
 * @param [in] b Double value _b_
 *
 * @retval The pointer of _a_ containing the division of _a_ and _b_ or _NULL_ if divide by zero
 */
double *div_two_numbers(double *, double);

/**
 * @fn const char *gen_rand_no_entropy_util(void *output, size_t output_len)
 * @brief This function generates a random number from PRNG of your OS system
 *
 * @param [out] output Output pointer. It can not be _NULL_
 * @param [in] output_len Size of _output_
 *
 * _output_ will contain _output_len_ random numbers.
 *
 * **WARNING** Don't use this random number generator to generate Bitcoin seed/passwords/private keys because it has no entropy counter. See <a href="https://unix.stackexchange.com/questions/324209/when-to-use-dev-random-vs-dev-urandom">this issue</a> for brief explanation
 *
 * @retval NULL if success or non _NULL_ if error.
 */
const char *gen_rand_no_entropy_util(void *, size_t);

/**
 * @fn const char *random_longint(unsigned long long int *value)
 * @brief This function generates a random unsigned long int value
 *
 * @param [out] value Output unsigned long int pointer. It can not be _NULL_
 *
 * @retval NULL if success or non _NULL_ if error.
 */
const char *random_longint(unsigned long long int *);
