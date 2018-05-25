/*
Comprehensive C++ Assignment 2 Example

Parking lot simulation.

This program creates two alleys (stacks) to park and retrieve
cars.
CarNode : A class for one node of linked list. One node represents
a car and its relative position in the parking alley.
Alley: A class for the stack of nodes. Two instantiations A and B
are used.
*/

#include <iostream>
#include <cstdlib>
using namespace std;

enum action {quit = 'q', Quit = 'Q', park = 'p', Park = 'P', retrieve = 'r', Retrieve = 'R', display = 'd', Display = 'D'};
/**********************************************
*Copyright 2007 Suleman Saya
*Edited by:  Author - Divyashree Hassan Ravindrakumar
*OS - macOS Sierra - version 10.12.5
*Compiler g++
*	Configured with: --prefix=/Library/Developer/CommandLineTools/usr --with-gxx-include-dir=/usr/include/c++/4.2.1
*	Apple LLVM version 8.1.0 (clang-802.0.42)
*	Target: x86_64-apple-darwin16.7.0
*	Thread model: posix
*	InstalledDir: /Library/Developer/CommandLineTools/usr/bin
*
**********************************************/

#define MAXSIZE 5

class CarNode {
	public:

	   CarNode() : m_pNext(0), m_ticketNum(0) { }

        /*
	   ~CarNode(){
          cout << "deleting car node" <<endl;
       }
       */

	   CarNode(CarNode &): m_pNext(0), m_ticketNum(0) { }

	    // assign next pointer
	    void SetNext(CarNode* p){m_pNext=p;}

	    // assign ticket number
	    void SetTicketNum(int tN){
            //cout << "setting ticket number "<< tN <<endl;
            m_ticketNum=tN;
        }

	    // get the next pointer
	    CarNode* GetNext(void){return(m_pNext);}

	    // get the ticket number
	    int GetTicketNum(void){
            //cout << "returning ticket number "<< m_ticketNum <<endl;
            return(m_ticketNum);
        }

	private:
  	    int m_ticketNum; // ticket number of car
	    CarNode* m_pNext; // pointer to next node in stack
};

class CAlley {
	public:

	   CAlley () : m_pTop(0), mSize(0), mMaxSize(MAXSIZE) {
           for(int i =1; i < MAXSIZE+1; i++)
           {
               tickets[i]=i;
//               cout << "tickets[i] "<< i << " " <<tickets[i];
           }
       }

	   ~CAlley () {
           CarNode *currCar = m_pTop;
           CarNode *delnode;
           while (currCar!= 0){
               delnode=currCar;
               currCar=currCar->GetNext();
               delete(delnode);
           }
       }

	   CAlley (CAlley &):m_pTop(0), mSize(0), mMaxSize(MAXSIZE) {
           for(int i =1; i < MAXSIZE+1; i++)
           {
               tickets[i]=i;
//               cout << "tickets[i] "<< i << " " <<tickets[i];

           }

       }

	   int Park(); // park a car

	   int Retrieve(int, CAlley*); // retrieve a car

	   void Terminate(); // quit the program

	   void Display(){
           if (mSize == 0){
               cout<<"No cars in Parking Alley"<<endl;
               return;
           }
           CarNode *currCar = m_pTop;
           while (currCar!= 0){
               cout<<"<"<<currCar->GetTicketNum()<<"> ";
               currCar=currCar->GetNext();
           }
           cout<<endl;
       }; // display contents af alley

	private:
	   void SetTop(CarNode* p){m_pTop=p;} // assign top pointer

	   // check if stack is empty
	   bool IsEmpty(){return ((mSize==0) ? true : false);}

	   // check if stack is full
	   bool IsFull() {return ((mSize==MAXSIZE) ? true : false);}

	   int Push(CarNode*); // push one node onto top of stack

	   CarNode* Pop(); // pop one node from the top of stack

	   CarNode* m_pTop; // pointer to top of Allay (stack)

	   int mSize; // number of nodes in Allay (stack)

	   int mMaxSize; //max number of nodes in Allay (stack)

       int tickets[MAXSIZE+1];

};

