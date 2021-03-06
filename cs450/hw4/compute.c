// HW4 - compute

//THIS CODE IS MY OWN WORK, IT WAS WRITTEN WITHOUT CONSULTING A TUTOR OR CODE WRITTEN BY OTHER STUDENTS - YIYANG ZHAO

#include "shmhw.h"

int shm_id;
st_shmem *sh_mem;

int msgq_id;
int localpid;




void suicide(int signum)
	
{
	//printf("SUICIDE!!!");
	//printf("stopping; localpid = %d\n",sh_mem ->process[localpid].pid);
	if (localpid ==-1) exit(0);
	sh_mem ->process[localpid].pid = 0;
	//printf("stopped; localpid = %d\n",sh_mem ->process[localpid].pid);
	sh_mem ->process[localpid].num_perfect_found = 0;
	sh_mem ->process[localpid].num_tested = 0;
	sh_mem ->process[localpid].num_ntested = 0;
	exit(0);
}

int isPerfect(int pang){
	if (pang <=1 ) return 0;	
	int i;
	int sum;
	sum=1;
	for (i=2;i<pang;i++)
		if (!(pang%i)) sum+=i; 
	if (sum==pang) return 1;
	return 0;

}



int main(int argc, char* argv[]){
	
;
	shm_id = shmget(MEMKEY, sizeof(st_shmem),0);
	
	if ( shm_id== -1){
		perror("Error shmget: shmget failed to allocate shared memor; check if manage is running.(./manage)");		
		exit(-1);
	} 

	
	sh_mem = shmat(shm_id,NULL,0);

	//printf("debug-1  add:%d\n",sh_mem);

	//handle signal
	struct sigaction action;
	action.sa_handler = suicide;
	
	sigaction(SIGINT, &action, NULL);
	sigaction(SIGQUIT, &action, NULL);
	sigaction(SIGHUP, &action, NULL);

	//set up msg queue
	msgq_id = msgget(MSGKEY,0);
	st_message *message = malloc(sizeof(st_message));

	//register itself
	message->type = 1;
	message->param = getpid();
	
	

	int sz = msgsnd(msgq_id,message,sizeof(message->param),0);
	//printf("MSG SENT type:%ld   MSG=:%d  s=:%d",message->type,message->param,sz);
		//printf("debug0\n");


	msgrcv(msgq_id,message,sizeof(message->param),4,0);
	localpid = message->param;

		//printf("debug msg\n");

	//start computing
	int start;
	if (argc == 2){
		start = atoi(argv[1]);
	}else{	
		start = 2;
	}	
	int current = start;

	//printf("debug1\n");


	while(1){
		int blockIndex = (current-2)/32;
		int bitIndex = (current-2)%32;

		//make sure not computed
		
		if(!(sh_mem->bitmap[blockIndex]&(1<<bitIndex))){
			if(isPerfect(current)){
				message->param = current;
				message->type = MSG_PERFECT;
				msgsnd(msgq_id, message, sizeof(message->param),0);
				sh_mem->process[localpid].num_perfect_found++;
			}
			sh_mem->bitmap[blockIndex]|=(1<<bitIndex);
			sh_mem->process[localpid].num_tested++;
		}else{
			sh_mem->process[localpid].num_ntested++;			
		}


		current++;
		//printf("%d\n ",current);
	}


}
