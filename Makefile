task1: task1_pthread.c
	gcc -o task1_pthread task1_pthread.c
task2: task2_ptread.c
	gcc -o task2_thread task2_pthread.c
task3: task1.c
	gcc -o task3 task3.c
task4: task4.c
	gcc -o task4 task4.c	
clean:
	rm -f *.o task1_pthread task1 task2 task2_pthread task3 task4