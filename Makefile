CC=gcc
CFLAGS= -c -Wall -ansi -pedantic
sdes: crypt.o key_gen.o s_DES.o main.o
	$(CC) crypt.o key_gen.o s_DES.o main.o -o sdes
s_DES_test: crypt.o key_gen.o s_DES.o s_DES_test.o
	$(CC) crypt.o key_gen.o s_DES.o s_DES_test.o -o s_DES_test
key_gen_test: crypt.o key_gen.o key_gen_test.o
	$(CC) crypt.o key_gen.o key_gen_test.o -o key_gen_test
main.o: main.c key_gen.h s_DES.h
	$(CC) $(CFLAGS) main.c
s_DES_test.o: s_DES_test.c s_DES.h key_gen.h
	$(CC) $(CFLAGS) s_DES_test.c
s_DES.o: s_DES.c crypt.h
	$(CC) $(CFLAGS) s_DES.c
key_gen_test.o: key_gen_test.c key_gen.h crypt.h
	$(CC) $(CFLAGS) key_gen_test.c
crypt.o: crypt.c crypt.h 
	$(CC) $(CFLAGS) crypt.c
key_gen.o: key_gen.c crypt.h
	$(CC) $(CFLAGS) key_gen.c
clean:
	rm -rf *.o key_gen_test s_DES_test sdes
