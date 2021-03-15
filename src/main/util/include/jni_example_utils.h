#include <string.h>
#include <jni.h>

/**
 * @def STR_MESSAGE_MAX_SZ
 * @brief Global Notification throwable message size.
 */
#define STR_MESSAGE_MAX_SZ (size_t)1024

/**
 * @def STR_MESSAGE_MAX_SZ
 * @brief Global Notification throwable message. Message string SHOULD NOT be greater than _STR_MESSAGE_MAX_SZ - 1_
 */
char str_message[STR_MESSAGE_MAX_SZ];

/**
 * @fn jint throwExampleNewException(JNIEnv *env, const char *class, const char *message, int error)
 * @brief Throws custom throwable error in JVM
 *
 * @param [in] env Java environment
 * @param [in] class Classname of your custom error class or Exception or Throwable
 * @param [in] message Error message to be thrown
 * @param [in] error Error code. If 0 it is omitted
 *
 * @see JNI_EXAMPLE_UTIL_EXCEPTION
 * @see throwExampleError
 *
 * @retval 0 if success otherwise error
 */
jint throwExampleNewException(
   JNIEnv *,
   const char *,
   const char *,
   int
);

#define JNI_EXAMPLE_EXCEPTION_CLASS "org/jni/example/exceptions/JniExampleException"
#define JNI_EXAMPLE_UTIL_EXCEPTION(msg, err) throwExampleNewException(env, JNI_EXAMPLE_EXCEPTION_CLASS, msg, err)
#define JNI_EXAMPLE_LANG_EXCEPTION_CLASS "java/lang/Exception"
#define throwExampleError(msg) throwExampleNewException(env, JNI_EXAMPLE_LANG_EXCEPTION_CLASS, msg, 0)

#define JNI_EXAMPLE_INIT "<init>"
#define JNI_EXAMPLE_JAVA_LANG_LONG_CLASS "java/lang/Long"
#define JNI_EXAMPLE_JAVA_LANG_LONG_CLASS_SIGNATURE "L"JNI_EXAMPLE_JAVA_LANG_LONG_CLASS";"
#define JNI_EXAMPLE_JAVA_LANG_STRING "java/lang/String"
#define JNI_EXAMPLE_JAVA_LANG_STRING_SIGNATURE "L"JNI_EXAMPLE_JAVA_LANG_STRING";"
#define JNI_EXAMPLE_JAVA_LANG_INTEGER "java/lang/Integer"
#define JNI_EXAMPLE_JAVA_LANG_INTEGER_SIGNATURE "L"JNI_EXAMPLE_JAVA_LANG_INTEGER";"
#define JNI_EXAMPLE_INIT_SET_LONG_SIGNATURE "(J)V"

#define C_STR_TO_JAVA_UTF8_ERROR_EXCEPTION "JNI example error. Parsing C string to Java UTF-8"
#define ERROR_CANT_CREATE_BYTE_ARRAY "JNI example error. Can't create byte array"
#define ERROR_CANT_WRITE_BYTE_ARRAY "JNI example error. Can't write byte array in allocated memory space"

#define JNI_EXAMPLE_DEREF_UTF8_STR(str, c_str) (*env)->ReleaseStringUTFChars(env, str, c_str)

/**
 * @fn int jni_example_javaUTF8_to_c_char_util(
 *   const char **c_str, size_t *c_str_sz, JNIEnv *env, jstring str, const char *function_name
 *  )
 *
 * @brief Parses Java UTF-8 string to C char
 *
 * @param [out] c_str Pointer of output C char string containing _NULL_ char at the end
 * @param [out] c_str_sz Pointer of size of C char string (not including _NULL_ char). It can be NULL
 * @param [in] env Java environment
 * @param [in] str Java with UTF-8 encoded string
 * @param [in] function_name Parent function name
 *
 * @retval 0 if success otherwise error if non zero
 *
 * **NOTICE** If error occurs _str_message_ will contain the reason of the error to be thrown in JVM
 *
 * **WARNING** You must dereference _c_str_ in Java VM. @see JNI_EXAMPLE_DEREF_UTF8_STR
 */
int jni_example_javaUTF8_to_c_char_util(
   const char **,
   size_t *,
   JNIEnv *,
   jstring,
   const char *
);

/**
 * @fn int jni_example_create_new_java_long(
 *         jobject *newJavaLongObj,
 *         JNIEnv *env,
 *         signed long long int value,
 *         const char *function_name
 *      )
 *
 * @brief Creates a new Java Long object with C signed long int value
 *
 * @param [out] newJavaLongObj Pointer containing a new Java Long with _value_
 * @param [in] env Java environment
 * @param [in] value Signed long int value
 * @param [in] function_name Parent function name
 *
 * @retval 0 if success otherwise error if non zero
 *
 * **NOTICE** If error occurs _str_message_ will contain the reason of the error to be thrown in JVM
 */
int jni_example_create_new_java_long(
   jobject *,
   JNIEnv *,
   signed long long int,
   const char *
);

/**
 * @fn int jni_example_create_new_object(
 *         jobject *thisNewObject,
 *         jclass *jniClass,
 *         jmethodID *jniMethodId,
 *         JNIEnv *env,
 *         const char *class_name,
 *         const char *signature,
 *         const char *function_name
 *      )
 *
 * @brief Creates a new Java object
 *
 * @param [out] thisNewObject Pointer containing a new Java object. It can be _NULL_
 * @param [out] jniClass Pointer of the Java class. It cannot be _NULL_
 * @param [out] jniMethodId Pointer of the Java method id. It cannot be _NULL_
 * @param [in] env Java environment
 * @param [in] class_name Classpath of Java class
 * @param [in] signature Signature of the object
 * @param [in] function_name Parent function name
 *
 * @retval 0 if success otherwise error if non zero
 *
 * **NOTICE** If error occurs _str_message_ will contain the reason of the error to be thrown in JVM
 */
int jni_example_create_new_object(
   jobject *,
   jclass *,
   jmethodID *,
   JNIEnv *,
   const char *,
   const char *,
   const char *
);

/**
 * @fn int jni_example_set_value(
 *         jclass destClass,
 *         jobject destObject,
 *         JNIEnv *env,
 *         jobject sourceObject,
 *         const char *fieldName,
 *         const char *signature,
 *         const char *function_name
 *      )
 *
 * @brief Sets a Java object value to Java object
 *
 * @param [in] destClass Destination class
 * @param [in] destObject Destination object
 * @param [in] env Java environment
 * @param [in] sourceObject Source object
 * @param [in] fieldName Class field name
 * @param [in] signature Destination object signature
 * @param [in] function_name Parent function name
 *
 * @retval 0 if success otherwise error if non zero
 *
 * **NOTICE** If error occurs _str_message_ will contain the reason of the error to be thrown in JVM
 */
int jni_example_set_value(
   jclass,
   jobject,
   JNIEnv *,
   jobject,
   const char *,
   const char *,
   const char *
);
