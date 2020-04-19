#ifndef WLIB_H_INCLUDED
#define WLIB_H_INCLUDED




/* Restart the calling process if it has ended for any reason. 'full_path'
should conatain the full path of the watched program. Return 0 if no error
occured, and -1 otherwise */
int MMI(int argc ,char *argv[]);

/* The process will not be restarted after termination */
void DNR(void);

#endif
