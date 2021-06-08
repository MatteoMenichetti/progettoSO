all : p p.o p1.o p2.o p3.o input_manager decision_function failure_manager main
	@echo 'compilazione completata'
main :
	cc ./src/main.c -o ./main

watchdog : ./lib/ipc.h
	cc ./src/watchdog.c -o watchdog

p : p.o p1.o p2.o p3.o
	cc ./p.o ./p1.o ./p2.o ./p3.o -o p

decision_function : lib/ipc.h
	cc ./src/decision_function.c -o decision_function

input_manager :
	cc ./src/input_manager.c -o input_manager

failure_manager :
	cc ./src/failure_manager.c -o failure_manager

p.o : lib/p.h
	cc -c ./src/p.c

p1.o : lib/p.h
	cc -c ./src/p1.c

p2.o :lib/p.h
	cc -c ./src/p2.c

p3.o : lib/p.h
	cc -c ./src/p3.c


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
	@echo 'install completato'

clean :
	@echo 'clean in esecuzione'
	rm -r bin
	rm -r tmp
	rm -r logs
	@echo 'clean completato'