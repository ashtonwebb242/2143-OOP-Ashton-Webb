/**
*                    
*  Author:           Ashton Webb
*  Email:            ashtonwebb46@gmailcom 
*  Label:            P02
*  Title:            MyVector 2
*  Course:           CMPS 2143
*  Semester:         Fall 2021
* 
*  Description:
*        A Vector project made out of a linked list that overloads operators.
*
*  Files:
*     main.cpp is the driver program
*
* 
*/



#include <fstream>
#include <iostream>
#include <string>

using namespace std;
/**************************************************************************************
 * MyVector
 * 
 * Description:
 *      A vector class made out of link list's
 *      
 * 
 * Public Methods:
 *       
*
                    myVector()
                    myVector(int A[], int size)
                    myVector(myVector& other)
                    myVector(string filename)


void               pushFront(int x)
void               pushFront(myVector& other)
void               pushAt(int x, int index)
void               inOrderPush(int x)
void               ascendingOrderPush(int x)
void               descendingOrderPush(int x)
int                popFront()
int                popRear()
int                popAt(int index)
int                find(int val)
void               setAscendingOrder(bool flag
string             print()
friend ostream     &operator<<(ostream &os, MyVector &v)
friend ofstream    &operator<<(ofstream &os, MyVector &v)
int                &operator[](int index)
MyVector           &operator+(MyVector &other)
MyVector           &operator-(MyVector &other)
MyVector           &operator*(MyVector &other)
MyVector           &operator/(MyVector &other)
friend bool        operator==(MyVector &v1, MyVector &v2)
ostream &operator<<(ostream &os, MyVector &v)
ofstream &operator<<(ofstream &os, MyVector &v)
bool                operator==(MyVector &v1, MyVector &v2)
 
Private Methods:







*/
 

// Node for our linked list
struct node
{
    int data; // data value (could be a lot more values)

    node *next; // we always need a "link" in a linked list

    node(int x)
    { // cunstructor to make adding values easy
        data = x;
        next = NULL;
    }
};
/**
* Load array with values from a file
*
* param string filename
* param int*& arr
* param int& size
*/
void loadArr(string filename, int *&arr, int &size)
{
    ifstream fin;        // stream reference
                         //
    fin.open(filename);  // open the file
                         //
    fin >> size;         // get first value which contains
                         // number of remaining values in file
                         //
    arr = new int[size]; // allocate new array of correct size
                         //
    int i = 0;           // need an array index for our while loop
                         //
    // Can also use for loop since we know the exact count in file.
    // eof = end of file flag
    // `!fin.eof()` evaulates to true when we hit end of file.
    while (!fin.eof())
    {
        fin >> arr[i]; // read file value straight into array
                       // at index i
        i++;           // increment array index
    }
}

/**
* Prints an array
*
* param int* arr
* param int size
*
* returns void
*/
void printArr(int *arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << "[" << arr[i] << "]";
    }
    cout << "\n";
}
/*
void writeToFile()
Writes the program to an ouput file using the string operator
param ofstream& fout
param string str
return void
*/
void writeToFile(ofstream &fout, string str)
{
    fout << str;
}

class MyVector
{
private:
    node *head; // base pointer of list
    bool ascendingOrder;

public:
    /**
* Default Constructor
*
* Creates a new Linked List object.
*
* param void
* return void
*/
    MyVector()
    {
        head = NULL; // NULL = zeros
                     // and zeros imply empty
        ascendingOrder = true;
    }

    /**
* Overloaded Constructor
*
* Creates a new Linked List object from
* an array of values.
*
* param int[] is a array of values
* param int size is the size of array
*
* return void
*/
    MyVector(int A[], int size)
    {
        head = NULL; // NULL = zeros

        for (int i = 0; i < size; i++)
        {
            pushRear(A[i]);
        }
        ascendingOrder = true;
    }
   //  Description: initializes a MyVector object with an array 
    //
    //  param: int &A[n]
    // 
    //
    //  returns: none
    //
    template <size_t n>
    MyVector(int (&A)[n])
    {
        int size = sizeof(A) / sizeof(A[0]);
        head = NULL; // NULL = zeros

        for (int i = 0; i < size; i++)
        {
            pushRear(A[i]);
        }
        ascendingOrder = true;
    }

