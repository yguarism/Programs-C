///////////////////////////////////////////////////////////////////////////
//
// Class: TaskQueue
//
// Note the name changes for methods double() and half(); why?
// Note the addition of "const" for 5 of the member functions;
// why was const added for those 5?  why only those 5?
// Note the INITIAL_TASKQUEUE_SIZE int; why is it needed?
// why is it inside the private member data? why is it static?
// Note the enum is moved into the Task struct; why? what else
// did that change force in the code? why do this?
// Note that we added _numItems; why?  why are front and back
// not sufficient?
//

#ifndef TASKQUEUE_H
#define TASKQUEUE_H

struct Task {
  enum TaskType { LAUNDRY, DISHES, MAKE_BED, VACUUM, MOP_FLOOR, ECE150 };

  TaskType type;         // LAUNDRY, DISHES, etc.
  int      taskID;       // Unique ID per task
  char*    description;  // Task description
};

class TaskQueue {
public:
  bool        enqueue(const Task& t);               // Add a new task
  Task*       dequeue();                            // Remove current task
  const Task* peek() const;                         // What is current task?
  const Task* next(const Task::TaskType& t) const;  // Return next task of type t
  bool        isFull() const;                       // Queue is full
  bool        isEmpty() const;                      // Queue is empty
  bool        quarterFull() const;                  // Queue is < quarter full    
  bool        doubleQueueSize();                    // Double queue size
  bool        halveQueueSize();                     // Halve queue size

  TaskQueue();
  ~TaskQueue();

 private:
  static const int INITIAL_TASKQUEUE_SIZE = 10;

  int   _front;
  int   _back;
  int   _numItems;
  int   _queueSize;  // Current size of _tasks
  Task* _tasks;      // Wrap-around array (Circular Queue)
};

#endif
