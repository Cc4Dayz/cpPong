#include "pch.h"
#include "wall.h"


Wall::Wall()
{
	this->wallHeight = 0;
	this->wallWdith = 0;
	this->wallPosition.x = 0.0;
	this->wallPosition.y = 0.0;
	this->wallHealth = 5;
	this->wallImage.Load(_T("wallBoss.png"));
}

Wall::Wall(int height, int wdith, double posX, double posY)
{
	this->wallHeight = height;
	this->wallWdith = wdith;
	this->wallPosition.x = posX;
	this->wallPosition.y = posY;
	this->wallHealth = 3;
	this->wallImage.Load(_T("wallBoss.png"));
}

double Wall::getXpos()
{
	return this->wallPosition.x;
}

double Wall::getYpos()
{
	return this->wallPosition.y;
}

int Wall::getW()
{
	return this->wallWdith;
}

int Wall::getH()
{
	return this->wallHeight;
}

void Wall::setWallHealth(int health)
{
	this->wallHealth = health;
}

int Wall::getWallHelth()
{
	return this->wallHealth;
}

void Wall::Render(FlickerFreeDC& dc)
{
	this->wallImage.Draw(dc.GetSafeHdc(), wallPosition.x, wallPosition.y, wallWdith, wallHeight);
}



void Wall::Serialize(CArchive& ar)
{

	if (ar.IsStoring())
	{
		ar << wallHealth;
	}
	else
	{
		ar >> wallHealth;
	}

}





