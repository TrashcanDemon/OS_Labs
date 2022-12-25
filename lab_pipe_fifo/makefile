TARGET1 = pipe
TARGET2 = fifo

all: $(TARGET1) $(TARGET2)

$(TARGET1): pipe.c
	gcc $< -o $@ -Wall -Werror -Wextra

$(TARGET2): fifo.c
	gcc $< -o $@ -Wall -Werror -Wextra

run:
	./$(TARGET1)
	./$(TARGET2)

run_pipe:
	./$(TARGET1)

run_fifo:
	./$(TARGET2)

clean:
	rm $(TARGET1)
	rm $(TARGET2)