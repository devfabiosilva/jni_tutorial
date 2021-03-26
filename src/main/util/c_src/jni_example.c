#include <jni_example_utils.h>
#include <foreign_library.h>

/*
 * Class:     org_jni_example_Main
 * Method:    welcome
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_jni_example_Main_welcome(
   JNIEnv *env,
   jobject thisObj
)
{
   jstring res;

   if (!(res=(*env)->NewStringUTF(env, welcome())))
      throwExampleError(C_STR_TO_JAVA_UTF8_ERROR_EXCEPTION);

   return res;
}

/*
 * Class:     org_jni_example_Main
 * Method:    helloGuest
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_jni_example_Main_helloGuest(
   JNIEnv *env,
   jobject thisObj,
   jstring message
)
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
      throwExampleError(C_STR_TO_JAVA_UTF8_ERROR_EXCEPTION);

   free(c_message_out);

Java_org_jni_example_Main_helloGuest_EXIT1:
   JNI_EXAMPLE_DEREF_UTF8_STR(message, c_message_in);

   return res;
}

/*
 * Class:     org_jni_example_Main
 * Method:    addTwoNumbers
 * Signature: (DD)D
 */
JNIEXPORT jdouble JNICALL Java_org_jni_example_Main_addTwoNumbers(
   JNIEnv *env,
   jobject thisObj,
   jdouble A,
   jdouble B
)
{
   return (jdouble)add_two_numbers((double)A, (double)B);
}

/*
 * Class:     org_jni_example_Main
 * Method:    subTwoNumbers
 * Signature: (DD)D
 */
JNIEXPORT jdouble JNICALL Java_org_jni_example_Main_subTwoNumbers(
   JNIEnv *env,
   jobject thisObj,
   jdouble A,
   jdouble B
)
{
   return (jdouble)sub_two_numbers((double)A, (double)B);
}

/*
 * Class:     org_jni_example_Main
 * Method:    multTwoNumbers
 * Signature: (DD)D
 */
JNIEXPORT jdouble JNICALL Java_org_jni_example_Main_multTwoNumbers(
   JNIEnv *env,
   jobject thisObj,
   jdouble A,
   jdouble B
)
{
   return (jdouble)mult_two_numbers((double)A, (double)B);
}

/*
 * Class:     org_jni_example_Main
 * Method:    divTwoNumbers
 * Signature: (DD)D
 */
JNIEXPORT jdouble JNICALL Java_org_jni_example_Main_divTwoNumbers(
   JNIEnv *env,
   jobject thisObj,
   jdouble A,
   jdouble B
)
{
   double result=(double)A;

   if (div_two_numbers(&result, (double)B))
      return (jdouble)result;

   JNI_EXAMPLE_UTIL_EXCEPTION("divTwoNumbers: Can not divide by ZERO!", 300);

   return 0.0;
}

/*
 * Class:     org_jni_example_Main
 * Method:    javaStringToNativeByte
 * Signature: (Ljava/lang/String;)[B
 */
#define PARROT_MESSAGE "You said the following message: "
#define JAVA_STRING_TO_NATIVE_BYTE_FUNCTION_NAME "javaStringToNativeByte"
JNIEXPORT jbyteArray JNICALL Java_org_jni_example_Main_javaStringToNativeByte(
   JNIEnv *env,
   jclass thisObj,
   jstring message
)
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
      outByteArray=NULL;
      JNI_EXAMPLE_UTIL_EXCEPTION(JAVA_STRING_TO_NATIVE_BYTE_FUNCTION_NAME": Message can not be an empty string", 800);
      goto Java_org_jni_example_Main_javaStringToNativeByte_EXIT1;
   }

   if ((outByteArray=(*env)->NewByteArray(env, sizeof(PARROT_MESSAGE)-1+c_message_in_sz))) {

      (*env)->SetByteArrayRegion(env, outByteArray, 0, sizeof(PARROT_MESSAGE)-1, (const jbyte *)PARROT_MESSAGE);

      if ((*env)->ExceptionCheck(env)) {
         strcpy(str_message, JAVA_STRING_TO_NATIVE_BYTE_FUNCTION_NAME": "ERROR_CANT_WRITE_BYTE_ARRAY);
         goto Java_org_jni_example_Main_javaStringToNativeByte_EXIT2;
      }

      (*env)->SetByteArrayRegion(env, outByteArray, sizeof(PARROT_MESSAGE)-1, c_message_in_sz, (const jbyte *)c_message_in);

      if ((*env)->ExceptionCheck(env)) {
         strcpy(str_message, JAVA_STRING_TO_NATIVE_BYTE_FUNCTION_NAME": "ERROR_CANT_WRITE_BYTE_ARRAY);
         goto Java_org_jni_example_Main_javaStringToNativeByte_EXIT2;
      }

      goto Java_org_jni_example_Main_javaStringToNativeByte_EXIT1;
   }

   throwExampleError(JAVA_STRING_TO_NATIVE_BYTE_FUNCTION_NAME": "ERROR_CANT_CREATE_BYTE_ARRAY);
   goto Java_org_jni_example_Main_javaStringToNativeByte_EXIT1;

