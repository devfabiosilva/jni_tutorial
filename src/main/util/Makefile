#
#	AUTHOR: Fábio Pereira da Silva
#	YEAR: 2021
#	LICENSE: MIT
#	EMAIL: fabioegel@gmail.com
#

# Generating tools
#thu mar 04 14:52:02 -03 2021
CC=gcc
STRIP=strip
EXECSTACK=execstack -c
INCLUDEDIR=$(PWD)/include/
LIBNAME=jniexample
CURDIR=$(PWD)
JAVAINCLUDE=/usr/lib/jvm/java-11-openjdk-amd64/include
JAVAINCLUDE_LINUX=/usr/lib/jvm/java-11-openjdk-amd64/include/linux
MAINFILE=jni_example
JNI_EXAMPLE_UTILS=jni_example_utils
FOREIGN_LIBRARY=foreign_library
C_SRC=$(PWD)/c_src
JNI_EXAMPLE_SUFFIX=-I$(INCLUDEDIR) -I$(JAVAINCLUDE) -I$(JAVAINCLUDE_LINUX)
PLATFORM?=UNIX

all: main

lib$(FOREIGN_LIBRARY).so: $(C_SRC)/$(FOREIGN_LIBRARY).c
	@echo "Compiling $(FOREIGN_LIBRARY).o object ..."
	@$(CC) -O2 -fPIC -c $(C_SRC)/$(FOREIGN_LIBRARY).c -o $(C_SRC)/$(FOREIGN_LIBRARY).o $(JNI_EXAMPLE_SUFFIX) -D$(PLATFORM)
	@echo "Compiling lib$(FOREIGN_LIBRARY).so ..."
	@$(CC) -O2 -shared $(C_SRC)/$(FOREIGN_LIBRARY).o -o lib$(FOREIGN_LIBRARY).so
	@echo "Stripping lib$(FOREIGN_LIBRARY).so ..."
	@$(STRIP) lib$(FOREIGN_LIBRARY).so
	@chmod -x lib$(FOREIGN_LIBRARY).so

$(JNI_EXAMPLE_UTILS).o: $(C_SRC)/$(JNI_EXAMPLE_UTILS).c
	@echo "Compiling $(JNI_EXAMPLE_UTILS).o object ..."
	@$(CC) -O2 -fPIC -c $(C_SRC)/$(JNI_EXAMPLE_UTILS).c -o $(C_SRC)/$(JNI_EXAMPLE_UTILS).o $(JNI_EXAMPLE_SUFFIX)

$(MAINFILE).o: $(C_SRC)/$(MAINFILE).c
	@echo "Compiling $(MAINFILE).o object ..."
	@$(CC) -O2 -fPIC -c $(C_SRC)/$(MAINFILE).c -o $(C_SRC)/$(MAINFILE).o $(JNI_EXAMPLE_SUFFIX)

main: lib$(FOREIGN_LIBRARY).so $(JNI_EXAMPLE_UTILS).o $(MAINFILE).o
	@echo "Compiling lib$(LIBNAME).so ..."
	@$(CC) -O2 -shared -o lib$(LIBNAME).so $(C_SRC)/$(MAINFILE).o $(C_SRC)/$(JNI_EXAMPLE_UTILS).o $(JNI_EXAMPLE_SUFFIX) -L$(PWD) -l$(FOREIGN_LIBRARY)
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
	@echo "Cleaning $(JNI_EXAMPLE_UTILS).o object ..."
	rm $(C_SRC)/$(JNI_EXAMPLE_UTILS).o
	@echo "Cleaning $(MAINFILE).o object ..."
	rm $(C_SRC)/$(MAINFILE).o
	@echo "Cleaning lib$(LIBNAME) library..."
	rm lib$(LIBNAME).so
	@echo "Cleaning lib$(FOREIGN_LIBRARY).so library..."
	rm lib$(FOREIGN_LIBRARY).so
