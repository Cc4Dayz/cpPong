
// cpPongView.h : interface of the CcpPongView class
//

#pragma once
#include "Stdafx.h"
#include "Ball.h"
#include "Player.h"
#include "Paddle.h"
#include "Enemy.h"
#include "Tweens.h"
#include "Enemy_Boss.h"
#include "wall.h"

const UINT_PTR gameTimer{ 1 };

class CcpPongView : public CView
{
protected: // create from serialization only
	CcpPongView() noexcept;
	DECLARE_DYNCREATE(CcpPongView)

	// Attributes
public:
	CcpPongDoc* GetDocument() const;

	// Operations
public:

	// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

	// Implementation
public:
	virtual ~CcpPongView();
	void CustomTick();	//custom tick

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
private:
	//memebers
	std::chrono::steady_clock::time_point previousUpdateTime;

	Wall* wall[2];
	Ball* ball;
	Ball* bossBall;

	bool GameOn;
	bool GamePause;
	bool load_Flag;
	bool newEnemy;
	bool nextLevel;
	bool gameRestart;
	bool bossShoot;
	int bossCD;
	int score;
	int level;
	int highScore;
	double timeElapsed;

	///
	SYSTEMTIME t_start;	//start
	SYSTEMTIME t_end;	//end


	///


	//paddles
	Player* player;
	Enemy* enemy;
	Tweens* tweens;
	Enemy_Boss* boss;
	Paddle* paddle[4];

	CImage* BackgdoundImage;
	CImage* nextLevelImage;
	CImage allImages[10];
	CImage numbersImage[11];
	CString ImagesPath[12];
	CString numberImagesPath[11];
	CString gameSoundsPath[10];

	//CWinThread* test1{ /*PlaySound(L"sound.wav", NULL, SND_LOOP | SND_ASYNC)*/ };

public:
	void Serialize(CArchive& ar);


	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnButtonStart();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);

	void initGame();
	void initPath();
	void restartGame();
	int flipNum(int n);
	afx_msg void OnFileSave();
	afx_msg void OnFileOpen();
};

#ifndef _DEBUG  // debug version in cpPongView.cpp
inline CcpPongDoc* CcpPongView::GetDocument() const
{
	return reinterpret_cast<CcpPongDoc*>(m_pDocument);
}
#endif

