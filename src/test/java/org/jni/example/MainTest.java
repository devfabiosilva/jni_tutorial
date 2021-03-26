package org.jni.example;

import org.jni.example.exceptions.JniExampleException;
import org.jni.example.registry.JniExampleRegistry;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;
import java.nio.charset.StandardCharsets;
import java.util.HashMap;

import static org.jni.example.Main.*;

class MainTest {

    private final double delta = 1E-9;

    private void exceptionSuccess(int error, String message) {
        System.out.println("\nException success");
        System.out.println("Expected error message: " + message);
        System.out.println("Expected error number: " + error + "\n");
    }

    private String printByteHexToString(byte[] byteArray) {
        StringBuilder str = new StringBuilder();

        for (byte b : byteArray)
            str.append(String.format("%02x", b));

        return str.toString();
    }

    private String printByteHexToIntegerStr(byte[] byteArray) {
        StringBuilder str = new StringBuilder();

        for (byte b : byteArray)
            str.append(String.format("%d ", b));

        return str.substring(0, str.length() - 1);
    }

    @Test
    void welcomeTest() throws Throwable {
        String welcomeMessage = welcome();
        Assertions.assertNotNull(welcomeMessage);
        Assertions.assertEquals("Welcome. This is a JNI example. I hope you enjoy this tutorial", welcomeMessage);
        System.out.println(welcomeMessage);
    }

    @Test
    void helloGuestTest() throws Throwable {
        String helloGuestMessage = helloGuest("my dear friend");
        Assertions.assertNotNull(helloGuestMessage);
        Assertions.assertEquals("Hello my dear friend this is a JNI example test. Have a nice day ;)", helloGuestMessage);
        System.out.println(helloGuestMessage);
    }

