compile: rand.c
	gcc rand.c -o rand

run: rand
	./rand

clean:
	rm *~
