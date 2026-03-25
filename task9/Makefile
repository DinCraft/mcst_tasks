task9: src/task9.c src/array_alg.c
	gcc ${CFLAGS} src/task9.c src/array_alg.c -o task9

clean:
	rm -f task9
	rm -f test

test: src/test.c src/array_alg.c
	gcc ${CFLAGS} src/test.c src/array_alg.c -o test
	./test
