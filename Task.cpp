#include <iostream>
#include <math.h>
#include "Task.h"
using namespace std;

///////////////////////////////////////////////////////////////////////////
//
// Public operators and methods
bool TaskQueue::enqueue(const Task& t){ // Add a new task
	if(_numItems >= _queueSize){ //QUEUE IS FULL
		return false;
	}
	if(_back ==_queueSize-1){
		_back = 0;
	}
	else{
		_back++;
	}	
	
	
	int length = 0;
	int i = 0;
	while (t.description[i] != '\0'){
		length++;
		i++;
	}
	if(length != 0){
		_tasks.description = new (std::nothrow) char [length];
		i = 0;
		while (t.description[i] != '\0'){
			_tasks.description[i] = t.description[i];
			i++;
		}
	}
	_tasks [_back] = t;
	_numItems ++;
	return true;
}  
Task* TaskQueue::dequeue(){// Remove current task
	if(_numItems == 0){ //QUEUE is EMPTY
		return NULL;
	}
	if(_front == _queueSize-1){
		_front = 0;
	}
	else {
		_front++;
	}
	_numItems--;
	return &_tasks[_front-1];
}
const Task* TaskQueue::peek() const { // What is current task?
	return &_tasks[_front];
}
const Task* TaskQueue::next(const Task::TaskType& t) const{// Return next task of type t
	if(_front < 0){
		return NULL;
	}
	for (int i = _front; i<= _back; i++){
		if(_tasks[i].type == t){
			return &_tasks[i];
		}
	}
	return 0;
}  
bool TaskQueue::isFull() const{// Queue is full
	if(_numItems >= _queueSize){ //QUEUE IS FULL
		return true;
	}
	else {
		return false;
	}
}                      
bool TaskQueue::isEmpty() const{ // Queue is empty
	if(_numItems == 0){ //QUEUE is EMPTY
		return true;
	}
	else{
		return false;
	}
}                    
bool TaskQueue::quarterFull() const {// Queue is < quarter full   
	if(_numItems <= 0.25*(_queueSize)){
		return true;
	}

	else {
		return false;
	}
}           
bool TaskQueue::doubleQueueSize(){// Double queue size
	
	_queueSize = 2*_queueSize;
	
	Task* temp = new (std::nothrow) Task [_queueSize];

	if(temp == 0){
		return false;
	}
	
	for (int i = _front; i <= _back; i++)
		temp[i] = _tasks[i];

	delete[] _tasks;

	_tasks = temp;

	return true;

}
bool TaskQueue::halveQueueSize(){// Halve queue size	

	if(_queueSize < _numItems){
		return false;
	}
	if(_queueSize/2 < _numItems){
		return false;
	}
	
	_queueSize = 0.5*_queueSize;
	
	Task* temp = new (std::nothrow) Task [_queueSize];

	if(temp == 0){
		return false;
	}
	
	for (int i = _front; i<=_back; i++)
		temp[i] = _tasks[i];

	delete[] _tasks;

	_tasks = temp;

	return true;

} 
///////////////////////////////////////////////////////////////////////////
// Constructors and Destructor
//
TaskQueue::TaskQueue(){
	_front = 0;
	_back = -1;
	_numItems = 0;
	_queueSize = INITIAL_TASKQUEUE_SIZE;  // Current size of _tasks
	_tasks = new (std::nothrow) Task [_queueSize];      // Wrap-around array

	if(_tasks == 0){
		return;
	}

}

TaskQueue::~TaskQueue(){
	_front = 0;
	_back = 0;
	_numItems = 0;
	_queueSize = 0;  // Current size of _tasks
	delete[] _tasks;
	//tasks = new  Task[1000];if (tasks == 0) {// Unable to allocate space for 1000 Tasks...}
}


#ifndef MARMOSET_TESTING

int main() {
	Task Morning={Task::MAKE_BED,345, "Hello"};

	TaskQueue tq;

	cout << tq.enqueue(Morning) << endl;

	return 0;
}

#endif



