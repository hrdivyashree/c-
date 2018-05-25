/**********************************************
*Copyright 2007 Suleman Saya
*Edited by:  Author - Divyashree Hassan Ravindrakumar
*Assignment 4
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

/*************
Write a program that creates a class hierarchy that stores information about airships. Start with a general base class
called airship that stores the number of passengers that can be carried and the amount of cargo (in pounds) that can be
carried. Then create two derived classes called airplane and balloon from airship.
Have airplane store the type of engine used (propeller or jet) and range, in miles; also give airplane a name.
Have balloon store information about the type of gas used to lift the balloon (hydrogen or helium) and its maximum altitude (in feet).
Also give balloon a name.

This program prints a report of airship data. It reads the data from the file “airship.dat”. Each line of data consists of
a comma-separated list. An airship is either an airplane or a balloon. The first field in each line of input determines whether
the line describes an airplane or a balloon.

The airplane data has these fields:
airshipType, airplaneName, maxPassengerCount, maxCargoWeight, engineType, range

The balloon data has these fields:
airshipType, balloonName, maxPassengerCount, maxCargoWeight, gasType, maxAltitude;

The program reads each line of input and checks the airship type for the data. If the line describes an airplane, the program creates
an airplane object, and if the line describes a balloon, the program creates a balloon object. The program places the airplane and balloon
objects in an array of pointer type airship.

The program then iterates through the array once to generate an airplane report and once to create a balloon report. You must demonstrate the
usage of pure virtual function and show run time polymorphism in this program. There is no need for user interface. Your program should take a
command line argument for the input file name.


Your program should read data from the file. Data file provides five records for airplane and five records for balloon.

Input File Data for Assignment #4

Use any text editor to enter the following data into a “airship.dat” file.

1,Blue Racer,10,10000,0,1000
0,SR-71 Blackbird,2,33000,0,80000
1,Desert Winds,20,20000,1,2000
0,U-2,4,22000,0,160000
1,Kaleidoscope,30,30000,1,3000
1,Desert Spirit,40,40000,0,4000
0,Boeing 747,300,11000,0,40000
0,McDonnel Douglas,225,11000,0,38000
0,Cessna 120,6,11000,1,10000
1,Painted Angel,50,50000,0,5000

Data fields Names
AirShipType {Airplane=0,Ballon=1}
AirShipName, NumberOfPassengers,AmountOfCargo
{Engine Type [Jet = 0, Propeller = 1] Gas Type [Helium = 0, Hydrogen = 1]} Maximum Range/Altitude


Output for Assignment #4
Use following output format:

Listing of all Airplanes
Name                Engine Type     Maximum Range
------------------------------------------------
SR-71 Blackbird     Jet                 80000
U-2                 Jet                 160000
Boeing 747          Jet                 40000
McDonnell Douglas   Jet                 38000
Cessna 120          Propellor           10000


Listing of all Balloons
Name                Gas             Altitude
----------------------------------------------------
Blue Racer          helium          1000
Desert Winds        hydrogen        2000
Kaleidoscope        hydrogen        3000
Desert Spirit       helium          4000
Painted Angel       helium          5000

**************/


#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <cstring>
using namespace std;
// This data structure should be a record in a input file

enum AirshipType {AIRPLANE=0,BALOON=1};
enum EngineType {Jet = 0, Propeller = 1};
enum GasType {Helium = 0, Hydrogen = 1};

// This data structure should be a record in a input file
struct AirshipData {
    AirshipType Type;
    string AirshipName;
    int NumberOfPassengers ;
    int AmountOfCargo;
    EngineType EType;
    GasType GType;
    int Range;
};

class Airship {
public:
    Airship() { }
    virtual void GetData(AirshipData &data) = 0;
    virtual void ShowData() = 0;
    AirshipType GetAirshipType() { return m_AirshipType; }
    virtual ~Airship(){ }
protected:
    AirshipType m_AirshipType;
    int m_NumberOfPassengers;
    int m_AmountOfCargo;
};





class Airplane : public Airship {
public:
    Airplane() : Airship() {}
    void GetData(AirshipData &data);
    void ShowData();
    static const char* setEngineType(EngineType);
    ~Airplane(){}
private:
    EngineType m_EngineType;
    string m_AirplaneName;
    int m_Range;
};

