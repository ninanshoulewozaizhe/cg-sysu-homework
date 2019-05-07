#pragma once
#ifndef DRAWCIRCLE_H
#define DRAWCIRCLE_H
#include <iostream>
#include <vector>

using namespace std;

class Circle
{
public:
	Circle(float x, float y, float r);
	float* getDrawPoints();
	int getPointsCount();
	void setR(float r);
	~Circle();

private:
	float x;
	float y;
	float r;
	float* Allpoints;
	int pointsCount;
};

Circle::Circle(float x, float y, float r){
	this->x = x;
	this->y = y;
	this->r = r;
	Allpoints = NULL;
	pointsCount = 0;
}
void Circle::setR(float r) {
	this->r = r;
}

int Circle::getPointsCount() {
	return pointsCount;
}


float* Circle::getDrawPoints() {
	float d = 1.25f - r;
	float tempX = 0, tempY = r;
	vector<float> pointsX;
	vector<float> pointsY;
	while (tempX < tempY) {
		// 1
		pointsX.push_back(tempX + x);
		pointsY.push_back(tempY + y);
		// 2
		pointsX.push_back(-tempX + x);
		pointsY.push_back(tempY + y);
		// 3
		pointsX.push_back(tempX + x);
		pointsY.push_back(-tempY + y);
		// 4
		pointsX.push_back(-tempX + x);
		pointsY.push_back(-tempY + y);
		// 5
		pointsX.push_back(tempY + y);
		pointsY.push_back(tempX + x);
		// 6
		pointsX.push_back(-tempY + y);
		pointsY.push_back(tempX + x);
		//7
		pointsX.push_back(tempY + y);
		pointsY.push_back(-tempX + x);
		// 8
		pointsX.push_back(-tempY + y);
		pointsY.push_back(-tempX + x);

		if (d < 0) {
			d += 2 * tempX + 3;
		}
		else {
			d += 2 * (tempX - tempY) + 5;
			tempY--;
		}
		tempX++;
	}
	pointsCount = pointsX.size();
	Allpoints = new float[pointsCount * 6];
	int pos = 0;
	for (int i = 0; i < pointsCount; ++i, pos += 6) {
		Allpoints[pos] = pointsX[i] / 800.0f;
		Allpoints[pos + 1] = pointsY[i] / 800.0f;
		// cout << line1[0][i] << ' ' << line1[1][i] << endl;
		Allpoints[pos + 2] = 0.0f;
		//color
		Allpoints[pos + 3] = 1.0f;
		Allpoints[pos + 4] = 0.0f;
		Allpoints[pos + 5] = 0.0f;
	}
	return Allpoints;
}


Circle::~Circle()
{
	if (Allpoints != NULL) {
		delete[] Allpoints;
	}
	Allpoints = NULL;
}




#endif // !DRAWCIRCLEH
