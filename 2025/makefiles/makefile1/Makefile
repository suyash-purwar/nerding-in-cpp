# If the timestamp of the target is more recent than the prerequisites
# then the instructions don't run, otherwise they do.
# BUT! This only happens when the output file has the same name as that
# of the target.
# In the example below, target name (sample.i) is same as the output file (sample1.i)
sample1.i: sample1.c
	gcc -E sample1.c -o sample1.i
	tail -n 10 a.i

# In the following two rules, there is no output file
# In this case the rule `hello` and `bye` runs everytime
hello:
	echo "Hello World"

bye:
	echo "Bye World"

# In this rule, there is an output file but it is different from the target name
# It runs everytime too
compile: sample1.c
	gcc sample1.c -o a.out
	./a.out
