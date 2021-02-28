package org.jni.example;

import org.jni.example.registry.JniExampleRegistry;

public class Main {

    static {
        System.loadLibrary("jniexample");
    }

    public native String welcome();
    public native String helloGuest(String message) throws Throwable;
    public native double addTwoNumbers(double A, double B);
    public native double subTwoNumbers(double A, double B);
    public native double multTwoNumbers(double A, double B);
    public native double divTwoNumbers(double A, double B) throws Throwable;
    public static native JniExampleRegistry createNewExampleRegistry(String name, Integer age, String occupation) throws Throwable;
}
