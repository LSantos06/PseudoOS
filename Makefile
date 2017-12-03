files= main.cpp filas.cpp arquivos.c dispatcher.cpp processos.cpp recurso.cpp memoria.cpp

default: compile

compile:
	g++ -std=c++11 $(files) -o main.out

clean:
	rm *.out *.c~ *.h~ *.txt~

run:
	./main.out
