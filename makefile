all : p p.o p1.o p2.o p3.o ipc.o main watchdog input_manager decision_function failure_manager
	@echo 'compilazione completata'
main : ./lib/common.h
	cc ./src/main.c -o ./main

watchdog : ./lib/ipc.h ipc.o
	cc ./src/watchdog.c ./ipc.o -o watchdog

p : p.o p1.o p2.o p3.o ipc.o
	cc ./p.o ./p1.o ./p2.o ./p3.o ./ipc.o -o p

decision_function : lib/ipc.h ipc.o
	cc ./src/decision_function.c ./ipc.o -o decision_function

input_manager : ./lib/ipc.h ipc.o
	cc ./src/input_manager.c ./ipc.o -o input_manager

failure_manager : ./lib/common.h
	cc ./src/failure_manager.c -o failure_manager

p.o : lib/p.h
	cc -c ./src/p.c

p1.o : lib/p.h
	cc -c ./src/p1.c

p2.o :lib/p.h
	cc -c ./src/p2.c

p3.o : lib/p.h
	cc -c ./src/p3.c

ipc.o : ./lib/ipc.h
	cc -c ./src/ipc.c


install :
	@echo 'install in esecuzione'
	mkdir bin
	mkdir tmp
	mkdir logs
	mv *.o tmp
	mv p bin
	mv failure_manager bin
	mv input_manager bin
	mv decision_function bin
	mv main bin
	mv watchdog bin
	@echo 'install completato'

clean :
	@echo 'clean in esecuzione'
	rm -r bin
	rm -r tmp
	rm -r logs
	@echo 'clean completato'