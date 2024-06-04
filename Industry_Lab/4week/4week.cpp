#define MAX_STAR 1000
#define MAX_DISTANCE 1733

extern int getStarPos(int id, int* x, int* y, int* z); //연료 반환
extern double distance(int from, int to); // 거리 반환

struct PlanetInfo
{
   int id;
   int x, y, z;
   double fuel;
   double distance;
   bool isStar;
   bool isVisited;
};

struct StarInfo
{
   int id;
   double fuel;
   double distance;
   bool isVisited;
};

void sortStars(StarInfo stars[], int n)
{
   for (int i = 0; i < n - 1; i++)
   {
      int minIndex = i;
      for (int j = i + 1; j < n; j++)
      {
         if (stars[j].distance < stars[minIndex].distance)
         {
            minIndex = j;
         }
      }

      StarInfo temp = stars[i];
      stars[i] = stars[minIndex];
      stars[minIndex] = temp;
   }
}

void sortPlanets(PlanetInfo planets[], int n)
{
   for (int i = 0; i < n - 1; i++)
   {
      int minIndex = i;
      for (int j = i + 1; j < n; j++)
      {
         if (planets[j].distance < planets[minIndex].distance)
         {
            minIndex = j;
         }
      }

      PlanetInfo temp = planets[i];
      planets[i] = planets[minIndex];
      planets[minIndex] = temp;
   }
}

double currnetMaxDistance(PlanetInfo planets[])
{
   int minIndex = -1, maxIndex = -1;
   int minX = 1000, minY = 1000, minZ = 1000;
   int maxX = 0, maxY = 0, maxZ = 0;   

   // 최소 좌표를 가진 행성과 최대 좌표를 가진 행성 찾기
   for (int i = 0; i < MAX_STAR; i++) 
   {
      if (planets[i].x <= minX && planets[i].y <= minY && planets[i].z <= minZ) 
      {
         minIndex = i;
         minX = planets[i].x;
         minY = planets[i].y;
         minZ = planets[i].z;
      }

      if (planets[i].x >= maxX && planets[i].y >= maxY && planets[i].z >= maxZ) 
      {
         maxIndex = i;
         maxX = planets[i].x;
         maxY = planets[i].y;
         maxZ = planets[i].z;
      }
   }   

   return distance(minIndex, maxIndex);
}

void test_main(int path[MAX_STAR], double fuel)
{
   PlanetInfo planets[MAX_STAR];
   StarInfo stars[MAX_STAR / 10];

   int shipPos = 0;
   int count = 0;
   int starCount = 0;

   double currentMaxDistance;

   //지구
   planets[0].id = 0;
   planets[0].x = 500;
   planets[0].y = 500;
   planets[0].z = 500;
   planets[0].fuel = 500;
   planets[0].isStar = true;
   planets[0].isVisited = true;

   // 행성 정보 초기화
   for (int i = 1; i < MAX_STAR; i++)
   {
      planets[i].id = 0;
      planets[i].x = 0;
      planets[i].y = 0;
      planets[i].z = 0;
      planets[i].isStar = false;
      planets[i].fuel = 0;
      planets[i].isVisited = false;
      planets[i].distance = 0;

      if (i < MAX_STAR / 10)
      {
         stars[i].id = 0;
         stars[i].fuel = 0;
         stars[i].distance = 0;
         stars[i].isVisited = false;
      }
   }

   // 연료 보유 행성 파악
   for (int i = 1; i < MAX_STAR; i++)
   {
      planets[i].fuel = getStarPos(i, &planets[i].x, &planets[i].y, &planets[i].z);
      planets[i].id = i;
      if (planets[i].fuel > 0)
      {
         planets[i].isStar = true;
         stars[starCount].id = i;
         stars[starCount].fuel = planets[i].fuel;
         stars[starCount].distance = distance(0, i);
         starCount++;
      }
      else
      {
         planets[i].fuel = 0;
      }
   }   

   currentMaxDistance = currnetMaxDistance(planets);

   // 탐사 시작
   while (true)
   {
      double nearestStarDistance = MAX_DISTANCE;
      int nearestStar = -1;
      double addFuel = 0;

      double nearestPlanetDistance = MAX_DISTANCE;
      int nearestPlanet = -1;
      int nearestPlanetIndex = -1;

      // 현재 거점에서 방문 가능한 가장 가까운 행성 찾기
      for (int i = 0; i < MAX_STAR; i++)
      {
         planets[i].distance = distance(shipPos, planets[i].id);
      }
      sortPlanets(planets, MAX_STAR);

      //행성 방문 여부
      for (int i = 0; i < MAX_STAR; i++)
      {
         if (!planets[i].isVisited && !planets[i].isStar)
         {
            nearestPlanet = planets[i].id;
            nearestPlanetIndex = i;
            nearestPlanetDistance = planets[i].distance;
            break;
         }
      }

      // 현재 거점에서 방문 가능한 가장 가까운 항성 찾기
      for (int i = 0; i < starCount; i++)
      {
         stars[i].distance = distance(shipPos, stars[i].id);
      }
      sortStars(stars, starCount);

      //가장 가까운 항성 설정
      nearestStar = stars[0].id;
      nearestStarDistance = stars[0].distance;
      addFuel = stars[0].fuel;

      //지구로의 거리
      double earthDistance = distance(shipPos, 0);      

      if (fuel < currentMaxDistance && count < 998)
      {         
         //항성 방문 처리            
         stars[0].isVisited = true;
         path[count++] = nearestStar;
         fuel -= nearestStarDistance;
         fuel += addFuel;
         shipPos = nearestStar;
      }
      else if (count > 997)
      {
         if (fuel < earthDistance)
         {            
            stars[0].isVisited = true;
            path[count++] = nearestStar;
            fuel -= nearestStarDistance;
            fuel += addFuel;
            shipPos = nearestStar;
         }         
         //지구 귀환         
         path[count++] = 0;
         fuel -= earthDistance;
         shipPos = 0;
         break;
      }
      else
      {
         //행성 방문 시         
         planets[nearestPlanetIndex].isVisited = true;
         path[count++] = nearestPlanet;
         fuel -= nearestPlanetDistance;
         shipPos = nearestPlanet;         
      }

      if (fuel < 0)
      {
         break;
      }
   }
}