#ifndef PRINTER_H
#define PRINTER_H

_Monitor Printer {
    unsigned int numStudents;
    unsigned int numVendingMachines;
    unsigned int numCouriers;
    unsigned int bufferLength;

    void flush();

   public:
    enum Kind { Parent,
                Groupoff,
                WATCardOffice,
                NameServer,
                Truck,
                BottlingPlant,
                Student,
                Vending,
                Courier };

    Printer( unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers );
    ~Printer();

    void print( Kind kind, char state );
    void print( Kind kind, char state, unsigned int value1 );
    void print( Kind kind, char state, unsigned int value1, unsigned int value2 );

    // lid means local identifier
    void print( Kind kind, unsigned int lid, char state );
    void print( Kind kind, unsigned int lid, char state, unsigned int value1 );
    void print( Kind kind, unsigned int lid, char state, unsigned int value1, unsigned int value2 );

   private:
    // Defines information that needs to be tracked.
    struct PrintState {
        Kind         kind;
        unsigned int lid;
        char         state;

        bool         value1Valid;
        bool         value2Valid;
        unsigned int value1;
        unsigned int value2;
    } * *buffer;  // buffer is the stored information.

    // returns the index of the print column that the caller belongs to
    unsigned int getBufferIndex( Kind kind, unsigned int lid = 0 );
};  // Printer

#endif