    /**
     *  copy constructor
     * 
     * param MyVector& other - Linked List to copy
     * 
     * return void
     * 
     * note This is deep copy.
     */
    MyVector(MyVector &other)
    {
        head = NULL; // NULL = zeros
                     // and zeros imply empty

        node *temp = other.head;
        while (temp != NULL)
        {
            pushRear(temp->data);
            temp = temp->next;
        }

        ascendingOrder = true;
    }
// Deascription- Initializes a MyVector object and places items from the file created into it.
//
// param string filename is the file of integers that will be read in
//
// returns nothing
    MyVector(string filename)
    {
        head = NULL; // NULL = zeros

        int size;
        int *arr;
        loadArr(filename, arr, size);

        for (int i = 0; i < size; i++)
        {
            pushRear(arr[i]);
        }

        delete[] arr;
        ascendingOrder = true;
    }
//
// Description: add integers to the front of the Vector
//
// param: int x (the number being added)
//
// returns: void
//
    void pushFront(int x)
    {
        node *tempPtr = new node(x); // create a new node and
                                     // add data to it

        if (!head)
        { // `!head` implies empty list
            // So does `head == NULL`

            head = tempPtr; // `head = tempPtr` places addrress of
                            // tempPtr in head (points head to tempPtr)
        }
        else
        {                         // list not empty
            tempPtr->next = head; // point tempPtr's next to what head points to
            head = tempPtr;       // now point head to tempPtr
        }
    }
//
// Description: will add a separate vector to the front of
// the Vector.
//
// param MyVector& other is being added
//
// returns void
//
    void pushFront(MyVector &other)
    {
        if (other.head)
        {
            node *tempHead = head;
            node *temp = other.head;
            head = NULL;
            while (temp != NULL)
            {
                this->pushRear(temp->data);
                temp = temp->next;
            }

            // get last node
            node *last = head;
            while (last->next != NULL)
            {
                last = last->next;
            }
            last->next = tempHead;
        }
    }
// Description It adds integers to the back of the vector
//
// param int x is the number being placed at the end
//
// returns void
//
    void pushRear(int x)
    {
        node *tempPtr = new node(x);

        if (!head)
        {
            head = tempPtr;
        }
        else
        {
            node *temp = head;
            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            temp->next = tempPtr;
        }
    }
//
//
// Description it adds a separate vector to the end of
// the Vector.
//
// param MyVector& other is the vector being added
//returns: Void
//
    void pushRear(MyVector &other)
    {
        node *temp = other.head;
        while (temp != NULL)
        {
            pushRear(temp->data);
            temp = temp->next;
        }
    }
//
// Description: adds an integer to a specific location
//
// param: int index is the location of where the int will be placed
// param: int x is the num that is being placed in the location
//
// returns void
//
    void pushAt(int x, int index)
    {
        if (index == 0)
        {
            pushFront(x);
            return;
        }
        node *tempPtr = new node(x);
        node *temp = head;
        int currIndex = 0;
        while (currIndex < index - 1 && temp != NULL)
        {
            temp = temp->next;
            currIndex++;
        }
        if (currIndex == index - 1)
        {
            tempPtr->next = temp->next;
            temp->next = tempPtr;
        }
    }
// Description: places the node in the correct position
// whether ascending or descending order.
// param int x is the integer being added
//
// return void
//
    void inOrderPush(int x)
    {
        if (ascendingOrder)
        {
            this->ascendingOrderPush(x);
        }
        else
        {
            this->descendingOrderPush(x);
        }
    }
// Description: Places LList in ascending order
// param int x number being added
//
// return void
//
    void ascendingOrderPush(int x)
    {
        node *tempPtr = new node(x);
        if (head == NULL)
        {
            pushFront(x);
        }
        else
        {
            node *temp = head;
            while (temp->next != NULL && temp->next->data < x)
            {
                temp = temp->next;
            }
            tempPtr->next = temp->next;
            temp->next = tempPtr;
        }
    }
// Description Places LList in descending order
// param int x is the number being added
//
// return void
//
    void descendingOrderPush(int x)
    {
        node *tempPtr = new node(x);
        if (!head)
        {
            pushFront(x);
        }
        else
        {
            node *temp = head;
            while (temp->next != NULL && temp->next->data > x)
            {
                temp = temp->next;
            }
            tempPtr->next = temp->next;
            temp->next = tempPtr;
        }
    }
//
// Description Removes an integer from the front of the list
//
// params none
//
// return int is the integer being removed
    int popFront()
    {
        if (!head)
        {
            return -1;
        }
        int temp = head->data;
        node *tempPtr = head;
        head = head->next;
        delete tempPtr;
        return temp;
    }
// Description: Removes an integer from the back of the list
//
// params none
//
// return int is the integer being removed
//
    int popRear()
    {
        // empty list
        if (!head)
        {
            return -1;
        }

        // only one node in list
        if (head->next == NULL)
        {
            return popFront();
        }

        node *tempPtr = head;
        while (tempPtr->next->next != NULL)
        {
            tempPtr = tempPtr->next;
        }

        int temp = tempPtr->next->data;
        delete tempPtr->next;
        tempPtr->next = NULL;
        return temp;
    }
// Description removes the int at that spot of particular subscript
//
// params int index is the location of the integer in vector
//
// returns the integer being removed
//
    int popAt(int index)
    {
        if (index == 0)
        {
            return popFront();
        }
        node *temp = head;
        int currIndex = 0;
        while (currIndex < index - 1 && temp != NULL)
        {
            temp = temp->next;
            currIndex++;
        }
        if (currIndex == index - 1)
        {
            node *temp2 = temp->next;
            temp->next = temp->next->next;
            int val = temp2->data;
            delete temp2;
            return val;
        }
        else
        {
            return -1;
        }
    }
// Description: Finds the integer in the list the user
// is looking for.
//
// params int val is the integers we're looking for
//
// return int is the subscript of where the integer is located
//
    int find(int val)
    {
        node *temp = head;
        int index = 0;
        while (temp != NULL)
        {
            if (temp->data == val)
            {
                return index;
            }
            temp = temp->next;
            index++;
        }
        return -1;
    }

