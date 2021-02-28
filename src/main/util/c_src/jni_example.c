#include <jni.h>
#include <jni_example_exception.h>
#include <foreign_library.h>

/*
 * Class:     org_jni_example_Main
 * Method:    welcome
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_jni_example_Main_welcome(JNIEnv *env, jobject thisObj)
{
   return (jstring)welcome();
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

   return res;
}

/*
 * Class:     org_jni_example_Main
 * Method:    addTwoNumbers
 * Signature: (DD)D
 */
JNIEXPORT jdouble JNICALL Java_org_jni_example_Main_addTwoNumbers(JNIEnv *env, jobject thisObj, jdouble A, jdouble B)
{

}

/*
 * Class:     org_jni_example_Main
 * Method:    subTwoNumbers
 * Signature: (DD)D
 */
JNIEXPORT jdouble JNICALL Java_org_jni_example_Main_subTwoNumbers(JNIEnv *env, jobject thisObj, jdouble A, jdouble B)
{

}

/*
 * Class:     org_jni_example_Main
 * Method:    multTwoNumbers
 * Signature: (DD)D
 */
JNIEXPORT jdouble JNICALL Java_org_jni_example_Main_multTwoNumbers(JNIEnv *env, jobject thisObj, jdouble A, jdouble B)
{

}

/*
 * Class:     org_jni_example_Main
 * Method:    divTwoNumbers
 * Signature: (DD)D
 */
JNIEXPORT jdouble JNICALL Java_org_jni_example_Main_divTwoNumbers(JNIEnv *env, jobject thisObj, jdouble A, jdouble B)
{

}

/*
 * Class:     org_jni_example_Main
 * Method:    createNewExampleRegistry
 * Signature: (Ljava/lang/String;Ljava/lang/Integer;Ljava/lang/String;)Lorg/jni/example/registry/JniExampleRegistry;
 */
JNIEXPORT jobject JNICALL Java_org_jni_example_Main_createNewExampleRegistry(JNIEnv *env, jclass thisObj, jstring name, jobject age, jstring occupation)
{


}

