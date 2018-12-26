#include <iostream>
#include <math.h>
#include "PriorityTask.h"
using namespace std;

///////////////////////////////////////////////////////////////////////////
//
// Public operators and methods

/*bool TaskQueue::enqueue(const Task& t){ // Add a new task
	
	if(_numItems > _queueSize){
		return false;
	}
	if(t.daysTillDue <= 0){
		return false;
	}
	Node *newTask = new (std::nothrow) Node;
	if (newTask == NULL){
		return false;
	}
	newTask -> _task = t;
	newTask -> dueOn = t.daysTillDue + _currentDay;
	//newTask -> _task.daysTillDue = newTask -> dueOn;
	
	int length = 0;
	int i = 0;
	while (t.description[i] != '\0'){
		length++;
		i++;
	}
	if(length != 0){
		newTask -> _task.description = new (std::nothrow) char [length];
		i = 0;
		while (t.description[i] != '\0'){
			newTask -> _task.description[i] = t.description[i];
			i++;
		}
	}
	if(newTask -> dueOn < _currentDay){
		return false;
	}
		
	if (front == NULL && rear == NULL){//first one
		front = newTask;
		rear = newTask;
		newTask -> next = front;
		return true;
		
	}  
	else{
		Node* currentTask = front;
		Node* prevTask = front;

		if(currentTask -> dueOn < newTask -> dueOn){ // put infront
			newTask -> next = currentTask -> next;
			currentTask -> next = newTask;
			cout << front -> _task.taskID << "infron" << endl;
			cout << rear -> _task.taskID << "infron" << endl;
			return true;
		}*/
		/*if(front == rear){	
			if(newTask -> dueOn < front -> dueOn){
				//GOES BEFORE
				newTask -> next = front -> next;
				front = newTask;
				_numItems++;
				return true;
			}
			if(newTask -> dueOn > front -> dueOn){
				//GOES After
				front -> next = newTask;
				rear = newTask;
				newTask -> next = rear;
				_numItems++;
				return true;
			}
		}
		//goes after prev and before current
		while(currentTask -> dueOn <= newTask -> dueOn && currentTask != rear){ 
			prevTask = currentTask;
			currentTask = currentTask -> next;
				
			
		}
		if(currentTask == front){
			newTask -> next = front;
			front = newTask;
			_numItems++;
			return true;
		}
		if(currentTask == rear){
			if(newTask -> dueOn < currentTask -> dueOn)	{
			prevTask -> next = newTask;
			newTask -> next = currentTask;
			_numItems++;
			return true;
		}

		currentTask -> next = newTask;
		rear = newTask;
		newTask -> next = rear;
	}
	
	_numItems++;

	return true;

	}  
}*/
bool TaskQueue::enqueue(const Task& t) {


    if (t.daysTillDue < 0) {
        return false;
    }

    Node* newTask = new (std::nothrow) Node;

    if (newTask == 0) {
        return false;
    } 

    int length = 0;
    if (t.description != 0) {
        for (int i = 0; t.description[i] != 0; i++) { //Length of description
            length++;
        } 
    }

    newTask -> _task = t;
    newTask -> _task.daysTillDue += _currentDay;

    if (length != 0) { //Copies description
        char* sary = new (std::nothrow) char[length];

        if (sary == 0) {
            delete newTask;
            return false;
        }
        
        newTask -> _task.description = sary;

        for (int i = 0; t.description[i] != 0; i++) {
            newTask -> _task.description[i] = t.description[i];
        } 
    }

    if (front == 0 && rear == 0) {
        newTask -> next = NULL;
        front = newTask;
        rear = newTask;
        return true;  
    } 



    Node* currentTask = front;
    int foundPrev = 1;

    while(foundPrev) {

        if (currentTask -> next == NULL) {
            foundPrev = 0;
        } else {
            if (t.daysTillDue > currentTask -> _task.daysTillDue && t.daysTillDue < currentTask -> next -> _task.daysTillDue) {
                foundPrev = 0;
            } else {

                if (currentTask -> next == NULL) {
                    foundPrev = 0;
                } else {
                    currentTask = currentTask -> next;
                }

            }
        }


    }

    if (currentTask == front &&  currentTask -> next == NULL) { //First _task case

        if (newTask -> _task.daysTillDue >= currentTask -> _task.daysTillDue) { //After case
            newTask -> next = NULL;
            rear = newTask;
            currentTask -> next = newTask;
        } else {
            newTask -> next = currentTask;
            front = newTask;
            rear = currentTask;
            currentTask -> next = NULL;
        }

    } else if(currentTask == rear && currentTask -> next == NULL) { //Last _task case
        //cout << "here " << t.daysTillDue;
        newTask -> next = NULL;
        currentTask -> next = newTask;
        rear = newTask;


    } else { //Last case

        newTask -> next = currentTask -> next;
        currentTask -> next = newTask;

    }
    

    return true;
}


