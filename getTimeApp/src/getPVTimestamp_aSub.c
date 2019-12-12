#include <aSubRecord.h>
#include <registryFunction.h>
#include <epicsExport.h>
#include <stdio.h>
#include <dbDefs.h>
#include <dbFldTypes.h>
#include <dbAccess.h>
#include <link.h>
#include <math.h>


static int getPVTimeStamp_aSub(aSubRecord *prec) {

epicsTimeStamp tick;    
unsigned long NANOSPERSECOND = 1000000000;

unsigned long ticksPerSecond=0;



	if (!dbGetTimeStamp(&prec->inpa, &tick)){ 			
		
				
		*(unsigned long *)prec->vala = tick.secPastEpoch; 		//Seconds past EPICS TimeStamp Epoch	
		*(unsigned long *)prec->valb = tick.nsec;	
		*(double *)prec->valc = tick.secPastEpoch + (double)tick.nsec*NANOSPERSECOND;
		
		return 0; 
	}
	else{
		printf("Could not retrieve timestamp.\n"); 
		return -1; /*Raise SOFT_ALARM, BRSV */
	}

}


//register the function with the dbd file

epicsRegisterFunction(getPVTimeStamp_aSub);