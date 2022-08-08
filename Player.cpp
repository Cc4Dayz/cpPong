#include "pch.h"
#include "Player.h"

Player::Player(int helth)
{
	this->setXpos(RESOLUTION_X - 60.0);
	this->setYpos(RESOLUTION_Y/2.0 - 40.0);
	this->setHelth(helth);
	//this->score = 0;
}

Player::Player(double xPos, int helth) : Paddle(xPos, helth)
{
	//this->score = 0;
	this->setHelth(helth);
	//this->setHelthPosition(160, 650);
}

Player::~Player()
{
}

void Player::Render(FlickerFreeDC& dc)
{
	Paddle::Render(dc);
}

void Player::Reset()
{
	this->setYpos(RESOLUTION_Y / 2.0);
	this->setXpos(760.0);
	this->setHelth(3);
}

//void Player::IncreaseScore()
//{
//	score++;
//}

void Player::Serialize(CArchive& ar)
{
	Paddle::Serialize(ar);

	//if (ar.IsStoring())
	//{
	//	ar << score;
	//}
	//else
	//{
	//	ar >> score;
	//}
}

Player* Player::operator=(const Player player)
{
	Paddle::operator=(player);
	//this->score = player.score;
	return this;
}
