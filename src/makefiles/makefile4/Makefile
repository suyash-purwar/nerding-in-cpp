app_src_files := $(wildcard *.c)
app_obj_files := $(app_src_files:%.c=build/%.o)

test:
	echo $(app_obj_files)

build_app: $(app_obj_files)
	gcc $< -o build/app

build/%.o: %.c
	gcc -c $< -o $@

#build/libs/%.o: libs
#	gcc -c $< -o $@