default: compile

compile:
	g++ -std=c++11 ./src/*.cpp ./src/*.c -o main.out

compile_tests:
	g++ -std=c++11 teste_recurso.cpp ./src/recurso.cpp ./src/processos.cpp -o teste_recurso.out

clean:
	rm *.out ./src/*.c~ ./include/*.h~ *.txt~

run:
	./main.out

test_recurso:
	./teste_recurso.out

test_memoria:
	./teste_memoria.out
