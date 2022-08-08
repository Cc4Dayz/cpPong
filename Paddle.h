#pragma once
#include "Stdafx.h"


class Paddle
{
	friend class Enemy;
private:
	Point2D position;
	double length;
	CImage* paddleImage = new CImage;
	//const char * imagePath[200] = { "Paddle.png" };
	int paddleHeight;
	int paddleWdith;
	int paddleHelth;
	int enemySpeed;
	
public:
	Point2D* helthPosition;
	CImage* helthImage;
	Paddle();
	Paddle(double xPos, int helth);
	~Paddle() {};
	virtual void initHelth(int helth, int xPos);
	virtual void Render(FlickerFreeDC& dc);
	virtual void Reset();
	virtual void setPoint(double yPos);
	virtual double getYpos_1();
	virtual double getYpos_2();
	virtual void MoveAI(double elapsedTime, float ballYPos);
	Point2D getPos();
	void setPos(Point2D pos);
	void setXpos(double PosX);
	void setYpos(double PosY);
	double getXpos();
	double getYpos();
	int getPaddleH();
	int getPaddleW();
	virtual void setPaddleH(int heigth);
	void setPaddleW(int wdith);
	void setEnemySpeed(int speed);
	virtual int getHelth();
	void setHelth(int helth);
	//void setHelthPosition(int x, int y);
	virtual bool IsOutsideLeft();
	virtual bool IsOutsideRight();
	Point2D getHelthPos();
	double getHelthXpos();
	double getHelthYpos();
	void setHelthXpos(double xPos);
	void setHelthYpos(double yPos);
	virtual CImage getHelthImage();

	virtual void Serialize(CArchive& ar);

	virtual Paddle* operator=(const Paddle paddle);
};

