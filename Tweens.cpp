#include "pch.h"
#include "Tweens.h"

Tweens::Tweens(double xPos, int helth)
{
	tween_1 = new Enemy(xPos, helth);
	tween_2 = new Enemy(xPos, helth);
	this->Enemy::setHelth(helth);
	this->tween_1->setPaddleH(40);
	this->tween_2->setPaddleH(40);
	this->tween_1->setYpos(110);
	this->tween_2->setYpos(410);
	this->tween_1->setEnemySpeed(200);
	this->tween_2->setEnemySpeed(200);
	tween1Image.Load(_T("tween1.png"));
	tween2Image.Load(_T("tween2.png"));
}

Tweens::~Tweens()
{
}

void Tweens::MoveAI(double elapsedTime, float ballYPos)
{
	if (ballYPos < 280.0 && ballYPos > 0.0)
		MoveTween_1(elapsedTime, ballYPos);
	else if(ballYPos < 560.0 && ballYPos > 280.0)
		MoveTween_2(elapsedTime, ballYPos);
}

void Tweens::MoveTween_1(double elapsedTime, float ballYPos)
{
	// Moves the paddle up or down, using a basic AI, also making sure it doesn't go outside the screen
	if (ballYPos < this->tween_1->getYpos())//goes up
	{
		// If the ball is higher, it moves up at a max speed
		if (this->tween_1->getYpos() > 1.0)
		{
			//if (Ypos - ballYpos) < (enemySpeed * elapsedTime) then -> (Ypos - ballYpos) or (enemySpeed * elapsedTime) => MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
			this->tween_1->setYpos(this->tween_1->getYpos() - Min_C(this->tween_1->getYpos() - ballYPos, this->tween_1->getEnemySpeed() * elapsedTime));
			if (this->tween_1->getYpos() < tween_1->getPaddleW() / 2.0)
			{
				this->tween_1->setYpos(tween_1->getPaddleW() / 2.0);
			}
		}
	}
	else if (ballYPos > this->tween_1->getYpos() - 40.0)//goes down
	{
		// If the ball is lower, it moves down at a max speed
		if (this->tween_1->getYpos() < 280.0 - 40.0)
		{
			this->tween_1->setYpos(tween_1->getYpos() + Min_C(ballYPos - this->tween_1->getYpos(), this->tween_1->getEnemySpeed() * elapsedTime));
			if (this->tween_1->getYpos() > RESOLUTION_Y - this->tween_1->getPaddleW() / 2.0)
			{
				this->tween_1->setYpos(RESOLUTION_Y - (tween_1->getPaddleW() / 2.0));
			}
		}
	}
}

void Tweens::MoveTween_2(double elapsedTime, float ballYPos)
{
	// Moves the paddle up or down, using a basic AI, also making sure it doesn't go outside the screen
	if (ballYPos < this->tween_2->getYpos())//goes up
	{
		// If the ball is higher, it moves up at a max speed
		if (this->tween_2->getYpos() > 280.0 - 40.0)
		{
			//if (Ypos - ballYpos) < (enemySpeed * elapsedTime) then -> (Ypos - ballYpos) or (enemySpeed * elapsedTime) => MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
			this->tween_2->setYpos(this->tween_2->getYpos() - Min_C(this->tween_2->getYpos() - ballYPos, this->tween_2->getEnemySpeed() * elapsedTime));
			if (this->tween_2->getYpos() < tween_2->getPaddleW() / 2.0)
			{
				this->tween_2->setYpos(tween_2->getPaddleW() / 2.0);
			}
		}
	}
	else if (ballYPos > this->tween_2->getYpos() - 40.0)//goes down
	{
		// If the ball is lower, it moves down at a max speed
		if (this->tween_2->getYpos() < RESOLUTION_Y)
		{
			this->tween_2->setYpos(tween_2->getYpos() + Min_C(ballYPos - this->tween_2->getYpos(), this->tween_2->getEnemySpeed() * elapsedTime));
			if (this->tween_2->getYpos() > RESOLUTION_Y - this->tween_2->getPaddleW() / 2.0)
			{
				this->tween_2->setYpos(RESOLUTION_Y - (tween_2->getPaddleW() / 2.0));
			}
		}
	}
}

void Tweens::Render(FlickerFreeDC& dc)
{
	Point2D temp_1 = tween_1->getPos();
	Point2D temp_2 = tween_2->getPos();
	int debug = Enemy::getHelth();
	this->tween1Image.Draw(dc.GetSafeHdc(), temp_1.x, temp_1.y, tween_1->getPaddleW(), tween_1->getPaddleH());
	this->tween2Image.Draw(dc.GetSafeHdc(), temp_2.x, temp_2.y, tween_2->getPaddleW(), tween_2->getPaddleH());
	for (int i = 0; i < Enemy::getHelth(); i++)
	{
		this->helthImage->Draw(dc.GetSafeHdc(), helthPosition[i].x, helthPosition[i].y);
	}
	//delete temp_helth;
}

void Tweens::Reset()
{
	tween_1->setPos({ 30.0, 150 });
	tween_2->setPos({ 30.0, 450 });
}

double Tweens::getYpos_1()
{
	return this->tween_1->getYpos();
}

double Tweens::getYpos_2()
{
	return this->tween_2->getYpos();
}

int Tweens::getPaddleH()
{
	return this->tween_1->getPaddleH();
}

//int Tweens::getHelth()
//{
//	return this->tween_1->getHelth();
//}

void Tweens::Serialize(CArchive& ar)
{
	//Paddle::Serialize(ar);

	tween_1->Serialize(ar);
	tween_2->Serialize(ar);
}

Tweens* Tweens::operator=(const Tweens tweens)
{
	Paddle::operator=(tweens);
	this->tween_1 = tweens.tween_1;
	this->tween_2 = tweens.tween_2;
	this->tween1Image = tweens.tween1Image;
	this->tween2Image = tweens.tween2Image;
	return this;
}
