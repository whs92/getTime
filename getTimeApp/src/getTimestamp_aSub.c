#include <aSubRecord.h>
#include <registryFunction.h>
#include <epicsExport.h>
#include <stdio.h>
#include <dbDefs.h>
#include <dbFldTypes.h>
#include <dbAccess.h>
#include <link.h>
#include <math.h>


static int getTimeStamp_aSub(aSubRecord *prec) {

epicsTimeStamp tick;    
unsigned long nSecRem=0;
unsigned long carrySec=0;
unsigned long ICSTICKSPERSECOND = 88052500;
unsigned long NANOSPERSECOND = 1000000000;
double NANOSPERTICK;
double ticksD;
unsigned long ticksC; 

unsigned long ticksPerSecond=0;
double clockRate = 0;
clockRate = (*((double *)prec->b));
//printf("Clock Rate %f MHz\n",clockRate);


	if (!dbGetTimeStamp(&prec->inpa, &tick)){ 			
		
		ticksPerSecond = floor(clockRate *1000000.00);
		//printf("Initial sec %lu ICS nsec %lu ",tick.secPastEpoch,tick.nsec);
		//printf("Ticks per second %lu \n",ticksPerSecond);
		NANOSPERTICK = ((double)NANOSPERSECOND/(double)ticksPerSecond);
		//printf("NANOSPERTICK = %f ",NANOSPERTICK);
		
						
		//convert the tick.nsec from nsecs to ticks
		ticksD = tick.nsec/NANOSPERTICK;
		//printf("ticksD = %f ",ticksD);
		
		ticksC = floor(ticksD);
		//printf("ticksC = %lu ",ticksC);
			
		
				
		*(unsigned long *)prec->vala = tick.secPastEpoch; 		//Seconds past EPICS TimeStamp Epoch	
		*(unsigned long *)prec->valb = ticksC;			//Fractional Nanoseconds Word	
		*(unsigned long *)prec->valc = tick.nsec;	
		
		return 0; 
	}
	else{
		printf("Could not retrieve timestamp.\n"); 
		return -1; /*Raise SOFT_ALARM, BRSV */
	}

}


//register the function with the dbd file

epicsRegisterFunction(getTimeStamp_aSub);