#include <iostream>
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <cstdlib>

using namespace std;

void *run(void *passingArgs);
void *parent_run(void *passingArgs);


pthread_mutex_t dish = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t feed = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t fillDish;
pthread_cond_t filled;

int portions = 0;
int food_left = 0;
int babies = 0;
int feedings = 0;

int r(int u) {
	return (rand()%u)+1;
}

typedef struct {
	int feedings;
} Args;

int main(int argc, char** argv)
{
	if(argc < 3){
		cout << argc << endl;
		printf("Usage: birds #Portions #Babies #Feedings\n");
		exit(0);
	}
	if(argc == 3) {
		argv[3] = argv[2];
		argv[2] = argv[1];
		argv[1] = argv[0];
	}
	
	portions = atoi(argv[1]);
	food_left = portions;
	babies = atoi(argv[2]);
	feedings =  atoi(argv[3]);
	
	pthread_cond_init(&fillDish, NULL);
	pthread_cond_init(&filled, NULL);
	
	pthread_t babies_t[babies];
	pthread_t parent;

	pthread_create( &parent, NULL, parent_run, NULL);
	

	for(int i=0; i< babies; i++){
		pthread_create( &babies_t[i], NULL, run, NULL);
	}
	
	for(int i=0; i<babies; i++){
		pthread_join( babies_t[i], NULL );
	}
	
	//pthread_join( parent, NULL );

	return 0;
}

void *run(void *passingArgs)
{
	while(feedings  > 0 ) {
		pthread_mutex_lock( &dish );
		printf(" eating a portion with portions left %d\n",food_left);
		//cout << food_left << endl;
		food_left--;
		
		if (food_left == 0 ){
			pthread_cond_signal(&fillDish);
			pthread_cond_wait(&filled, &feed);
		}
		
		pthread_mutex_unlock( &dish );
		sleep(r(3));
	}
}


void *parent_run(void *passingArgs)
{
	while(feedings > 0 ){
		pthread_cond_wait(&fillDish, &feed);
		cout << "filling " << endl;
		feedings--;
		sleep(1);
		food_left = portions;
		pthread_cond_signal(&filled);
	}
	if(feedings <=0)
		exit(0);
}

















