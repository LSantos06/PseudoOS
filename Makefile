default: compile

compile:
	g++ -std=c++11 ./src/*.cpp ./src/*.c -o pseudoSO.out

clean:
	rm *.out ./src/*.c~ ./include/*.h~ *.txt~ ./testes/*.out

run:
<<<<<<< HEAD
	./pseudoSO.out processes.txt files.txt
=======
	./main.out

teste_recurso:
	g++ -std=c++11 ./testes/teste_recurso.cpp ./src/recurso.cpp ./src/processos.cpp -o ./testes/teste_recurso.out && ./testes/teste_recurso.out

teste_processo:
	g++ -std=c++11 ./testes/teste_processo.cpp ./src/processos.cpp -o ./testes/teste_processo.out && ./testes/teste_processo.out

teste_filas:
	g++ -std=c++11 ./testes/teste_filas.cpp ./src/processos.cpp ./src/filas.cpp -o ./testes/teste_filas.out && ./testes/teste_filas.out

>>>>>>> e74c2950e96ad81dcf4875df2c113c07bea3870f
