#pragma once
#include "Enemy.h"
class Tweens : public Enemy
{
private:
	Enemy* tween_1;
	Enemy* tween_2;
	CImage tween1Image;
	CImage tween2Image;

public:
	Tweens(double xPos, int helth);
	~Tweens();
	void MoveAI(double elapsedTime, float ballYPos);
	void MoveTween_1(double elapsedTime, float ballYPos);
	void MoveTween_2(double elapsedTime, float ballYPos);
	void Render(FlickerFreeDC& dc);
	void Reset();
	double getYpos_1();
	double getYpos_2();
	int getPaddleH();
	//int getHelth();

	void Serialize(CArchive& ar) override;

	Tweens* operator=(const Tweens tweens);
};

