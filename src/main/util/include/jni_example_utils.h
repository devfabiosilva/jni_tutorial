#include <string.h>
#include <jni.h>

/**
 * @def STR_MESSAGE_MAX_SZ
 * @brief Global Notification throwable message size.
 */
#define STR_MESSAGE_MAX_SZ (size_t)1024

/**
 * @brief Global _Throwable notification_ message. Message string SHOULD NOT be greater than _STR_MESSAGE_MAX_SZ - 1_
 */
char str_message[STR_MESSAGE_MAX_SZ];

/**
 * @fn jint throwExampleNewException(JNIEnv *env, const char *class, const char *message, int error)
 * @brief Throws custom throwable error in JVM
 *
 * @param [in] env Java environment
 * @param [in] class Classname of your custom error class or Exception or Throwable. See a custom example <a href="https://github.com/devfabiosilva/jni_tutorial/blob/master/src/main/java/org/jni/example/exceptions/JniExampleException.java">here</a>
 * @param [in] message Error message to be thrown
 * @param [in] error Error code. If 0 error code will be omitted and default JVM Exception (_java.lang.Exception_) will be thrown
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

/**
 * @def JNI_EXAMPLE_EXCEPTION_CLASS
 * @brief Sample Exception class
 *
 * You can create a custom _Throwable_. See <i><a href="https://github.com/devfabiosilva/jni_tutorial/blob/master/src/main/java/org/jni/example/exceptions/JniExampleException.java">org.jni.example.exceptions.JniExampleException</a></i> for details
 */
#define JNI_EXAMPLE_EXCEPTION_CLASS "org/jni/example/exceptions/JniExampleException"

/**
 * @def JNI_EXAMPLE_UTIL_EXCEPTION
 * @brief Sample Exception macro
 */
#define JNI_EXAMPLE_UTIL_EXCEPTION(msg, err) throwExampleNewException(env, JNI_EXAMPLE_EXCEPTION_CLASS, msg, err)

/**
 * @def JNI_EXAMPLE_LANG_EXCEPTION_CLASS
 * @brief Default _java.lang.Exception_ Java Class
 */
#define JNI_EXAMPLE_LANG_EXCEPTION_CLASS "java/lang/Exception"

/**
 * @def throwExampleError
 * @brief Default _java.lang.Exception_ error message macro
 */
#define throwExampleError(msg) throwExampleNewException(env, JNI_EXAMPLE_LANG_EXCEPTION_CLASS, msg, 0)


/**
 * @def JNI_EXAMPLE_INIT
 * @brief Default _init_ method name. See <a href="https://docs.oracle.com/javase/7/docs/technotes/guides/jni/spec/jniTOC.html">docs</a> for details
 */
#define JNI_EXAMPLE_INIT "<init>"

/**
 * @def JNI_EXAMPLE_JAVA_LANG_LONG_CLASS
 * @brief Default _java.lang.Long_ Java Class
 */
#define JNI_EXAMPLE_JAVA_LANG_LONG_CLASS "java/lang/Long"

/**
 * @def JNI_EXAMPLE_JAVA_LANG_LONG_CLASS_SIGNATURE
 * @brief Default _java.lang.Long_ signature
 */
#define JNI_EXAMPLE_JAVA_LANG_LONG_CLASS_SIGNATURE "L"JNI_EXAMPLE_JAVA_LANG_LONG_CLASS";"

/**
 * @def JNI_EXAMPLE_JAVA_LANG_STRING
 * @brief Default _java.lang.String_ Java Class
 */
#define JNI_EXAMPLE_JAVA_LANG_STRING "java/lang/String"

/**
 * @def JNI_EXAMPLE_JAVA_LANG_STRING_SIGNATURE
 * @brief Default _java.lang.String_ signature
 */
#define JNI_EXAMPLE_JAVA_LANG_STRING_SIGNATURE "L"JNI_EXAMPLE_JAVA_LANG_STRING";"

/**
 * @def JNI_EXAMPLE_JAVA_LANG_INTEGER
 * @brief Default _java.lang.Integer_ Java Class
 */
#define JNI_EXAMPLE_JAVA_LANG_INTEGER "java/lang/Integer"

/**
 * @def JNI_EXAMPLE_JAVA_LANG_INTEGER_SIGNATURE
 * @brief Default _java.lang.Integer_ signature
 */
#define JNI_EXAMPLE_JAVA_LANG_INTEGER_SIGNATURE "L"JNI_EXAMPLE_JAVA_LANG_INTEGER";"

/**
 * @def JNI_EXAMPLE_INIT_SET_LONG_SIGNATURE
 * @brief Customizable _java.lang.Long_ signature. It is equivalent to _value = Long.valueOf(myLongNumber)_
 */
#define JNI_EXAMPLE_INIT_SET_LONG_SIGNATURE "(J)V"

/**
 * @def C_STR_TO_JAVA_UTF8_ERROR_EXCEPTION
 * @brief Sample Java UTF-8 to C char exception message example
 */
#define C_STR_TO_JAVA_UTF8_ERROR_EXCEPTION "JNI example error. Parsing C string to Java UTF-8"

/**
 * @def ERROR_CANT_CREATE_BYTE_ARRAY
 * @brief Sample Java exception message on create byte array example
 */
#define ERROR_CANT_CREATE_BYTE_ARRAY "JNI example error. Can't create byte array"

/**
 * @def ERROR_CANT_WRITE_BYTE_ARRAY
 * @brief Sample Java exception message on write allocated byte array example
 */
#define ERROR_CANT_WRITE_BYTE_ARRAY "JNI example error. Can't write byte array in allocated memory space"

/**
 * @def JNI_EXAMPLE_DEREF_UTF8_STR
 * @brief C char dereferencer macro. It is equivalent to a high level garbage collector
 */
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


#define PARM_CHECKER_IS_TRUE (char)'t'
#define PARM_CHECKER_IS_JSTRING (char)'n'
#define PARM_CHECKER_IS_JBYTE_ARRAY (char)'b'
#define PARM_CHECKER_IS_JAVA_INTEGER (char)'I'
#define PARM_CHECKER_END (char)'\0'
int jni_example_input_parameters_checker_util(
   JNIEnv *,
   const char *,
   ...
);

