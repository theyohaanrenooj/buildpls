buildpls: main.o
	cc -o buildpls main.o
	
main.o: src/main.c
	cc -c src/main.c -o main.o

clean:
	rm -r main.o

install: buildpls
	sudo mv buildpls /usr/bin/buildpls