    @Test
    void helloGuestNullStringTest() throws Throwable {

        try {
            System.out.println(helloGuest(null));
            Assertions.fail("helloGuest error should add an JniExampleException");
        } catch (Throwable e) {
            if (e instanceof AssertionError)
                throw e;

            Assertions.assertTrue(e instanceof JniExampleException);
            Assertions.assertEquals(20, ((JniExampleException) e).getError());
            Assertions.assertEquals(
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
            Assertions.fail("helloGuest should throw an JniExampleException in an empty string");
        } catch (Throwable e) {
            if (e instanceof AssertionError)
                throw e;

            Assertions.assertTrue(e instanceof JniExampleException);
            Assertions.assertEquals(100, ((JniExampleException) e).getError());
            Assertions.assertEquals(
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
        Assertions.assertEquals(9.1, addTwoNumbers(A, B), 0.0);
    }

    @Test
    void subTwoNumbersTest() {
        double A = 3.5;
        double B = 5.6;
        Assertions.assertEquals(-2.1, subTwoNumbers(A, B), delta);
    }

    @Test
    void multTwoNumbersTest() {
        double A = 15.23;
        double B = 26.32;
        Assertions.assertEquals(400.8536, multTwoNumbers(A, B), delta);
    }

    @Test
    void divTwoNumbersTest() throws Throwable {
        double A = 10;
        double B = 3;
        Assertions.assertEquals((double) 10 / 3, divTwoNumbers(A, B), delta);
    }

    @Test
    void divTwoNumbersExceptionTest() throws Throwable {
        double A = 10.0;
        double B = 0.0;
        Double result = null;
        try {
            result = divTwoNumbers(A, B);
            Assertions.fail("Divide by zero is inconsistent. Should return an error");
        } catch (Throwable e) {
            if (e instanceof AssertionError)
                throw e;

            Assertions.assertTrue(e instanceof JniExampleException);
            Assertions.assertEquals(300, ((JniExampleException) e).getError());
            Assertions.assertEquals(
                    "divTwoNumbers: Can not divide by ZERO!",
                    e.getMessage());
            exceptionSuccess(((JniExampleException) e).getError(), e.getMessage());
        }
        Assertions.assertNull(result);
    }

    @Test
    void stringToNativeByteTest() throws Throwable {
        byte[] byteArray = javaStringToNativeByte("Hello world from JNI");

        Assertions.assertNotNull(byteArray);
        String returnedMessage = new String(byteArray, StandardCharsets.UTF_8);
        Assertions.assertEquals(
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
            Assertions.fail("It should expect a throw JniExampleException");
        } catch (Throwable e) {
            if (e instanceof AssertionError)
                throw e;

            Assertions.assertTrue(e instanceof JniExampleException);
            Assertions.assertEquals(20, ((JniExampleException) e).getError());
            Assertions.assertEquals(
                    "jni_example_javaUTF8_to_c_char_util @ javaStringToNativeByte. Error in JNI example library 20. String can not be NULL",
                    e.getMessage()
            );
        }

        Assertions.assertNull(byteArray);

        try {
            byteArray = javaStringToNativeByte("");
            Assertions.fail("It should expect an JniExampleException on empty string");
        } catch (Throwable e) {
            if (e instanceof AssertionError)
                throw e;

            Assertions.assertTrue(e instanceof JniExampleException);
            Assertions.assertEquals(800, ((JniExampleException) e).getError());
            Assertions.assertEquals(
                    "javaStringToNativeByte: Message can not be an empty string",
                    e.getMessage()
            );
        }

        Assertions.assertNull(byteArray);
    }

    HashMap<Integer, JniExampleRegistry> loadCandidates() throws Throwable {
        HashMap<Integer, JniExampleRegistry> exampleRegistryHashMap = new HashMap<>();

        exampleRegistryHashMap.put(0, createNewExampleRegistry("Albert Einstein", 76, "Physicist and Nobel prize"));
        exampleRegistryHashMap.put(1, createNewExampleRegistry("Nikola Tesla", 86, "Electrical Engineer"));
        exampleRegistryHashMap.put(2, createNewExampleRegistry("Dennis Richie", 70, "Bell Labs employee and creator of the God Language C and Unix system"));
        exampleRegistryHashMap.put(3, createNewExampleRegistry("Federico Faggin", 79, "Physicist and Engineer and creator of the first microprocessor"));
        exampleRegistryHashMap.put(4, createNewExampleRegistry("Marie Curie", 66, "Chemist and Nobel prize"));
        exampleRegistryHashMap.put(5, createNewExampleRegistry("Roberto Landell de Moura", 67, "Priest and Inventor. The first one to transmit human voice over electromagnetic wave"));
        exampleRegistryHashMap.put(6, createNewExampleRegistry("Rudolf Diesel", 55, "Engineer and inventor of the Diesel engine"));
        exampleRegistryHashMap.put(7, createNewExampleRegistry("James Clerk Maxwell", 48, "Physicist"));
        exampleRegistryHashMap.put(8, createNewExampleRegistry("Michael Faraday", 75, "Physicist"));
        exampleRegistryHashMap.put(9, createNewExampleRegistry("Daniel Fraga", 40, "Crypto anarchist, activist and computer science"));
        exampleRegistryHashMap.put(10, createNewExampleRegistry("Julian Assange", 49, "Wikileaks reporter and activist"));
        exampleRegistryHashMap.put(11, createNewExampleRegistry("Ghoncheh Ghavami", 32, "Iranian woman fighting for humans rights and activist"));
        exampleRegistryHashMap.put(12, createNewExampleRegistry("Alberto Santos-Dumont", 59, "Inventor and aviation pioneer"));
        exampleRegistryHashMap.put(13, createNewExampleRegistry("Andreas Vesalius", 49, "The father of the human body anatomy studies. See 'De humani corporis fabrica - 1543'"));
        exampleRegistryHashMap.put(14, createNewExampleRegistry("Sir Isaac Newton", 84, "Physicist"));
        exampleRegistryHashMap.put(15, createNewExampleRegistry("Gottfried Wilhelm Leibniz", 70, "Mathematician and philosopher"));
        exampleRegistryHashMap.put(16, createNewExampleRegistry("Carl Friedrich Gauss", 77, "Mathematician and philosopher"));
        exampleRegistryHashMap.put(17, createNewExampleRegistry("Hans Camenzind", 78, "Inventor of the IC 555 and Engineer"));
        exampleRegistryHashMap.put(18, createNewExampleRegistry("Paul Brokaw", 84, "Integrated Circuit expert and Inventor of the band gap reference voltage regulator"));
        exampleRegistryHashMap.put(19, createNewExampleRegistry("Thomas Sowell", 90, "Economist"));
        exampleRegistryHashMap.put(20, createNewExampleRegistry("Satoshi Nakamoto", 50, "Creator of the Bitcoin (first decentralized cryptocurrency immune to dictatorships, central banks, stupid laws, inflation and regulations)"));
        exampleRegistryHashMap.put(21, createNewExampleRegistry("Ayn Rand", 77, "Philosopher"));
        exampleRegistryHashMap.put(22, createNewExampleRegistry("Oskar Schindler", 66, "German industrialist who is credited with saving the lives of 1,200 Jews during the Holocaust"));
        exampleRegistryHashMap.put(23, createNewExampleRegistry("Satoshi Nakamoto", 50, "Creator of the Bitcoin (first decentralized cryptocurrency immune to dictatorships, central banks, stupid laws, inflation and regulations)"));
        exampleRegistryHashMap.put(24, createNewExampleRegistry("Ayn Rand", 77, "Philosopher"));

        return exampleRegistryHashMap;
    }

    @Test
    void createNewExampleRegistryTest() throws Throwable {

        loadCandidates().forEach((k, v) -> {
            System.out.println("Testing k = " + k);
            Assertions.assertNotNull(v);
            Assertions.assertNotNull(v.getId());
            Assertions.assertNotNull(v.getName());
            Assertions.assertNotNull(v.getAge());
            Assertions.assertNotNull(v.getOccupation());
            System.out.println("==============================");
            System.out.println("Generated long random ID = " + v.getId());
            System.out.println("Name = " + v.getName());
            System.out.println("Age = " + v.getAge());
            System.out.println("Occupation = " + v.getOccupation());
            System.out.println("-------------------------------\n");
        });

    }

    @Test
    void createNewExampleRegistryNameNullOrEmpty_Test() throws Throwable {
        JniExampleRegistry jniExampleRegistry = null;
        try {
            jniExampleRegistry = createNewExampleRegistry(null, 20, "Test");
            Assertions.fail("createNewExampleRegistry should throw a JniExampleException when \"name\" field is null");
        } catch (Throwable e) {
            if (e instanceof AssertionError)
                throw e;

            Assertions.assertTrue(e instanceof JniExampleException);
            Assertions.assertEquals(700, ((JniExampleException) e).getError());
            Assertions.assertEquals("createNewExampleRegistry: \"name\" field can not be null", e.getMessage());
        }

        Assertions.assertNull(jniExampleRegistry);

        try {
            jniExampleRegistry = createNewExampleRegistry("", 20, "Test");
            Assertions.fail("createNewExampleRegistry should throw a JniExampleException when \"name\" field is empty");
        } catch (Throwable e) {
            if (e instanceof AssertionError)
                throw e;

            Assertions.assertTrue(e instanceof JniExampleException);
            Assertions.assertEquals(701, ((JniExampleException) e).getError());
            Assertions.assertEquals(
                    "createNewExampleRegistry: \"name\" field can not be an empty string",
                    e.getMessage()
            );
        }
        Assertions.assertNull(jniExampleRegistry);
    }

    @Test
    void createNewExampleRegistryAgeNull_Test() throws Throwable {
        JniExampleRegistry jniExampleRegistry = null;
        try {
            jniExampleRegistry = createNewExampleRegistry("Alice", null, "Test");
            Assertions.fail("\"createNewExampleRegistry should throw a JniExampleException when \"age\" field is null\"");
        } catch (Throwable e) {
            if (e instanceof AssertionError)
                throw e;

            Assertions.assertTrue(e instanceof JniExampleException);
            Assertions.assertEquals(702, ((JniExampleException) e).getError());
            Assertions.assertEquals(
                    "createNewExampleRegistry: \"age\" field can not be null",
                    e.getMessage()
            );
        }
        Assertions.assertNull(jniExampleRegistry);
    }

    @Test
    void createNewExampleRegistryOccupationNullOrEmpty_Test() throws Throwable {
        JniExampleRegistry jniExampleRegistry = null;
        try {
            jniExampleRegistry = createNewExampleRegistry("Alice", 20, null);
            Assertions.fail("createNewExampleRegistry should throw a JniExampleException when \"occupation\" field is null");
        } catch (Throwable e) {
            if (e instanceof AssertionError)
                throw e;

            Assertions.assertTrue(e instanceof JniExampleException);
            Assertions.assertEquals(703, ((JniExampleException) e).getError());
            Assertions.assertEquals("createNewExampleRegistry: \"occupation\" field can not be null", e.getMessage());
        }

        Assertions.assertNull(jniExampleRegistry);

        try {
            jniExampleRegistry = createNewExampleRegistry("Alice", 20, "");
            Assertions.fail("createNewExampleRegistry should throw a JniExampleException when \"occupation\" field is empty");
        } catch (Throwable e) {
            if (e instanceof AssertionError)
                throw e;

            Assertions.assertTrue(e instanceof JniExampleException);
            Assertions.assertEquals(704, ((JniExampleException) e).getError());
            Assertions.assertEquals(
                    "createNewExampleRegistry: \"occupation\" field can not be an empty string",
                    e.getMessage()
            );
        }
        Assertions.assertNull(jniExampleRegistry);
    }

    @Test
    void createNewExampleRegistryOccupationInvalidAge_Test() throws Throwable {
        final String name = "Dennis Richie";
        final String occupation = "Bell Labs computer engineer";

        JniExampleRegistry jniExampleRegistry = null;
        try {
            jniExampleRegistry = createNewExampleRegistry(name, -20, occupation);
            Assertions.fail("createNewExampleRegistry should throw a JniExampleException when \"age\" has negative value");
        } catch (Throwable e) {
            if (e instanceof AssertionError)
                throw e;

            Assertions.assertTrue(e instanceof JniExampleException);
            Assertions.assertEquals(705, ((JniExampleException) e).getError());
            Assertions.assertEquals("createNewExampleRegistry: \"age\" cannot have negative value", e.getMessage());
        }

        try {
            jniExampleRegistry = createNewExampleRegistry(name, 10, occupation);
            Assertions.fail("createNewExampleRegistry should throw a JniExampleException when \"age\" is less than 18");
        } catch (Throwable e) {
            if (e instanceof AssertionError)
                throw e;

            Assertions.assertTrue(e instanceof JniExampleException);
            Assertions.assertEquals(706, ((JniExampleException) e).getError());
            Assertions.assertEquals("createNewExampleRegistry: Candidate with \"age\" = must be 18+", e.getMessage());
        }

        Assertions.assertNull(jniExampleRegistry);
    }

    @Test
    void systemRandomTest() throws Throwable {
        final long size = 32;
        byte [] rand = nativeRandomNumberGeneratorNoEntropy(size);
        Assertions.assertNotNull(rand);
        Assertions.assertEquals(size, rand.length);
        System.out.println("Generated random size");
        System.out.println(printByteHexToString(rand));
        System.out.println(printByteHexToIntegerStr(rand));

        rand = null;
        try {
            rand = nativeRandomNumberGeneratorNoEntropy(0);
            Assertions.fail("Should fail. Can't generate random number with 0 size");
        } catch (Throwable e) {
            if (e instanceof AssertionError)
                throw e;

            Assertions.assertTrue(e instanceof JniExampleException);
            Assertions.assertEquals(901, ((JniExampleException)e).getError());
            Assertions.assertEquals("nativeRandomNumberGeneratorNoEntropy: Size cannot be zero 901", e.getMessage());
        }

        Assertions.assertNull(rand);

        try {
            rand = nativeRandomNumberGeneratorNoEntropy(-1);
            Assertions.fail("Should fail. Can't generate random number with negative size");
        } catch (Throwable e) {
            if (e instanceof AssertionError)
                throw e;

            Assertions.assertTrue(e instanceof JniExampleException);
            Assertions.assertEquals(900, ((JniExampleException)e).getError());
            Assertions.assertEquals("nativeRandomNumberGeneratorNoEntropy: Size value cannot be negative 900", e.getMessage());
        }

        Assertions.assertNull(rand);
    }
}