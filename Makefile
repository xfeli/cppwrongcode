all : test

CXX ?= g++

test.o : test.cpp
	$(CXX) -DWRONG_CODE -std=c++11 -c test.cpp
test : test.o
	$(CXX) test.o -o test
clean:
	rm test.o test
