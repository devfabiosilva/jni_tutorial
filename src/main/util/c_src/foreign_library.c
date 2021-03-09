#include <foreign_library.h>

#define WELCOME_MSG "Welcome. This is a JNI example"
#define HELLO_GUEST_MSG "Hello %s this is a JNI example test. Have a nice day ;)"

void gen_rand_no_entropy_util(void *output, size_t output_len)
{
#ifdef EXAMPLE_WIN
 #error "Windows DLL not implemented yet"
#else
   FILE *f;
   size_t rnd_sz, left;

   if (!(f=fopen("/dev/urandom", "r")))
      return;

   rnd_sz=0;
   left=output_len;

   while ((rnd_sz+=fread(output+rnd_sz, 1, left, f))<output_len)
      left-=rnd_sz;

   fclose(f);
#endif
}

inline const char *welcome()
{
   return WELCOME_MSG;
}

inline int hello_guest_dynamic(char **ret_msg, const char *guest)
{
   return asprintf(ret_msg, HELLO_GUEST_MSG, guest);
}

inline double add_two_numbers(double a, double b)
{
   return a+b;
}

inline double sub_two_numbers(double a, double b)
{
   return a-b;
}

inline double mult_two_numbers(double a, double b)
{
   return a*b;
}

inline double *div_two_numbers(double *a, double b)
{
   if (b==0.0)
      return NULL;

   *a/=b;

   return a;
}

unsigned long long int random_longint()
{
   unsigned long long int val;
   gen_rand_no_entropy_util((void *)&val, sizeof(val));
   return val;
}
