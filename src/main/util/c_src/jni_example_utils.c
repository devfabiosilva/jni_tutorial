#include <jni_example_utils.h>

#define JNI_EXAMPLE_INIT_THROWABLE_WITH_CODE(class) (*env)->GetMethodID(env, class, "<init>", "(Ljava/lang/String;I)V")

jint throwExampleNewException(
   JNIEnv *env,
   const char *class,
   const char *message,
   int error
)
{
   jint err;
   jclass exClass;
   jmethodID methodId;
   jobject jErrObj;
   jstring errMsg;
   static char err_msg[1024];

   if (!(exClass=(*env)->FindClass(env, class))) {
      if (class==JNI_EXAMPLE_LANG_EXCEPTION_CLASS)
         return 1;

      if (!(exClass=(*env)->FindClass(env, JNI_EXAMPLE_LANG_EXCEPTION_CLASS)))
         return 2;

      sprintf(err_msg, "throwExampleNewException: Class not found '%s' with related message = '%s'", class, message);

      message=err_msg;
   } else if (error) {

      if (!(errMsg=(*env)->NewStringUTF(env, message))) {
         sprintf(err_msg, "throwExampleNewException: Cannot set message '%s' into throwable class '%s' and errcode %d", message, class, error);
         throwExampleError(env, err_msg);
         return 3;
      }

      if (!(methodId=JNI_EXAMPLE_INIT_THROWABLE_WITH_CODE(exClass))) {
         sprintf(err_msg, "throwExampleNewException: Cannot initialize throwable class '%s' with message '%s' and errcode %d", class, message, error);
         throwExampleError(env, err_msg);
         err=4;
         goto throwExampleNewException_EXIT1;
      }

      if (!(jErrObj=(*env)->NewObject(env, exClass, methodId, errMsg, error))) {
         sprintf(err_msg, "throwExampleNewException: Cannot create throwable class '%s' with message '%s' and errcode %d", class, message, error);
         throwExampleError(env, err_msg);
         err=5;
      } else if ((err=(*env)->Throw(env, jErrObj))) {
         (*env)->DeleteLocalRef(env, jErrObj);
         sprintf(err_msg, "throwExampleNewException: Can't throw '%s' with message '%s' and errcode %d", class, message, error);
         throwExampleError(env, err_msg);
      }

throwExampleNewException_EXIT1:
      (*env)->DeleteLocalRef(env, errMsg);

      return err;

   }

   return (*env)->ThrowNew(env, exClass, message);
}

int jni_example_javaUTF8_to_c_char_util(
   const char **c_str,
   size_t *c_str_sz,
   JNIEnv *env,
   jstring str,
   const char *function_name
)
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
      *c_str_sz=(size_t)(*env)->GetStringUTFLength(env, str);

   return 0;
}

int jni_example_create_new_java_long(
   JNIEnv *env,
   jobject *newJavaLongObj,
   signed long long int value,
   const char *function_name
)
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

