all: compile run

compile:
	gcc -fdiagnostics-color=always -g -fsanitize=thread -O0 main.c list.c UnboundedBlockingMPMCQueue.c StaticThreadPool.c -o main
run:
	./main