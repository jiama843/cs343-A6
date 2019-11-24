#ifndef BANK_H
#define BANK_H

// A monitor that behaves like a server
_Monitor Bank {
    unsigned int numStudents;

	// TODO: Need a data structure to store students' bank information

   public: 
	Bank( unsigned int numStudents );
    void deposit( unsigned int id, unsigned int amount );
	void withdraw( unsigned int id, unsigned int amount );
};

#endif