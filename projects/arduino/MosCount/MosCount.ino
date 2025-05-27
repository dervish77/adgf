// moscount - example sketch of using Mosduino library
//

#include <mos.h>

#include "apptasks.h"


void setup()
{
    int	taskid;
    
    mosInitTasking();
    mosPrintEnable( TRUE );
    
    mosPrint("MOSduino\n");
    
    mosTraceInit(13);
    mosTraceInit(12);
    
    taskid = mosCreateTask( "counttask", (void *) &counttask, &dummyargs, 16 );
    taskid = mosCreateTask( "printtask", (void *) &printtask, &dummyargs, 16 );
}

void loop()
{
    // execute the tasks       
    mosSequenceTaskListOnce();
}
