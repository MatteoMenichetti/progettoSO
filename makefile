all : p p.o p1.o p2.o p3.o input_manager decision_function failure_manager
	@echo 'compilazione completato'
p : p.o p1.o p2.o p3.o
	cc ./p.o ./p1.o ./p2.o ./p3.o -o p

decision_function : src/decision_function.c lib/ipc.h
	cc ./src/decision_function.c ./lib/ipc.h -o decision_function

input_manager : src/input_manager.c
	cc ./src/input_manager.c -o input_manager

failure_manager : src/failure_manager.c
	cc ./src/failure_manager.c -o failure_manager

p.o : src/p.c lib/p.h
	cc -c ./src/p.c

p1.o : src/p1.c lib/p.h
	cc -c ./src/p1.c

p2.o : src/p2.c lib/p.h
	cc -c ./src/p2.c

p3.o : src/p3.c lib/p.h
	cc -c ./src/p3.c


install :
	@echo 'install in esecuzione'
	mkdir bin
	mkdir tmp
	mv *.o tmp
	mv p bin
	mv failure_manager bin
	mv input_manager bin
	mv decision_function bin
	@echo 'install completato'

clean :
	@echo 'clean in esecuzione'
	rm -r bin
	rm -r tmp
	@echo 'clean completato'