default: compile

compile:
	g++ -std=c++11 ./src/*.cpp ./src/*.c -o main.out

clean:
	rm *.out ./src/*.c~ ./include/*.h~ *.txt~

run:
	./main.out

teste_processo:
	g++ -std=c++11 ./testes/teste_processo.cpp ./src/processos.cpp -o ./testes/teste_processo

teste_filas:
	g++ -std=c++11 ./testes/teste_filas.cpp ./src/processos.cpp ./src/filas.cpp -o ./testes/teste_filas
