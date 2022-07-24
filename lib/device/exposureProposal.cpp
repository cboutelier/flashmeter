#include "exposure_proposal.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;

ExposureProposal::~ExposureProposal(){
    delete this->speedDisplay;
    this->speedDisplay = nullptr;
}

void ExposureProposal::setSpeedDisplay(const char *s)
{
    this->speedDisplay = new char[strlen(s) + 1];
    sprintf(this->speedDisplay, s);
}