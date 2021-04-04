#include <stdio.h>
#include <asserts.h>
#include <foreign_library.h>
#include <stdint.h>

#define EXPECTED_HELLO_GUEST_MESSAGE "Hello GUEST this is a JNI example test. Have a nice day ;)"
void free_on_error(void *ctx)
{
   printf("\nError when compare result string. Expected \""EXPECTED_HELLO_GUEST_MESSAGE"\" but returned %s\n", (const char *)ctx);
   free(ctx);
}

int main(int argc, char **argv)
{
   int err;
   char *msg=NULL;
   double a, *division_result;
   unsigned long long int random1, random2;
   uint8_t rnd1[64], rnd2[64];

   assert_equal_string(
      "Welcome. This is a JNI example. I hope you enjoy this tutorial",
       welcome(),
       "welcome() desire welcome message is wrong",
       "Testing welcome() message is correct ok"
   );

   assert_equal_double(2.3, add_two_numbers(1.0, 1.3), "Error: Adding two numbers", "Adding two numbers ok");

   assert_equal_double(/*2.*/ 2.3-.3, sub_two_numbers(2.3, 0.3), "Error: Subtract two numbers", "Subtract two numbers ok");

   assert_equal_double(2.2, mult_two_numbers(1.1, 2.0), "Error: Multiply two numbers", "Multiply two numbers ok");

   a=8.4;
   division_result=div_two_numbers(&a, 2);

   assert_not_null(division_result, NULL, NULL, "\"division_result\" is NULL", "\"division_result\" ok");

   assert_equal_double(4.2, *division_result, "Error: Divide two numbers", "Divide two numbers ok");

   a=10.;
   division_result=div_two_numbers(&a, 0);

   assert_null(division_result, NULL, NULL, "\"division_result\" is NOT NULL", "\"division_result\" == NULL -> ok");

   assert_null(
      (void *)random_longint(&random1),
      NULL,
      NULL,
      "\"random_longint()\" error. Expected NULL",
      "Parsing system random long int value to \"random1\" -> ok"
   );

   assert_null(
      (void *)random_longint(&random2),
      NULL,
      NULL,
      "\"random_longint()\" error. Expected NULL 2",
      "Parsing system random long int value to \"random2\" -> ok"
   );

   assert_not_equal_longint(
      (long long int)random1,
      (long long int)random2,
      "Fatal. System random may not working",
      "\"random1\" and \"random2\" are different -> ok"
   );

   assert_null(
      (void *)gen_rand_no_entropy_util(rnd1, sizeof(rnd1)),
      NULL,
      NULL,
      "\"gen_rand_no_entropy_util()\" error. Expected NULL",
      "Parsing system random value to \"rnd1\" -> ok"
   );

   assert_null(
      (void *)gen_rand_no_entropy_util(rnd2, sizeof(rnd2)),
      NULL,
      NULL,
      "\"gen_rand_no_entropy_util()\" error. Expected NULL 2",
      "Parsing system random value to \"rnd2\" -> ok"
   );

   assert_not_equal_byte(
      (void *)rnd1,
      (void *)rnd2,
      sizeof(rnd1),
      NULL,
      NULL,
      "\"rnd1\" is equal to \"rnd2\".",
      "\"rnd1\" and \"rnd2\" are different -> ok"
   );

   assert_false((err=hello_guest_dynamic(&msg, "GUEST"))<0, "hello_guest_dynamic() returned an error (negative value)", "hello_guest_dynamic() passed");

   assert_not_null(msg, NULL, NULL, "\"msg\" returned NULL. It should be NON NULL.", "\"msg\" is NOT NULL (OK)");

   assert_equal_byte(
      (void *)EXPECTED_HELLO_GUEST_MESSAGE,
      (void *)msg,
      (size_t)err,
      free_on_error,
      (void *)msg,
      "\"msg\" string contains wrong string expected in \"hello_guest_dynamic()\".",
      "\"hello_guest_dynamic()\" returned string \""EXPECTED_HELLO_GUEST_MESSAGE"\""
   );

   begin_tests();
   end_tests();
   free(msg);
   return 0;
}

