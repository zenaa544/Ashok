#include<pthread.h>

#define MAX 100;

pthread_mutex_t my_mutex;
pthread_cond_t  my_cond;

int current=1;

void* printOdd(void* args){
    while(currrent<=MAX){
    
        pthread_mutex_lock(&my_mutex);
        while(current%2==0){
 		
		pthread_cond_wait(&my_cond, &mutex);
                
		if(current<=MAX)
                print(current);
                current++;
                
	}
        pthread_cond_signal(&my_cond);
        pthread_mutex_unlock(&my_mutex);
 
    }
    return NULL;
}

void* printEven(void* arg){
    while(currrent<=MAX){
    
        pthread_mutex_lock(&my_mutex);
        while(current%2!=0){
 		
		pthread_cond_wait(&my_cond, &mutex);
                
		if(current<=MAX)
                print(current);
                current++;
                
	}
        pthread_cond_signal(&my_cond);
        pthread_mutex_unlock(&my_mutex);
 
    }
    return NULL;
}

main(){
	pthread_t oddThread,evenThread;

        pthread_mutex_initialize(&my_mutex,NULL);
        pthread_cond_initialize(&my_cond,NULL);

        pthread_create(&oddThread,NULL,printOdd,NULL);
        pthread_create(&evenThread,NULL,printEven,NULL);
        
        pthread_join(oddThread,NULL);
        pthread_join(evenThread,NULL);
       
        pthread_mutex_destroy(&my_mutex);
        pthread_cond_destroy(&my_cond);
}
