
#define JNI_EXAMPLE_LANG_EXCEPTION_CLASS "java/lang/Exception"
#define JNI_EXAMPLE_INIT_THROWABLE_WITH_CODE(class) (*env)->GetMethodID(env, class, "<init>", "(Ljava/lang/String;I)V")

jint throwNewException(JNIEnv *env, const char *class, const char *message, int error)
{
   jint err;
   jclass exClass;
   jfieldID field;
   jmethodID methodId;
   jobject jErrObj;
   jstring errMsg;
   static char err_msg[1024];

   if (!(exClass=(*env)->FindClass(env, class))) {
      if (class==JNI_EXAMPLE_LANG_EXCEPTION_CLASS)
         return 1;

      if (!(exClass=(*env)->FindClass(env, JNI_EXAMPLE_LANG_EXCEPTION_CLASS)))
         return 2;

      sprintf(err_msg, "throwNewException: Class not found '%s' with related message = '%s'", class, message);

      message=err_msg;
   } else if (error) {

      if (!(errMsg=(*env)->NewStringUTF(env, message))) {
         sprintf(err_msg, "throwNewException: Cannot set message '%s' into throwable class '%s' and errcode %d", message, class, error);
         throwError(env, err_msg);
         return 3;
      }

      if (!(methodId=JNI_EXAMPLE_INIT_THROWABLE_WITH_CODE(exClass))) {
         sprintf(err_msg, "throwNewException: Cannot initialize throwable class '%s' with message '%s' and errcode %d", class, message, error);
         throwError(env, err_msg);
         err=4;
         goto throwNewException_EXIT1;
      }

      if (!(jErrObj=(*env)->NewObject(env, exClass, methodId, errMsg, error))) {
         sprintf(err_msg, "throwNewException: Cannot create throwable class '%s' with message '%s' and errcode %d", class, message, error);
         throwError(env, err_msg);
         err=5;
      } else if ((err=(*env)->Throw(env, jErrObj))) {
         (*env)->DeleteLocalRef(env, jErrObj);
         sprintf(err_msg, "throwNewException: Can't throw '%s' with message '%s' and errcode %d", class, message, error);
         throwError(env, err_msg);
      }

throwNewException_EXIT1:
      (*env)->DeleteLocalRef(env, errMsg);

      return err;

   }

   return (*env)->ThrowNew(env, exClass, message);
}

