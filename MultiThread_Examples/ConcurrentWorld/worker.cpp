#include "worker.h"

Worker::Worker(int id) : _id{id} {}

void Worker::operator()() const { cout << " worker " << _id << " is working" << endl; }
