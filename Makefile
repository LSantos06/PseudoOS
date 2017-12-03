default: compile

compile:
	g++ -std=c++11 ./src/*.cpp ./src/*.c -o main.out

clean:
	rm *.out ./src/*.c~ ./include/*.h~ *.txt~

run:
	./main.out
