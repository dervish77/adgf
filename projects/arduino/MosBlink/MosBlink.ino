// mosblink - example sketch of using Mosduino library
//

#include <mos.h>

#include "apptasks.h"

void setup()
{
    int	taskid;
    
    pinMode(13, OUTPUT);
    
    mosInitTasking();
    mosPrintEnable( TRUE );
    
    mosPrint("MOSduino\n");
    
    taskid = mosCreateTask( "getid", (void *) &getid, &dummyargs, 16 );
    taskid = mosCreateTask( "blinktask", (void *) &blinktask, &dummyargs, 16 );
}

void loop()
{
    // execute the tasks       
    mosSequenceTaskListOnce();
}

