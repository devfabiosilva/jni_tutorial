#include <string.h>
#include <jni.h>
#include <jni_example_exception.h>
#include <foreign_library.h>

#define STR_MESSAGE_MAX_SZ (size_t)768
static char str_message[STR_MESSAGE_MAX_SZ];

#define C_STR_TO_JAVA_UTF8_ERROR_EXCEPTION "Error when parsing C string to Java UTF-8"

int jni_example_javaUTF8_to_c_char_util(const char **c_str, size_t *c_str_sz, JNIEnv *env, jstring str, const char *function_name)
{
   int err;

   if (!str) {
      sprintf(str_message, "jni_example_javaUTF8_to_c_char_util @ %s. Error in JNI example library %d. String can not be NULL", function_name, err=20);
      return err;
   }

   if (!(*c_str=(*env)->GetStringUTFChars(env, str, NULL))) {
      sprintf(str_message, "jni_example_javaUTF8_to_c_char_util @ %s. Error in JNI example library %d. Can't parse Java UTF8 to C char", function_name, err=21);
      return err;
   }

   if (c_str_sz)
      *c_str_sz=strlen(*c_str);

   return 0;
}

/*
 * Class:     org_jni_example_Main
 * Method:    welcome
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_jni_example_Main_welcome(JNIEnv *env, jobject thisObj)
{
   jstring res;

   if (!(res=(*env)->NewStringUTF(env, welcome())))
      throwError(env, C_STR_TO_JAVA_UTF8_ERROR_EXCEPTION);

   return res;
}

/*
 * Class:     org_jni_example_Main
 * Method:    helloGuest
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_jni_example_Main_helloGuest(JNIEnv *env, jobject thisObj, jstring message)
{
   int err;
   jstring res;
   size_t c_message_in_sz;
   const char *c_message_in;
   char *c_message_out;

   if ((err=jni_example_javaUTF8_to_c_char_util(&c_message_in, &c_message_in_sz, env, message, "helloGuest"))) {
      JNI_EXAMPLE_UTIL_EXCEPTION(str_message, err);
      return NULL;
   }

   res=NULL;

   if (!c_message_in_sz) {
      JNI_EXAMPLE_UTIL_EXCEPTION("helloGuest: \"message\" is an empty string!", 100);
      goto Java_org_jni_example_Main_helloGuest_EXIT1;
   }

   if ((err=hello_guest_dynamic(&c_message_out, c_message_in))<0) {
      sprintf(str_message, "hello_guest @ helloGuest: Internal error in foreign library %d", err);
      JNI_EXAMPLE_UTIL_EXCEPTION(str_message, err);
      goto Java_org_jni_example_Main_helloGuest_EXIT1;
   }

   if (!(res=(*env)->NewStringUTF(env, c_message_out)))
      throwError(env, C_STR_TO_JAVA_UTF8_ERROR_EXCEPTION);

   free(c_message_out);

Java_org_jni_example_Main_helloGuest_EXIT1:
   (*env)->ReleaseStringUTFChars(env, message, c_message_in);

   return res;
}

/*
 * Class:     org_jni_example_Main
 * Method:    addTwoNumbers
 * Signature: (DD)D
 */
JNIEXPORT jdouble JNICALL Java_org_jni_example_Main_addTwoNumbers(JNIEnv *env, jobject thisObj, jdouble A, jdouble B)
{
   return (jdouble)add_two_numbers((double)A, (double)B);
}

/*
 * Class:     org_jni_example_Main
 * Method:    subTwoNumbers
 * Signature: (DD)D
 */
JNIEXPORT jdouble JNICALL Java_org_jni_example_Main_subTwoNumbers(JNIEnv *env, jobject thisObj, jdouble A, jdouble B)
{
   return (jdouble)sub_two_numbers((double)A, (double)B);
}

/*
 * Class:     org_jni_example_Main
 * Method:    multTwoNumbers
 * Signature: (DD)D
 */
JNIEXPORT jdouble JNICALL Java_org_jni_example_Main_multTwoNumbers(JNIEnv *env, jobject thisObj, jdouble A, jdouble B)
{
   return (jdouble)mult_two_numbers((double)A, (double)B);
}

/*
 * Class:     org_jni_example_Main
 * Method:    divTwoNumbers
 * Signature: (DD)D
 */
JNIEXPORT jdouble JNICALL Java_org_jni_example_Main_divTwoNumbers(JNIEnv *env, jobject thisObj, jdouble A, jdouble B)
{
   double result=(double)A;

   if (div_two_numbers(&result, B))
      return result;

   JNI_EXAMPLE_UTIL_EXCEPTION("divTwoNumbers: Can not divide by ZERO!", 300);

   return 0.0;
}

/*
 * Class:     org_jni_example_Main
 * Method:    createNewExampleRegistry
 * Signature: (Ljava/lang/String;Ljava/lang/Integer;Ljava/lang/String;)Lorg/jni/example/registry/JniExampleRegistry;
 */
JNIEXPORT jobject JNICALL Java_org_jni_example_Main_createNewExampleRegistry(JNIEnv *env, jclass thisObj, jstring name, jobject age, jstring occupation)
{
   //TODO to be implemented
   return NULL;
}

