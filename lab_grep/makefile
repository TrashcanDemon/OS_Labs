TARGET = grep
FILE = file.txt
FLAGS = ad

all: $(TARGET)

$(TARGET): main.c
	gcc $< -o $@ -Wall -Werror -Wextra

run:
	./$(TARGET) $(FLAGS) $(FILE)

clean:
	rm $(TARGET)