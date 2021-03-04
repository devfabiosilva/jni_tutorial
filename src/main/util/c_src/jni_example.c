#include <jni_example_utils.h>
#include <foreign_library.h>

/*
 * Class:     org_jni_example_Main
 * Method:    welcome
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_jni_example_Main_welcome(JNIEnv *env, jobject thisObj)
{
   jstring res;

   if (!(res=(*env)->NewStringUTF(env, welcome())))
      throwExampleError(env, C_STR_TO_JAVA_UTF8_ERROR_EXCEPTION);

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
      throwExampleError(env, C_STR_TO_JAVA_UTF8_ERROR_EXCEPTION);

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

   if (div_two_numbers(&result, (double)B))
      return result;

   JNI_EXAMPLE_UTIL_EXCEPTION("divTwoNumbers: Can not divide by ZERO!", 300);

   return 0.0;
}

#define PARROT_MESSAGE "You said the following message: "
/*
 * Class:     org_jni_example_Main
 * Method:    javaStringToNativeByte
 * Signature: (Ljava/lang/String;)[B
 */
JNIEXPORT jbyteArray JNICALL Java_org_jni_example_Main_javaStringToNativeByte(JNIEnv *env, jclass thisObj, jstring message)
{
   int err;
   size_t c_message_in_sz;
   const char *c_message_in;
   jbyteArray outByteArray;

   if ((err=jni_example_javaUTF8_to_c_char_util(&c_message_in, &c_message_in_sz, env, message, "javaStringToNativeByte"))) {
      JNI_EXAMPLE_UTIL_EXCEPTION(str_message, err);
      return NULL;
   }

   if (!c_message_in_sz) {
      JNI_EXAMPLE_UTIL_EXCEPTION("javaStringToNativeByte: Message can not be an empty string", 800);
      return NULL;
   }

   if ((outByteArray=(*env)->NewByteArray(env, sizeof(PARROT_MESSAGE)-1+c_message_in_sz))) {
      (*env)->SetByteArrayRegion(env, outByteArray, 0, sizeof(PARROT_MESSAGE)-1, (const jbyte *)PARROT_MESSAGE);
      (*env)->SetByteArrayRegion(env, outByteArray, sizeof(PARROT_MESSAGE)-1, c_message_in_sz, (const jbyte *)c_message_in);
   } else
      throwExampleError(env, "javaStringToNativeByte: Can't create JNI byte array");

   return outByteArray;
}

/*
 * Class:     org_jni_example_Main
 * Method:    createNewExampleRegistry
 * Signature: (Ljava/lang/String;Ljava/lang/Integer;Ljava/lang/String;)Lorg/jni/example/registry/JniExampleRegistry;
 */
#define MY_JNI_EXAMPLE_RESGISTRY_CLASS "org/jni/example/registry/JniExampleRegistry"
#define MY_JNI_EXAMPLE_RESGISTRY_CLASS_SIGNATURE "()V"
#define CREATE_NEW_EXAMPLE_REGISTRY_FUNCTION_NAME "createNewExampleRegistry"
JNIEXPORT jobject JNICALL Java_org_jni_example_Main_createNewExampleRegistry(JNIEnv *env, jclass thisObj, jstring name, jobject age, jstring occupation)
{
   int err;
   jobject result, javaLongObject;
   jclass jniClass;
   jmethodID jniMethodId;

   if (!name) {
      JNI_EXAMPLE_UTIL_EXCEPTION(CREATE_NEW_EXAMPLE_REGISTRY_FUNCTION_NAME": \"name\" field can not be null", 700);
      return NULL;
   }

   if ((*env)->GetStringUTFLength(env, name)==0) {
      JNI_EXAMPLE_UTIL_EXCEPTION(CREATE_NEW_EXAMPLE_REGISTRY_FUNCTION_NAME": \"name\" field can not be an empty string", 701);
      return NULL;
   }

   if (!age) {
      JNI_EXAMPLE_UTIL_EXCEPTION(CREATE_NEW_EXAMPLE_REGISTRY_FUNCTION_NAME": \"age\" field can not be null", 702);
      return NULL;
   }

   if (!occupation) {
      JNI_EXAMPLE_UTIL_EXCEPTION(CREATE_NEW_EXAMPLE_REGISTRY_FUNCTION_NAME": \"occupation\" field can not be null", 703);
      return NULL;
   }

   if ((*env)->GetStringUTFLength(env, occupation)==0) {
      JNI_EXAMPLE_UTIL_EXCEPTION(CREATE_NEW_EXAMPLE_REGISTRY_FUNCTION_NAME": \"occupation\" field can not be an empty string", 704);
      return NULL;
   }

   if ((err=jni_example_create_new_object_util(env, &result, &jniClass, &jniMethodId, MY_JNI_EXAMPLE_RESGISTRY_CLASS, MY_JNI_EXAMPLE_RESGISTRY_CLASS_SIGNATURE,
      CREATE_NEW_EXAMPLE_REGISTRY_FUNCTION_NAME))) {
      JNI_EXAMPLE_UTIL_EXCEPTION(str_message, err);
      return NULL;
   }

   if ((err=jni_example_create_new_java_long(env, &javaLongObject, (signed long long int)random_longint(), CREATE_NEW_EXAMPLE_REGISTRY_FUNCTION_NAME))) {
      JNI_EXAMPLE_UTIL_EXCEPTION(str_message, err);
      goto Java_org_jni_example_Main_createNewExampleRegistry_EXIT1;
   }

   if ((err=jni_example_set_value(env, jniClass, result, javaLongObject, "id", JNI_EXAMPLE_JAVA_LANG_LONG_CLASS_SIGNATURE,
         CREATE_NEW_EXAMPLE_REGISTRY_FUNCTION_NAME))) {
      JNI_EXAMPLE_UTIL_EXCEPTION(str_message, err);
      goto Java_org_jni_example_Main_createNewExampleRegistry_EXIT2;
   }

   if ((err=jni_example_set_value(env, jniClass, result, name, "name", JNI_EXAMPLE_JAVA_LANG_STRING_SIGNATURE,
         CREATE_NEW_EXAMPLE_REGISTRY_FUNCTION_NAME))) {
      JNI_EXAMPLE_UTIL_EXCEPTION(str_message, err);
      goto Java_org_jni_example_Main_createNewExampleRegistry_EXIT2;
   }

   if ((err=jni_example_set_value(env, jniClass, result, age, "age", JNI_EXAMPLE_JAVA_LANG_INTEGER_SIGNATURE,
         CREATE_NEW_EXAMPLE_REGISTRY_FUNCTION_NAME))) {
      JNI_EXAMPLE_UTIL_EXCEPTION(str_message, err);
      goto Java_org_jni_example_Main_createNewExampleRegistry_EXIT2;
   }

   if ((err=jni_example_set_value(env, jniClass, result, occupation, "occupation", JNI_EXAMPLE_JAVA_LANG_STRING_SIGNATURE,
         CREATE_NEW_EXAMPLE_REGISTRY_FUNCTION_NAME))) JNI_EXAMPLE_UTIL_EXCEPTION(str_message, err);

Java_org_jni_example_Main_createNewExampleRegistry_EXIT2:
   (*env)->DeleteLocalRef(env, javaLongObject);

   if (err) {
Java_org_jni_example_Main_createNewExampleRegistry_EXIT1:
      (*env)->DeleteLocalRef(env, result);
      result=NULL;
   }

   return result;

}

