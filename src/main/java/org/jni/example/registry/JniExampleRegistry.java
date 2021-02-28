package org.jni.example.registry;

public class JniExampleRegistry {
    private Long id = null;
    private String name = null;
    private Integer age = null;
    private String occupation = null;

    private JniExampleRegistry() {}

    public Long getId() {
        return this.id;
    }

    public String getName() {
        return this.name;
    }

    public Integer getAge() {
        return this.age;
    }

    public String getOccupation() {
        return this.occupation;
    }
}
