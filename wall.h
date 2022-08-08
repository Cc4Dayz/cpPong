#pragma once
#include "Stdafx.h"

class Wall
{
private:
	int wallHeight;
	int wallWdith;
	int wallHealth;
	Point2D wallPosition;
	CImage wallImage;
public:
	Wall();
	Wall(int height, int wdith, double posX, double posY);
	double getXpos();
	double getYpos();
	int getW();
	int getH();
	void setWallHealth(int health);
	int getWallHelth();
	void Render(FlickerFreeDC& dc);
	void Serialize(CArchive& ar);
};

