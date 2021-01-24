#include "worker.h"

Worker::Worker(int id) : _id{id} { cout << "Cteated worker id: " << _id << endl; }

void Worker::operator()() const { cout << " worker " << _id << " is working" << endl; }
