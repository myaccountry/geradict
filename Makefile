static: libgeradict.a

libgeradict.a: geradict.o
	ar rcs $@ $^

geradict.o: geradict.cpp geradict.h
	g++ -c $< -o $@

clean:
	rm geradict.o libgeradict.a

install:
	sudo cp libgeradict.a /usr/local/lib/ && sudo cp geradict.h /usr/local/include/

all:
	make && make install && make clean