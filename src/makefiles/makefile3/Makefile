steps := one two three

all: $(steps)

one:
	echo "one"
two three:
	echo $@


files := file1.c file2.c

create: $(files)
	echo "files are ready"

file1.c file2.c:
	touch $@

clean:
	rm *.c