Task* TaskQueue::dequeue(){// Remove current task
    if(front == NULL && rear == NULL){
        return NULL;
    }

    Node* old = front;

    if (front == rear){
        front = NULL;
        rear = NULL;
    } else{
        front = old -> next;
    }
    _currentDay =  old -> _task.daysTillDue;
    old -> _task.daysTillDue = 0;
    _numItems--;
    return &(old->_task);
}
const Task* TaskQueue::peek() const { // What is current task?
    if(front == NULL && rear == NULL){
        return NULL;
    }

    front -> _task.daysTillDue = (front -> _task.daysTillDue) - _currentDay;

    return &front-> _task;
}
const Task* TaskQueue::next(const Task::TaskType& t) {// Return next task of type t

    Node* currentTask = front;
    if(front -> _task.type == t){
        front -> _task.daysTillDue = (front -> _task.daysTillDue) - _currentDay;
        return &(front->_task);
    }
	
    while(currentTask != rear){
        if(currentTask -> _task.type == t){
            currentTask -> _task.daysTillDue = (currentTask -> _task.daysTillDue) - _currentDay;
            return &(currentTask->_task);
        }	
        currentTask = currentTask -> next;
    }

    if(rear-> _task.type == t){
        rear -> _task.daysTillDue = (rear -> _task.daysTillDue) - _currentDay;
        return &(rear->_task);
    }
	
    return NULL;
}  

bool TaskQueue::isEmpty() const{ // Queue is empty
    if(_numItems == 0){
        return true;
    }
    return false;
} 

bool TaskQueue::remove(const int& t){
    Node* previousTask = front;
    Node* currentTask = front;
	
    if(front -> _task.taskID == t){
        front = front -> next;
        return true;
    }

    while(currentTask != rear){
		
        if(currentTask -> _task.taskID == t){
            previousTask -> next = currentTask -> next;
            return true;
        }	
        previousTask = currentTask;
        currentTask = currentTask -> next;
    }

    if(rear-> _task.taskID == t){
        previousTask -> next = NULL;
        rear = previousTask;
        return true;
    }
    _numItems--;
    return false;
}   

///////////////////////////////////////////////////////////////////////////
// Constructors and Destructor
//
TaskQueue::TaskQueue(){
    front = NULL;
    rear = NULL;           
    _currentDay = 0;    //What day is it currently?
    _numItems = 0;
    _queueSize = INITIAL_TASKQUEUE_SIZE;  // Current size of _tasks
}

TaskQueue::~TaskQueue(){
    front = NULL;
    rear = NULL;
    _currentDay = 0;    //What day is it currently?
    _numItems = 0;
    _queueSize = 0;  // Current size of _tasks
}


