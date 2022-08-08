#pragma once
#include"Stdafx.h"
#include "Paddle.h"

class Enemy : public Paddle
{
	friend class Tweens;
private:
	//int enemySpeed;
	//int enemyHealth;

public:
	Enemy();
	Enemy(double xPos, int helth);
	~Enemy() {};
	virtual void MoveAI(double elapsedTime, float ballYPos);
	void Render (FlickerFreeDC& dc);
	virtual void Reset();
	//int Enemy::getPlayerHelth();
	int getEnemySpeed();
	void setEnemySpeed(int speed);
	double getYpos_1();
	//double getYpos_2();
	CImage getHelthImage();
	//Enemy getTween_1();
	//Enemy getTween_2();

	void Serialize(CArchive& ar) override;

	Enemy* operator=(const Enemy enemy);
};

