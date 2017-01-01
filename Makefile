CPPFLAGS = -isystem $(HOME)/opt/fmt/fmt-3.0.0 -isystem /usr/local/include -DDEBUG
CXXFLAGS = -std=c++1z -pedantic -Wall
LDFLAGS =

.PHONY: default
default: main

.PHONY: test
test: main
	./main < input

.PHONY: clean
clean:
	rm -f *.o main

%: %.o
	$(CXX) $(CXXFLAGS) -o $@ *.o $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ -c $<