////////////////////////////////////////////////////////////////
// Function: CAlley::Push
// Purpose: Add a new node to top of stack
// Parameters:
// CarNode * pNewNode - the node to be added to top of stack
// Local Variables:
// status - return 1 if pushed sucessfully
// - return 0 if stack was full
////////////////////////////////////////////////////////////////
int CAlley::Push(CarNode* pNewNode)
{
//    cout << "mSize: " <<mSize;
    if(IsFull()){
        return 0;
    }
    mSize+=1;
//    int ticketNumber = mSize;
//    pNewNode->SetTicketNum(ticketNumber);
    pNewNode->SetNext(m_pTop);
    SetTop(pNewNode);
//    cout << "mSize: " <<mSize;
	return 1;
}

/////////////////////////////////////////////////////////////////
// Function: CAlley::Pop
// Purpose: Remove a node to top of Allay (stack).
// Parameters:
// CarNode * pNewNode - returns the node removed from top of Allay
// is zero if stack is empty
// Local Variables:
/////////////////////////////////////////////////////////////////
CarNode* CAlley::Pop()
{
//    cout << "mSize: " <<mSize;
    if(IsEmpty()){
        return 0;
    }
    CarNode* node;
    node = m_pTop;
    SetTop(m_pTop->GetNext());
    mSize--;
//    cout << "mSize: " <<mSize;
    return (node);
}

///////////////////////////////////////////////////////////////
// Function: CAlley::Park ( )
// Purpose: Park a car, if lot is not full. First allocate a
// node, then add it to the top of the stack
// Parameters:
// userTicketNum - the ticket number for the node to be added
// Local Variables:
// CarNode *pNewNode - local pointer to newly allocated node
// int status - 1 if parked sucessfully (lot not full)
// 0 if not parked (lot was full)
///////////////////////////////////////////////////////////////
int CAlley::Park()
{
    int status=0;
    int userTicketNum;
    CarNode* newcar = new CarNode;
    if (Push(newcar) != 0) {
//        cout << "mptop ticket number " << m_pTop->GetTicketNum() <<endl;
//        userTicketNum=m_pTop->GetTicketNum()+1;
//        userTicketNum=mSize;
        if(tickets[mSize] !=0 ) {
            userTicketNum=tickets[mSize];
            tickets[mSize] = 0;
        }
        else{
            for(int i=1; i< MAXSIZE+1; i++)
                if(tickets[i]!=0)
                {
                    userTicketNum=tickets[i];
                    tickets[i]=0;
                    break;
                }
        }
        newcar->SetTicketNum(userTicketNum);
//        cout << "After Push " << endl;
//        Display();
//        cout << "Ticket no. = <" << newcar->GetTicketNum()<< ">\n";
        status=1;
    }
    else
        cout << "PARKING LOT FULL" << endl;
    return status;
}

///////////////////////////////////////////////////////////////
// Function: CAlley:: Retrieve ( int userTicketNum, CAlley *pB)
// Purpose: Retrieve a car from alley A. Search for the car/node
// based on ticket num. by driving a car (popping off top) out of
// A and driving (pushing onto top) into B.
// If the car is found, it is not pushed onto B, but rather,
// it is deleted. Then the cars in B are moved back into A.
//
// Parameters:
// userTicketNum - the ticket number for the node to be added
// pB - pointer to CAlley B
//
// Local Variables:
// CarNode* pCurr - local pointer used as index
// int found - 1 if car is found, 0 if not found
///////////////////////////////////////////////////////////////
int CAlley::Retrieve(int userTicketNum, CAlley* pB)
{
    int found=0;
    CarNode* pCurr = m_pTop;

    while (pCurr!= 0){
        int currTicketNum = pCurr->GetTicketNum();
        if(currTicketNum != userTicketNum) {
            pB->Push(Pop());
//            cout << "After Pop in A - A alley" << endl;
//            Display();
//            cout << "B Alley "<<endl;
//            pB->Display();
        }
        else{
            found=1;
            break;
        }
        pCurr=m_pTop;
    }
    if (found){
        mSize--;
        m_pTop = m_pTop->GetNext();
        pCurr->SetNext(NULL);
        tickets[pCurr->GetTicketNum()] = pCurr->GetTicketNum();
        delete(pCurr);
        CarNode* pBCurr = pB->m_pTop;
        while (pBCurr!= 0){
            Push(pB->Pop());
            pBCurr=pB->m_pTop;
//            cout << "After pop in B - B Alley "<<endl;
//            pB->Display();
        }
    }
    else
    {
        cout << "CAR NOT PARKED IN MY LOT\n";
        CarNode* pBCurr = pB->m_pTop;
        while (pBCurr!= 0){
            Push(pB->Pop());
            pBCurr=pB->m_pTop;
        }
    }
    return found;
}


