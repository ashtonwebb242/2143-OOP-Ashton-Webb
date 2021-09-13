/**
*                    
*  Author:           Ashton WEbb
   Email:            ashtonwebb46@gmail.com
*  Title:            Progam 1 MyVector
*  Course:           2143
*  Semester:         Fall 2021
* 
*  Description:
*        Vector made out of a Linked List
Files: Main.cpp     driver program
* 
*/
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

/*

myVector


Description:

 * Public Methods:
 *            
    myVector()
        myVector(int A[], int size)
        myVector(myVector& other)
        myVector(string filename) 
        void pushFront(int x)
        void pushFront(myVector& other)
        void pushAt(int x, int index)
        void inOrderPush(int x)
        void ascendingOrderPush(int x)
        void descendingOrderPush(int x)
        int popFront()
        int popRear()
        int popAt(int index)
        int find(int val)
        void setAscendingOrder(bool flag
        string print()

*/














// Node for our linked list
struct node {
    int data;  // data value (could be a lot more values)

    node* next;  // we always need a "link" in a linked list

    node(int x) {  // cunstructor to make adding values easy
        data = x;
        next = NULL;
    }
};

/**
 * @brief Load array with values from a file
 * 
 * @param string filename 
 * @param int*& arr 
 * @param int& size 
 */





void loadArr(string filename, int*& arr, int& size) {
    ifstream fin;         // stream reference
                          //
    fin.open(filename);   // open the file
                          //
    fin >> size;          // get first value which contains
                          // number of remaining values in file
                          //
    arr = new int[size];  // allocate new array of correct size
                          //
    int i = 0;            // need an array index for our while loop
                          //
    // Can also use for loop since we know the exact count in file.
    // eof = end of file flag
    // `!fin.eof()` evaulates to true when we hit end of file.
    while (!fin.eof()) {
        fin >> arr[i];  // read file value straight into array
                        // at index i
        i++;            // increment array index
    }
}

/**
 * @brief Prints an array
 * 
 * @param int arr 
 * @param int size
 * 
 * @returns void
 */
void printArr(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        cout << "[" << arr[i] << "]";
    }
    cout << "\n";
}

void writeToFile(ofstream& fout, string str) {
    fout << str;
}



    


class myVector{
private:
    node* head;  // base pointer of list
    bool ascendingOrder;
public:
    /**
     *  Default Constructor 
     * 
     * Creates a new Linked List object.
     * 
     * param void
     * return void
     */
    myVector() {
        head = NULL;  // NULL = zeros
                      // and zeros imply empty
        ascendingOrder = true;
    }

    /**
     * Overloaded Constructor 
     * 
     * Creates a new Linked List object from 
     * an array of values.
     * 
     * param int* A - array of values
     * param int size - size of array
     * 
     * return void
     */
    myVector(int A[], int size) {
        head = NULL;  // NULL = zeros
                      // and zeros imply empty

        for (int i = 0; i < size; i++) {
            pushRear(A[i]);
        }
        ascendingOrder = true;
    }

    /**
     *  copy constructor
     * 
     * param myVector& other - Linked List to copy
     * 
     * return void
     * 
     *  This is a deep copy.
     */
    myVector(myVector& other) {
        head = NULL;  // NULL = zeros
                      // and zeros imply empty
        
        node* temp = other.head;
        while (temp != NULL) {
            pushRear(temp->data);
            temp = temp->next;
        }

        ascendingOrder = true;
    }

    myVector(string filename) {
        head = NULL;  // NULL = zeros

        int size;
        int* arr;
        loadArr(filename, arr, size);

        for (int i = 0; i < size; i++) {
            pushRear(arr[i]);
        }

        delete[] arr;
        ascendingOrder = true;
    }
  
    //
    //  Description: add integers to the front of the Vector
    //
    //  param: int num (the number being added)
    //
    //  returns: void
    //


