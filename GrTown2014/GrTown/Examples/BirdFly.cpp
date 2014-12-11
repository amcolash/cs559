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

BirdFly::BirdFly(GrObject* bird, int count, float _u) :
Behavior(bird)
{
	SetUp(bird, count);

}
void BirdFly::SetUp(GrObject* bird, int count)
{
	//make birds face up the X axis
	rotMatrix(owner->transform, 'Y', PI / 2);

	//Position all birds in V formation
	if (count % 17 < 8){
		owner->transform[3][0] = -(count % 17 + 1) * 45;
		owner->transform[3][1] = 2000;
		owner->transform[3][2] = (count % 17 + 1) * 15;
	}
	//transMatrix(owner->transform, -(cnt)* 15, 100, -(cnt)* 45);
	else{
		owner->transform[3][0] = -(count % 17 - 8) * 45;
		owner->transform[3][1] = 2000;
		owner->transform[3][2] = -(count % 17 - 8) * 15;
		//transMatrix(owner->transform, (cnt - 8) * 15, 100, -(cnt - 8) * 45);
	}
	//transMatrix(owner->transform, 1000, 0, -1000);

	// Move birds into 5 lanes across the Z-axis on different X coordinates
	if (count > 16 && count <= 33){
		owner->transform[3][1] += 150;
		owner->transform[3][0] -= 1000;
		owner->transform[3][2] += 500;
	}
	if (count > 33 && count <= 51){
		owner->transform[3][1] += 100;
		owner->transform[3][0] -= 5000;
		owner->transform[3][2] += 1000;
	}
	if (count > 51 && count <= 68){
		owner->transform[3][1] += 200;
		owner->transform[3][0] += 2000;
		owner->transform[3][2] += 1500;
	}
	if (count > 68){
		owner->transform[3][1] += 50;
		owner->transform[3][0] += 3000;
		owner->transform[3][2] -= 500;
	}

}