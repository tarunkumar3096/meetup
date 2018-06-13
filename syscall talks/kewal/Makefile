SRC := $(wildcard *.c)
OBJ := $(SRC:.c=.o)

.PHONY : clean run

FLAG := -Wall

all : prod cons

prod : producer.o
	gcc -o $@ $< -pthread -lrt

cons : consumer.o
	gcc -o $@ $< -pthread -lrt

OBJ : SRC
	gcc -c $@ FLAG $^

clean :
	rm -rf *.o prod cons