Java_org_jni_example_Main_javaStringToNativeByte_EXIT2:
   throwExampleError(str_message);
   (*env)->DeleteLocalRef(env, outByteArray);
   outByteArray=NULL;

Java_org_jni_example_Main_javaStringToNativeByte_EXIT1:
   JNI_EXAMPLE_DEREF_UTF8_STR(message, c_message_in);

   return outByteArray;
}

/*
 * Class:     org_jni_example_Main
 * Method:    nativeRandomNumberGeneratorNoEntropy
 * Signature: (J)[B
 */
#define NATIVE_RANDOM_NUMBER_GENERATOR_MO_ENTROPY_FUNCTION_NAME "nativeRandomNumberGeneratorNoEntropy"
JNIEXPORT jbyteArray JNICALL Java_org_jni_example_Main_nativeRandomNumberGeneratorNoEntropy(JNIEnv *env, jclass thisObject, jlong size)
{
   int err;
   jbyteArray outByteArray;
   unsigned char *rnd;
   const char *p;

   err=0;
   if (size<0)
      sprintf(str_message, NATIVE_RANDOM_NUMBER_GENERATOR_MO_ENTROPY_FUNCTION_NAME": Size value cannot be negative %d", err=900);
   else if (!size)
      sprintf(str_message, NATIVE_RANDOM_NUMBER_GENERATOR_MO_ENTROPY_FUNCTION_NAME": Size cannot be zero %d", err=901);

   if (err) {
      JNI_EXAMPLE_UTIL_EXCEPTION(str_message, err);
      return NULL;
   }

   if (!(outByteArray=(*env)->NewByteArray(env, (jsize)size))) {
      sprintf(str_message, NATIVE_RANDOM_NUMBER_GENERATOR_MO_ENTROPY_FUNCTION_NAME": "ERROR_CANT_CREATE_BYTE_ARRAY". Maybe size %llu is too long",
         (unsigned long long int)size);
      throwExampleError(str_message);
      return NULL;
   }

   if (!(rnd=malloc((size_t)size))) {
      sprintf(str_message, "Can't alloc %llu bytes to store in system memory. Maybe size is too long. Err = %d", (unsigned long long int)size, err=902);
      goto Java_org_jni_example_Main_nativeRandomNumberGeneratorNoEntropy_EXIT1;
   }

   if ((p=gen_rand_no_entropy_util((void *)rnd, (size_t)size))) {
      sprintf(str_message, "gen_rand_no_entropy_util @ "NATIVE_RANDOM_NUMBER_GENERATOR_MO_ENTROPY_FUNCTION_NAME": Can't open file: %s. Err = %d", p, err=903);
      goto Java_org_jni_example_Main_nativeRandomNumberGeneratorNoEntropy_EXIT2;
   }

   (*env)->SetByteArrayRegion(env, outByteArray, 0, (jsize)size, (const jbyte *)rnd);

   if ((*env)->ExceptionCheck(env))
      sprintf(str_message,
         NATIVE_RANDOM_NUMBER_GENERATOR_MO_ENTROPY_FUNCTION_NAME": Can't set random bytes (%llu) at region [%p]. Error = %d",
         (unsigned long long int)size, (void *)outByteArray, err=904);

   memset(rnd, 0, (size_t)size);

Java_org_jni_example_Main_nativeRandomNumberGeneratorNoEntropy_EXIT2:
   free(rnd);

   if (err) {
Java_org_jni_example_Main_nativeRandomNumberGeneratorNoEntropy_EXIT1:
      JNI_EXAMPLE_UTIL_EXCEPTION(str_message, err);
      (*env)->DeleteLocalRef(env, outByteArray);
      return NULL;
   }

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
#define CHECK_CREATE_NEW_EXAMPLE_REGISTRY_INPUTS_ARE_NULL (const char []){\
  PARM_CHECKER_IS_JSTRING,\
  PARM_CHECKER_IS_JAVA_INTEGER,\
  PARM_CHECKER_IS_JSTRING,\
  PARM_CHECKER_END\
}
#define CHECK_CREATE_NEW_EXAMPLE_REGISTRY_INPUTS_ARE_VALID (const char []){\
  PARM_CHECKER_IS_TRUE,\
  PARM_CHECKER_IS_TRUE,\
  PARM_CHECKER_END\
}

