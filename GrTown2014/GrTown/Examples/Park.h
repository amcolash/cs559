#pragma once

#include "../GrObject.H"
#include "../DrawingState.H"

const int numParticles = 250;
const int divs = 48;

// Fountain
class Fountain : public GrObject {
public:
  Fountain();
};

// Simple park put onto a block
class Park : public GrObject {
public:
  Park();
};