int main(){ 
	//Create 2 instances of CAlley
    char choice;
    int ticket;
	CAlley* A = new CAlley;
    CAlley* B = new CAlley;

    cout << "Enter one of the options below "<< endl
         << "D)isplay P)ark R)etrieve Q)uit:";
    cin >> choice;

    /*
    while (choice != 'q' && choice != 'Q'){

        switch (choice ){
            case 'd':
            case 'D':
                cout << "Display alley A\n";
                A->Display();
                break;
            case 'p':
            case 'P':
                if (A->Park())
                    cout << "Car Parked\n";
                break;
            case 'r':
            case 'R':
                cout << "Please enter ticket number: ";
                if(!(cin >> ticket)) {
                    cout << "Incorrect input. Please try again.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }
                if (ticket < 1){
                    cout << "Invalid ticket. Please enter a ticket number from 1-5"<<endl;
                    break;
                }
                if(A->Retrieve(ticket, B))
                    cout << "Car retrieved for ticket number <"<<ticket<<">"<<endl;
                break;
            default:
                cout << "Invalid input entry\n";
                break;
        }
        cout << "Enter one of the options below "<< endl
             << "D)isplay P)ark R)etrieve Q)uit:";
        cin >> choice;
    }
    */
    while (choice != quit && choice != Quit){

        switch (choice ){
            case display:
            case Display:
                cout << "Display alley A\n";
                A->Display();
                break;
            case park:
            case Park:
                if (A->Park())
                    cout << "Car Parked\n";
                break;
            case retrieve:
            case Retrieve:
                cout << "Please enter ticket number: ";
                if(!(cin >> ticket)) {
                    cout << "Incorrect input. Please try again.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }
                if (ticket < 1){
                    cout << "Invalid ticket. Please enter a ticket number from 1-5"<<endl;
                    break;
                }
                if(A->Retrieve(ticket, B))
                    cout << "Car retrieved for ticket number <"<<ticket<<">"<<endl;
                break;
            default:
                cout << "Invalid input entry\n";
                break;
        }
        cout << "Enter one of the options below "<< endl
             << "D)isplay P)ark R)etrieve Q)uit:";
        cin >> choice;
    }
    cout << "Quitting Program\n";
    delete A;
    delete B;
	return 0;
}

/*
 * OUTPUT

TUSCA09UMLVT00I:Assignment-2 hasdi8d$ g++ parkinglot.cpp
//TUSCA09UMLVT00I:Assignment-2 hasdi8d$ ./a.out
//Enter one of the options below
//D)isplay P)ark R)etrieve Q)uit:p
//Car Parked
//Enter one of the options below
//D)isplay P)ark R)etrieve Q)uit:p
//Car Parked
//Enter one of the options below
//D)isplay P)ark R)etrieve Q)uit:p
//Car Parked
//Enter one of the options below
//D)isplay P)ark R)etrieve Q)uit:p
//Car Parked
//Enter one of the options below
//D)isplay P)ark R)etrieve Q)uit:d
//Display alley A
//<4> <3> <2> <1>
//Enter one of the options below
//D)isplay P)ark R)etrieve Q)uit:r
//Please enter ticket number: 2
//Car retrieved for ticket number <2>
//Enter one of the options below
//D)isplay P)ark R)etrieve Q)uit:d
//Display alley A
//<4> <3> <1>
//Enter one of the options below
//D)isplay P)ark R)etrieve Q)uit:p
//Car Parked
//Enter one of the options below
//D)isplay P)ark R)etrieve Q)uit:d
//Display alley A
//<2> <4> <3> <1>
//Enter one of the options below
//D)isplay P)ark R)etrieve Q)uit:d
//Display alley A
//<2> <4> <3> <1>
//Enter one of the options below
//D)isplay P)ark R)etrieve Q)uit:p
//Car Parked
//Enter one of the options below
//D)isplay P)ark R)etrieve Q)uit:d
//Display alley A
//<5> <2> <4> <3> <1>
//Enter one of the options below
//D)isplay P)ark R)etrieve Q)uit:r
//Please enter ticket number: 4
//Car retrieved for ticket number <4>
//Enter one of the options below
//D)isplay P)ark R)etrieve Q)uit:p
//Car Parked
//Enter one of the options below
//D)isplay P)ark R)etrieve Q)uit:d
//Display alley A
//<4> <5> <2> <3> <1>
//Enter one of the options below
//D)isplay P)ark R)etrieve Q)uit:kdflkdfj
//Invalid input entry
//Enter one of the options below
//D)isplay P)ark R)etrieve Q)uit:Display alley A
//<4> <5> <2> <3> <1>
//Enter one of the options below
//D)isplay P)ark R)etrieve Q)uit:Invalid input entry
//Enter one of the options below
//D)isplay P)ark R)etrieve Q)uit:Invalid input entry
//Enter one of the options below
//D)isplay P)ark R)etrieve Q)uit:Invalid input entry
//Enter one of the options below
//D)isplay P)ark R)etrieve Q)uit:Display alley A
//<4> <5> <2> <3> <1>
//Enter one of the options below
//D)isplay P)ark R)etrieve Q)uit:Invalid input entry
//Enter one of the options below
//D)isplay P)ark R)etrieve Q)uit:Invalid input entry
//Enter one of the options below
//D)isplay P)ark R)etrieve Q)uit:r
//Please enter ticket number: 1
//Car retrieved for ticket number <1>
//Enter one of the options below
//D)isplay P)ark R)etrieve Q)uit:d
//Display alley A
//<4> <5> <2> <3>
//Enter one of the options below
//D)isplay P)ark R)etrieve Q)uit:r
//Please enter ticket number: 4
//Car retrieved for ticket number <4>
//Enter one of the options below
//D)isplay P)ark R)etrieve Q)uit:d
//Display alley A
//<5> <2> <3>
//Enter one of the options below
//D)isplay P)ark R)etrieve Q)uit:r
//Please enter ticket number: 3
//Car retrieved for ticket number <3>
//Enter one of the options below
//D)isplay P)ark R)etrieve Q)uit:d
//Display alley A
//<5> <2>
//Enter one of the options below
//D)isplay P)ark R)etrieve Q)uit:r
//Please enter ticket number: 2
//Car retrieved for ticket number <2>
//Enter one of the options below
//D)isplay P)ark R)etrieve Q)uit:d
//Display alley A
//<5>
//Enter one of the options below
//D)isplay P)ark R)etrieve Q)uit:r
//Please enter ticket number: 5
//Car retrieved for ticket number <5>
//Enter one of the options below
//D)isplay P)ark R)etrieve Q)uit:d
//Display alley A
//No cars in Parking Alley
//Enter one of the options below
//D)isplay P)ark R)etrieve Q)uit:p
//Car Parked
//Enter one of the options below
//D)isplay P)ark R)etrieve Q)uit:d
//Display alley A
//<1>
//Enter one of the options below
//D)isplay P)ark R)etrieve Q)uit:q
//
// Enter one of the options below
//D)isplay P)ark R)etrieve Q)uit:p
//<1>
//Car Parked
//Enter one of the options below
//D)isplay P)ark R)etrieve Q)uit:p
//<2> <1>
//Car Parked
//Enter one of the options below
//D)isplay P)ark R)etrieve Q)uit:p
//<3> <2> <1>
//Car Parked
//Enter one of the options below
//D)isplay P)ark R)etrieve Q)uit:p
//<4> <3> <2> <1>
//Car Parked
//Enter one of the options below
//D)isplay P)ark R)etrieve Q)uit:pp
//<5> <4> <3> <2> <1>
//Car Parked
//Enter one of the options below
//D)isplay P)ark R)etrieve Q)uit:PARKING LOT FULL
//Enter one of the options below
//D)isplay P)ark R)etrieve Q)uit:d
//Display alley A
//<5> <4> <3> <2> <1>
//Enter one of the options below
//D)isplay P)ark R)etrieve Q)uit:r
//Please enter ticket number: 6
//CAR NOT PARKED IN MY LOT
//Enter one of the options below
//D)isplay P)ark R)etrieve Q)uit:d
//Display alley A
//<5> <4> <3> <2> <1>
//Enter one of the options below
//D)isplay P)ark R)etrieve Q)uit:r
//Please enter ticket number: 5
//Car retrieved for ticket number <5>
//Enter one of the options below
//D)isplay P)ark R)etrieve Q)uit:d
//Display alley A
//<4> <3> <2> <1>
//Enter one of the options below
//D)isplay P)ark R)etrieve Q)uit:r
//Please enter ticket number: 1
//Car retrieved for ticket number <1>
//Enter one of the options below
//D)isplay P)ark R)etrieve Q)uit:r
//Please enter ticket number:
//6
//CAR NOT PARKED IN MY LOT
//Enter one of the options below
//D)isplay P)ark R)etrieve Q)uit:d
//Display alley A
//<4> <3> <2>
//Enter one of the options below
//D)isplay P)ark R)etrieve Q)uit:r
//Please enter ticket number: 1
//CAR NOT PARKED IN MY LOT
//Enter one of the options below
//D)isplay P)ark R)etrieve Q)uit:d
//Display alley A
//<4> <3> <2>
//Enter one of the options below
//D)isplay P)ark R)etrieve Q)uit:r
//Please enter ticket number: 3
//Car retrieved for ticket number <3>
//Enter one of the options below
//D)isplay P)ark R)etrieve Q)uit:d
//Display alley A
//<4> <2>
//Enter one of the options below
//D)isplay P)ark R)etrieve Q)uit:r
//Please enter ticket number: 2
//Car retrieved for ticket number <2>
//Enter one of the options below
//D)isplay P)ark R)etrieve Q)uit:d
//Display alley A
//<4>
//Enter one of the options below
//D)isplay P)ark R)etrieve Q)uit:r
//Please enter ticket number: 4
//Car retrieved for ticket number <4>
//Enter one of the options below
//D)isplay P)ark R)etrieve Q)uit:d
//Display alley A
//No cars in Parking Alley
//Enter one of the options below
//D)isplay P)ark R)etrieve Q)uit:r
//Please enter ticket number: 5
//CAR NOT PARKED IN MY LOT
//Enter one of the options below
//D)isplay P)ark R)etrieve Q)uit:d
//Display alley A
//No cars in Parking Alley
//Enter one of the options below
//D)isplay P)ark R)etrieve Q)uit:q
//
//#######################
//
//invalid check
//
//
//Enter one of the options below
//D)isplay P)ark R)etrieve Q)uit:lkdfjldkf
//Invalid input entry
//Enter one of the options below
//D)isplay P)ark R)etrieve Q)uit:Invalid input entry
//Enter one of the options below
//D)isplay P)ark R)etrieve Q)uit:Display alley A
//<5> <4> <3> <2> <1>
//Enter one of the options below
//D)isplay P)ark R)etrieve Q)uit:Invalid input entry
//Enter one of the options below
//D)isplay P)ark R)etrieve Q)uit:Invalid input entry
//Enter one of the options below
//D)isplay P)ark R)etrieve Q)uit:Invalid input entry
//Enter one of the options below
//D)isplay P)ark R)etrieve Q)uit:Display alley A
//<5> <4> <3> <2> <1>
//Enter one of the options below
//D)isplay P)ark R)etrieve Q)uit:Invalid input entry
//Enter one of the options below
//D)isplay P)ark R)etrieve Q)uit:Invalid input entry
//Enter one of the options below
//D)isplay P)ark R)etrieve Q)uit:r
//Please enter ticket number: 4
//Car retrieved for ticket number <4>
//Enter one of the options below
//D)isplay P)ark R)etrieve Q)uit:d
//Display alley A
//<5> <3> <2> <1>
//Enter one of the options below
//D)isplay P)ark R)etrieve Q)uit:r
//Please enter ticket number: -3
//Invalid ticket. Please enter a ticket number from 1-5
//Enter one of the options below
//D)isplay P)ark R)etrieve Q)uit:r
//Please enter ticket number: -2
//Invalid ticket. Please enter a ticket number from 1-5
//Enter one of the options below
//D)isplay P)ark R)etrieve Q)uit:r
//Please enter ticket number: 2
//Car retrieved for ticket number <2>
//Enter one of the options below
//D)isplay P)ark R)etrieve Q)uit:d
//Display alley A
//<5> <3> <1>
//Enter one of the options below
//D)isplay P)ark R)etrieve Q)uit:
//###########################
 */
