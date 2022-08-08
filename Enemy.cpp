#include "pch.h"
#include "Enemy.h"

Enemy::Enemy()
{

}

Enemy::Enemy(double xPos, int helth) : Paddle(xPos, helth)
{

}

void Enemy::MoveAI(double elapsedTime, float ballYPos)
{
	if(this->getYpos() <= 600 && this->getYpos() >= 0.0)
	// Moves the paddle up or down, using a basic AI, also making sure it doesn't go outside the screen
	if (ballYPos < this->getYpos())
	{
		// If the ball is higher, it moves up at a max speed
		if (this->getYpos() > 1.0)
		{//if (Ypos - ballYpos) < (enemySpeed * elapsedTime) then -> (Ypos - ballYpos) or (enemySpeed * elapsedTime) => MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
			this->setYpos(this->getYpos() - Min_C(this->getYpos() - ballYPos, enemySpeed * elapsedTime));
			if (this->getYpos() < getPaddleW() / 2)
			{
				this->setYpos(getPaddleW() / 2.0);
			}
		}
	}
	else if (ballYPos > this->getYpos() + 40)
	{
		// If the ball is lower, it moves down at a max speed
		if (this->getYpos() < (double)RESOLUTION_Y - getPaddleH())
		{
			setYpos(getYpos() + Min_C(ballYPos - this->getYpos(), enemySpeed * elapsedTime));
			if (this->getYpos() > RESOLUTION_Y - getPaddleW() / 2.0)
			{
				this->setYpos(RESOLUTION_Y - (getPaddleW() / 2.0));
			}
		}
	}
}

void Enemy::Render(FlickerFreeDC& dc)
{
	Paddle::Render(dc);
}

void Enemy::Reset()
{
	this->setYpos(RESOLUTION_Y / 2.0);
	this->setXpos(30.0);
}

//int Enemy::getPlayerHelth()
//{
//	return enemyHealth;
//}

int Enemy::getEnemySpeed()
{
	return enemySpeed;
}

void Enemy::setEnemySpeed(int speed)
{
	enemySpeed = speed;
}

double Enemy::getYpos_1()
{
	return this->getYpos_1();
}

CImage Enemy::getHelthImage()
{
	return this->Paddle::getHelthImage();
}
//
//Enemy Enemy::getTween_1()
//{
//	//return this->Tween::tween_1;
//}

void Enemy::Serialize(CArchive& ar)
{
	Paddle::Serialize(ar);

	if (ar.IsStoring())
	{
		ar << enemySpeed /*<< enemyHealth*/;
	}
	else
	{
		ar >> enemySpeed /*>> enemyHealth*/;
	}
}

Enemy* Enemy::operator=(const Enemy enemy)
{
	Paddle::operator=(enemy);
	/*this->enemyHealth = enemy.enemyHealth;*/
	return this;
}
