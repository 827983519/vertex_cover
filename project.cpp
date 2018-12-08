#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include "input.h"
#include "CNF.h"
#include "time.h"
#include <iomanip>

sem_t print;
sem_t CNF;
sem_t VC_1;
sem_t VC_2;
int vertices_num = 0;
std::vector<int> edge;
std::vector<int> vertex_coverC;
std::vector<int> vertex_cover1; 
std::vector<int> vertex_cover2; 



void *Get_input(void *arg)
{
	while(1)
	{
		if(get_input(vertices_num,edge) == V_E_INFO)
		{
			sem_post(&CNF);
		}
	}
}


void *CNF_SAT_VC(void *arg)
{
	
	while(1)
	{	
		sem_wait(&CNF);
		vertex_coverC.clear();
		binary_calculate_vertex_cover(vertices_num,edge,vertex_coverC);
       	sem_post(&VC_1);
    }	
}


void *APPROX_VC_1(void *arg)
{	
	while(1)
	{
		sem_wait(&VC_1);
		vertex_cover1.clear();
		approx_vc_1(vertices_num,edge,vertex_cover1);
		sem_post(&VC_2);
	}
}

void *APPROX_VC_2(void *arg)
{
	while(1)
	{
		sem_wait(&VC_2);
		vertex_cover2.clear();
		approx_vc_2(vertices_num,edge,vertex_cover2);
		sem_post(&print);
	}
}

void *print_VC(void *arg)
{
	while(1)
	{
		sem_wait(&print);
		print_vertex_cover(vertex_coverC,vertex_cover1,vertex_cover2);
	}
}




int main()
{
	pthread_t pid[5];
	sem_init(&CNF,NULL,0);
	sem_init(&VC_1,NULL,0);
	sem_init(&VC_2,NULL,0);
	sem_init(&print,NULL,0);

	if(pthread_create(&pid[0],NULL,Get_input,NULL)!=0)
		std::cerr << "Error: cannot create pthread." << std::endl;

	if(pthread_create(&pid[1],NULL,CNF_SAT_VC,NULL)!=0)
		std::cerr << "Error: cannot create pthread." << std::endl;

	if(pthread_create(&pid[2],NULL,APPROX_VC_1,NULL)!=0)
		std::cerr << "Error: cannot create pthread." << std::endl;

	if(pthread_create(&pid[3],NULL,APPROX_VC_2,NULL)!=0)
		std::cerr << "Error: cannot create pthread." << std::endl;

	if(pthread_create(&pid[4],NULL,print_VC,NULL)!=0)
		std::cerr << "Error: cannot create pthread." << std::endl;


	pthread_join(pid[0],NULL);
	pthread_join(pid[1],NULL);
	pthread_join(pid[2],NULL);
	pthread_join(pid[3],NULL);
	pthread_join(pid[4],NULL);


	sem_destroy(&CNF);
	sem_destroy(&VC_1);
	sem_destroy(&VC_2);
	sem_destroy(&print);
	return 0;
}
