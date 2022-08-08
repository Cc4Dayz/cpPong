#include "pch.h"
#include "Ball.h"

Ball::Ball()
{
	ballImage.Load(_T("Ball.png"));
	position.x = 40;
	position.y = RESOLUTION_Y / 2.0 - 45;

	speed.x = 300.0;
	speed.y = 200.0;

	sounds[0] = "pop0.wav";
	sounds[1] = "pop1.wav";
	sounds[2] = "enemyHit.wav";
	sounds[3] = "playerHit.wav";
	//sounds[4] = "pop4.wav";
	//sounds[5] = "sound.wav";
}

Ball::~Ball()
{
}

void Ball::Reset()
{
	//random ball starting point
	position.x = (double)(rand() % 100) + 60/* / (RAND_MAX + 1.0) * RESOLUTION_X / 3.0*/;
	position.y = (double)(rand() % 500);

	//ball speed
	speed.x = 250.0;
	speed.y = 200.0;
}

void Ball::Advance(double elapsedTime)
{
	//Logic of the ball movement
	position.x += (speed.x * elapsedTime);
	position.y += (speed.y * elapsedTime);

	//If it hits the upper or lower walls it bounces back
	if (position.y > RESOLUTION_Y - 30.0)
	{
		speed.y = -abs(speed.y);
		playSound();
	}
	if (position.y < 1)
	{
		playSound();
		speed.y = abs(speed.y);
	}
}
void Ball::Render(FlickerFreeDC& dc)
{
	ballImage.Draw(dc.GetSafeHdc(), position.x, position.y, 20, 20);
}

//need to fix ball hit
void Ball::CheckHitLeftPaddle(double paddleY, int paddleH, int paddleW)
{
	// Checks if the ball going out side the game area and if its in the right direction
	if (position.x < 42.0 && speed.x < 0.0)
	{    //      100   >    100          100   <  100+80=180
		//if (position.y >= paddleY && position.y <= paddleY + (double)paddleH)
		if ((position.y <= paddleY - 10.0 && position.y >= paddleY + paddleH + 10.0) || (position.y >= paddleY - 10.0 && position.y <= paddleY + paddleH + 10.0))
		{//need to twick
			playSound();
			// We don't simply want to reverse the x speed. In order to make the game more interesting, we change the X and Y speeds based on where on the ball hits the paddle
			float paddleHitPos = (position.y - paddleY) / (paddleH / 2.0);
			speed.x = abs(speed.x + speed.x * (1.0 - abs(paddleHitPos)) * RECOIL_X_MAX - abs(speed.x * paddleHitPos * RECOIL_X_MIN));
			speed.y = speed.y + abs(speed.y) * paddleHitPos * RECOIL_Y_MAX;
			return;
		}
	}
}

//for tweens
void Ball::CheckHitLeftPaddle(double paddleY_1, int paddleH, int paddleW, double paddleY_2)
{
	// Checks if the ball going out side the game area and if its in the right direction
	if (position.x < 42.0 && speed.x < 0.0)
	{    //      100   >    100          100   <  100+80=180
		//if (position.y >= paddleY && position.y <= paddleY + (double)paddleH)
		if ((position.y <= paddleY_1 - 10.0 && position.y >= paddleY_1 + paddleH + 10.0) || (position.y >= paddleY_1 - 10.0 && position.y <= paddleY_1 + paddleH + 10.0))
		{//need to twick
			playSound();
			// We don't simply want to reverse the x speed. In order to make the game more interesting, we change the X and Y speeds based on where on the ball hits the paddle
			float paddleHitPos = (position.y - paddleY_1) / (paddleH /*/ 2.0*/);
			speed.x = abs(speed.x + speed.x * (1.0 - abs(paddleHitPos)) * RECOIL_X_MAX - abs(speed.x * paddleHitPos * RECOIL_X_MIN));
			speed.y = speed.y + abs(speed.y) * paddleHitPos * RECOIL_Y_MAX;
			return;
		}
	}
	// Checks if the ball going out side the game area and if its in the right direction
	if (position.x < 42.0 && speed.x < 0.0)
	{    //      100   >    100          100   <  100+80=180
		//if (position.y >= paddleY && position.y <= paddleY + (double)paddleH)
		if ((position.y <= paddleY_2 - 10.0 && position.y >= paddleY_2 + paddleH + 10.0) || (position.y >= paddleY_2 - 10.0 && position.y <= paddleY_2 + paddleH + 10.0))
		{//need to twick
			playSound();
			// We don't simply want to reverse the x speed. In order to make the game more interesting, we change the X and Y speeds based on where on the ball hits the paddle
			float paddleHitPos = (position.y - paddleY_2) / (paddleH /*/ 2.0*/);
			speed.x = abs(speed.x + speed.x * (1.0 - abs(paddleHitPos)) * RECOIL_X_MAX - abs(speed.x * paddleHitPos * RECOIL_X_MIN));
			speed.y = speed.y + abs(speed.y) * paddleHitPos * RECOIL_Y_MAX;
			return;
		}
	}
}
void Ball::CheckHitRightPaddle(double paddleY, int paddleH, int paddleW)
{
	// Checks if the ball hits the right paddle. If it does, it bounces back
	//need to fix for all paddles
	if (position.x > RESOLUTION_X - 60.0 && speed.x > 0.0)
	{   //       100   >   80                                                  100 <  80+80=160
		if (position.y >= paddleY - 10.0 && position.y <= paddleY + (double)paddleH + 10.0)
		{
			playSound();
			// We don't simply want to reverse the x speed. In order to make the game more interesting, we change the X and Y speeds based on where on the paddle the ball hita
			float paddleHitPos = (position.y - paddleY) / (paddleH / 2);
			speed.x = -abs(speed.x + speed.x * (1.0 - abs(paddleHitPos)) * RECOIL_X_MAX - abs(speed.x * paddleHitPos * RECOIL_X_MIN));
			speed.y = speed.y + abs(speed.y) * paddleHitPos * RECOIL_Y_MAX;
			return;
		}
	}
}