    void pushFront(int x) {
        node* tempPtr = new node(x);  // create a new node and
                                      // add data to it

        if (!head) {  // `!head` implies empty list
                      // So does `head == NULL`

            head = tempPtr;  // `head = tempPtr` places addrress of
                             // tempPtr in head (points head to tempPtr)

        } else {                   // list not empty
            tempPtr->next = head;  // point tempPtr's next to what head points to
            head = tempPtr;        // now point head to tempPtr
        }
    }

     
    //
    //  Description: will add a separate vector to the front of 
    //               the Vector.
    //
    //  param MyVector other is being added
    //
    //  returns void
    //

    void pushFront(myVector& other) {
        if (other.head) {
            node* tempHead = head;
            node* temp = other.head;
            head = NULL;
            while (temp != NULL) {
                this->pushRear(temp->data);
                temp = temp->next;
            }

            // get last node
            node* last = head;
            while (last->next != NULL) {
                last = last->next;
            }
            last->next = tempHead;
        }
    }
     
    //  Description: adds integers to the back of the vector
    //
    //  param int num the number being placed at the end
    //
    //  return void
    //

    void pushRear(int x) {
        node* tempPtr = new node(x);  

        if (!head) {
            head = tempPtr;
        } else {
            node* temp = head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = tempPtr;
        }
    }
    //
    //
    //  Description: adds a separate vector to the end of 
    //               the Vector.
    //
    //  param MyVector other is  the vector being added
    // 
    //
    //  returns: void
    //
    void pushRear(myVector& other) {
        node* temp = other.head;
        while (temp != NULL) {
            pushRear(temp->data);
            temp = temp->next;
        }
    }

    //
    //  Description: adds an integer to a specific location
    //
    //  param: int sub is the subscript of where the int will be placed
    //  param: int num is the num that is being placed
    //
    //  returns: void
    //
    void pushAt(int x, int index) {
        if (index == 0) {
            pushFront(x);
            return;
        }
        node* tempPtr = new node(x);
        node* temp = head;
        int currIndex = 0;
        while (currIndex < index - 1 && temp != NULL) {
            temp = temp->next;
            currIndex++;
        }
        if (currIndex == index - 1) {
            tempPtr->next = temp->next;
            temp->next = tempPtr;
        }
    }     
    //  Description: places the node in the correct position  
    // whether ascending or descending order.

    //  param: int numis the integer being added
    //
    //  return: void
    //

    void inOrderPush(int x) {
        if (ascendingOrder) {
            this->ascendingOrderPush(x);
        } else {
            this->descendingOrderPush(x);
        }
    }  
      //  Description: Places LList in ascending order
    //  param: int number being added
    //
    //  return: void
    //


