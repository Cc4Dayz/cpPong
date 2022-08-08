#pragma once
#include "Stdafx.h"

#define RECOIL_Y_MAX 0.4
#define RECOIL_X_MIN -0.1
#define RECOIL_X_MAX 0.1

class Ball
{
private:
	char imagePath[200] = { "Ball.png" };
	//CBrush ballBrush;
	CImage ballImage;
	CString sounds[4];
	//PlaySound(L"sound.wav", NULL, SND_LOOP | SND_ASYNC);
public:
	//members
	Point2D speed;
	Point2D position;
	//constractor 
	Ball();
	~Ball();

	//reset ball place
	void Reset();

	//move ball
	void Advance(double elapsedTime);

	//draw ball
	void Render(FlickerFreeDC& dc);

	//normal game logic
	void CheckHitLeftPaddle(double paddleY, int paddleH, int paddleW);
	void CheckHitRightPaddle(double paddleY, int paddleH, int paddleW);

	//tweens logic
	void CheckHitLeftPaddle(double paddleY_1, int paddleH, int paddleW, double paddleY_2);

	//wall logic
	bool CheckHitWall(double wallYpos, double wallXpos, int wallH, int wallW);

	//check if the ball out side of game area
	bool IsOutsideLeft();
	bool IsOutsideRight();

	// set/getter`s
	void setXpos(double xPos);
	void setYpos(double yPos);
	double getXpos();
	double getYpos();
	void setXspeed(double xSpeed);
	void setYspeed(double ySpeed);
	double getXspeed();
	double getYspeed();
	void setBallspeed(double num);
	CImage getBallImage();
	void setBallImage(CString ImagesPath);

	void Serialize(CArchive& ar);
	void playSound();
};

