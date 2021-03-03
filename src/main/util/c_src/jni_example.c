#include <string.h>
#include <jni.h>
#include <jni_example_exception.h>
#include <foreign_library.h>

#define STR_MESSAGE_MAX_SZ (size_t)1024
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

   if (div_two_numbers(&result, (double)B))
      return result;

   JNI_EXAMPLE_UTIL_EXCEPTION("divTwoNumbers: Can not divide by ZERO!", 300);

   return 0.0;
}

#define JNI_EXAMPLE_INIT "<init>"
#define JNI_EXAMPLE_JAVA_LANG_LONG_CLASS "java/lang/Long"
#define JNI_EXAMPLE_JAVA_LANG_LONG_CLASS_SIGNATURE "L"JNI_EXAMPLE_JAVA_LANG_LONG_CLASS";"
#define JNI_EXAMPLE_JAVA_LANG_STRING "java/lang/String"
#define JNI_EXAMPLE_JAVA_LANG_STRING_SIGNATURE "L"JNI_EXAMPLE_JAVA_LANG_STRING";"
#define JNI_EXAMPLE_JAVA_LANG_INTEGER "java/lang/Integer"
#define JNI_EXAMPLE_JAVA_LANG_INTEGER_SIGNATURE "L"JNI_EXAMPLE_JAVA_LANG_INTEGER";"
#define JNI_EXAMPLE_INIT_SIGNATURE "(J)V"
int jni_example_create_new_java_long(JNIEnv *env, jobject *newJavaLongObj, signed long long int value, const char *function_name)
{
   int err;
   jmethodID methodId;
   jclass javaLongClass;

   *newJavaLongObj=NULL;
   if (!(javaLongClass=(*env)->FindClass(env, JNI_EXAMPLE_JAVA_LANG_LONG_CLASS))) {
      sprintf(str_message, "jni_example_create_new_java_long @ %s. Could not find class \""JNI_EXAMPLE_JAVA_LANG_LONG_CLASS"\". Error = %d",
         function_name, err=500);
      return err;
   }

   if (!(methodId=(*env)->GetMethodID(env, javaLongClass, JNI_EXAMPLE_INIT, JNI_EXAMPLE_INIT_SIGNATURE))) {
      sprintf(str_message, "jni_example_create_new_java_long @ %s. Could not init method with signature \""JNI_EXAMPLE_INIT_SIGNATURE"\". Error = %d",
         function_name, err=501);
      return err;
   }

   err=0;
   if (!(*newJavaLongObj=(*env)->NewObject(env, javaLongClass, methodId, (jlong)value)))
      sprintf(str_message, "jni_example_create_new_java_long @ %s. Could not create new Long object. Error = %d", function_name, err=502);

   return err;
}

int jni_example_create_new_object_util(
   JNIEnv *env,
   jobject *thisNewObject,
   jclass *jniClass,
   jmethodID *jniMethodId,
   const char *class_name,
   const char *signature,
   const char *function_name
)
{
   int err;

   *thisNewObject=NULL;
   *jniMethodId=NULL;

   if (!(*jniClass=(*env)->FindClass(env, class_name))) {
      sprintf(str_message, "jni_example_create_new_object @ %s. Could not find class \"%s\". Error = %d", function_name, class_name, err=400);
      return err;
   }

   if (!(*jniMethodId=(*env)->GetMethodID(env, *jniClass, JNI_EXAMPLE_INIT, signature))) {
      *jniClass=NULL;
      sprintf(str_message, "jni_example_create_new_object @ %s. Could not get method at \"%s\" class. Error = %d", function_name, class_name, err=401);
      return err;
   }

   err=0;
   if (!(*thisNewObject=(*env)->NewObject(env, *jniClass, *jniMethodId))) {
      *jniClass=NULL;
      *jniMethodId=NULL;
      sprintf(str_message, "jni_example_create_new_object @ %s. Could not create new object with \"%s\" class. Error = %d", function_name, class_name, err=402);
   }

   return err;
}

int jni_example_set_value(
   JNIEnv *env,
   jclass destClass,
   jobject destObject,
   jobject sourceObject,
   const char *fieldName,
   const char *signature,
   const char *function_name
)
{
   int err;
   jfieldID field;

   if (!(field=(*env)->GetFieldID(env, destClass, fieldName, signature))) {
      sprintf(str_message, "jni_example_set_value @ %s. Can not get field name \"%s\" in referenced signature \"%s\". JNI Example error = %d", function_name,
         fieldName, signature, err=600);
      return err;
   }

   (*env)->SetObjectField(env, destObject, field, sourceObject);

   err=0;
   if ((*env)->ExceptionCheck(env))
      sprintf(str_message, "jni_example_set_value @ %s. Can not set attribute to \"%s\". Error = %d", function_name, fieldName, err=601);

   return err;
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

