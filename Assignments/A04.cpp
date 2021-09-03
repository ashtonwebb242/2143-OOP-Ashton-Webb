/*
Name:         Ashton Webb
Email:        ashtonwebb46@gmail.com
Code By:      Proffesor Terry Griffin
Course:       2143 OOP
Semester:     Fall 2021

Description:  
        This Program represents and defines a class that creates,
    a circular queue. It can oush and/or pop items in and out of the queue.
My objectiuve is to comment the entire Program,

Usage:  
    Enter values into the class and the methods created will add them to the list.
*/


/*------------------------------------------------------------------

CircularArrayQue

Description: This class contains the prototypes and variables needed to excecute array.

Public Methods:       
                              CircularArrayQue()
                              CircularArrayQue(int size)

                       void    Push(int item)
                       int     Pop()
Private Methods:
                       bool    Full()
                       void    init(int size =0)\

Usage:

----------------------------------------------------------------------------*/


#include <iostream>

using namespace std;


class CircularArrayQue {
private:
    int *Container;                //Points to the queue array
    int Front;                     //Tracks and Holds Front of queue
    int Rear;                      //Tracks the back of the queue
    int QueSize;                   // items in the queue
    int CurrentSize;               //Contains the currents size and amount of items in the queue
  
  /*******************************************************************************
   Private: init

   Description: 
      Initialize the values at Front Rear, and Current ansd sets it to 0

Paramaters:
      int: size of the queue

Returns:
  Void:  Does not return Anything

  *******************************************************************************/
  
  
  
    void init(int size = 0) {
        Front = Rear = CurrentSize = 0;
        QueSize = size;
    }
    /******************************************************************************
Private : Full

Deascription:
     Does a check to see whether or not the queue is full
    
Params : 
    Does not recquire a parameter

Returns:
    bool  : Returning either true or false depending on the queue's currents size
    true if queue is full
    false if queue is not full
    *******************************************************************************/

    bool Full() {
        return CurrentSize == QueSize;   
    }

public:
 /*******************************************************************************
Public : CircularArrayQueue

Deascription:
     Assigns the variable container to a new queue array and initializes its value to 10, then passes
    then sets "init" to 10;
Params : 
    Does not recquire a parameter

*******************************************************************************/

    CircularArrayQue() {
        Container = new int[10];  /// allocates mmemmory to create a new array of size 10
        init(10);
    }
    /*******************************************************************************
Public : CircularArrayQueue

Deascription:
    Assigns "Container to a new queue array " of whataver size is entered by the user. then passess that size into "init"
Params : 
  An int size of the queue is recquired as a parameter

*******************************************************************************/

    CircularArrayQue(int size) {
        Container = new int[size];    //dynamically allocates new memory to set array to "size:"
        init(size);
    }
   /*******************************************************************************
Public : Push

Deascription:
    Adds an integer to the end of the queue if the queue is not full. 
     1 is added to the rear meaning it is pushed back , and current size increases by 1 also.
     If the array is full the ccout statement empasizing full will be printed to screen. 
Params : 
    int the item being added
    Returns:  
    Void Not returning anything

*******************************************************************************/


    void Push(int item) {
        if (!Full()) {                     //If the queue array isnot full
            Container[Rear] = item;        // add the entered item to the rear
            Rear = (Rear + 1) % QueSize;   // push rear back
            CurrentSize++;                 // increment the current size
        } else {
            cout << "FULL!!!!" << endl;    // else if the array is full print the Full 
                                           //message to the screen
        }
    }
    /*******************************************************************************
Public : Pop

Deascription:
Assigns tempt to the front number, then moves front down one and removes
the first number of the queue. Then this method subtraatcs one from the currents
size and returns the number that was being popped.  
Params : 
No parameters
Return: 
int : returnes the number being popped from the queue

*******************************************************************************/


    int Pop() {
        int temp = Container[Front];     //Temp is now the ront of the queue
        Front = (Front + 1) % QueSize;   //Moves front down by addinbg 1
        CurrentSize--;                   // subtracts 1 from the  current size
        return temp;                     //returns the number being popped
    }
    // Allowing ostream to access the private members of he class
    friend ostream &operator<<(ostream &os, const CircularArrayQue &other);
};
    // allows the program to be printed 
ostream &operator<<(ostream &os, const CircularArrayQue &other) {

    for (int i = other.Front; i < other.CurrentSize; i = (i + 1) % other.QueSize) {
        os << other.Container[i] << " ";
    }
    os << endl;
    return os;
}

/********************************************************************************
 * Main Driver
 * 
 * For this program, the main driver was used to test the CircularArrayQue class
 * 
 *******************************************************************************/
int main() {
    CircularArrayQue C1(5);             //creates que with a size of 5

    // C1.Push(34);
    // C1.Push(38);
    // C1.Push(44);
    // C1.Push(22);
    // C1.Push(99);
    // C1.Push(100);
    C1.Push(1);                          // Adds "1" to the queue
    C1.Push(2);                          // Adds "2" to the queue
    C1.Push(3);                          // Adds "3" to the queue
    // C1.Push(6);
    // C1.Push(7);
    cout << C1 << endl;                  // Prints out the queue

    // C1.Push(1);
    // C1.Push(2);
    // C1.Push(3);

    cout << C1 << endl;                  // Prints the queue
}
