CC = clang
CFLAGS = -Wall -Wextra

main: build/main.o build/lexer.o build/utils.o
	$(CC) $(CFLAGS) $^ -o $@

build/main.o: src/main.c
	mkdir -p build
	$(CC) $(CFLAGS) -c $^ -o $@
src/main.c: src/lexer.h
	touch $@

build/lexer.o: src/lexer.c 
	$(CC) $(CFLAGS) -c $^ -o $@
src/lexer.c: src/lexer.h src/utils/string_view.h
	touch $@


# --------------------- Utils ---------------------
build/utils.o: build/utils/heap_str.o build/utils/string_view.o
	ld -r $^ -o $@

build/utils/heap_str.o: src/utils/heap_str.c
	mkdir -p build/utils
	$(CC) $(CFLAGS) -c $^ -o $@
src/utils/heap_str.c: src/utils/heap_str.h
	touch $@

build/utils/string_view.o: src/utils/string_view.c
	$(CC) $(CFLAGS) -c $^ -o $@
src/utils/string_view.c: src/utils/string_view.h
	touch $@
