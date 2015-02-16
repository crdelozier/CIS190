CXXFLAGS=-std=c++11
OBJS=bigint.o main.o

all: $(OBJS)
	g++ -o main $(OBJS) $(CXXFLAGS)

bigint.o:
	g++ -c bigint.cpp $(CXXFLAGS)

main.o:
	g++ -c main.cpp $(CXXFLAGS)

clean:
	rm *.o main
