#include "printer.h"

#include <iostream>
#include <string>

using namespace std;

// -----------------------------------
//  Helper Methods
// -----------------------------------
void Printer::flush() {
    for ( unsigned int i = 0; i < bufferLength; i++ ) {
        if ( buffer[i] ) {
            PrintState* item = buffer[i];  // read stored information

            // print the alphabet that represents this state
            cout << item->state;

            if ( item->value1Valid ) cout << item->value1;
            if ( item->value2Valid ) cout << ',' << item->value2;

            delete buffer[i];
            buffer[i] = nullptr;
        }  // if

        cout << "\t";
    }  // for

    cout << endl;
}  // Printer::flush

unsigned int Printer::getBufferIndex( Kind kind, unsigned int lid ) {
    switch ( kind ) {
        case Parent:
            return 0;

        case Groupoff:
            return 1;

        case WATCardOffice:
            return 2;

        case NameServer:
            return 3;

        case Truck:
            return 4;

        case BottlingPlant:
            return 5;

        case Student:
            return 6 + lid;

        case Vending:
            return 6 + numStudents + lid;

        case Courier:
            return 6 + numStudents + numVendingMachines + lid;

        default:
            break;
    }  // switch

    return 0;
}  // Printer::getBufferIndex

// -----------------------------------
//  Constructor and Destructor
// -----------------------------------
Printer::Printer( unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers ) : numStudents( numStudents ), numVendingMachines( numVendingMachines ), numCouriers( numCouriers ) {
    /*
     * There are 6 kinds of objects that have single instances: 
     *  - parent
     *  - groupoff
     *  - WATCard office
     *  - name server
     *  - truck
     *  - bottling plant
     * 
     * Then there are 3 kinds of objects that have multiple instances:
     *  - student
     *  - vending machine
     *  - courier
     */
    bufferLength = 6 + numStudents + numVendingMachines + numCouriers;
    buffer       = new PrintState*[bufferLength];

    for ( unsigned int i = 0; i < bufferLength; i++ ) {
        // fill the buffer with nullptrs
        buffer[i] = nullptr;
    }  // for

    /*
     * print out the first row:
     *  - Parent Gropoff WATOff Names Truck Plant
     *  - Stud0 Stud1 Mach0 Mach1 Mach2 Cour0
     */
    cout << "Parent\tGropoff\tWATOff\tNames\tTruck\tPlant\t";

    for ( unsigned int i = 0; i < numStudents; i++ ) {
        cout << "Stud" << i << '\t';
    }  // for

    for ( unsigned int i = 0; i < numVendingMachines; i++ ) {
        cout << "Mach" << i << '\t';
    }  // for

    for ( unsigned int i = 0; i < numCouriers; i++ ) {
        cout << "Cour" << i << '\t';
    }  // for

    cout << endl;

    // print out the second row (7 asterisks + space)
    for ( unsigned int i = 0; i < bufferLength; i++ ) {
        cout << "*******\t";
    }  // for

    cout << endl;
}  // Printer::Printer

Printer::~Printer() {
    // print out any remaining items
    flush();

    for ( unsigned int i = 0; i < bufferLength; i++ ) {
        // delete all the Items
        delete buffer[i];
    }  // for

    delete[] buffer;

    // ending message
    cout << "***********************" << endl;
}

// -----------------------------------
//  Print Methods
// -----------------------------------
void Printer::print( Kind kind, char state ) {
    unsigned int bufferIndex = getBufferIndex( kind );
    if ( buffer[bufferIndex] ) flush();  // if we're overwriting current buffer, then flush first

    PrintState* newPrintState = new PrintState;
    newPrintState->kind       = kind;
    newPrintState->state      = state;

    newPrintState->value1Valid = false;
    newPrintState->value2Valid = false;

    buffer[bufferIndex] = newPrintState;
}  // Printer::print base overload (parent, groupoff, WATCard office, name server, truck, bottling plant)

void Printer::print( Kind kind, char state, unsigned int value1 ) {
    unsigned int bufferIndex = getBufferIndex( kind );
    if ( buffer[bufferIndex] ) flush();  // if we're overwriting current buffer, then flush first

    PrintState* newPrintState = new PrintState;
    newPrintState->kind       = kind;
    newPrintState->state      = state;
    newPrintState->value1     = value1;

    newPrintState->value1Valid = true;
    newPrintState->value2Valid = false;

    buffer[bufferIndex] = newPrintState;
}  // Printer::print one value overload (parent, groupoff, WATCard office, name server, truck, bottling plant)

void Printer::print( Kind kind, char state, unsigned int value1, unsigned int value2 ) {
    unsigned int bufferIndex = getBufferIndex( kind );
    if ( buffer[bufferIndex] ) flush();  // if we're overwriting current buffer, then flush first

    PrintState* newPrintState = new PrintState;
    newPrintState->kind       = kind;
    newPrintState->state      = state;
    newPrintState->value1     = value1;
    newPrintState->value2     = value2;

    newPrintState->value1Valid = true;
    newPrintState->value2Valid = true;

    buffer[bufferIndex] = newPrintState;
}  // Printer::print two values overload (parent, groupoff, WATCard office, name server, truck, bottling plant)

void Printer::print( Kind kind, unsigned int lid, char state ) {
    unsigned int bufferIndex = getBufferIndex( kind );
    if ( buffer[bufferIndex] ) flush();  // if we're overwriting current buffer, then flush first

    PrintState* newPrintState = new PrintState;
    newPrintState->kind       = kind;
    newPrintState->lid        = lid;
    newPrintState->state      = state;

    newPrintState->value1Valid = false;
    newPrintState->value2Valid = false;

    buffer[bufferIndex] = newPrintState;
}  // Printer::print base overload (student, vending machine, courier)

void Printer::print( Kind kind, unsigned int lid, char state, unsigned int value1 ) {
    unsigned int bufferIndex = getBufferIndex( kind );
    if ( buffer[bufferIndex] ) flush();  // if we're overwriting current buffer, then flush first

    PrintState* newPrintState = new PrintState;
    newPrintState->kind       = kind;
    newPrintState->lid        = lid;
    newPrintState->state      = state;
    newPrintState->value1     = value1;

    newPrintState->value1Valid = true;
    newPrintState->value2Valid = false;

    buffer[bufferIndex] = newPrintState;
}  // Printer::print one value overload (student, vending machine, courier)

void Printer::print( Kind kind, unsigned int lid, char state, unsigned int value1, unsigned int value2 ) {
    unsigned int bufferIndex = getBufferIndex( kind );
    if ( buffer[bufferIndex] ) flush();  // if we're overwriting current buffer, then flush first

    PrintState* newPrintState = new PrintState;
    newPrintState->kind       = kind;
    newPrintState->lid        = lid;
    newPrintState->state      = state;
    newPrintState->value1     = value1;
    newPrintState->value2     = value2;

    newPrintState->value1Valid = true;
    newPrintState->value2Valid = true;

    buffer[bufferIndex] = newPrintState;
}  // Printer::print two values overload (student, vending machine, courier)
