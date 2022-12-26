project = fifo

all: writer reader


writer: writer.c
	gcc writer.c -o writer -Wall

reader: reader.c
	gcc reader.c -o reader -Wall

run: writer reader
	./writer&
	./reader

clean:
	rm writer
	rm reader