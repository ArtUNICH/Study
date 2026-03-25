TARGET = imageprog

CC = gcc
CFLAGS = -Wall -g

all: $(TARGET)

$(TARGET): main.c lodepng.c
	$(CC) $(CFLAGS) main.c lodepng.c -o $(TARGET)

clean:
	rm -f $(TARGET) contrast.png gauss.png picture_out.png intermediate_result.png