default: compile

compile:
	g++ -std=c++11 ./src/*.cpp ./src/*.c -o main.out

clean:
	rm *.out ./src/*.c~ ./include/*.h~ *.txt~ ./testes/*.out

run:
	./main.out

teste_recurso:
	g++ -std=c++11 ./testes/teste_recurso.cpp ./src/recurso.cpp ./src/processos.cpp -o ./testes/teste_recurso.out && ./testes/teste_recurso.out

teste_processo:
	g++ -std=c++11 ./testes/teste_processo.cpp ./src/processos.cpp -o ./testes/teste_processo.out && ./testes/teste_processo.out

teste_filas:
	g++ -std=c++11 ./testes/teste_filas.cpp ./src/processos.cpp ./src/filas.cpp -o ./testes/teste_filas.out && ./testes/teste_filas.out