    void setAscendingOrder(bool flag)
    {
        ascendingOrder = flag;
    }
///
//
// Description prints the Vector from backwards to forwards
//
// params none
//
// returns string
//
    string print()
    {
        node *temp = head; // temp pointer copies head

        string str = "[";
        while (temp)
        { // this loops until temp is NULL
            // same as `while(temp != NULL)`

            str += to_string(temp->data); // print data from node
            if (temp->next)
            {
                str += ", ";
            }
            temp = temp->next; // move to next node
        }
        str += "]\n";
        cout << str;
        return str;
    }

    // overloading
    friend ostream &operator<<(ostream &os, MyVector &v);
    friend ofstream &operator<<(ofstream &os, MyVector &v);

    //  Description: allows MyVector can be treated as an array
    //
    //  Param int index is the subscript of where you want to go
    //
    //  returns: the data at the indexed spot
    //
    // overload []
    int &operator[](int index)
    {
        node *temp = head;
        int currIndex = 0;
        while (currIndex < index && temp != NULL)
        {
            temp = temp->next;
            currIndex++;
        }
        return temp->data;
    }
 //  Description: adds two vectors together
    //
    //  params: MyVectors& is the vector left of the '+' being added
    //
    //  returns: a new vector
    //
    MyVector &operator+(MyVector &other)
    {
        MyVector *temp = new MyVector();
        node *tempPtr = head;
        node *tempPtrOther = other.head;
        while (tempPtr != NULL || tempPtrOther != NULL)
        {
            if (tempPtr != NULL && tempPtrOther != NULL)
            {
                temp->pushRear(tempPtr->data + tempPtrOther->data);
                tempPtr = tempPtr->next;
                tempPtrOther = tempPtrOther->next;
            }
            else if (tempPtr != NULL)
            {
                temp->pushRear(tempPtr->data);
                tempPtr = tempPtr->next;
            }
            else
            {
                temp->pushRear(tempPtrOther->data);
                tempPtrOther = tempPtrOther->next;
            }
        }
        return *temp;
    }
 //  Description: adds two vectors together
    //
    //  params: MyVectors& is the vector left of the '-' being added
    //
    //  returns: a new vector
    //
    MyVector &operator-(MyVector &other)
    {
        MyVector *temp = new MyVector();
        node *tempPtr = head;
        node *tempPtrOther = other.head;
        while (tempPtr != NULL || tempPtrOther != NULL)
        {
            if (tempPtr != NULL && tempPtrOther != NULL)
            {
                temp->pushRear(tempPtr->data - tempPtrOther->data);
                tempPtr = tempPtr->next;
                tempPtrOther = tempPtrOther->next;
            }
            else if (tempPtr != NULL)
            {
                temp->pushRear(tempPtr->data);
                tempPtr = tempPtr->next;
            }
            else
            {
                temp->pushRear(tempPtrOther->data);
                tempPtrOther = tempPtrOther->next;
            }
        }
        return *temp;
    }
 
    //  Description multiplies two vectors together
    //
    //  Paramsarams MyVectors& is the vector left of the '*' being added
    //
    //  returns a new vector
    //
    MyVector &operator*(MyVector &other)
    {
        MyVector *temp = new MyVector();
        node *tempPtr = head;
        node *tempPtrOther = other.head;
        while (tempPtr != NULL || tempPtrOther != NULL)
        {
            if (tempPtr != NULL && tempPtrOther != NULL)
            {
                temp->pushRear(tempPtr->data * tempPtrOther->data);
                tempPtr = tempPtr->next;
                tempPtrOther = tempPtrOther->next;
            }
            else if (tempPtr != NULL)
            {
                temp->pushRear(tempPtr->data);
                tempPtr = tempPtr->next;
            }
            else
            {
                temp->pushRear(tempPtrOther->data);
                tempPtrOther = tempPtrOther->next;
            }
        }
        return *temp;
    }
 
