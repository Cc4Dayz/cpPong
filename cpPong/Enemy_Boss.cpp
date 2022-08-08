#include "pch.h"
#include "Enemy_Boss.h"

Enemy_Boss::Enemy_Boss()
{
	
}

Enemy_Boss::Enemy_Boss(double xPos, int helth) : Enemy(xPos, helth)
{
	this->setPaddleH(120);
	this->setEnemySpeed(190);
	//this->setEnemyHealth(3);
	this->BossImage.Load(_T("Boss.png"));
	//this->bossBallImage->Load(_T("bossBall.png"));
	//bossCD = 0;
	//ballCD = false;
//wall 1
	//this->wall1.setPaddleH(300);
	//this->wall1.setYpos(150);
	////this->wall1.setEnemySeed(100);
	//wall1_img.Load(_T("Paddle.png"));
}

void Enemy_Boss::MoveAI(double elapsedTime, float ballYPos)
{
	Enemy::MoveAI(elapsedTime, ballYPos);
	//// Moves the paddle up or down, using a basic AI, also making sure it doesn't go outside the screen
	//if (ballYPos < this->getYpos())
	//{
	//	// If the ball is higher, it moves up at a max speed
	//	if (this->getYpos() > 1.0)
	//	{//                                if (Ypos - ballYpos) < (enemySpeed * elapsedTime) then -> (Ypos - ballYpos) or (enemySpeed * elapsedTime) => MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
	//		this->setYpos(this->getYpos() - min(this->getYpos() - ballYPos, this->getEnemySpeed() * elapsedTime));
	//		if (this->getYpos() < getPaddleW() / 2)
	//		{
	//			this->setYpos(getPaddleW() / 2.0);
	//		}
	//	}
	//}
	//else if (ballYPos > this->getYpos() + 80)
	//{
	//	// If the ball is lower, it moves down at a max speed
	//	if (this->getYpos() < RESOLUTION_Y - 100.0)
	//	{
	//		setYpos(getYpos() + min(ballYPos - this->getYpos(), this->getEnemySpeed() * elapsedTime));
	//		if (this->getYpos() > RESOLUTION_Y - getPaddleW() / 2.0)
	//		{
	//			this->setYpos(RESOLUTION_Y - (getPaddleW() / 2.0));
	//		}
	//	}
	//}
}

void Enemy_Boss::Render(FlickerFreeDC& dc)
{
	this->BossImage.Draw(dc.GetSafeHdc(), getXpos(), getYpos(), getPaddleW(), getPaddleH());
	for (int i = 0; i < getHelth(); i++)
	{
		this->helthImage->Draw(dc.GetSafeHdc(), helthPosition[i].x, helthPosition[i].y);
	}
	//if (ballCD)
	//{
	//	this->bossBallImage->Draw(dc.GetSafeHdc(), getXpos(), getYpos(), 20, 20);
	//}
}

void Enemy_Boss::Reset()
{
	this->setPos({ 30.0, 300 });
	this->setHelth(5);
}

//void Enemy_Boss::shootBossBall(double elapsedTime)
//{
//	bossCD++;
//
//	if (bossCD >= 90.0 && ballCD)
//	{
//		ballCD = false;
//		delete bossBall;
//	}
//
//	if (bossCD >= 90.0 && !ballCD)//every 90 sec shoot boss ball
//	{
//		bossCD = 0;
//		ballCD = true;
//
//		bossBall = new Ball;
//		bossBall->setYspeed(0.0);
//		bossBall->setXspeed(150.0);
//		bossBall->setXpos(this->getXpos()+10);
//		bossBall->setYpos(this->getYpos());
//	}
//}

void Enemy_Boss::Serialize(CArchive& ar)
{
	Paddle::Serialize(ar);
}

Enemy_Boss* Enemy_Boss::operator=(const Enemy_Boss boss)
{
	Paddle::operator=(boss);
	this->BossImage = boss.BossImage;
	return this;
}