/*#ifndef MARMOSET_TESTING

ostream& operator<<(ostream& os, const Task& t) {
	if(&t == 0)	{
		os << "nullTask";
		return os;
	}

	os << t.taskID << "(";
	os << t.daysTillDue << ", ";
	switch (t.type) {
		case Task::LAUNDRY:
			os << "Laundry; ";
			break;
		case Task::DISHES:
			os << "Dishes; ";
			break;
		case Task::MAKE_BED:
			os << "Make Bed; ";
			break;
		case Task::VACUUM:
			os << "Vacuum; ";
			break;
		case Task::MOP_FLOOR:
			os << "Mop Floor; ";
			break;
		case Task::ECE150:
			os << "ECE 150; ";
			break;
		default:
			os << "Unknown Task Type; ";
		break;
	}
	if (t.description)
		os << t.description;
	else
		os << "0x0";
	os << ")";
	return os;
}

ostream& operator<<(ostream& os, const Node* n)	{
	if(n == 0)
		os << "NULL NODE\n";
	else	{
		int dueOn = n -> dueOn;
		os << "Due on: " << dueOn << "\tTask is: ";
		Task task = n -> _task;
		os << task << "\n";
	}
}

int main() {
	TaskQueue tq;


	Task laundry;
	char description1[] = "Yeah clothes";
	laundry.daysTillDue = 3;
	laundry.description = description1;
	laundry.taskID = 8008135;
	laundry.type = (Task::TaskType) 0;

	Task dishes;
	char description2[] = "Some nonlaundry bois here";
	dishes.daysTillDue = 2;
	dishes.description = description2;
	dishes.taskID = 80085;
	dishes.type = (Task::TaskType) 1;

	Task ECE;
	char description3[] = "Pointers. Oof";
	ECE.daysTillDue = 4;
	ECE.description = description3;
	ECE.taskID = 666;
	ECE.type = (Task::TaskType) 5;

	Task vacuum;
	char description4[] = "sucky";
	vacuum.daysTillDue = 4;
	vacuum.description = description4;
	vacuum.taskID = 0202;
	vacuum.type = (Task::TaskType) 3;

	Task mop;
	char description5[] = "wet wet";
	mop.daysTillDue = 6;
	mop.description = description5;
	mop.taskID = 308;
	mop.type = (Task::TaskType) 4;


	Task invalid;
	invalid.daysTillDue = 0;


	cout << "LAUNDRY: DTD: 3 " << tq.enqueue(laundry) << "\n";
	cout << "INVALID " << tq.enqueue(invalid) << "\n";
	cout << "ECE: DTD: 4" << tq.enqueue(ECE) << "\n";
	cout << "DISHES: DTD: 2 " << tq.enqueue(dishes) << "\n";
	cout << "MOP: DTD: 6 " << tq.enqueue(mop) << "\n";
	cout << "VACUUM: DTD: 4 " << tq.enqueue(vacuum) << "\n";

	Node* c = tq.front;
	
	for(int i = 0; i < 5; i++)	{
		cout << c << "\n";
		c = c -> next;
	}

	// cout << "Front: " << tq.front << "\n";
	// cout << "Next: " << tq.front -> next << "\n";
	cout << tq.dequeue() << "\n";
	Task p = *tq.peek();
	const Task* n = tq.next((Task::TaskType) 0);
	cout << "p is: " << p << "\n";
	cout << "n is: " << n << "\n";
	cout << *n << "\n";
	cout << tq.remove(666) << "\n";
	cout << tq.dequeue() << "\n";
	cout << tq.dequeue() << "\n";
	cout << tq.dequeue() << "\n";

	// cout << "Pointer to Task 1: " << tq.front -> _task<< "\n";
	//cout << "Pointer to Task 2: " << &tq.front -> next -> _task << "\n";
	//cout << "Pointer to Task 3: " <<  "\n";

	// cout << "Pointer to front: " << tq.front << "\n";

	// cout << "Front Node: " << tq.front << "\n";
	// cout << "Back Node: " << tq.rear << "\n";


	return 0;
}

#endif*/