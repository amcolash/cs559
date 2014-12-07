#include "BirdFly.h"
#include <glm/glm.hpp>
#include "GrTown_PCH.H"
#include "MMatrix.H"
#include <cstdlib>
#include <vector>

std::vector<std::vector<float>> positions;
int cnt = 0;
std::vector<glm::vec3> test;

//all Birds in one array
GrObject* los[40];

BirdFly::BirdFly(GrObject* bird, bool last) :
Behavior(bird)
{
	Fly(bird, last);

}
void BirdFly::Fly(GrObject* bird, bool last)
{
	
	
	float totalXTrans=0, totalYTrans=0, totalZTrans=0;
	std::vector<float> pos;
	glm::vec3 avgPos;
	if (lastV)
		printf("HELLO\n");
	float transX, transY, transZ;
	if (!lastV){

		//add Bird to array
		los[cnt] = bird;

		transX = rand() % 2500;
		transY = rand() % 100 + 50;
		transZ = rand() % 1000;
		pos.push_back(transX);
		pos.push_back(transY);
		pos.push_back(transZ);


		test.push_back(glm::vec3(transX,transY, transZ));

		

		//transMatrix(owner->transform, transX, transY, transZ);
		positions.push_back(pos);

		if (last){
				for (int j = 0; j < positions.size(); j++){
					totalXTrans += positions[j][0];
				}
				for (int j = 0; j < positions.size(); j++)
					totalYTrans += positions[j][1];
				for (int j = 0; j < positions.size(); j++)
					totalZTrans += positions[j][2];
				printf("Average position: (%f, %f, %f)\n", totalXTrans / 40, totalYTrans / 40, totalZTrans / 40);
				avgPos = glm::vec3(totalXTrans / 40, totalYTrans / 40, totalZTrans / 40);
				
				for (int i = 0; i < 40; i++)
					RotateToFace(los[i], test[i], avgPos, glm::vec3(0, 1, 0));
				lastV += 1;
		}
		cnt++;
	}
	else{
		for (int i = 0; i < 40; i++){
			los[i]->transform[3][0] += glm::normalize(glm::vec3(test[i].x - avgPos.x, test[i].y - avgPos.y, test[i].z - avgPos.z).x);
			los[i]->transform[3][1] += glm::normalize(glm::vec3(test[i].x - avgPos.x, test[i].y - avgPos.y, test[i].z - avgPos.z).y);
			los[i]->transform[3][2] += glm::normalize(glm::vec3(test[i].x - avgPos.x, test[i].y - avgPos.y, test[i].z - avgPos.z).z);
		}
	}
	
}
void BirdFly::RotateToFace(GrObject* b, glm::vec3 objPos, glm::vec3 lookAt, glm::vec3 U){
	glm::vec3 D = glm::vec3(objPos.x - lookAt.x, objPos.y - lookAt.y, objPos.z - lookAt.z);
	glm::vec3 dNorm = glm::normalize(D);
	glm::vec3 Right = glm::cross(U, D);
	Right = glm::normalize(Right);
	glm::vec3 Backwards = glm::cross(Right, U);
	Backwards = glm::normalize(Backwards);
	glm::vec3 Up = glm::cross(Backwards, Right);
	b->transform[0][0] = Right.x;
	b->transform[1][0] = Right.y;
	b->transform[2][0] = Right.z;
	b->transform[3][0] = objPos.x;
	b->transform[0][1] = Up.x;
	b->transform[1][1] = Up.y;
	b->transform[2][1] = Up.z;
	b->transform[3][1] = objPos.y;
	b->transform[0][2] = Backwards.x;
	b->transform[1][2] = Backwards.y;
	b->transform[2][2] = Backwards.z;
	b->transform[3][2] = objPos.z;
	b->transform[0][3] = 0;
	b->transform[1][3] = 0;
	b->transform[2][3] = 0;
	b->transform[3][3] = 1;
}
void BirdFly::setMatrix(){
	float x, y, z, dx, dy, dz;

}