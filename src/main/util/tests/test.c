#include <stdio.h>
#include <asserts.h>
#include <foreign_library.h>
#include <stdint.h>

char *msg=NULL;

#define EXPECTED_HELLO_GUEST_MESSAGE "Hello GUEST this is a JNI example test. Have a nice day ;)"

void abort_fn(void *ctx)
{
   printf("\nAborting. Receiving context pointer (%p) ...\n", ctx);
   printf("\nChecking pointer %p ...", (void *)msg);
   if (msg) {
      printf("\nFreeing msg ...\n");
      free(msg);
   }
}

#define EXPECTED_DEFAULT_MESSAGE "Welcome. This is a JNI example. I hope you enjoy this tutorial"
#define TESTING_FUNCTION_MSG_TITLE "Testing \"%s()\" function ..."
int main(int argc, char **argv)
{
   int err;
   double a, delta=1e-15, *division_result;
   unsigned long long int random1, random2;
   uint8_t rnd1[64], rnd2[64];

   on_abort(abort_fn);

   C_ASSERT_EQUAL_STRING(
      EXPECTED_DEFAULT_MESSAGE,
      welcome(),
      CTEST_SETTER(
         CTEST_TITLE(TESTING_FUNCTION_MSG_TITLE, "welcome"),
         CTEST_ON_SUCCESS("Testing welcome() message is correct ok"),
         CTEST_ON_ERROR("welcome() desire welcome message is wrong")
      )
   )

   C_ASSERT_EQUAL_DOUBLE(
      2.3,
      add_two_numbers(1.0, 1.3),
      delta,
      CTEST_SETTER(
         CTEST_TITLE(TESTING_FUNCTION_MSG_TITLE, "add_two_numbers"),
         CTEST_ON_SUCCESS("Adding two numbers ok"),
         CTEST_ON_ERROR("Error: Adding two numbers")
      )
   )

   C_ASSERT_EQUAL_DOUBLE(
      2.,
      sub_two_numbers(2.3, 0.3),
      delta,
      CTEST_SETTER(
         CTEST_TITLE(TESTING_FUNCTION_MSG_TITLE, "sub_two_numbers"),
         CTEST_ON_SUCCESS("Subtract two numbers ok"),
         CTEST_ON_ERROR("Error: Subtract two numbers")
      )
   )

   C_ASSERT_EQUAL_DOUBLE(
      2.2,
      mult_two_numbers(1.1, 2.0),
      delta,
      CTEST_SETTER(
         CTEST_TITLE(TESTING_FUNCTION_MSG_TITLE, "mult_two_numbers"),
         CTEST_ON_SUCCESS("Multiply two numbers ok"),
         CTEST_ON_ERROR("Error: Multiply two numbers")
      )
   )

   a=8.4;
   division_result=div_two_numbers(&a, 2);

   C_ASSERT_NOT_NULL(
      division_result,
      CTEST_SETTER(
         CTEST_TITLE(TESTING_FUNCTION_MSG_TITLE, "div_two_numbers"),
         CTEST_ON_SUCCESS("\"division_result\" ok"),
         CTEST_ON_ERROR("\"division_result\" is NULL")
      )
   )

   C_ASSERT_EQUAL_DOUBLE(
      4.2,
      *division_result,
      delta,
      CTEST_SETTER(
         CTEST_TITLE(TESTING_FUNCTION_MSG_TITLE, "div_two_numbers"),
         CTEST_ON_SUCCESS("Divide two numbers ok"),
         CTEST_ON_ERROR("Error: Divide two numbers")
      )
   )

   a=10.;
   division_result=div_two_numbers(&a, 0);

   C_ASSERT_NULL(
      division_result,
      CTEST_SETTER(
         CTEST_TITLE(TESTING_FUNCTION_MSG_TITLE, "div_two_numbers"),
         CTEST_ON_SUCCESS("\"division_result\" == NULL -> ok"),
         CTEST_ON_ERROR("\"division_result\" is NOT NULL")
      )
   )

   C_ASSERT_NULL(
      (void *)random_longint(&random1),
      CTEST_SETTER(
         CTEST_TITLE(TESTING_FUNCTION_MSG_TITLE, "random_longint"),
         CTEST_ON_SUCCESS("Parsing system random long int value to \"random1\" -> ok"),
         CTEST_ON_ERROR("\"random_longint()\" error. Expected NULL")
      )
   )

   C_ASSERT_NULL(
      (void *)random_longint(&random2),
      CTEST_SETTER(
         CTEST_TITLE(TESTING_FUNCTION_MSG_TITLE, "random_longint"),
         CTEST_ON_SUCCESS("Parsing system random long int value to \"random2\" -> ok"),
         CTEST_ON_ERROR("\"random_longint()\" error. Expected NULL")
      )
   )

   C_ASSERT_NOT_EQUAL_UNSIGNED_LONG_INT(
      random1,
      random2,
      CTEST_SETTER(
         CTEST_TITLE(TESTING_FUNCTION_MSG_TITLE, "random_longint"),
         CTEST_WARN("Checking if \"random1\" and \"random2\" has different values"),
         CTEST_ON_SUCCESS("\"random1\" and \"random2\" are different -> ok"),
         CTEST_ON_ERROR("Fatal. System random may not working")
      )
   )

   C_ASSERT_NULL(
      (void *)gen_rand_no_entropy_util(rnd1, sizeof(rnd1)),
      CTEST_SETTER(
         CTEST_TITLE(TESTING_FUNCTION_MSG_TITLE, "gen_rand_no_entropy_util"),
         CTEST_ON_SUCCESS("Parsing system random value to \"rnd1\" -> ok"),
         CTEST_ON_ERROR("\"gen_rand_no_entropy_util()\" error. Expected NULL")
      )
   )

   C_ASSERT_NULL(
      (void *)gen_rand_no_entropy_util(rnd2, sizeof(rnd2)),
      CTEST_SETTER(
         CTEST_TITLE(TESTING_FUNCTION_MSG_TITLE, "gen_rand_no_entropy_util"),
         CTEST_ON_SUCCESS("Parsing system random value to \"rnd2\" -> ok"),
         CTEST_ON_ERROR("\"gen_rand_no_entropy_util()\" error. Expected NULL")
      )
   )

  C_ASSERT_NOT_EQUAL_BYTE(
      (void *)rnd1,
      (void *)rnd2,
      sizeof(rnd1),
      CTEST_SETTER(
         CTEST_TITLE(TESTING_FUNCTION_MSG_TITLE, "gen_rand_no_entropy_util"),
         CTEST_ON_SUCCESS("\"rnd1\" and \"rnd2\" are different -> ok"),
         CTEST_ON_ERROR("\"rnd1\" is equal to \"rnd2\".")
      )
   )

   err=hello_guest_dynamic(&msg, "GUEST");

   C_ASSERT_FALSE(
      err<0,
      CTEST_SETTER(
         CTEST_TITLE(TESTING_FUNCTION_MSG_TITLE, "hello_guest_dynamic"),
         CTEST_ON_SUCCESS("hello_guest_dynamic() passed with allocated pointer (%p) with size %d", msg, err+1),
         CTEST_ON_ERROR("hello_guest_dynamic() returned an error (negative value)")
      )
   )

   C_ASSERT_NOT_NULL(
      msg,
      CTEST_SETTER(
         CTEST_TITLE(TESTING_FUNCTION_MSG_TITLE, "hello_guest_dynamic"),
         CTEST_ON_SUCCESS("\"msg\" is NOT NULL (%p)", msg),
         CTEST_ON_ERROR("\"msg\" returned NULL It should be NON NULL.")
      )
   )

   C_ASSERT_EQUAL_STRING(
      EXPECTED_HELLO_GUEST_MESSAGE,
      msg,
      CTEST_SETTER(
         CTEST_TITLE(TESTING_FUNCTION_MSG_TITLE, "hello_guest_dynamic"),
         CTEST_ON_SUCCESS("\"hello_guest_dynamic()\" returned string \"%s\" at (%p)", EXPECTED_HELLO_GUEST_MESSAGE, msg),
         CTEST_ON_ERROR("\"msg\" string contains wrong string expected in \"hello_guest_dynamic()\". msg = %s", msg)
      )
   )

   free(msg);
   end_tests();
   return 0;
}

