/**********************************************
*Copyright 2007 Suleman Saya
*Edited by:  Author - Divyashree Hassan Ravindrakumar
*Assignment 3
*
*OS - macOS Sierra - version 10.12.5
*Compiler g++
*	Configured with: --prefix=/Library/Developer/CommandLineTools/usr --with-gxx-include-dir=/usr/include/c++/4.2.1
*	Apple LLVM version 8.1.0 (clang-802.0.42)
*	Target: x86_64-apple-darwin16.7.0
*	Thread model: posix
*	InstalledDir: /Library/Developer/CommandLineTools/usr/bin
*
**********************************************/

//Assignment Description
//
//Write a program using link list to manage an Employee database.
//Each entry in the data file includes three fields: Employee Name, Employee Age, and Employee Salary.
//Data is semicolon delimited in the file. Your program should read data from the file into a link list in
//a sorted order by employee name. Your program must be able to open a data file when its name is passed
//as a command line argument. When user adds an employee record, make sure that data goes into a link list in
//a sorted order. When “List All Employees” is selected by the user it should display the employee data in a
//sorted order by employee name and formatted according the table in figure 1. When user selects “Exit Employee
//Database”, write all the data, if need, from the link list to a file and terminate the program gracefully.
//Display the following menu one the screen
//after reading the data file into a link list:
//
//Menu Options:

//1. Add Employee
//2. Delete Employee
//3. Search Employee
//4. List All Employees
//5. Save Employee Database
//6. Exit Employee Database
//Enter Your Choice:

//Input File Data for Project #3
//Use any text editor to enter following data into a file.

//Patrick Stroud;48;140565
//Ursula Spencer;27;36450
//Clifton Stillman;65;99900
//William Reynolds;37;77550
//Dean Niles;53;120000
//John Kaufman;53;69597
//Paul Kane;51;169650
//Paul Goldsmith;60;200000
//Larry Godwin;45;59500
//Kurt Lamm;39;90000
//Susan Carltom;42;85000
//Cameron Wu;29;50589
//
//
//output
//# Employee Name 		 Age 	Salary
//=============================================
//1. Cameron Wu            29		50,589
//2. Clifton Stillman      65     99,900
//3. Dean Niles            53     120,000
//4. John Kaufman          53     69,597
//5. Kurt Lamm             39     90,000
//6. Larry Godwin          45     59,500
//7. Patrick Stroud        48		140,565
//8. Paul Goldsmith        60		200,000
//9. Paul Kane             51		169,650
//10. Susan Carlton        42		85,000
//11. Ursula Spencer       27 	36,450
//12. William Reynolds     37		77,550

//Recommended Project #3 Code Design
/*******************************************************************
*   FILE NAME: Prj3                                                *
********************************************************************/
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include<limits>
using namespace std;
/********************************************************************
*   CLASS NAME: CEmployee                                           *
*   PURPOSE:
*
*   MEMBER FUNCTIONS:                                               *
*     void Open (CEmployee *&pHeadPtr, CEmployee *&pCurrPtr );
*     void AddEmp (CEmployee *&pHeadPtr, CEmployee *&pCurrPtr );
*     void DeleteEmp (CEmployee *&pHeadPtr);
*     void SearchEmp (CEmployee *pHeadPtr);
*     void ListAllEmp (CEmployee *&pHeadPtr, CEmployee *&pCurrPtr);
*     void SaveToFile (CEmployee *&pHeadPtr, CEmployee *&pCurrPtr);
*     void ExitProg (CEmployee *pHeadPtr);                           *
**********************************************************************/

void instructions(){
    printf("\nEnter your choice\n");
    printf("1. Add Employee\n");
    printf("2. Delete Employee\n");
    printf("3. Search Employee\n");
    printf("4. List All Employees\n");
    printf("5. Save Employee Databse\n");
    printf("6. Exit Employee Database\n");
}