bool Ball::CheckHitWall(double wallYpos, double wallXpos, int wallH, int wallW)
{
	//need to check if in the Y area
	if (speed.x > 0.0)
	{
		return false;
	}
	if (position.y >= wallYpos - 10.0 && position.y <= wallYpos + wallH + 10.0)
	{
		//check if the ball in wall x size + wall.x
		if (position.x <= wallXpos + wallW && position.x >= wallXpos)
		{
			////check speed of ball to know if its direction
			//if (speed.x > 0.0)
			//{	
			//	float wallHitPos = (position.y - wallYpos) / (wallH / 2.0);
			//	speed.x = -abs(speed.x + speed.x * (1.0 - abs(wallHitPos)) * RECOIL_X_MAX - abs(speed.x * wallHitPos * RECOIL_X_MIN));
			//	speed.y = speed.y + abs(speed.y) * wallHitPos * RECOIL_Y_MAX;
			//	return;
			//}
			//else // speed.x < 0.0
			if (speed.x < 0.0)
			{
				playSound();
				float wallHitPos = (position.y - wallYpos) / (wallH / 2.0);
				speed.x = abs(speed.x + speed.x * (1.0 - abs(wallHitPos)) * RECOIL_X_MAX - abs(speed.x * wallHitPos * RECOIL_X_MIN));
				speed.y = speed.y + abs(speed.y) * wallHitPos * RECOIL_Y_MAX;
				return true;
			}
		}
	}
	return false;
}

bool Ball::IsOutsideLeft()
{
	// Returns true if the ball is outside the play area on the left side
	//PlaySound(L"enemyHit.wav", NULL, SND_FILENAME | SND_ASYNC);
	return this->position.x < 20.0;
}

bool Ball::IsOutsideRight()
{
	// Returns true if the ball is outside the play area on the right side
	//PlaySound(L"playerHit.wav", NULL, SND_FILENAME | SND_ASYNC);
	return this->position.x > RESOLUTION_X - 20.0;
}

void Ball::setBallspeed(double num)
{
	this->speed.x += num;
	this->speed.y += num;
}

CImage Ball::getBallImage()
{
	return this->ballImage;
}

void Ball::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << speed.x << speed.y << position.x << position.y;
	}
	else
	{
		ar >> speed.x >> speed.y >> position.x >> position.y;
	}
}

double Ball::getXpos()
{
	return position.x;
}

void Ball::setXpos(double xPos)
{
	this->position.x = xPos;
}
double Ball::getXspeed()
{
	return this->speed.x;
}
double Ball::getYspeed()
{
	return this->speed.y;
}
void Ball::setBallImage(CString ImagesPath)
{
	this->ballImage.Detach();
	this->ballImage.Load(ImagesPath);
}
void Ball::playSound()
{
	switch (rand() % 2) {
	case 0:PlaySound(sounds[0], NULL, SND_FILENAME | SND_ASYNC);
		break;
	case 1:PlaySound(sounds[1], NULL, SND_FILENAME | SND_ASYNC);
		break;
		//case 2:PlaySound(sounds[2], NULL, SND_FILENAME | SND_ASYNC);
		//	break;
		//case 3:PlaySound(sounds[3], NULL, SND_FILENAME | SND_ASYNC);
		//	break;
		//case 4:PlaySound(sounds[4], NULL, SND_FILENAME | SND_ASYNC);
		//	break;
	}
	//PlaySound(sounds[5], NULL, SND_LOOP | SND_ASYNC);
}
void Ball::setYpos(double yPos)
{
	this->position.y = yPos;
}

double Ball::getYpos()
{
	return position.y;
}

void Ball::setXspeed(double xSpeed)
{
	this->speed.x = xSpeed;
}

void Ball::setYspeed(double ySpeed)
{
	this->speed.y = ySpeed;
}



