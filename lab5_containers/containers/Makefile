all: container-test container

container-test: container-test.c
	gcc -O -o container-test container-test.c

container: container.c
	gcc -O -o container container.c

clean:
	rm -f container-test container
