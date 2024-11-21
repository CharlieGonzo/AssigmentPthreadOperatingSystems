#include <pthread.h>
#include <stdio.h>
#include <unistd.h> // For sleep()

pthread_mutex_t count_mutex;
int count = 0;

void *thread2_function(){

    
    for(int i = 0;i<5;i++){
    pthread_mutex_lock(&count_mutex);
	    printf("%d\n",count);
    pthread_mutex_unlock(&count_mutex);
    sleep(1);

    }
	   
}

void *thread1_function(void *arg){
    
   //using mutex lock to only allow one process at a time.
   for(int i =0;i<5;i++){
	    pthread_mutex_lock(&count_mutex);
            count = count + 1;
	    pthread_mutex_unlock(&count_mutex);
         sleep(1);
   }
        
}



int main(int argc, char const *argv[])
{
    pthread_t thread_id1;
    pthread_t thread_id2;

    pthread_create(&thread_id1, NULL, thread1_function, NULL);
   

    pthread_create(&thread_id2, NULL, thread2_function, NULL);

     // Wait for the thread to finish
    pthread_join(thread_id1, NULL);

    pthread_join(thread_id2, NULL);

    return 0;
}



