TARGET = ls
FLAGS = -l

all: $(TARGET)

$(TARGET): main.c
	gcc $< -o $@ -Wall -Werror -Wextra

run:
	./$(TARGET) $(FLAGS) $(FILE)

clean:
	rm $(TARGET)