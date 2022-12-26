TARGET1 = writer
TARGET2 = reader

all: $(TARGET1) $(TARGET2)

$(TARGET1): writer.c
	gcc $< -o $@ -Wall -Werror -Wextra

$(TARGET2): reader.c
	gcc $< -o $@ -Wall -Werror -Wextra

run:
	./$(TARGET1)
	./$(TARGET2)

clean:
	rm $(TARGET1)
	rm $(TARGET2)