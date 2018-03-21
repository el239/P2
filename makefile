all: P2

P2: main.o sequence.o test.o k-assembler.o EulerPath.o deBruijnByStringComp.o deBruijnByHash.o
	g++ main.o sequence.o test.o k-assembler.o EulerPath.o deBruijnByStringComp.o deBruijnByHash.o -o P2

main.o: main.cpp
	g++ -c main.cpp

sequence.o: sequence.cpp sequence.hpp
	g++ -c sequence.cpp
	
test.o: test.cpp
	g++ -c test.cpp

k-assembler.o: k-assembler.cpp k-assembler.hpp
	g++ -c k-assembler.cpp
	
EulerPath.o: EulerPath.cpp
	g++ -c EulerPath.cpp

deBruijnByHash.o: deBruijnByHash.cpp
	g++ -c deBruijnByHash.cpp
	
deBruijnByStringComp.o: deBruijnByStringComp.cpp
	g++ -c deBruijnByStringComp.cpp

clean:
	rm *o P2