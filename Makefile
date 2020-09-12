CC = g++
CFLAGS = -w
LDFLAGS = -lSDL2 -lSDL2_image

EXEC = ThanksEngine.out

SRC=$(wildcard *.cpp)
OBJ=$(SRC: .cpp=.o)

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS) 

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS) $(CFLAGS)

clean:
	rm -f *.o

mrproper: clean
	rm -f $(EXEC)
