
/*THIS CODE IS MY OWN WORK, IT WAS WRITTEN WITHOUT CONSULTING
A TUTOR OR CODE WRITTEN BY OTHER STUDENTS - YIYANG ZHAO*/

#define EXTERN

#include <stdio.h>
#include <stdlib.h>

//length of each segment
#define seg_length (8*256*sizeof(int))


struct _seg{
    int bits[256];
    struct _seg *next, *prev;
};
typedef struct _seg seg;

//defining methods
seg *head, *tail;
seg* whichseg(int);
seg* segalloc(int,seg*);
int whichint(int);
int whichbit(int);
int marknonprime(int);
void setBit(int);
int testBit(int);//0 if 0 and others if 1
int marknonprime(int);
int seg_size;


int main(int argc, char *argv[]){
	seg_size = sizeof(seg);
	int N ;
	int total_segs;
	// read input
	if (argc == 2){
		sscanf(argv[1],"%d",&N);
	}else{
		printf("Max = ?");
		scanf("%d",&N);
	}
	total_segs = ((N-3) / 2 / seg_length)+1;
	head = segalloc(total_segs,NULL); //allocate total_segs number of segments by recursive function segalloc() and clear
	if (N % 2){
		N = N-1;
	}
	//find prime

	//mark prime
	//printf("bbb\n");

	int i,j;
	for (i=3; i<N;i=i+2){
		if (i*i>N) break;
		if (testBit(i)) continue;
		for (j=3*i; j<=N;j=j+2*i){
			setBit(j);
		}
	}

	int prime_count = 0;
	for (i=3; i<=N;i=i+2){
		if (testBit(i)) continue;
		prime_count ++;
		//printf("Prime %d \n", i );
	}

	printf("Found %d odd primes \n", prime_count );

	int Gold;
	printf("Enter Even Numbers between [5,N] for Goldbach Tests \n");
	while ((scanf("%d", &Gold)!=-1)){

		if (Gold % 2 ){
			printf("Come on man!!! Learn some math!");
			continue;
		}
		if (Gold > N){
			printf("Nope. Too big.");
			continue;
		}

		int smaller = 3;
		int bigger = Gold - 3;


		seg* frontseg;
		seg* endseg;
		frontseg = whichseg(smaller);
		endseg = whichseg(bigger);
		int frontint = whichint(smaller);
		int endint = whichint(bigger);
		int frontbit = whichbit(smaller);
		int endbit = whichbit(bigger);


		int gold_counter = 0;
		int bestsol_smaller = 0;
		int bestsol_bigger = 0;

		while (1){

			//validate move
			//printf("testing %d %d  %d  %d  \n",smaller,bigger,frontbit,endbit);
			if (frontbit > 31){
				frontbit = 0;
				frontint ++;
				if (frontint>255){
					frontint = 0;
					frontseg = frontseg->next;
				}
			}

			if (endbit < 0){
				endbit =31;
				endint --;
				if (endint < 0){
					endint = 255;
					endseg = endseg->prev;
				}
			}
			// if both bits inspected are 0
			if (!((frontseg->bits[frontint])&(1<<frontbit)) && !((endseg->bits[endint])&(1<<endbit) ) ){
				gold_counter++;
				bestsol_smaller = smaller;
				bestsol_bigger = bigger;
			}


			// perpare for next move
			smaller += 2;
			bigger -= 2;
			frontbit ++;
			endbit --;
			if (bigger<=smaller) break;
		}

	    printf("%d Goldbach decomposition found. Largest %d =  %d + %d  \n",gold_counter,Gold,bestsol_smaller,bestsol_bigger);


	}

}


seg* segalloc(int num_seg,seg* prev_seg){  //allocate
	seg* this_seg;
	this_seg= (seg*)malloc(seg_size);
	this_seg->prev = prev_seg;
	//printf("Building block %d...\n",num_seg);
	if (num_seg > 1) {
		this_seg->next = segalloc(num_seg-1,this_seg);

	}
    int ii;
    for (ii=0; ii<256; ii++) {
    	this_seg->bits[ii]=0;
    }
	return this_seg;
}


int whichint(int j)
{
	return  ((j-2)/2%seg_length)/32;
}

int whichbit(int j)
{
    return  (j-2)/2%32;

}
seg* whichseg (int j)
{
    int seg_Num = (j-2)/2/seg_length;
    seg* this_seg = head;
    int i = 0;
    for (i =0; i<seg_Num;i++) this_seg = this_seg -> next;
    return this_seg;
}
// mark a number j if it is prime
int marknonprime(int j){
	setBit(j);
	return 1;
}
void setBit(int j){
	whichseg(j)->bits[whichint(j)]|=(1<<whichbit(j));
}
int testBit(int j){
	return whichseg(j)->bits[whichint(j)]  & (1<<whichbit(j));
}


