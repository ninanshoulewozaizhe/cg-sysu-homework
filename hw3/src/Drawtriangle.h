#pragma once
#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <iostream>
#include <vector>

using namespace std;

class Triangle
{
public:
	Triangle(float x1, float y1, float x2, float y2, float x3, float y3);
	vector<vector<float>> DrawLine(float x1, float y1, float x2, float y2);
	vector<vector<float>> fillTriangle();
	vector<float> getLine(float x1, float y1, float x2, float y2);
	float findMaxInThree(float n1, float n2, float n3);
	float findMinInThree(float n1, float n2, float n3);
	float* getDrawPoints(bool fill);
	int getPointsCount();
	~Triangle();

private:
	float x1;
	float x2;
	float x3;
	float y1;
	float y2;
	float y3;
	float* Allpoints;
	int pointsCount;
};

Triangle::Triangle(float x1, float y1, float x2, float y2, float x3, float y3) {
	this->x1 = x1;
	this->x2 = x2;
	this->x3 = x3;
	this->y1 = y1;
	this->y2 = y2;
	this->y3 = y3;
	Allpoints = NULL;
	pointsCount = 0;
}

float* Triangle::getDrawPoints(bool fill) {
	vector<vector<float>> line1 = DrawLine(x1, y1, x2, y2);
	vector<vector<float>> line2 = DrawLine(x1, y1, x3, y3);
	vector<vector<float>> line3 = DrawLine(x2, y2, x3, y3);
	vector<vector<float>> fillPoints;
	if (fill) {
		fillPoints = fillTriangle();
		pointsCount = line1[0].size() + line2[0].size() + line3[0].size() + fillPoints[0].size();
	}
	else {
		pointsCount = line1[0].size() + line2[0].size() + line3[0].size();

	}
	Allpoints = new float[pointsCount * 6];
	int pos = 0;
	for (int i = 0; i < line1[0].size(); ++i, pos += 6) {
		//position
		Allpoints[pos] = line1[0][i] / 800.0f;
		Allpoints[pos + 1] = line1[1][i] / 800.0f;
		Allpoints[pos + 2] = 0.0f;
		//color
		Allpoints[pos + 3] = 1.0f;
		Allpoints[pos + 4] = 0.0f;
		Allpoints[pos + 5] = 0.0f;
	}
	for (int i = 0; i < line2[0].size(); ++i, pos += 6) {
		//position
		Allpoints[pos] = line2[0][i] / 800.0f;
		Allpoints[pos + 1] = line2[1][i] / 800.0f;
		Allpoints[pos + 2] = 0.0f;
		//color
		Allpoints[pos + 3] = 1.0f;
		Allpoints[pos + 4] = 0.0f;
		Allpoints[pos + 5] = 0.0f;
	}
	for (int i = 0; i < line3[0].size(); ++i, pos += 6) {
		//position
		Allpoints[pos] = line3[0][i] / 800.0f;
		Allpoints[pos + 1] = line3[1][i] / 800.0f;
		Allpoints[pos + 2] = 0.0f;
		//color
		Allpoints[pos + 3] = 1.0f;
		Allpoints[pos + 4] = 0.0f;
		Allpoints[pos + 5] = 0.0f;
	}
	if (fill) {
		for (int i = 0; i < fillPoints[0].size(); ++i, pos += 6) {
			//position
			Allpoints[pos] = fillPoints[0][i] / 800.0f;
			Allpoints[pos + 1] = fillPoints[1][i] / 800.0f;
			Allpoints[pos + 2] = 0.0f;
			//color
			Allpoints[pos + 3] = 1.0f;
			Allpoints[pos + 4] = 1.0f;
			Allpoints[pos + 5] = 0.0f;
		}
	}
	
	return Allpoints;
}

int Triangle::getPointsCount() {
	return pointsCount;
}

