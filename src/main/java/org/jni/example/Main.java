package org.jni.example;

import org.jni.example.registry.JniExampleRegistry;

public class Main {
    static {
        try {
            System.loadLibrary("jniexample");
        } catch (Throwable e) {
            System.out.println("JNI example load library error.");
            System.out.println(e.getMessage());
            throw e;
        }
    }

    public static native String welcome() throws Throwable;
    public static native String helloGuest(String message) throws Throwable;
    public static native double addTwoNumbers(double A, double B);
    public static native double subTwoNumbers(double A, double B);
    public static native double multTwoNumbers(double A, double B);
    public static native double divTwoNumbers(double A, double B) throws Throwable;
    public static native byte[] javaStringToNativeByte(String message) throws Throwable;
    public static native byte[] nativeRamdomNumberGeneratorNoEntropy(long size) throws Throwable;
    public static native JniExampleRegistry createNewExampleRegistry(String name, Integer age, String occupation) throws Throwable;
}
