CXXFLAGS=-std=c++11

OBJS=driver.o points.o

all: points

points: $(OBJS)
	$(CXX) -o points $(OBJS) $(CXXFLAGS)

%.o: %.c
	$(CXX) -c $< -o $@ $(CXXFLAGS)

%.o: %.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

clean:
	rm $(OBJS) points
