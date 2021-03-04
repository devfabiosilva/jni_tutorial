#include <string.h>
#include <jni.h>

#define STR_MESSAGE_MAX_SZ (size_t)1024
char str_message[STR_MESSAGE_MAX_SZ];

jint throwExampleNewException(
   JNIEnv *,
   const char *,
   const char *,
   int
);

#define JNI_EXAMPLE_EXCEPTION_CLASS "org/jni/example/exceptions/JniExampleException"
#define JNI_EXAMPLE_UTIL_EXCEPTION(msg, err) throwExampleNewException(env, JNI_EXAMPLE_EXCEPTION_CLASS, msg, err)
#define JNI_EXAMPLE_LANG_EXCEPTION_CLASS "java/lang/Exception"
#define throwExampleError(env, msg) throwExampleNewException(env, JNI_EXAMPLE_LANG_EXCEPTION_CLASS, msg, 0)

#define JNI_EXAMPLE_INIT "<init>"
#define JNI_EXAMPLE_JAVA_LANG_LONG_CLASS "java/lang/Long"
#define JNI_EXAMPLE_JAVA_LANG_LONG_CLASS_SIGNATURE "L"JNI_EXAMPLE_JAVA_LANG_LONG_CLASS";"
#define JNI_EXAMPLE_JAVA_LANG_STRING "java/lang/String"
#define JNI_EXAMPLE_JAVA_LANG_STRING_SIGNATURE "L"JNI_EXAMPLE_JAVA_LANG_STRING";"
#define JNI_EXAMPLE_JAVA_LANG_INTEGER "java/lang/Integer"
#define JNI_EXAMPLE_JAVA_LANG_INTEGER_SIGNATURE "L"JNI_EXAMPLE_JAVA_LANG_INTEGER";"
#define JNI_EXAMPLE_INIT_SIGNATURE "(J)V"

#define C_STR_TO_JAVA_UTF8_ERROR_EXCEPTION "Error when parsing C string to Java UTF-8"

int jni_example_javaUTF8_to_c_char_util(
   const char **,
   size_t *,
   JNIEnv *,
   jstring,
   const char *
);

int jni_example_create_new_java_long(
   JNIEnv *,
   jobject *,
   signed long long int,
   const char *
);

int jni_example_create_new_object_util(
   JNIEnv *,
   jobject *,
   jclass *,
   jmethodID *,
   const char *,
   const char *,
   const char *
);

int jni_example_set_value(
   JNIEnv *,
   jclass,
   jobject,
   jobject,
   const char *,
   const char *,
   const char *
);

