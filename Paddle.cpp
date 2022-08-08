#include "pch.h"
#include "Paddle.h"

Paddle::Paddle() 
{
	this->position.x = 60.0;
	this->position.y = RESOLUTION_Y / 2.0;
	this->paddleHeight = 80;
	this->paddleWdith = 20;
	initHelth(4,0);
}

Paddle::Paddle(double xPos, int helth)
{
	//need to add IStream if want diffrent photos.
	this->paddleImage->Load(_T("Paddle.png"));
	this->position.x = xPos;
	this->position.y = RESOLUTION_Y / 2 - 80;
	this->paddleHeight = 80;
	this->paddleWdith = 10;
	this->enemySpeed = 200;
	initHelth(helth, xPos);
	//this->paddleHelthBar = new Helth(&helth);
	//this->helthPosition.x = 156;
	//this->helthPosition.y = 612;
	//for (int i = 0; i < paddleHelth; i++)
	//	this->helthImage[i].Load(_T("Heart.png"));
}

void Paddle::Render(FlickerFreeDC& dc)
{
	this->paddleImage->Draw(dc.GetSafeHdc(), position.x, position.y, paddleWdith, paddleHeight);
	for (int i = 0; i < this->paddleHelth; i++)
	{
		this->helthImage->Draw(dc.GetSafeHdc(), helthPosition[i].x, helthPosition[i].y);
	}
	//paddleHelthBar->Render(dc);
	//draw helth
	//for (int i = 0; i < paddleHelth; i++)
	//{
	//	this->helthImage[i].Draw(dc.GetSafeHdc(), helthPosition.x + (i*42.0), helthPosition.y);
	//}
}

void Paddle::initHelth(int helth, int xPos)
{
	this->paddleHelth = helth;
	helthPosition = new Point2D[5];
	helthImage = new CImage[5];
	for (int i = 0; i < 5; i++)
	{
		this->helthImage[i].Load(_T("Heart.png"));
	}
	if (xPos == 760.0)//player side
	{
		this->helthPosition[0].x = 618.0;
		this->helthPosition[0].y = 612.0;
		for (int i = 1; i < 5; i++)
		{
			this->helthPosition[i].x = this->helthPosition[i - 1].x - 35.0;
			this->helthPosition[i].y = 612.0;
		}
	}
	else if(xPos == 30.0)//enemyg side
	{
		this->helthPosition[0].x = 156.0;
		this->helthPosition[0].y = 612.0;
		for (int i = 1; i < 5; i++)
		{
			this->helthPosition[i].x = this->helthPosition[i - 1].x + 35.0;
			this->helthPosition[i].y = 612.0;
		}
	}
	else
	{
		//tweens
		this->helthPosition[0].x = 156.0;
		this->helthPosition[0].y = 612.0;
		for (int i = 1; i < 5; i++)
		{
			this->helthPosition[i].x = this->helthPosition[i - 1].x + 35.0;
			this->helthPosition[i].y = 612.0;
		}
	}
}

void Paddle::Reset()
{
	this->position.x = 30.0;
	this->position.y = RESOLUTION_Y / 2;
}

void Paddle::setPoint(double yPos)
{
	this->position.y = yPos;
}

double Paddle::getYpos_1()
{
	return 0.0;
}

double Paddle::getYpos_2()
{
	return 0.0;
}

void Paddle::MoveAI(double elapsedTime, float ballYPos)
{
	// Moves the paddle up or down, using a basic AI, also making sure it doesn't go outside the screen
	if (ballYPos < this->getYpos())
	{
		// If the ball is higher, it moves up at a max speed
		if (this->getYpos() > 1.0)
		{//                                if (Ypos - ballYpos) < (enemySpeed * elapsedTime) then -> (Ypos - ballYpos) or (enemySpeed * elapsedTime) => MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
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
		if (this->getYpos() < RESOLUTION_Y - 80.0)
		{
			setYpos(getYpos() + Min_C(ballYPos - this->getYpos(), enemySpeed * elapsedTime));
			if (this->getYpos() > RESOLUTION_Y - getPaddleW() / 2.0)
			{
				this->setYpos(RESOLUTION_Y - (getPaddleW() / 2.0));
			}
		}
	}
}


Point2D Paddle::getPos()
{
	return position;
}

void Paddle::setXpos(double PosX)
{
	this->position.x = PosX;
}

void Paddle::setYpos(double PosY)
{
	this->position.y = PosY;
}

double Paddle::getXpos()
{
	return this->position.x;
}

void Paddle::setPos(Point2D pos)
{
	this->position.x = pos.x;
	this->position.y = pos.y;
}

double Paddle::getYpos()
{
	return this->position.y;
}


int Paddle::getPaddleH()
{
	return this->paddleHeight;
}

int Paddle::getPaddleW()
{
	return this->paddleWdith;
}

void Paddle::setPaddleH(int heigth)
{
	this->paddleHeight = heigth;
}

void Paddle::setPaddleW(int wdith)
{
	this->paddleWdith = wdith;
}

void Paddle::setEnemySpeed(int speed)
{
	this->enemySpeed = speed;
}

int Paddle::getHelth()
{
	return paddleHelth;
}

void Paddle::setHelth(int helth)
{
	this->paddleHelth = helth;
}

bool Paddle::IsOutsideLeft()
{
	return position.x < 40.0;
}

bool Paddle::IsOutsideRight()
{
	return position.x > RESOLUTION_X - 40.0;
}

Point2D Paddle::getHelthPos()
{
	return *helthPosition;
}

double Paddle::getHelthXpos()
{
	return this->helthPosition->x;
}

double Paddle::getHelthYpos()
{
	return this->helthPosition->y;
}

void Paddle::setHelthXpos(double xPos)
{
	this->helthPosition->x = xPos;
}

void Paddle::setHelthYpos(double yPos)
{
	this->helthPosition->y = yPos;
}

CImage Paddle::getHelthImage()
{
	return *helthImage;
}

void Paddle::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << length << paddleHeight << paddleWdith << paddleHelth << position.x << position.y << helthPosition->x << helthPosition->y;
	}
	else
	{
		ar >> length >> paddleHeight >> paddleWdith >> paddleHelth >> position.x >> position.y >>helthPosition->x >> helthPosition->y;
	}
}

Paddle* Paddle::operator=(const Paddle paddle)
{
	this->position = paddle.position;
	this->length = paddle.length;
	this->paddleHeight = paddle.paddleHeight;
	this->paddleWdith = paddle.paddleWdith;
	this->paddleHelth = paddle.paddleHelth;
	this->helthPosition = paddle.helthPosition;
	this->helthImage = paddle.helthImage;
	this->paddleImage = paddle.paddleImage;
	return this;
}
