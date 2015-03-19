CXXFLAGS = -g -std=c++11

all: karaoke.o main.o cleaner
	$(CXX) -Wall karaoke.o main.o -o karaoke $(CXXFLAGS)

main.o: main.cpp
	$(CXX) -c -Wall main.cpp $(CXXFLAGS)

karaoke.o: karaoke.cpp list.hpp karaoke.hpp
	$(CXX) -c -Wall karaoke.cpp $(CXXFLAGS)

clean: 
	rm -f *.o karaoke

cleaner: 
	rm -f *~

cleanest: clean cleaner 