    //  Description divides two vectors together
    //
    //  Params MyVectors& is the vector left of the '/' being added
    //
    //  returns a new vector
    //
    MyVector &operator/(MyVector &other)
    {
        MyVector *temp = new MyVector();
        node *tempPtr = head;
        node *tempPtrOther = other.head;
        while (tempPtr != NULL || tempPtrOther != NULL)
        {
            if (tempPtr != NULL && tempPtrOther != NULL)
            {
                int div = 0;
                if (tempPtrOther->data != 0)
                {
                    div = tempPtr->data / tempPtrOther->data;
                }
                temp->pushRear(div);
                tempPtr = tempPtr->next;
                tempPtrOther = tempPtrOther->next;
            }
            else if (tempPtr != NULL)
            {
                temp->pushRear(tempPtr->data);
                tempPtr = tempPtr->next;
            }
            else
            {
                temp->pushRear(tempPtrOther->data);
                tempPtrOther = tempPtrOther->next;
            }
        }
        return *temp;
    }

    friend bool operator==(MyVector &v1, MyVector &v2);

    /**brief Destructor
     * 
     * return void
     */
    ~MyVector()
    {
        node *temp = head;
        while (temp != NULL)
        {
            node *temp2 = temp;
            temp = temp->next;
            delete temp2;
        }
    }
};
    //  Description  It prints out a vector
    //
    //  params ostream& os is the output we are returning
    //  params const MyVector vector is the vector we are printing
    //
    //  returns the vector
    //
ostream &operator<<(ostream &os, MyVector &v)
{
    node *temp = v.head; // temp pointer copies head

    os << "[";
    while (temp)
    {                     // this loops until temp is NULL
        os << temp->data; // print data from node
        if (temp->next)
        {
            os << ",";
        }
        temp = temp->next; // move to next node
    }
    os << "]";

    return os;
}

    //  Description It prints out a vector
    //
    //  params ostream& os is the output we are returning
    //  params const MyVector vector is the vector we are printing
    //
    //  returns the data at the indexed spot
    //
ofstream &operator<<(ofstream &os, MyVector &v)
{
    node *temp = v.head; // temp pointer copies head

    os << "[";
    while (temp)
    {                     // this loops until temp is NULL
        os << temp->data; // print data from node
        if (temp->next)
        {
            os << ",";
        }
        temp = temp->next; // move to next node
    }
    os << "]";

    return os;
}
 
    //
    //  Description: Checks to see if the 2 two vectors are equal
    //
    //  params MyVectors &v1  the vector to the right of "=="
    //
    //  returns  whether the vectors are equal or not
    //
bool operator==(MyVector &v1, MyVector &v2)
{
    node *tempPtr = v1.head;
    node *tempPtrOther = v2.head;
    while (tempPtr != NULL && tempPtrOther != NULL)
    {
        if (tempPtr->data != tempPtrOther->data)
        {
            return false;
        }
        tempPtr = tempPtr->next;
        tempPtrOther = tempPtrOther->next;
    }
    return tempPtr == NULL && tempPtrOther == NULL;
}

int main()
{
    int a1[] = {1, 2, 3, 4, 5};
    int a2[] = {10, 20, 30};

    MyVector v1(a1);
    MyVector v2(a2);

    ofstream fout;
    fout.open("output.txt");
    fout << "Ashton Webb\n9/29/2021\nFall 2143\n\n";

    cout << v1[2] << endl;
    // writes out 3

    v1[4] = 9;
    // v1 now = [1,2,3,4,9]

    cout << v1 << endl;
    // writes out [1,2,3,4,9] to console.

    fout << v1 << endl;
    // writes out [1,2,3,4,9] to your output file.

    MyVector v3 = v1 + v2;
    cout << v3 << endl;
    // writes out [11,22,33,4,9] to console.

    v3 = v1 - v2;
    cout << v3 << endl;
    // writes out [-9,-18,-27,4,9] to console.

    v3 = v2 - v1;
    cout << v3 << endl;
    // writes out [9,18,27,4,9] to console.

    v3 = v2 * v1;
    cout << v3 << endl;
    // writes out [10,40,90,4,9] to console.

    v3 = v1 * v2;
    cout << v3 << endl;
    // writes out [10,40,90,4,9] to console.

    v3 = v1 / v2;
    cout << v3 << endl;
    // writes out [0,0,0,4,9] to console.

    v3 = v2 / v1;
    cout << v3 << endl;
    // writes out [10,10,10,4,9] to console.

    cout << (v2 == v1) << endl;
    // writes 0 to console (false) .

    MyVector v4 = v1;
    cout << (v4 == v1) << endl;
    // writes 1 to console (true) .
}