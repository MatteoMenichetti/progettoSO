cc -c ./src/ipc.c ;
cc -c ./src/watchdog.c ;
cc ./src/watchdog.c ./ipc.o -o ./bin/watchdog ;
cc -c src/p.c ; cc -c src/p1.c ; cc -c ./src/p2.c ; cc -c ./src/p3.c ;
cc ./p.o ./p1.o ./p2.o ./p3.o ./ipc.o -o ./bin/p ;
cc ./src/failure_manager.c -o ./bin/failure_manager ;
cc ./src/input_manager.c ./ipc.o -o ./bin/input_manager ;
cc ./src/decision_function.c ./ipc.o -o ./bin/decision_function ;
cc ./src/main.c ./ipc.o -o ./bin/main ; mv *.o tmp ;