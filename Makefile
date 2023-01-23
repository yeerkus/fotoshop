EXENAME = lab_intro
OBJS = main.o PNG.o RGBAPixel.o lodepng.o lab_intro.o

CXX = clang++
CXXFLAGS = -std=c++14 -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++14 -lpng -lpthread -lm

all : $(EXENAME)

$(EXENAME) : $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

main.o : main.cpp lab_intro.h cs221util/PNG.h cs221util/RGBAPixel.h
	$(CXX) $(CXXFLAGS) main.cpp

lab_intro.o : lab_intro.cpp lab_intro.h
	$(CXX) $(CXXFLAGS) lab_intro.cpp

PNG.o : cs221util/PNG.cpp cs221util/PNG.h cs221util/RGBAPixel.h cs221util/lodepng/lodepng.h
	$(CXX) $(CXXFLAGS) cs221util/PNG.cpp

RGBAPixel.o : cs221util/RGBAPixel.cpp cs221util/RGBAPixel.h
	$(CXX) $(CXXFLAGS) cs221util/RGBAPixel.cpp

lodepng.o : cs221util/lodepng/lodepng.cpp cs221util/lodepng/lodepng.h
	$(CXX) $(CXXFLAGS) cs221util/lodepng/lodepng.cpp


test: basic.o PNG.o RGBAPixel.o lodepng.o lab_intro.o
	$(LD) basic.o PNG.o RGBAPixel.o lodepng.o lab_intro.o $(LDFLAGS) -o test

basic.o : tests/basic.cpp tests/catch.hpp
	$(CXX) $(CXXFLAGS) tests/basic.cpp


clean :
	-rm -f *.o $(EXENAME) test
