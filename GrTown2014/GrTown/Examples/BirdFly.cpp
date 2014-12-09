#include "BirdFly.h"
#include <glm/glm.hpp>
#include "../GrTown_PCH.H"
#include "../MMatrix.H"
#include <cstdlib>
#include <vector>

#define PI 3.1459265359

std::vector<std::vector<float>> positions;
int cnt = 0;
std::vector<glm::vec3> test;

//all Birds in one array
GrObject* los[40];

BirdFly::BirdFly(GrObject* bird, bool last, int count, float _u) :
Behavior(bird)
{
	Fly(bird, last, count);

}
void BirdFly::Fly(GrObject* bird, bool last, int count)
{
	
	float totalXTrans = 0, totalYTrans = 0, totalZTrans = 0; 
	
	//probably won't use this vector
	//std::vector<float> pos;
	glm::vec3 avgPos;

	float transX, transY, transZ;

	if (count <= 16){
		rotMatrix(owner->transform, 'Y', PI / 2);
		if (count <= 8){
			owner->transform[3][0] = -(count)* 45;
			owner->transform[3][1] = 100;
			owner->transform[3][2] = (count)* 15;
		}
			//transMatrix(owner->transform, -(cnt)* 15, 100, -(cnt)* 45);

		if (count > 8 && count <= 16){
			owner->transform[3][0] = -(count - 8) * 45;
			owner->transform[3][1] = 100;
			owner->transform[3][2] = -(count - 8) * 15;
			//transMatrix(owner->transform, (cnt - 8) * 15, 100, -(cnt - 8) * 45);

		}
		//transMatrix(owner->transform, 1000, 0, -1000);
	}


		//add Bird to array
		/*los[cnt] = bird;
		transX = rand() % 2500;
		transY = rand() % 100 + 50;
		transZ = rand() % 1000;

		//probably won't use this vector
		pos.push_back(transX);
		pos.push_back(transY);
		pos.push_back(transZ);


		test.push_back(glm::vec3(transX,transY, transZ));
		*/


		//transMatrix(owner->transform, transX, transY, transZ);
		//positions.push_back(pos);

		/*if (last){
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
				}*/
		/*else{
			for (int i = 0; i < 40; i++){
			los[i]->transform[3][0] += glm::normalize(glm::vec3(test[i].x - avgPos.x, test[i].y - avgPos.y, test[i].z - avgPos.z).x);
			los[i]->transform[3][1] += glm::normalize(glm::vec3(test[i].x - avgPos.x, test[i].y - avgPos.y, test[i].z - avgPos.z).y);
			los[i]->transform[3][2] += glm::normalize(glm::vec3(test[i].x - avgPos.x, test[i].y - avgPos.y, test[i].z - avgPos.z).z);
			}
			*/
}

void BirdFly::simulateUntil(unsigned long t){
	unsigned long leftover = 0;
	if (u >= 1) u = 0;
	leftover = advanceU(t);
	
	// if we didn't go far enough since we hit the end, we need to
	// do something
	// idea: say that our last update is not now, so next time, we'll
	// take a longer step
	if (leftover)
		lastV -= leftover;
	if (owner->transform[3][0] > 10000)
		owner->transform[3][0] = -10000;
	
	
	float speed = static_cast<float>(t - lastV)*.1;
	printf("%lu\n", t);
	//if (t - u > 100){
		//owner->transform[3][0] += 1;
		//u = t;
	//}
		//u = t;
	//unsigned long move = advanceU(t);
	//owner->transform[3][0] += move;
	//printf("XCOORD: %f\n", owner->transform[3][0]);
	
}
unsigned long BirdFly::advanceU(unsigned long time){
	/*// need to keep these things in case we need them
	float d = 0, dur = 0;
	float speed = .25f;
	// guess at the u increment
	float uig = .02f; // 2 * dist;

	if (!lastV) {		// on the first step, do something random
		u += uig;
	}
	else {
		float bx = owner->transform[3][0];
		float bz = owner->transform[3][2];
		float bdx = 1;
		float bdz = 0;
		// figure out how long the step is
		dur = static_cast<float>(time - lastV);

		// how far should we go in that amount of time
		float dist = dur * speed;


		// see where this speed would have us end up
		float fx, fz;
		fx = u + owner->transform[3][0];
		fz = owner->transform[3][2];

		// how far would we go
		d = sqrt((fx - bx)*(fx - bx) + (fz - bz)*(fz - bz));
		float du = uig * (1 / (dist + .00001f));
		//if (du > road->speedLimit) du = road->speedLimit;
		
		u += du;
		return(unsigned long)time / lastV;
	}
	
	//lastV = time;	
		float leftOverU = u - 1;
		// figure out how long that was 
		float leftOverD = leftOverU * d / uig;
		float leftOverT = leftOverD / speed;

		 //printf("Duration: %g,  LeftOver: %g  lU:%g\n", dur,leftOverT,leftOverU);
		// left over time must be less than the original duration
		//assert(leftOverT >= dur);

		u = 1;
		printf("leftoverT: %lu\n", leftOverT);
		if (lastV == 0)
			lastV = 1;
		return (unsigned long)time / lastV;
		return static_cast<unsigned long>(leftOverT);
	*/	
	return 0;
}
void BirdFly::setMatrix(){
	float x, y, z, dx, dy, dz;

}
/*
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
*/