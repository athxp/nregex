# Simple build
RM = rm
CFLAGS = -std=c99 -g -Wall -I.
ifeq ($(OS),Windows_NT)
	EXT = .exe
	RM = del
endif

OUT = nnfa$(EXT)
OBJ = nnfa.o 

.PHONY: all
all: clean build

.PHONY: build
build: $(OUT)

.PHONY: clean
clean: 
	$(RM) *.o 

.PHONY: run
run:$(OUT)
	./$(OUT)

$(OUT): $(OBJ) $(INC)
	gcc -o $@ $^ $(CFLAGS)  

%.o : %.c $(INC)
	gcc -c -o $@ $< $(CFLAGS) 