all: libnative-exec.so

libnative-exec.so: native-exec.o
	$(CC) $^ -o $@ -shared -Wl,-soname,native-exec

native-exec.o: native-exec.c
	$(CC) -c -o $@ -fPIC $^ -I/usr/lib/jvm/default-java/include \
		-I/usr/lib/jvm/default-java/include/linux

clean:
	rm -f *.o *.so *.jar *.class com/huawei/NativeExec.class
