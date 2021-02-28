#
#	AUTHOR: Fábio Pereira da Silva
#	YEAR: 2020
#	LICENSE: MIT
#	EMAIL: fabioegel@gmail.com or fabioegel@protonmail.com
#

# Generating tools
#dom dez 06 16:49:52 -03 2020 
CC=gcc
STRIP=strip
EXECSTACK=execstack -c
INCLUDEDIR=$(PWD)/include/
LIBNAME=jniexample
CURDIR=$(PWD)
JAVAINCLUDE=/usr/lib/jvm/java-11-openjdk-amd64/include
JAVAINCLUDE_LINUX=/usr/lib/jvm/java-11-openjdk-amd64/include/linux
MAINFILE=jni_example
JNI_EXAMPLE_EXCEPTION=jni_example_exception
FOREIGN_LIBRARY=foreign_library
C_SRC=$(PWD)/c_src
JNI_EXAMPLE_SUFFIX=-I$(INCLUDEDIR) -I$(JAVAINCLUDE) -I$(JAVAINCLUDE_LINUX)

all: main

$(FOREIGN_LIBRARY).o: $(C_SRC)/$(FOREIGN_LIBRARY).c
	@echo "Compiling $(FOREIGN_LIBRARY).o object ..."
	@$(CC) -O2 -fPIC -c $(C_SRC)/$(FOREIGN_LIBRARY).c -o $(C_SRC)/$(FOREIGN_LIBRARY).o $(JNI_EXAMPLE_SUFFIX)

$(JNI_EXAMPLE_EXCEPTION).o: $(C_SRC)/$(JNI_EXAMPLE_EXCEPTION).c
	@echo "Compiling $(JNI_EXAMPLE_EXCEPTION).o object ..."
	@$(CC) -O2 -fPIC -c $(C_SRC)/$(JNI_EXAMPLE_EXCEPTION).c -o $(C_SRC)/$(JNI_EXAMPLE_EXCEPTION).o $(JNI_EXAMPLE_SUFFIX)

$(MAINFILE).o: $(C_SRC)/$(MAINFILE).c
	@echo "Compiling $(MAINFILE).o object ..."
	@$(CC) -O2 -fPIC -c $(C_SRC)/$(MAINFILE).c -o $(C_SRC)/$(MAINFILE).o $(JNI_EXAMPLE_SUFFIX)

main: $(FOREIGN_LIBRARY).o $(JNI_EXAMPLE_EXCEPTION).o $(MAINFILE).o
	@echo "Compiling lib$(LIBNAME).so ..."
	@$(CC) -O2 -shared -o lib$(LIBNAME).so $(C_SRC)/$(MAINFILE).o $(C_SRC)/$(JNI_EXAMPLE_EXCEPTION).o $(C_SRC)/$(FOREIGN_LIBRARY).o $(JNI_EXAMPLE_SUFFIX)
	@echo "Striping $(LIBNAME).so ..."
	@$(STRIP) lib$(LIBNAME).so
	@echo "Disabling execstack ..."
	@$(EXECSTACK) lib$(LIBNAME).so
	@echo "Unchecking executable library ..."
	@chmod -x lib$(LIBNAME).so
	@echo "Finished"

.PHONY: clean
clean:
	@echo "Cleaning $(FOREIGN_LIBRARY).o object ..."
	rm $(C_SRC)/$(FOREIGN_LIBRARY).o
	@echo "Cleaning $(JNI_EXAMPLE_EXCEPTION).o object ..."
	rm $(C_SRC)/$(JNI_EXAMPLE_EXCEPTION).o
	@echo "Cleaning $(MAINFILE).o object ..."
	rm $(C_SRC)/$(MAINFILE).o
	@echo "Cleaning $(LIBNAME) library..."
	rm lib$(LIBNAME).so

