default: compile

compile:
	g++ dispatcher.cpp -o dispatcher.out

clean:
	rm *.out

run:
	./dispatcher.out processes.txt files.arq