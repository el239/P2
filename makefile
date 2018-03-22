
all: P2

P2: main.o sequence.o test.o k-assembler.o EulerPath.o deBruijnByStringComp.o deBruijnByHash.o
	g++ main.o sequence.o test.o k-assembler.o EulerPath.o deBruijnByStringComp.o deBruijnByHash.o -o P2

main.o: main.cpp
	g++ -c main.cpp

test.o: test.cpp
	g++ -c -std=c++11 test.cpp

k-assembler.o: k-assembler.cpp k-assembler.hpp
	g++ -c -std=c++11 k-assembler.cpp

sequence.o: sequence.cpp sequence.hpp
	g++ -c -std=c++11 sequence.cpp 

EulerPath.o: EulerPath.cpp
	g++ -c -std=c++11 EulerPath.cpp 

deBruijnByHash.o: deBruijnByHash.cpp
	g++ -c -std=c++11 deBruijnByHash.cpp
	
deBruijnByStringComp.o: deBruijnByStringComp.cpp
	g++ -c -std=c++11 deBruijnByStringComp.cpp 

clean:
	rm *o 
