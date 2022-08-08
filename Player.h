#pragma once
#include "Paddle.h"
#include <string>
class Player : public Paddle
{
private:
	//int score;
public:
	Player(int helth);
	Player(double xPos, int helth);
	~Player();

	virtual void Render(FlickerFreeDC& dc);
	virtual void Reset();
	//void IncreaseScore();

	void Serialize(CArchive& ar) override;
	Player* operator=(const Player player);
};

