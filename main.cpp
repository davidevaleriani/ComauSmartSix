//Example that uses the RobotComau library to move from a starting position towards
//a set of different points, and then back to the initial position (after a keypress).
//
//Developed by Davide Valeriani
//www.davidevaleriani.it

#include "libs/RobotComau.h"
#include "libs/pthread.h"

RobotComau r("192.168.1.101", 10000, 10001);

bool stop = false;

void * getPos (void * arg) {
    Point6d p1;
	ofstream fout("trace.txt");
    while (!stop) {
		p1 = r.GetCurrentPositionOR();
        fout << p1;
    }
	fout.close();
    return NULL;
}

void * motion (void * arg) {
	r.SetSpeed("30");
	r.MoveLinearTo("starting_point.txt");
	r.MoveRelative(0, 0, -200);
	r.MoveRelative(0, 100, 0);
	r.MoveRelative(0, 0, 200);
	r.MoveRelative(0, 100, 0);
	r.MoveRelative(0, 0, -200);
	r.MoveRelative(0, 100, 0);
	r.MoveRelative(0, 0, 200);
	r.MoveRelative(0, 100, 0);
	r.MoveRelative(0, 0, -200);
	r.MoveRelative(0, 100, 0);
	r.MoveRelative(0, 0, 200);
	stop = true;
	system("PAUSE");
	r.MoveLinearTo("starting_point.txt");
	r.CloseConnection();
	return NULL;
}

int main () {
    pthread_t thread1;
	pthread_t thread2;
    pthread_create(&thread2, NULL, motion, NULL);
	pthread_create(&thread1, NULL, getPos, NULL);
	pthread_join(thread2, NULL);
	pthread_join(thread1, NULL);
}
