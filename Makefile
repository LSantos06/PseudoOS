default: compile

compile:
	g++ -std=c++11 dispatcher.cpp -o dispatcher.out

clean:
	rm *.out

run:
	./dispatcher.out processes.txt files.arq