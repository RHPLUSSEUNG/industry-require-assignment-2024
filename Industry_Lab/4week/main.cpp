#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define MAX_STAR 1000
#define MAX_RANGE 1000
#define FUEL 10000

void test_main(int path[MAX_STAR], double fuel);

static int star[MAX_STAR][4] = {0};

int getStarPos(int id, int *x, int *y, int *z)
{
	*x = star[id][0];
	*y = star[id][1];
	*z = star[id][2];
	return star[id][3];
}
double distance(int from, int to)
{
	return sqrt((double)(star[from][0] - star[to][0])*(star[from][0] - star[to][0])+
		(star[from][1] - star[to][1])*(star[from][1] - star[to][1])+
		(star[from][2] - star[to][2])*(star[from][2] - star[to][2]));
}

static void build_data()
{
	star[0][0] = MAX_RANGE /2;
	star[0][1] = MAX_RANGE /2;
	star[0][2] = MAX_RANGE /2;
	star[0][3] = MAX_RANGE /2;

	for(int i=1; i<MAX_STAR; i++)
	{
		star[i][0] = rand() %1000;
		star[i][1] = rand() %1000;
		star[i][2] = rand() %1000;
		star[i][3] = 0;

		int o=0;
		for(; o<i; o++)
		{
			if(star[o][0] == star[i][0] && star[o][1] == star[i][1]) 
				break;
		}
		if(o != i){
			i--;
			continue;
		}
		
		if(rand() %100 == 0)
			star[i][3] = (rand() %5000) +2500;
	}
}

int main()
{
	int SCORE = 0;
	srand((unsigned int)main);

	for(int test = 0; test<10; test++){
		build_data();
		int path[MAX_STAR] = {0};
		double fuel = FUEL;

		test_main(path, fuel);

		bool found[MAX_STAR] = {true, false};

		int shipPos = 0;
		for(int i=0; i<MAX_STAR; i++)
		{
			fuel -= distance(shipPos, path[i]);
			if(fuel <0){
				SCORE -= 1000;
				break;
			}
			shipPos = path[i];

			fuel += star[path[i]][3];
			if(shipPos == 0) 
				break;
			if(found[shipPos]) continue;
			found[shipPos] = true;
			SCORE++;
		}
		if(shipPos != 0)
			SCORE -= 1000;
	}
	printf("SCORE = %d\n", SCORE);
	return 0;
}
