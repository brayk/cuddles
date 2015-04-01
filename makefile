all:
	gcc -Wall ./src/main.c -o ./cuddles.exe

run:
	./cuddles.exe

edit:
	vim ./src/main.c

clean:
	rm *.exe

