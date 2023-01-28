all: prog0

prog0: prog0.o libuser.a
	gcc -o prog0 prog0.o -L. -luser

prog0.o: prog0.c user.h
	gcc -c prog0.c

libuser.a: user.o
	ar rcs libuser.a user.o

user.o: user.c user.h
	gcc -c user.c


clean:
	rm -f prog0 prog0.o user.o libuser.a