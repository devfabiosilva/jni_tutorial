package org.jni.example;

import org.jni.example.exceptions.JniExampleException;
import org.jni.example.registry.JniExampleRegistry;
import org.junit.jupiter.api.Test;

import java.util.HashMap;

import static java.lang.Double.valueOf;
import static org.jni.example.Main.*;
import static org.junit.Assert.*;

class MainTest {

    private double delta = 1E-9;

    private void exceptionSuccess(int error, String message) {
        System.out.println("\nException success");
        System.out.println("Expected error message: " + message);
        System.out.println("Expected error numner: " + error + "\n");
    }

    @Test
    void welcomeTest() throws Throwable {
        System.out.println(welcome());
    }

    @Test
    void helloGuestTest() throws Throwable {
        System.out.println(helloGuest("my dear friend"));
    }

    @Test
    void helloGuestNullStringTest() {

        try {
            System.out.println(helloGuest(null));
            fail();
        } catch (Throwable e) {
            assertTrue(e instanceof JniExampleException);
            assertEquals(20, ((JniExampleException) e).getError());
            assertEquals(
                    "jni_example_javaUTF8_to_c_char_util @ helloGuest. Error in JNI example library 20. String can not be NULL",
                    e.getMessage()
            );
            exceptionSuccess(((JniExampleException)e).getError(), e.getMessage());
        }
    }

    @Test
    void helloGuestEmptyStringTest() {

        try {
            System.out.println(helloGuest(""));
            fail();
        } catch (Throwable e) {
            assertTrue(e instanceof JniExampleException);
            assertEquals(100, ((JniExampleException) e).getError());
            assertEquals(
                    "helloGuest: \"message\" is an empty string!",
                    e.getMessage()
            );
            exceptionSuccess(((JniExampleException)e).getError(), e.getMessage());
        }
    }

    @Test
    void addTwoNumbersTest() {
        double A = 3.5;
        double B = 5.6;
        assertEquals(9.1, addTwoNumbers(A, B), 0.0);
    }

    @Test
    void subTwoNumbersTest() {
        double A = 3.5;
        double B = 5.6;
        assertEquals( -2.1, subTwoNumbers(A, B), delta);
    }

    @Test
    void multTwoNumbersTest() {
        double A = 15.23;
        double B = 26.32;
        assertEquals(400.8536, multTwoNumbers(A, B), delta);
    }

    @Test
    void divTwoNumbersTest() throws Throwable {
        double A = 10;
        double B = 3;
        assertEquals((double) 10/3, divTwoNumbers(A, B), delta);
    }

    @Test
    void divTwoNumbersExceptionTest() {
        double A = 10.0;
        double B = 0.0;
        Double result = null;
        try {
            result = valueOf(divTwoNumbers(A, B));
            fail();
        } catch (Throwable e) {
            assertTrue(e instanceof JniExampleException);
            assertEquals(300, ((JniExampleException)e).getError());
            assertEquals("divTwoNumbers: Can not divide by ZERO!", e.getMessage());
            exceptionSuccess(((JniExampleException)e).getError(), e.getMessage());
        } finally {
            assertNull(result);
        }
    }

    @Test
    void createNewExampleRegistryTest() throws Throwable {
        HashMap<Integer, JniExampleRegistry> exampleRegistryHashMap = new HashMap<>();

        exampleRegistryHashMap.put(0, createNewExampleRegistry("Alice", 23, "Student"));
        exampleRegistryHashMap.put(1, createNewExampleRegistry("Bob", 34, "Engineer"));
        exampleRegistryHashMap.put(2, createNewExampleRegistry("Albert Einstein", 76, "Physicist"));
        exampleRegistryHashMap.put(3, createNewExampleRegistry("Nikola Tesla", 86, "Electrical Engineer"));

        exampleRegistryHashMap.forEach((k, v) -> {
            System.out.println("Testing k = " + k);
            assertNull(v);
            //TODO to finish
        });

    }
}