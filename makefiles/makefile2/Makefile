build: build.s
	gcc -c build.s -o build

build.s: build.i
	gcc -S build.i -o build.s

build.i: build.c
	gcc -E build.c -o build.i

build.c:
	echo "int main() { return 0; }" >> build.c

clean_all:
	rm -rf *.c *.i *.s *.o

clean:
	rm -rf *.i *.s *.o build