const char* Airplane::setEngineType(EngineType engine) {
    switch (engine) {
        case 0:
            return "Jet";
            break;
        case 1:
            return "Propellor";
            break;
        default:
            return "ERROR";
            break;
    } // end switch
}

// Function: GetData
void Airplane::GetData(AirshipData &data)
{
    // cast integer to enum
    m_AirshipType = AirshipType(data.Type);
    m_NumberOfPassengers = data.NumberOfPassengers;
    m_AmountOfCargo = data.AmountOfCargo;
    m_AirplaneName = data.AirshipName;
    m_EngineType = EngineType(data.EType);
    m_Range = data.Range;
}
void Airplane::ShowData()
{
    cout << setw(20)<<m_AirplaneName << setw(20) << setEngineType(m_EngineType) << setw(20) << m_Range << endl;
}

class Baloon : public Airship {
public:
    Baloon() : Airship() {}
    void GetData(AirshipData &data);
    void ShowData();
    static const char* setGasType(GasType);
    ~Baloon(){ }
private:
    GasType m_GasType;
    string m_BaloonName;
    int m_Altitude;
};

const char* Baloon::setGasType(GasType gas){
    switch (gas) {
        case 0:
            return "Helium";
            break;
        case 1:
            return "Hydrogen";
            break;
        default:
            return "ERROR";
            break;
    } // end switch
}

void Baloon::GetData(AirshipData &data)
{
    m_AirshipType = AirshipType(data.Type);
    m_NumberOfPassengers = data.NumberOfPassengers;
    m_AmountOfCargo = data.AmountOfCargo;
    m_BaloonName = data.AirshipName;
    m_GasType = data.GType;
    m_Altitude = data.Range;
}
void Baloon::ShowData()
{
    cout << setw(20)<<m_BaloonName << setw(20) << setGasType(m_GasType) <<  setw(20)  << m_Altitude << endl;
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        cout << "Usage: PR <filename>\n";
        return 1; }
    ifstream Infile(argv[1]);
    if (!Infile) {
        cout << "Cannot open file\n";
        return 1; }
    char LineBuf[100];
    char d[] = ",";
    Airship *pShip[10];
    int i=0;
    //while (Infile.getline(LineBuf, 100) && !Infile.eof())
    while (!Infile.eof()) {
        if (Infile.getline(LineBuf, 100)){
        struct AirshipData data;
        data.Type = AirshipType(atoi(strtok(LineBuf, d)));
        switch (data.Type) {
            case AIRPLANE:
                // Create Ariplane Object
                pShip[i] = new Airplane();
                data.AirshipName= strtok(NULL, d);
                data.NumberOfPassengers= atoi(strtok(NULL, d));
                data.AmountOfCargo=atoi(strtok(NULL, d));
                data.EType = EngineType(atoi(strtok(NULL, d)));
                data.Range = atoi(strtok(NULL, d));
                break;
            case BALOON:
                // Create Orange Object
                pShip[i] = new Baloon();
                data.AirshipName= strtok(NULL, d);
                data.NumberOfPassengers= atoi(strtok(NULL, d));
                data.AmountOfCargo=atoi(strtok(NULL, d));
                data.GType =  GasType(atoi(strtok(NULL, d)));
                data.Range = atoi(strtok(NULL, d));
                break;
            default:
                break;
        } // end switch
        // call appropriate function
        pShip[i++]->GetData(data);
        memset(LineBuf,'\0',100);
        }
    }
    cout << "Following are Airplane values\n";
    cout << "\n"<<setw(20)<<"Airplane name" << setw(20) << "Engine Type"<< setw(20) << "Maximum Range\n";
    cout << "------------------------------------------------------------------\n";
    for (int i = 0; i < 10; i++) {
        if (pShip[i]->GetAirshipType() == AIRPLANE)
            pShip[i]->ShowData();
    }
    cout << "\n\nFollowing are Baloon values\n";
    cout << "\n"<<setw(20)<<"Baloon name" << setw(20) << "Gas Type "<< setw(20) << "Maximum Altitude\n";
    cout << "------------------------------------------------------------------\n";
    for (int i = 0; i < 10; i++) {
        if (pShip[i]->GetAirshipType() == BALOON)
            pShip[i]->ShowData();
    }
    for (int i = 0; i < 10; i++) {
        if (pShip[i])
            delete pShip[i];// Delete appropriate object
    } // end for loop
    return 0;
}

