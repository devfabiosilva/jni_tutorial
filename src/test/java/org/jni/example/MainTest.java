package org.jni.example;

import org.jni.example.exceptions.JniExampleException;
import org.jni.example.registry.JniExampleRegistry;
import org.junit.jupiter.api.Test;

import java.util.HashMap;

import static org.jni.example.Main.*;
import static org.junit.Assert.*;

class MainTest {

    private final double delta = 1E-9;

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
    void helloGuestNullStringTest() throws Throwable {

        try {
            System.out.println(helloGuest(null));
            fail("helloGuest error should add an JniExampleException");
        } catch (Throwable e) {
            if (e instanceof AssertionError)
                throw e;

            assertTrue(e instanceof JniExampleException);
            assertEquals(20, ((JniExampleException) e).getError());
            assertEquals(
                    "jni_example_javaUTF8_to_c_char_util @ helloGuest. Error in JNI example library 20. String can not be NULL",
                    e.getMessage()
            );
            exceptionSuccess(((JniExampleException) e).getError(), e.getMessage());
        }
    }

    @Test
    void helloGuestEmptyStringTest() throws Throwable {

        try {
            System.out.println(helloGuest(""));
            fail("helloGuest should throw an JniExampleException in an empty string");
        } catch (Throwable e) {
            if (e instanceof AssertionError)
                throw e;

            assertTrue(e instanceof JniExampleException);
            assertEquals(100, ((JniExampleException) e).getError());
            assertEquals(
                    "helloGuest: \"message\" is an empty string!",
                    e.getMessage()
            );
            exceptionSuccess(((JniExampleException) e).getError(), e.getMessage());
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
        assertEquals(-2.1, subTwoNumbers(A, B), delta);
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
        assertEquals((double) 10 / 3, divTwoNumbers(A, B), delta);
    }

    @Test
    void divTwoNumbersExceptionTest() throws Throwable {
        double A = 10.0;
        double B = 0.0;
        Double result = null;
        try {
            result = divTwoNumbers(A, B);
            fail("Divide by zero is inconsistent. Should return an error");
        } catch (Throwable e) {
            if (e instanceof AssertionError)
                throw e;

            assertTrue(e instanceof JniExampleException);
            assertEquals(300, ((JniExampleException) e).getError());
            assertEquals(
                    "divTwoNumbers: Can not divide by ZERO!",
                    e.getMessage());
            exceptionSuccess(((JniExampleException) e).getError(), e.getMessage());
        }
        assertNull(result);
    }

    @Test
    void stringToNativeByteTest() throws Throwable {
        byte[] byteArray = javaStringToNativeByte("Hello world from JNI");

        assertNotNull(byteArray);
        String returnedMessage = new String(byteArray, "UTF-8");
        assertEquals(
                "You said the following message: Hello world from JNI",
                returnedMessage
        );
        System.out.println(returnedMessage);
    }

    @Test
    void stringToNativeByteNullOrEmptyTest() throws Throwable {
        byte[] byteArray = null;
        try {
            byteArray = javaStringToNativeByte(null);
            fail("It should expect a throw JniExampleException");
        } catch (Throwable e) {
            if (e instanceof AssertionError)
                throw e;

            assertTrue(e instanceof JniExampleException);
            assertEquals(20, ((JniExampleException) e).getError());
            assertEquals(
                    "jni_example_javaUTF8_to_c_char_util @ javaStringToNativeByte. Error in JNI example library 20. String can not be NULL",
                    e.getMessage()
            );
        }

        assertNull(byteArray);

        try {
            byteArray = javaStringToNativeByte("");
            fail("It should expect an JniExampleException on empty string");
        } catch (Throwable e) {
            if (e instanceof AssertionError)
                throw e;

            assertTrue(e instanceof JniExampleException);
            assertEquals(800, ((JniExampleException) e).getError());
            assertEquals(
                    "javaStringToNativeByte: Message can not be an empty string",
                    e.getMessage()
            );
        }

        assertNull(byteArray);
    }

    @Test
    void createNewExampleRegistryTest() throws Throwable {
        HashMap<Integer, JniExampleRegistry> exampleRegistryHashMap = new HashMap<>();

        exampleRegistryHashMap.put(0, createNewExampleRegistry("Alice", 20, "Student"));
        exampleRegistryHashMap.put(1, createNewExampleRegistry("Bob", 34, "Engineer"));
        exampleRegistryHashMap.put(2, createNewExampleRegistry("Albert Einstein", 76, "Physicist"));
        exampleRegistryHashMap.put(3, createNewExampleRegistry("Nikola Tesla", 86, "Electrical Engineer"));

        exampleRegistryHashMap.forEach((k, v) -> {
            System.out.println("Testing k = " + k);
            assertNotNull(v);
            assertNotNull(v.getId());
            assertNotNull(v.getName());
            assertNotNull(v.getAge());
            assertNotNull(v.getOccupation());
            System.out.println("==============================");
            System.out.println("Generated long random ID = " + v.getId());
            System.out.println("Name = " + v.getName());
            System.out.println("Age = " + v.getAge());
            System.out.println("Occupation " + v.getOccupation());
            System.out.println("-------------------------------\n");
        });

    }

    @Test
    void createNewExampleRegistryNameNullOrEmpty_Test() throws Throwable {
        JniExampleRegistry jniExampleRegistry = null;
        try {
            jniExampleRegistry = createNewExampleRegistry(null, 20, "Test");
            fail("createNewExampleRegistry should throw a JniExampleException when \"name\" field is null");
        } catch (Throwable e) {
            if (e instanceof AssertionError)
                throw e;

            assertTrue(e instanceof JniExampleException);
            assertEquals(700, ((JniExampleException) e).getError());
            assertEquals("createNewExampleRegistry: \"name\" field can not be null", e.getMessage());
        }

        assertNull(jniExampleRegistry);

        try {
            jniExampleRegistry = createNewExampleRegistry("", 20, "Test");
            fail("createNewExampleRegistry should throw a JniExampleException when \"name\" field is empty");
        } catch (Throwable e) {
            if (e instanceof AssertionError)
                throw e;

            assertTrue(e instanceof JniExampleException);
            assertEquals(701, ((JniExampleException) e).getError());
            assertEquals(
                    "createNewExampleRegistry: \"name\" field can not be an empty string",
                    e.getMessage()
            );
        }
        assertNull(jniExampleRegistry);
    }

    @Test
    void createNewExampleRegistryAgeNull_Test() throws Throwable {
        JniExampleRegistry jniExampleRegistry = null;
        try {
            jniExampleRegistry = createNewExampleRegistry("Alice", null, "Test");
            fail("\"createNewExampleRegistry should throw a JniExampleException when \"age\" field is null\"");
        } catch (Throwable e) {
            if (e instanceof AssertionError)
                throw e;

            assertTrue(e instanceof JniExampleException);
            assertEquals(702, ((JniExampleException) e).getError());
            assertEquals(
                    "createNewExampleRegistry: \"age\" field can not be null",
                    e.getMessage()
            );
        }
        assertNull(jniExampleRegistry);
    }

    @Test
    void createNewExampleRegistryOccupationNullOrEmpty_Test() throws Throwable {
        JniExampleRegistry jniExampleRegistry = null;
        try {
            jniExampleRegistry = createNewExampleRegistry("Alice", 20, null);
            fail("createNewExampleRegistry should throw a JniExampleException when \"occupation\" field is null");
        } catch (Throwable e) {
            if (e instanceof AssertionError)
                throw e;

            assertTrue(e instanceof JniExampleException);
            assertEquals(703, ((JniExampleException) e).getError());
            assertEquals("createNewExampleRegistry: \"occupation\" field can not be null", e.getMessage());
        }

        assertNull(jniExampleRegistry);

        try {
            jniExampleRegistry = createNewExampleRegistry("Alice", 20, "");
            fail("createNewExampleRegistry should throw a JniExampleException when \"occupation\" field is empty");
        } catch (Throwable e) {
            if (e instanceof AssertionError)
                throw e;

            assertTrue(e instanceof JniExampleException);
            assertEquals(704, ((JniExampleException) e).getError());
            assertEquals(
                    "createNewExampleRegistry: \"occupation\" field can not be an empty string",
                    e.getMessage()
            );
        }
        assertNull(jniExampleRegistry);
    }
}