    void ascendingOrderPush(int x) {
        node* tempPtr = new node(x);
        if (head == NULL) {
            pushFront(x);
        } else {
            node* temp = head;
            while (temp->next != NULL && temp->next->data < x) {
                temp = temp->next;
            }
            tempPtr->next = temp->next;
            temp->next = tempPtr;
        }
    }
    //  Description: Places LList in descending order
    //  param: int number being added
    //
    //  return: void
    //
    void descendingOrderPush(int x) {
        node* tempPtr = new node(x);
        if (!head) {
            pushFront(x);
        } else {
            node* temp = head;
            while (temp->next != NULL && temp->next->data > x) {
                temp = temp->next;
            }
            tempPtr->next = temp->next;
            temp->next = tempPtr;
        }
    }
/
    //
    //  Description Removes an integer from the front of the list
    //
    //  params none
    //
    //  return: int is the integer being removed
    int popFront() {
        if (!head) {
            return -1;
        }
        int temp = head->data;
        node* tempPtr = head;
        head = head->next;
        delete tempPtr;
        return temp;
    }
    //  Description: Removes an integer from the back of the list
    //
    //  params: none
    //
    //  return: int is the integer being removed
    //
    int popRear() {
        // empty list
        if (!head) {
            return -1;
        }

        // only one node in list
        if (head->next == NULL) {
            return popFront();
        }

        node* tempPtr = head;
        while (tempPtr->next->next != NULL) {
            tempPtr = tempPtr->next;
        }

        int temp = tempPtr->next->data;
        delete tempPtr->next;
        tempPtr->next = NULL;
        return temp;
    }
//
    //  Description:  removes the int at that spot of particular subscript 
    //
    //  params: int sub - the subscript location of the integer in vector
    //
    //  return: int - the integer being removed
    //
    int popAt(int index) {
        if (index == 0) {
            return popFront();
        }
        node* temp = head;
        int currIndex = 0;
        while (currIndex < index - 1 && temp != NULL) {
            temp = temp->next;
            currIndex++;
        }
        if (currIndex == index - 1) {
            node* temp2 = temp->next;
            temp->next = temp->next->next;
            int val = temp2->data;
            delete temp2;
            return val;
        } else {
            return - 1;
        }
    }
     //  Description: Finds the  integer in the list the user
    //               is looking, then returns the subscript. If the integer 
    //               is not found then it will return the index
    //
    //  params      int val is the integers we're looking for
    //
    //  return      int is the subscript of where the integer is located
    //
    int find(int val) {
        node* temp = head;
        int index = 0;
        while (temp != NULL) {
            if (temp->data == val) {
                return index;
            }
            temp = temp->next;
            index++;
        }
        return -1;
    }

    void setAscendingOrder(bool flag) {
        ascendingOrder = flag;
    }
    ///
    //
    //  Description: prints the Vector from backwards to forwards
    //
    //  params: none
    //
    //  returns: string
    //
    string print() {
        node* temp = head;  // temp pointer copies head
        
        string str = "[";
        while (temp) {  // this loops until temp is NULL
                        // same as while(temp != NULL)

            str += to_string(temp->data);  // print data from node
            if (temp->next) {
                str += ", ";
            }
            temp = temp->next;  // move to next node
        }
        str += "]\n";
        cout << str;
        return str;
    }

    /**  Destructor
     * 
     *  return void
     */
    ~myVector() {
        node* temp = head;
        while (temp != NULL) {
            node* temp2 = temp;
            temp = temp->next;
            delete temp2;
        }
    }
};

int main() {
    int x = 0;

    ofstream file("test.out");
 
    writeToFile(file, "Ashton Webb\n");
    writeToFile(file, "09/13/2021\n");
    writeToFile(file, "Fall 2143e\n");

    myVector L;
    L.pushFront(18);
    L.pushFront(20);
    L.pushFront(25);
    L.pushRear(18);
    L.pushRear(20);
    L.pushRear(25);

    writeToFile(file, L.print());

    int A[] = {11, 25, 33, 47, 51};
    myVector L2(A, 5);
    writeToFile(file, L2.print());

    L2.pushFront(9);
    L2.inOrderPush(27);
    L2.pushRear(63);
    writeToFile(file, L2.print());

    L.pushRear(L2);
    writeToFile(file, L.print());

    x = L.popFront();
    x = L.popFront();
    x = L.popFront();
    writeToFile(file, L.print());
    cout << x << endl;
    writeToFile(file, to_string(x) + "\n");

    x = L.popRear();
    x = L.popRear();
    x = L.popRear();
    writeToFile(file, L.print());
    cout << x << endl;
    writeToFile(file, to_string(x) + "\n");

    x = L2.popAt(3);
    writeToFile(file, L2.print());
    cout << x << endl;  
    writeToFile(file, to_string(x) + "\n");

    x = L2.find(51);
    cout << x << endl;
    writeToFile(file, to_string(x) + "\n");

    x = L2.find(99);
    cout << x << endl;
    writeToFile(file, to_string(x) + "\n");

    myVector L3(L);
    writeToFile(file, L3.print());

    L3.pushFront(L2);
    writeToFile(file, L3.print());

    myVector L4("input.dat");
    writeToFile(file, L4.print());

    file.close();
}