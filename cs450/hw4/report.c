// HW4 - report

//THIS CODE IS MY OWN WORK, IT WAS WRITTEN WITHOUT CONSULTING A TUTOR OR CODE WRITTEN BY OTHER STUDENTS - YIYANG ZHAO

#include "shmhw.h"

int shm_id;
st_shmem *sh_mem;

int msgq_id;

int main(int argc, char *argv[]){
	shm_id = shmget(MEMKEY, sizeof(st_shmem),0);
	if (shm_id  == -1){
		perror("Error shmget: shmget failed to allocate shared memory; check if manage is running.(./manage)");		
		exit(-1);
	} 
	
	
	sh_mem = shmat(shm_id,NULL,0);

	printf("shmemed ; add %d", sh_mem );

	//set up msg queue
	msgq_id = msgget(MSGKEY,IPC_CREAT|0666);
	st_message *message;

	//List perfectnumbers

	printf("Perfect numbers:\n");
	int i,j;
	for(i=0;i<20;i++)
	{
		if (sh_mem->perfectnum[i]!=0)
		{
			printf("%d    ",sh_mem->perfectnum[i]);
		}
	}
	printf("\n");
	//Process Summary
	printf("Process\n");
	int total_tested = 0;
	int total_ntested = 0;
	int max_tested = 0;

	for(i=0; i<20; i++){
		if(sh_mem->process[i].pid !=0){
			printf("Process pid%10d : tested: %10d skipped: %10d; found : %10d \n",sh_mem->process[i].pid,sh_mem->process[i].num_tested,sh_mem->process[i].num_ntested,sh_mem->process[i].num_perfect_found);
		}
			
	}	

	//Total Summary
	for(i=0;i<20000;i++){
		for(j=0;j<32;j++){
			if((sh_mem->bitmap[i] & (1<<j)) == 1){
				total_tested++;
				if(i*32+j>max_tested){
					max_tested = i*32+j;
				}
			}
			
		}
		
	}
	total_ntested = max_tested - total_tested;
	printf("\n");
	
	printf("Total number, perfect found: %10d tested: %10d skipped %10d \n",sh_mem->num_perfect_found, total_tested,total_ntested);




	//implement -k option
	if(argc >=2)
	{
		if (strcmp(argv[1], "-k")==0)
		{	

			kill(sh_mem->manage_pid, SIGINT);
		}
	}









}
