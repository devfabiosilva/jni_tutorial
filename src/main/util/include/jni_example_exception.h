
jint throwNewException(JNIEnv *, const char *, const char *, int);
#define JNI_EXAMPLE_EXCEPTION_CLASS "org/jni/example/exceptions/JniExampleException"
#define JNI_EXAMPLE_UTIL_EXCEPTION(msg, err) throwNewException(env, JNI_EXAMPLE_EXCEPTION_CLASS, msg, err)

