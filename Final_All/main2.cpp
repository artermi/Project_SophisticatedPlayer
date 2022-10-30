#include "soph_PGG.h"
#include <sys/types.h>
#include <unistd.h>
#include <cstdlib>
using namespace std;

int main(int argc, char** argv){
	printf("%d\n",getpid());
	srand( (unsigned) (getpid()  * 1000));

	double dens = 0.98;
	double r = 3.0;
	if(argc > 2){
		r =    atof(argv[1]);
		dens = atof(argv[2]);
	}
	for (double c = 1.0; c < 1000; c += 1.0){
			int rand_sleep = rand() % 1000;

			usleep(rand_sleep*1000);

			char file_name [60];
			sprintf(file_name,"SNAP_dns_%03d_r_%04d_t_%03d.dat", 
				(int)((dens+0.00001)*100), (int)((r +0.000001)*1000), (int)(c+0.00001) );

			printf("%s\n",file_name);

		  	FILE *file;
		  	file = fopen(file_name, "r");

	   		if (file) {
		      	fclose(file);
	    	  	printf("file:'%s' exists\n",file_name);
	      		continue;
	   		}
	   		else{
	   			file = fopen(file_name, "w+");
	   		}

			printf("Now doing sophisticated PGG with r:%f, density:%f, times:%.0f\n",r,dens,c);
			soph_PGG gameOBJ(r,dens,c);
			gameOBJ.game(false);
		
	}

	return 0;
}
