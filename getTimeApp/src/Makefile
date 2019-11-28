TOP=../..

include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE
#=============================

#==================================================
# build a support library

LIBRARY_IOC += getTime

# xxxRecord.h will be created from xxxRecord.dbd
#DBDINC += xxxRecord
# install getTime.dbd into <top>/dbd
DBD += getTime.dbd

# specify all source files to be compiled and added to the library
getTime_SRCS += getTimestamp_aSub.c

getTime_LIBS += $(EPICS_BASE_IOC_LIBS)

#===========================

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

