default: compile

compile:
	g++ -std=c++11 ./pseudoSO/src/*.cpp ./pseudoSO/src/*.c -o ./pseudoSO/pseudoSO.out
	gcc ./sistemaArquivos/src/*.c -o ./sistemaArquivos/sistemaArquivos.out

clean:
	rm ./pseudoSO/*.out ./pseudoSO/src/*.c~ ./pseudoSO/src/*.cpp~ ./pseudoSO/include/*.h~ *.txt~ ./pseudoSO/testes/*.out ./sistemaArquivos/*.out ./sistemaArquivos/src/*.c~ ./sistemaArquivos/include/*.h~

<<<<<<< HEAD
run_pseudoSO:
	./pseudoSO/pseudoSO.out $(processes) $(files)
	
run_sistemaArquivos:
	./sistemaArquivos/sistemaArquivos.out $(processes) $(files)

teste_arquivos:
	gcc ./pseudoSO/testes/teste_arquivos.c ./pseudoSO/src/arquivos.c ./pseudoSO/include/arquivos.h -o ./pseudoSO/testes/teste_arquivos.out && ./pseudoSO/testes/teste_arquivos.out files.txt
=======
run:
	./pseudoSO.out $(processes) $(files)

teste_arquivos:
	gcc ./testes/teste_arquivos.c ./src/arquivos.c ./include/arquivos.h -o ./testes/teste_arquivos.out && ./testes/teste_arquivos.out mixed_file.txt
>>>>>>> d1e796a597cf8cc1f6fb95dc6dff06f1f5c6117e

teste_recurso:
	g++ -std=c++11 ./pseudoSO/testes/teste_recurso.cpp ./pseudoSO/src/recurso.cpp ./pseudoSO/src/processos.cpp -o ./pseudoSO/testes/teste_recurso.out && ./pseudoSO/testes/teste_recurso.out

teste_processo:
	g++ -std=c++11 ./pseudoSO/testes/teste_processo.cpp ./pseudoSO/src/processos.cpp -o ./pseudoSO/testes/teste_processo.out && ./pseudoSO/testes/teste_processo.out

teste_filas:
	g++ -std=c++11 ./pseudoSO/testes/teste_filas.cpp ./pseudoSO/src/processos.cpp ./pseudoSO/src/filas.cpp -o ./pseudoSO/testes/teste_filas.out && ./pseudoSO/testes/teste_filas.out
