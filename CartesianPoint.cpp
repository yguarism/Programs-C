#include <iostream>
#include <stdlib.h>
#include <math.h>
#include "CartesianPoint.h"

using namespace std;


void CartesianPoint::operator=(CartesianPoint const &p){
	m_x = p.m_x;
	m_y = p.m_y;
}
bool CartesianPoint::operator==(CartesianPoint const &p) const{
	if(fabs(p.m_x-m_x)<COMPARE_DELTA){
		if(fabs(p.m_y-m_y)<COMPARE_DELTA){
			return true;
		}
	}
	return false;
}
float CartesianPoint::distance(CartesianPoint const &p) const{
	float diffx = p.m_x - m_x;
	float diffy = p.m_y - m_y;
	float dist = sqrt(pow(diffx,2)+pow(diffy,2));
	return dist;
}

CartesianPoint::CartesianPoint(CartesianPoint const &p){
	m_x = p.m_x;
	m_y = p.m_y;
}

CartesianPoint::CartesianPoint(float x, float y){
	m_x = x;
	m_y = y;
}

CartesianPoint::~CartesianPoint (){
	m_x = -2;
	m_y = 0;
}

