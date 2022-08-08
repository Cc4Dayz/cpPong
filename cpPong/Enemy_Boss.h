#pragma once
#include "Enemy.h"
#include"Ball.h"

class Enemy_Boss:public Enemy
{
private:
	CImage BossImage;
	//CImage* bossBallImage{ new CImage };
	//Ball* bossBall{ new Ball };
	//int bossCD;
	//bool ballCD;

public:

	Enemy_Boss();
	~Enemy_Boss() {};
	Enemy_Boss(double xPos, int helth);
	void MoveAI(double elapsedTime, float ballYPos);
	void Render(FlickerFreeDC& dc);
	void Reset();
	//void shootBossBall(double elapsedTime);

	void Serialize(CArchive& ar) override;
	Enemy_Boss* operator=(const Enemy_Boss boss);
};