class CEmployee {
public:
    void Open(CEmployee *&pHeadPtr, CEmployee *&pCurrPtr , string);
    void AddEmp(CEmployee *&pHeadPtr, CEmployee *&pCurrPtr );
    void DeleteEmp(CEmployee *&pHeadPtr);
    void SearchEmp(CEmployee *pHeadPtr);
    void ListAllEmp(CEmployee *&pHeadPtr, CEmployee *&pCurrPtr);
    void SaveToFile(CEmployee *&pHeadPtr, CEmployee *&pCurrPtr);
    void ExitProg(CEmployee *pHeadPtr);
private:
    char m_Name [20];
    unsigned int m_Age;
    unsigned int m_Salary;
    CEmployee *m_pLink;
};
/********************************************************************
*   FUNCTION: Open                                                  *
*   PURPOSE:
*
*   PARAMETERS: pHeadPtr, pCurrPtr                                  *
*   LOCAL VARIABLES: temp_name                                      *
********************************************************************/
void CEmployee::Open(CEmployee *&pHeadPtr, CEmployee *&pCurrPtr, string filename)
{
    ifstream infile;
    infile.open(filename);
    char Str[80]; // string to be read from the file
    char d[] = ";"; //delimiter
    int i = 0;
//    cout << "In Open "<< endl;
    while (infile.getline(Str, 80)){
        cout << "Str "<<Str<< endl;
        CEmployee *prevptr;
        CEmployee *newptr = new CEmployee;
        if (newptr != NULL){
            strcpy(newptr->m_Name,strtok(Str, d));
            newptr->m_Age = atoi(strtok(NULL, d));
            newptr->m_Salary = atoi(strtok(NULL, d));
            prevptr=NULL;
            pCurrPtr=pHeadPtr;
            while (pCurrPtr != NULL && (strcmp(newptr->m_Name, pCurrPtr->m_Name) > 0)){
                prevptr = pCurrPtr;
                pCurrPtr = pCurrPtr->m_pLink;
            }
            if(prevptr == NULL){
                newptr->m_pLink=pHeadPtr;
                pHeadPtr=newptr;
            } else{
                prevptr->m_pLink = newptr;
                newptr->m_pLink = pCurrPtr;
            }
        }
        i++;
    }
    infile.close();
    cout << endl << i << " Employee records are loaded from the data file into the link list" << endl;
}


/***********************************************************************
*   FUNCTION:  DeleteEmp                                               *
*   PURPOSE:  Deletes employees from link list.                        *
*   PARAMETERS:  pHeadPtr                                              *
*   LOCAL VARIABLES: CurrPtr, LastPtr, Del_name                        *
***********************************************************************/
void CEmployee::DeleteEmp(CEmployee *&pHeadPtr)
{
        string name;
        bool found = false;
        cout << "Enter Employee Name to Delete: ";
//        cin >> name;
        cin.ignore();
        cin.clear();
        getline(cin, name);
//        cout << "\nto be deleted : "<<name.c_str()<<endl;
        CEmployee *prevptr, *currptr, *tempptr;
        if (strcmp(name.c_str(),pHeadPtr->m_Name) ==0 ){
            tempptr = pHeadPtr;
            pHeadPtr = pHeadPtr->m_pLink;
            cout << "Deleting Node "<< name << endl;
            free (tempptr);
            found = true;
        }
        else {
            prevptr = pHeadPtr;
            currptr = pHeadPtr->m_pLink;
            while ((currptr != NULL) && (strcmp(currptr->m_Name,name.c_str())!=0)) {
                prevptr = currptr;
                currptr = currptr->m_pLink;
            }
            if (currptr != NULL) {
                tempptr = currptr;
                prevptr->m_pLink = currptr->m_pLink;
                currptr = currptr->m_pLink;
                cout << "Deleting Node "<< name.c_str() << endl;
                found = true;
                free(tempptr);
            }
        }
        if (!found)
            cout << "Name "<< name.c_str() << " node not found " << endl;
}

/***********************************************************************
*   FUNCTION: SaveToFile                                               *
*   PURPOSE: Saves data in link list to data file empinfo.data         *
*   PARAMETERS: pHeadPtr, pCurrPtr                                     *
*   LOCAL VARIABLES:  None                                             *
***********************************************************************/
void CEmployee::SaveToFile(CEmployee *&pHeadPtr, CEmployee *&pCurrPtr)
{
    ofstream outfile;
    char filename[40]="emp_output.txt";
    outfile.open(filename);
    cout << "Saving Data to File "<< filename<< endl;
    if(pHeadPtr == NULL){
        outfile << "EmptyList. No Data found"<< endl;
    }
    else {
        outfile <<setw(20)<<"# Employee Name"<<setw(20) <<"Age"<<setw(20)<<"Salary"<<endl;
        pCurrPtr = pHeadPtr;
        while(pCurrPtr!= NULL){
            outfile << setw(20) << pCurrPtr->m_Name << setw(20) <<pCurrPtr->m_Age<<setw(20)<<pCurrPtr->m_Salary<<endl;
            pCurrPtr = pCurrPtr->m_pLink;
        }
    }
    outfile.close();
}
/***********************************************************************
*   FUNCTION: AddEmp                                                   *
*   PURPOSE:  Adds emmployees to link list.                            *
*   PARAMETERS:  None                                                  *
*   LOCAL VARIABLES:  None                                             *
***********************************************************************/
void CEmployee::AddEmp(CEmployee *&pHeadPtr, CEmployee *&pCurrPtr )
{
    CEmployee *newptr, *prevptr;
    newptr = new CEmployee;

    if (newptr != NULL){
        prevptr=NULL;
        pCurrPtr=pHeadPtr;
        cout << "\nEnter Employee Name: ";
        cin >> newptr->m_Name;
        cout << "\nEnter Employee's Age: ";
        cin >> newptr->m_Age;
        cout << "\nEnter Employee's Salary: ";
        cin >> newptr->m_Salary;
        while (pCurrPtr != NULL && (strcmp(newptr->m_Name, pCurrPtr->m_Name) > 0)){
            prevptr = pCurrPtr;
            pCurrPtr = pCurrPtr->m_pLink;
        }
        prevptr->m_pLink = newptr;
        newptr->m_pLink = pCurrPtr;
    }
}

