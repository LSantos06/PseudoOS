default: compile

compile:
	g++ -std=c++11 main.cpp -o main.out

clean:
	rm *.out *.c~ *.h~ *.txt~

run:
	./main.out