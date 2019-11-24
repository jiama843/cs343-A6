#include "parent.h"

using namespace std;

/**
 * TODO:
 *  - Periodically give [$1, $3] to a random student
 *      -- Yield for parentalDelay times before gifting
 *      -- Check for call to destructor to know when to terminate
 *      -- Use a terminating _Else on the accept statement
 */


// ---------------------------------
//  Private Methods
// ---------------------------------
void Parent::main() {
    // TODO
}  // Parent::main

// ---------------------------------
//  Constructor
// ---------------------------------
Parent::Parent( Printer& prt, Bank& bank, unsigned int numStudents, unsigned int parentalDelay ) : prt( prt ), bank( bank ), numStudents( numStudents ), parentalDelay( parentalDelay ) {

}  // Parent::Parent