JNIEXPORT jobject JNICALL Java_org_jni_example_Main_createNewExampleRegistry(
   JNIEnv *env,
   jclass thisObj, 
   jstring name,
   jobject age,
   jstring occupation
)
{
   int err;
   jobject result, javaLongObject;
   jclass jniClass;
   jmethodID jniMethodId;
   jint c_int_value;
   unsigned long long int random_system_id;
   const char *p;

   if (jni_example_input_parameters_checker_util(
         env,
         CHECK_CREATE_NEW_EXAMPLE_REGISTRY_INPUTS_ARE_NULL,
         name, CREATE_NEW_EXAMPLE_REGISTRY_FUNCTION_NAME": \"name\" field can not be null", 700,
         age, CREATE_NEW_EXAMPLE_REGISTRY_FUNCTION_NAME": \"age\" field can not be null", 702,
         occupation, CREATE_NEW_EXAMPLE_REGISTRY_FUNCTION_NAME": \"occupation\" field can not be null", 703
      )) return NULL;

   if (jni_example_input_parameters_checker_util(
         env,
         CHECK_CREATE_NEW_EXAMPLE_REGISTRY_INPUTS_ARE_VALID,
         (int)((*env)->GetStringUTFLength(env, name)==0), CREATE_NEW_EXAMPLE_REGISTRY_FUNCTION_NAME": \"name\" field can not be an empty string", 701,
         (int)((*env)->GetStringUTFLength(env, occupation)==0), CREATE_NEW_EXAMPLE_REGISTRY_FUNCTION_NAME": \"occupation\" field can not be an empty string", 704
      )) return NULL;

   if ((err=jni_example_get_integer_value(&c_int_value, env, age, CREATE_NEW_EXAMPLE_REGISTRY_FUNCTION_NAME))) {
        JNI_EXAMPLE_UTIL_EXCEPTION(str_message, err);
        return NULL;
   }

   if (c_int_value<0) {
      err=705;
      p=CREATE_NEW_EXAMPLE_REGISTRY_FUNCTION_NAME": \"age\" cannot have negative value";
   } else if (c_int_value<18) {
      err=706;
      p=CREATE_NEW_EXAMPLE_REGISTRY_FUNCTION_NAME": Candidate with \"age\" = must be 18+";
   }

   if (err) {
      JNI_EXAMPLE_UTIL_EXCEPTION(p, err);
      return NULL;
   }

   if ((p=random_longint(&random_system_id))) {
      sprintf(str_message, CREATE_NEW_EXAMPLE_REGISTRY_FUNCTION_NAME": Can't open system ramdom number generator \"%s\".", p);
      JNI_EXAMPLE_UTIL_EXCEPTION(str_message, 705);
      return NULL;
   }

   if ((err=jni_example_create_new_object(&result, &jniClass, &jniMethodId, env, MY_JNI_EXAMPLE_RESGISTRY_CLASS, MY_JNI_EXAMPLE_RESGISTRY_CLASS_SIGNATURE,
      CREATE_NEW_EXAMPLE_REGISTRY_FUNCTION_NAME))) {
      JNI_EXAMPLE_UTIL_EXCEPTION(str_message, err);
      return NULL;
   }

   if ((err=jni_example_create_new_java_long(&javaLongObject, env, (signed long long int)random_system_id, CREATE_NEW_EXAMPLE_REGISTRY_FUNCTION_NAME))) {
      JNI_EXAMPLE_UTIL_EXCEPTION(str_message, err);
      goto Java_org_jni_example_Main_createNewExampleRegistry_EXIT1;
   }

   if ((err=jni_example_set_value(jniClass, result, env, javaLongObject, "id", JNI_EXAMPLE_JAVA_LANG_LONG_CLASS_SIGNATURE,
         CREATE_NEW_EXAMPLE_REGISTRY_FUNCTION_NAME))) {
      JNI_EXAMPLE_UTIL_EXCEPTION(str_message, err);
      goto Java_org_jni_example_Main_createNewExampleRegistry_EXIT2;
   }

   if ((err=jni_example_set_value(jniClass, result, env, name, "name", JNI_EXAMPLE_JAVA_LANG_STRING_SIGNATURE,
         CREATE_NEW_EXAMPLE_REGISTRY_FUNCTION_NAME))) {
      JNI_EXAMPLE_UTIL_EXCEPTION(str_message, err);
      goto Java_org_jni_example_Main_createNewExampleRegistry_EXIT2;
   }

   if ((err=jni_example_set_value(jniClass, result, env, age, "age", JNI_EXAMPLE_JAVA_LANG_INTEGER_SIGNATURE,
         CREATE_NEW_EXAMPLE_REGISTRY_FUNCTION_NAME))) {
      JNI_EXAMPLE_UTIL_EXCEPTION(str_message, err);
      goto Java_org_jni_example_Main_createNewExampleRegistry_EXIT2;
   }

   if ((err=jni_example_set_value(jniClass, result, env, occupation, "occupation", JNI_EXAMPLE_JAVA_LANG_STRING_SIGNATURE,
         CREATE_NEW_EXAMPLE_REGISTRY_FUNCTION_NAME))) JNI_EXAMPLE_UTIL_EXCEPTION(str_message, err);

Java_org_jni_example_Main_createNewExampleRegistry_EXIT2:
   (*env)->DeleteLocalRef(env, javaLongObject);

   if (err) {
Java_org_jni_example_Main_createNewExampleRegistry_EXIT1:
      (*env)->DeleteLocalRef(env, result);
      return NULL;
   }

   return result;

}