/********************************************************************
*  FUNCTION: ExitProg
* PURPOSE: Exits program and deletes memory spaces that were being
*        used.
*  PARAMETERS: pHeadNode
*   LOCAL VARIABLES:  pCurr, pDeleteThisNode
***********************************************************************/
void CEmployee::ExitProg(CEmployee *pHeadNode)
{
    CEmployee *pCurr, *pDeleteThisNode;
    SaveToFile(pHeadNode, pCurr);
    pCurr = pHeadNode;
    cout << "Deleting All Nodes"<< endl;
    while ( pCurr != 0)
    {
        pDeleteThisNode = pCurr;
        pCurr = pCurr->m_pLink;
        delete pDeleteThisNode;
    }
    cout << "Exiting..."<< endl;
}
/*********************************************************************
*   FUNCTION:  ListAllEmp                                            *
*   PURPOSE:  Lists all employees in link list to the screen.        *
*   PARAMETER:  pHeadPtr, pCurrPtr                                   *
*   LOCAL VARIABLES: count                                           *
**********************************************************************/
void CEmployee::ListAllEmp(CEmployee *&pHeadPtr, CEmployee *&pCurrPtr)
{
    if(pHeadPtr == NULL){
        cout << "\n Empty list found\n"<<endl;
    }
    else {
        cout <<setw(20)<<"# Employee Name"<<setw(20) <<"Age"<<setw(20)<<"Salary"<<endl;
        pCurrPtr = pHeadPtr;
        while(pCurrPtr!= NULL){
            cout << setw(20) << pCurrPtr->m_Name << setw(20) <<pCurrPtr->m_Age<<setw(20)<<pCurrPtr->m_Salary<<endl;
            pCurrPtr = pCurrPtr->m_pLink;
        }
    }

}
/*********************************************************************
*   FUNCTION:  SearchEmp                                             *
*   PURPOSE:  Searches link list for specified employee.             *
*   PARAMTERS:  pHeadPtr                                             *
*   LOCAL VARIABLES: CurrPtr, Search_name, flag                      *
**********************************************************************/
void CEmployee::SearchEmp(CEmployee *pHeadPtr)
{
    string name;
    bool found = false;
    cout << "Enter Employee Name to search: ";
    cin.ignore();
    cin.clear();
    getline(cin, name);
    CEmployee *currptr;
    int count =0;
    if (pHeadPtr == NULL){
        cout << "Empty list "<< endl;
        return;
    }
    currptr=pHeadPtr;
    while(currptr != NULL){
        if (strcmp(name.c_str(),currptr->m_Name) ==0 ) {
            found = true;
            cout << "Employee "<< name << " found at position "<< count << endl;
            break;
        }
        currptr = currptr->m_pLink;
        count++;
    }
    if (!found){
        cout << "Employee "<< name << " not found in database"<< endl;
    }
}

/**********************************************************************/

int main(int argc, char *argv[]){
    string filename;
    CEmployee *linkedlist;
    CEmployee *pHeadPtr  = NULL ;
    CEmployee *pCurrPtr = NULL ;
    int choice;

    if (argc != 2) {
        cout << "Usage: PR <filename>\n";
        return 1;
    }

    filename = argv[1];
    ifstream Infile(filename);
    if (!Infile) {
        cout << "Cannot open file " << filename <<endl;
        exit(1);
    }
    /*
    cout << "Please Enter filename to Load Initial Data into LinkedList: ";
    getline (cin,filename);
    cout << "filename "<< filename <<endl;
     */

    linkedlist->Open(pHeadPtr, pCurrPtr, filename);
    linkedlist->ListAllEmp(pHeadPtr, pCurrPtr);

    instructions();
    cout << "?  " ;
    while(!(cin >> choice)){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input.  Try again: ";
    }

    while (1){
        switch(choice){
            case 1:
                linkedlist->AddEmp(pHeadPtr, pCurrPtr);
                break;
            case 2:
                linkedlist->DeleteEmp(pHeadPtr);
                break;
            case 3:
                linkedlist->SearchEmp(pHeadPtr);
                break;
            case 4:
                linkedlist->ListAllEmp(pHeadPtr, pCurrPtr);
                break;
            case 5:
                linkedlist->SaveToFile(pHeadPtr, pCurrPtr);
                break;
            case 6:
                linkedlist->ExitProg(pHeadPtr);
                exit(0);
            default:
                instructions();
                cout << "?  " ;
                while(!(cin >> choice)){
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input.  Try again: ";
                }
        }
        instructions();
        cout << "?  " ;
        while(!(cin >> choice)){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input.  Try again: ";
        }
    }
    return 0;
}
