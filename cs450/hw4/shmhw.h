#define MSG_REG 1;
#define MSG_PERFECT 2;
#define MSG_INDEX 4;

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <signal.h>

#include <sys/shm.h>

#include <sys/msg.h>

#include<sys/types.h>


//define shared memory key
#define MEMKEY 19858

//define mssage key
#define MSGKEY 85891
#include <errno.h>

int errno;

//The stuct of process in the process arrays
typedef struct{
	//pid
	pid_t pid;
	int num_perfect_found;
	int num_tested;
	int num_ntested;
	
}st_process ;



//The struct of shared memory
typedef struct{

	//bit-array storing bits
	int bitmap[200000];
	
	//array store perfect nums found
	int perfectnum[20];

	//array of process of active computes
	st_process process[20];

	pid_t manage_pid;

	int num_perfect_found;
	
} st_shmem;

//IPC: structure of a message
typedef struct{
	long type;
	int param;
} st_message;







