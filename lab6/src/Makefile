all : client server

client : head head.h
	gcc -o client MultModulo client.c -lpthread

server : head head.h
	gcc -o server MultModulo server.c -lpthread -fsanitize=address

head : head.h
	gcc -o MultModulo -c MultModulo.c

clean :
	rm -rf client server MultModulo
