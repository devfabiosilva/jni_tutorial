package org.jni.example.exceptions;

public class JniExampleException extends Throwable {
    private final int error;

    JniExampleException(String message) {
        super(message);
        this.error= -1;
    }

    JniExampleException(String message, int error) {
        super(message);
        this.error = error;
    }

    public int getError() {
        return error;
    }
}