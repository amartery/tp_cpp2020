TARGET = main.out

# XXX: Don't forget backslash at the end of any line except the last one
# Main
HDRS = \
	   project/include

SRCS = \
	   project/src/main.c \
	   project/src/matrix.c


.PHONY: all main clean

all: main

main: $(SRCS)
	$(CC) -Wall -Wextra -Werror $(addprefix -I,$(HDRS)) -o $(TARGET) $(CFLAGS) $(SRCS) -lm

clean:
	rm -f $(TARGET)
