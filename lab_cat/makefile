TARGET = cat
FILE =	file
FLAGS = -n

all: $(TARGET)

$(TARGET): main.c
	gcc $< -o $@ -Wall -Werror -Wextra

run:
	./$(TARGET) $(FILE) $(FLAGS)

clean:
	rm $(TARGET)