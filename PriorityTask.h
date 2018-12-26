#ifndef TASKQUEUE_H
#define TASKQUEUE_H

struct Task {
  enum TaskType { LAUNDRY, DISHES, MAKE_BED, VACUUM, MOP_FLOOR, ECE150 };
  TaskType type;         // LAUNDRY, DISHES, etc.
  int      taskID;       // Unique ID per task
  int      daysTillDue;  // Days till due, relative to current day
  char*    description;  // Task description
};

struct Node{
    Task _task;
    int dueOn;      // daysTillDue + _currentDay
    Node* next; 
  };

class TaskQueue {
public:
  bool        enqueue(const Task& t);               // Add a new task
  Task*       dequeue();                            // Remove current task
  const Task* peek() const;                         // What is current task?
  const Task* next(const Task::TaskType& t);        // Return next task of type t
  bool        remove(const int& t);              // Queue is full
  bool        isEmpty() const;
            
  TaskQueue();
  ~TaskQueue();  
  Node* front;
  Node* rear; 

 private:
  static const int INITIAL_TASKQUEUE_SIZE = 10;
  int _currentDay;    //What day is it currently?
  int   _numItems;
  int   _queueSize;  // Current size of _tasks


};

#endif