vector<vector<float>> Triangle::DrawLine(float x1, float y1, float x2, float y2) {
	vector<vector<float>> points;
	vector<float> pointsX;
	vector<float> pointsY;
	float deltaY = abs(y1 - y2);
	float deltaX = abs(x1 - x2);
	float incX = x1 > x2 ? -1.0f : 1.0f;
	float incY = y1 > y2 ? -1.0f : 1.0f;
	float tempX = x1, tempY = y1;
	pointsX.push_back(tempX);
	pointsY.push_back(tempY);
	if (deltaX > deltaY) {
		float Pi = 2 * deltaY - deltaX;
		for (float i = 0.0f; i < deltaX; i += 1.0f) {
			if (Pi <= 0.0f) {
				Pi += 2 * deltaY;
			}
			else {
				tempY += incY;
				Pi += 2 * deltaY - 2 * deltaX;
			}
			tempX += incX;
			pointsX.push_back(tempX);
			pointsY.push_back(tempY);
		}
	}
	else {
		float Pi = 2 * deltaX - deltaY;
		for (float i = 0.0f; i < deltaY; i += 1.0f) {
			if (Pi <= 0.0f) {
				Pi += 2 * deltaX;
			}
			else {
				tempX += incX;
				Pi += 2 * deltaX - 2 * deltaY;
			}
			tempY += incY;
			pointsX.push_back(tempX);
			pointsY.push_back(tempY);
		}
	}
	points.push_back(pointsX);
	points.push_back(pointsY);
	return points;
}

vector<float> Triangle::getLine(float x1, float y1, float x2, float y2) {
	vector<float> line;
	if (x1 == x2) {
		line.push_back(1);
		line.push_back(0);
		line.push_back(-x1);
	}
	else if (y1 == y2) {
		line.push_back(0);
		line.push_back(1);
		line.push_back(-y1);
	}
	else {
		line.push_back(y2 - y1);
		line.push_back(x1 - x2);
		line.push_back(x2 * y1 - x1 * y2);
	}
	return line;
} 

float Triangle::findMaxInThree(float n1, float n2, float n3) {
	float temp = n1 > n2 ? n1 : n2;
	return n3 > temp ? n3 : temp;
}

float Triangle::findMinInThree(float n1, float n2, float n3) {
	float temp = n1 < n2 ? n1 : n2;
	return n3 < temp ? n3 : temp;
}

vector<vector<float>> Triangle::fillTriangle() {
	vector<vector<float>> fillPoints;
	vector<float> pointsX;
	vector<float> pointsY;
	vector<vector<float>> lines;
	lines.push_back(getLine(x1, y1, x2, y2));
	lines.push_back(getLine(x1, y1, x3, y3));
	lines.push_back(getLine(x2, y2, x3, y3));

	for (int i = 0; i < 3; i++) {
		float x, y;
		if (i == 0) {
			x = x3;
			y = y3;
		}
		else if (i == 1) {
			x = x2;
			y = y2;
		}
		else {
			x = x1;
			y = y1;
		}
		if (lines[i][0] * x + lines[i][1] * y + lines[i][2] < 0) {
			for (int j = 0; j < 3; j++) {
				lines[i][j] *= -1;
			}
		}
	}
	float maxX = findMaxInThree(x1, x2, x3);
	float maxY = findMaxInThree(y1, y2, y3);
	float minX = findMinInThree(x1, x2, x3);
	float minY = findMinInThree(y1, y2, y3);
	
	for (float x = minX; x <= maxX; x += 1.0f) {
		for (float y = minY; y <= maxY; y += 1.0f) {
			bool inside = true;
			for (int i = 0; i < lines.size(); ++i) {
				if (lines[i][0] * x + lines[i][1] * y + lines[i][2] < 0) {
					inside = false;
				}
			}
			if (inside) {
				pointsX.push_back(x);
				pointsY.push_back(y);
			}
		}
	}
	fillPoints.push_back(pointsX);
	fillPoints.push_back(pointsY);
	return fillPoints;
}

Triangle::~Triangle()
{
	if (Allpoints != NULL) {
		delete [] Allpoints;
	}
	Allpoints = NULL;
}

#endif
