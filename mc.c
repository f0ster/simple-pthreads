
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>


void *run(void *passingArgs);

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int q[4];
int select_road = 0;

typedef struct {
	int id;
} Args;


int main(int argc, char** argv)
{
	if(argc != 5){
		printf("Usage: cars #N #S #W #E\n");
		exit(0);
	}
	
	Args *passingArgs =  (Args *) malloc( 4*sizeof(Args) );

	
	int i;
	
	for(i=0; i<4; i++){
		q[i] = atoi(argv[i+1]);
		(passingArgs+i)->id = i;
	}
	
	
	pthread_t road_id[4];
		
	/*      create threads and pass their args struct *             */
	for(i=0; i<4; i++){
		pthread_create( &road_id[i], NULL, run, &(passingArgs[i]));
	}


	
	for(i=0; i<4; i++){
		pthread_join( road_id[i], NULL );
	}

	return 0;
}

void *run(void *passingArgs)
{
	Args* ptr = (Args *) passingArgs;
	while(q[3] + q[2] + q[1] + q[0] > 0) {
		if( select_road == ptr->id ){
			pthread_mutex_lock( &mutex );
			
			printf("Car is crossing from roadpath %i\n", select_road);
			q[ptr->id]--;
			select_road = (select_road + 1) % 4;
			while( q[select_road] <= 0  ) {
				if( q[3] + q[2] + q[1] + q[0] == 0)
					exit(0);
				select_road = (select_road + 1) % 4;	
			}
			
			pthread_mutex_unlock( &mutex );
		}
	}
}













