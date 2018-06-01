// mosduino - Arduino port of MOS
//

#include "mos.h"

#include "apptasks.h"

const int ledA = 13;


void setup()
{
    int	taskid;
    
    pinMode(ledA, OUTPUT);
//    digitalWrite(13, HIGH);
    
    mosInitTasking();
    mosPrintEnable( TRUE );
    mosSetVerboseState( FALSE );
    
    mosPrint("MOSduino");
    
    taskid = mosCreateTask( "getid", (void *) &getid, &dummyargs, 16 );
    //taskid = mosCreateTask( "blinktask", (void *) &blinktask, &dummyargs, 16 );
    taskid = mosCreateTask( "cmdtask", (void *) &cmdtask, &dummyargs, 32 );
    taskid = mosCreateTask( "kbdtask", (void *) &kbdtask, &dummyargs, 32 );

}

void loop()
{
    digitalWrite(ledA, HIGH);   // set the LED on
    
    // execute the tasks until user says 'done'      
    mosSequenceTaskListOnce();
}

