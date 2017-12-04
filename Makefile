default: compile

compile:
	g++ -std=c++11 ./src/*.cpp ./src/*.c -o pseudoSO.out

clean:
	rm *.out ./src/*.c~ ./include/*.h~ *.txt~

run:
	./pseudoSO.out processes.txt files.txt
