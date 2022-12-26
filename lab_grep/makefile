project = grep
flags = ad
file = file.txt

$(project): main.c
	gcc main.c -o $(project) -Wall

run: $(project)
	./$(project) $(flags) $(file)

clean:
	rm $(project)