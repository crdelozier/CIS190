CXXFLAGS=-std=c++11
OBJS=types.o abilities.o pokemon.o driver.o

all: $(OBJS)
	$(CXX) -o pokemon $(OBJS) $(CXXFLAGS)

%.o: %.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

clean:
	rm $(OBJS) pokemon
