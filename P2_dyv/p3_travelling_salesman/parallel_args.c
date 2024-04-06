/**
 * @brief This code purpose is to parallelise multiples execution of the same program.
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>
#include <wait.h>

#ifdef _OPENMP
    #include <omp.h>
#else
   #define omp_get_thread_num() 1
#endif

int main(int argc, char * argv[]){
    // Check parameters
    if(argc < 2){
        printf("Error: missing parameters\n");
        printf("%s <program> <number of executions>\n",argv[0]);
        return -1;
    }

    int n = atoi(argv[2]);
    printf("Number of executions: %d\n",n);

    #pragma omp parallel for
    for(int i=0; i<n; ++i){
        //printf("Hebra %d ejecuta la iteración %d del bucle\n",omp_get_thread_num(),i);

        int pidproxy;
        if((pidproxy = fork()) < 0){
            perror("fork");
            exit(-1);
        }

        char arg[20];
        sprintf(arg,"%d",i);
        
        // Proxy se encarga de gestionar la petición 
        if(!pidproxy)
            execl(argv[1],argv[1],arg,NULL);
    }

    return 0;
}