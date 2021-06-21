# JNI (Java Native Interface) tutorial for beginners

## Introduction

This tutorial will brief explain to you how to create a simple resource access between your Java VM code and native OS

What you will learn:

- Create a shared library in C containing simple basic functions and simple resource to access your system
- Create your JNI library in C to access your shared library
- Compile JNI shared library, access your custom class, throw an Exception or Throwable through native code
- Integrate JNI to your Java or Kotlin
- Create a documentation for C using Doxygen
- Create a documentation for Java using Javadoc
- Integrate tests

### Create a shared library in C containing simple basic functions

To create a native library in your OS system you need:

- _Install a C compiler_ e.g.: gcc for unix system (Linux, Mac) or Visual Studio for Windows
- _Install the latest version of Java 8 or 11_ in your machine
- _Clone this repository_
- _Run **Make**_ to compile this source code
- _Run this example_ in your JVM

TODO ...

## Compiling libraries

- Just type

```sh
cd <YOUR_PROJECT>/src/main/util && make
```

- To test your library

```sh
cd <YOUR_PROJECT>/src/main/util && make test
```

### Cleaning compiled library

Just type in your _src/main/util_ folder:

```sh
make clean
```

## Contact

mailto: fabioegel@gmail.com

## License

MIT

