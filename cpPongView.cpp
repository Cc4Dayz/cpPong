
// cpPongView.cpp : implementation of the CcpPongView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "cpPong.h"
#endif

#include "cpPongDoc.h"
#include "cpPongView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CcpPongView

IMPLEMENT_DYNCREATE(CcpPongView, CView)

BEGIN_MESSAGE_MAP(CcpPongView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_ERASEBKGND()
	ON_WM_TIMER()
	ON_COMMAND(ID_BUTTON_START, &CcpPongView::OnButtonStart)
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(ID_FILE_SAVE, &CcpPongView::OnFileSave)
	ON_COMMAND(ID_FILE_OPEN, &CcpPongView::OnFileOpen)
END_MESSAGE_MAP()

// CcpPongView construction/destruction

CcpPongView::CcpPongView() noexcept
{
	// TODO: add construction code here
	initGame();
	initPath();
	wall[0] = new Wall(150, 20, 100, 100);
	wall[1] = new Wall(150, 20, 100, 350);
	BackgdoundImage->Load(ImagesPath[1]);
	nextLevelImage->Load(ImagesPath[4]);

}

CcpPongView::~CcpPongView()
{

}

BOOL CcpPongView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CcpPongView drawing

void CcpPongView::OnDraw(CDC* dc)
{
	FlickerFreeDC pDC(dc);
	CcpPongDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	if (!GamePause)
	{
		BackgdoundImage->Detach();
		BackgdoundImage->Load(ImagesPath[11]);//start game
	}
	BackgdoundImage->Draw(pDC->GetSafeHdc(), 0, 0);
	if (!GameOn)
	{
		load_Flag = true;
	}
	if (paddle[0]->getHelth() <= 0 || level == 4)
	{
		GameOn = false;
		BackgdoundImage->Draw(pDC->GetSafeHdc(), 0, 0);
		if (load_Flag)
		{//CImage numbersImage[i]  CString numberImagesPath[i]	displayTime
			if (highScore < score)
				highScore = score;
			BackgdoundImage->Detach();
			BackgdoundImage->Load(ImagesPath[0]);//game over
			BackgdoundImage->Draw(pDC->GetSafeHdc(), 0, 0);

			////	DISPLAY SCORE + TIME	////h

			numbersImage[0].Draw(pDC->GetSafeHdc(), 332, 298);
			numbersImage[0].Draw(pDC->GetSafeHdc(), 332 + 20 * 1, 298);


			GetLocalTime(&t_end);	//set end
			int Minutes = (t_end.wMinute - t_start.wMinute);
			int Seconds = (t_end.wSecond - t_start.wSecond);
			int total_Time = Minutes * 60 + Seconds;

			///
			int temp_Score = score;
			//int temp_time = abs(displayTime);
			//temp_time = temp_time/100000000;
			int spacer_digits = 0;
			//int num_digits = 0;	
			temp_Score = flipNum(temp_Score);
			//temp_time = flipNum(temp_time);
			int temp_time = total_Time; //flipNum(total_Time);

			while (temp_Score)
			{
				//draw Image (temp_Score%10) at y=? x=?				
				numbersImage[temp_Score % 10].Draw(pDC->GetSafeHdc(), 352 + 20 * spacer_digits, 241);
				spacer_digits++;
				temp_Score = temp_Score / 10;
			}
			// down y position (for time)
			spacer_digits = 0;
			int minutes = temp_time / 60;
			int seconds = temp_time % 60;

			//print minutes:
			numbersImage[minutes / 10].Draw(pDC->GetSafeHdc(), 332 + 20 * 0, 298);
			numbersImage[minutes % 10].Draw(pDC->GetSafeHdc(), 332 + 20 * 1, 298);

			//print :
			numbersImage[10].Draw(pDC->GetSafeHdc(), 332 + 20 * 2, 298);

			//print seconds:
			numbersImage[seconds / 10].Draw(pDC->GetSafeHdc(), 332 + 20 * 3, 298);
			numbersImage[seconds % 10].Draw(pDC->GetSafeHdc(), 332 + 20 * 4, 298);

			/*	if(minutes == 0)
				{
				numbersImage[0].Draw(pDC->GetSafeHdc(), 332, 298);
				numbersImage[0].Draw(pDC->GetSafeHdc(), 332 + 20*1, 298);
				numbersImage[10].Draw(pDC->GetSafeHdc(), 332 + 20*2, 298);
				spacer_digits +=3;
				}
				else {
					while (minutes)
					{
						numbersImage[minutes % 10].Draw(pDC->GetSafeHdc(), 332 + 20 * spacer_digits, 298);
						spacer_digits++;
						minutes = minutes / 10;

					}
				}
				if(seconds<10)
				{
					numbersImage[0].Draw(pDC->GetSafeHdc(), 332 + 20*3, 298);
					numbersImage[seconds].Draw(pDC->GetSafeHdc(), 332 + 20*4, 298);
				}
				else {
					while (seconds)
					{
						numbersImage[seconds % 10].Draw(pDC->GetSafeHdc(), 332 + 20 * spacer_digits, 298);
						spacer_digits++;
						seconds = seconds / 10;
					}
				}*/
				////
			load_Flag = false;
			//stop timer
			previousUpdateTime = std::chrono::high_resolution_clock::now();
			SetTimer(0, 10, NULL);
		}
	}
	else
	{
		if (load_Flag && GameOn)
		{
			BackgdoundImage->Detach();
			BackgdoundImage->Load(ImagesPath[level]);//can add here dynamic background image!
			load_Flag = false;
		}
		BackgdoundImage->Draw(pDC->GetSafeHdc(), 0, 0);
	}
	if (GameOn && GamePause)
	{
		if (paddle[level]->getHelth() == 0)
		{
			paddle[0]->setHelth(paddle[0]->getHelth() + 1);
			delete paddle[level];
			paddle[level] = NULL;
			score += 15 + level * 15; // basic 30, tweens 45 ,boss 60
			load_Flag = true;
			level += 1;
		}
		if (level == 3)
		{
			if (bossCD >= 1200.0 && !bossShoot /*|| bossBall == NULL*/)//cd on shoot ball
			{
				int i;
				bossCD = 0;
				bossShoot = true;
				bossBall = new Ball;
				bossBall->setXpos(boss->getXpos() + 20);
				bossBall->setYpos(boss->getYpos() + 60);
				bossBall->setXspeed(100.0);
				bossBall->setYspeed(0.0);
				bossBall->setBallImage(ImagesPath[5]);
				for (i = 0; i < 2; i++)
				{
					if (wall[i] == NULL)
					{
						if (i == 0)
						{
							wall[0] = new Wall(150, 20, 100, 100);
							break;
						}
						if (i == 1)
						{
							wall[1] = new Wall(150, 20, 100, 350);
							break;
						}
					}
				}
				PlaySound(L"bossShoot.wav", NULL, SND_FILENAME | SND_ASYNC);
			}
			if (bossCD <= 1400.0 && bossShoot && bossBall != NULL)// how long ball get renderd
			{
				bossBall->Render(pDC);
			}
			if (bossCD >= 1400.0)// how long the ball is alive 
			{
				if (bossBall != NULL)
				{
					bossShoot = false;
					delete bossBall;
				}
			}
			for (int i = 0; i < 2; i++)
			{
				if (wall[i] != NULL)
					if (wall[i]->getWallHelth() == 0)
					{
						score += 20;
						delete wall[i];
						wall[i] = NULL;
					}
				if (wall[i] != NULL)
				{
					wall[i]->Render(pDC);
					//need to add test to wall
				}
			}
		}
		//BackgdoundImage->Draw(pDC->GetSafeHdc(), 0, 0);
		ball->Render(pDC);
		paddle[0]->Render(pDC);
		if (level != 4 && paddle[level] != NULL)
			paddle[level]->Render(pDC);
	}
	else if (GameOn)
	{
		if (load_Flag && GameOn)
		{
			BackgdoundImage->Detach();
			BackgdoundImage->Load(ImagesPath[level]);//can add here dynamic background image!
			load_Flag = false;
		}
		BackgdoundImage->Draw(pDC->GetSafeHdc(), 0, 0);
	}
}

void CcpPongView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CcpPongView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CcpPongView diagnostics

#ifdef _DEBUG
void CcpPongView::AssertValid() const
{
	CView::AssertValid();
}

void CcpPongView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CcpPongDoc* CcpPongView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CcpPongDoc)));
	return (CcpPongDoc*)m_pDocument;
}
#endif //_DEBUG


// CcpPongView message handlers



BOOL CcpPongView::OnEraseBkgnd(CDC* pDC)
{
	return FALSE;
}


void CcpPongView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	score++;

	if (level == 3)
		bossCD++;
	//if (level == 4)
	//{

	//}
	if (GameOn && GamePause)
	{
		if (nIDEvent == gameTimer)
		{
			//https://www.youtube.com/watch?v=M13otPgOePs chrono explain 
			auto currentTime = std::chrono::high_resolution_clock::now();
			timeElapsed = std::chrono::duration_cast<std::chrono::milliseconds> (currentTime - previousUpdateTime).count() / 1000.0;
			previousUpdateTime = currentTime;
			//Render
			if (paddle[0]->getHelth() == 0)//player lose 
			{
				PlaySound(L"playerLose.wav", NULL, SND_FILENAME | SND_ASYNC);
				GameOn = false;
			}
			if (paddle[3] == NULL)//player won
			{
				PlaySound(L"playerWin.wav", NULL, SND_FILENAME | SND_ASYNC);
				GameOn = false;
			}

			ball->Advance(timeElapsed);
			if (bossBall != NULL && bossShoot)
			{
				bossBall->Advance(timeElapsed);
				bossBall->CheckHitRightPaddle(paddle[0]->getYpos(), paddle[0]->getPaddleH(), paddle[0]->getPaddleW());
				for (int i = 0; i < 2; i++)
				{
					if (wall[i] != NULL)
					{
						if (bossBall->CheckHitWall(wall[i]->getYpos(), wall[i]->getXpos(), wall[i]->getH(), wall[i]->getW()))
						{
							wall[i]->setWallHealth(wall[i]->getWallHelth() - 1);
							score += 20;
						}
					}
				}
				if (bossBall != NULL && bossBall->IsOutsideRight())
				{
					PlaySound(L"playerHit.wav", NULL, SND_FILENAME | SND_ASYNC);
					score -= 30;
					paddle[0]->setHelth(paddle[0]->getHelth() - 1);
					delete bossBall;
					bossBall = NULL;
				}
				if (bossBall != NULL && bossBall->IsOutsideLeft())
				{
					PlaySound(L"enemyHit.wav", NULL, SND_FILENAME | SND_ASYNC);
					score += 30;
					paddle[level]->setHelth(paddle[level]->getHelth() - 1);
					delete bossBall;
					bossBall = NULL;
				}

			}
			if (paddle[level] != NULL && level != 4)
				paddle[level]->MoveAI(timeElapsed, ball->position.y);
			Invalidate();
			UpdateWindow();

			//game logic
			ball->CheckHitRightPaddle(paddle[0]->getYpos(), paddle[0]->getPaddleH(), paddle[0]->getPaddleW());
			if (level == 3)
			{
				for (int i = 0; i < 2; i++)
				{
					if (wall[i] != NULL && ball->CheckHitWall(wall[i]->getYpos(), wall[i]->getXpos(), wall[i]->getH(), wall[i]->getW()))
					{
						wall[i]->setWallHealth(wall[i]->getWallHelth() - 1);
						score += 5;
					}
				}
			}
			if (level == 2)
			{
				ball->CheckHitLeftPaddle(paddle[level]->getYpos_1(), paddle[level]->getPaddleH(), paddle[level]->getPaddleW(), paddle[level]->getYpos_2());
			}
			else
			{
				ball->CheckHitLeftPaddle(paddle[level]->getYpos(), paddle[level]->getPaddleH(), paddle[level]->getPaddleW());
			}

			if (ball->IsOutsideLeft())
			{
				PlaySound(L"enemyHit.wav", NULL, SND_FILENAME | SND_ASYNC);
				paddle[level]->setHelth(paddle[level]->getHelth() - 1);
				ball->Reset();
				score += 10;
			}

			if (ball->IsOutsideRight())
			{
				PlaySound(L"playerHit.wav", NULL, SND_FILENAME | SND_ASYNC);
				paddle[0]->setHelth(paddle[0]->getHelth() - 1);
				ball->Reset();
			}
		}
	}
	CView::OnTimer(nIDEvent);
}


void CcpPongView::OnButtonStart()
{
	if (!GamePause)
	{
		GamePause = true;
		previousUpdateTime = std::chrono::high_resolution_clock::now();
		SetTimer(1, 10, NULL);
	}
	else
	{
		GamePause = false;
		previousUpdateTime = std::chrono::high_resolution_clock::now();
		SetTimer(0, 10, NULL);
	}
}


void CcpPongView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{

	if (nChar == VK_UP)
	{
		if (paddle[0]->getYpos() > 9.0)
			paddle[0]->setYpos(paddle[0]->getYpos() - 10.0);
	}
	if (nChar == VK_DOWN)
	{
		if (paddle[0]->getYpos() < RESOLUTION_Y - 80.0)
			paddle[0]->setYpos(paddle[0]->getYpos() + 10.0);
	}
	if (nChar == VK_SPACE)
	{
		if (!GameOn)
		{
			previousUpdateTime = std::chrono::high_resolution_clock::now();
			SetTimer(1, 10, NULL);
			GameOn = true;
			load_Flag = true;
			restartGame();
			gameRestart = true;
			GamePause = true;
			load_Flag = true;
		}
		else
		{
			if (!GamePause)
			{
				GetLocalTime(&t_start);	//set start
				GamePause = true;
				load_Flag = true;
				previousUpdateTime = std::chrono::high_resolution_clock::now();
				SetTimer(1, 10, NULL);
			}
			else
			{
				GamePause = false;
				previousUpdateTime = std::chrono::high_resolution_clock::now();
				SetTimer(0, 10, NULL);
			}
		}
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

//cheat !
void CcpPongView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	if (point.x > 670 && point.y > 600)
		paddle[level]->setHelth(paddle[level]->getHelth() - 1);
	CView::OnLButtonDblClk(nFlags, point);
}

void CcpPongView::restartGame()
{
	GetLocalTime(&t_start);
	level = 1;
	delete ball;
	initGame();
	BackgdoundImage->Load(ImagesPath[1]);
}

void CcpPongView::initGame()
{
	int i = 0;
	GameOn = true;
	GamePause = false;
	load_Flag = false;
	newEnemy = false;
	nextLevel = false;
	bossShoot = false;
	highScore = 0;
	bossCD = 0;
	score = 0;
	level = 1;

	BackgdoundImage = new CImage;
	nextLevelImage = new CImage;

	ball = new Ball;
	player = new Player(760.0, 3);
	enemy = new Enemy(30.0, 3);
	tweens = new Tweens(30.0, 4);
	boss = new Enemy_Boss(30.0, 5);
	wall[0] = new Wall(150, 20, 100, 100);
	wall[1] = new Wall(150, 20, 100, 350);

	paddle[0] = player;
	paddle[1] = enemy;
	paddle[2] = tweens;
	paddle[3] = boss;
}

void CcpPongView::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);

	if (ar.IsLoading())
	{
		ar >> level >> score >> highScore;

	}
	else if (ar.IsStoring())
	{
		ar << level << score << highScore;
	}
}


void CcpPongView::OnFileSave()
{
	// FALSE to SAVE
	CFileDialog dlg(FALSE, _T(".pong"), NULL, 0, _T("cPong (*.pong)|*.pong|All Files (*.*)|*.*||"));
	CString filename;
	if (dlg.DoModal() == IDOK)
	{
		filename = dlg.GetPathName(); // return full path and filename
		CFile file(filename, CFile::modeCreate | CFile::modeWrite);
		CArchive ar(&file, CArchive::store);
		ar << level << score;
		ball->Serialize(ar);
		paddle[0]->Serialize(ar);
		paddle[level]->Serialize(ar);
		if (wall[0] != NULL) { wall[0]->Serialize(ar); }
		else { ar << 0; }
		if (wall[1] != NULL) { wall[1]->Serialize(ar); }
		else { ar << 0; }
		ar.Close();
		file.Close();
	}
}


void CcpPongView::OnFileOpen()
{
	// TODO: Add your control notification handler code here
			 // TRUE to LOAD
	CFileDialog dlg(TRUE, _T(".pong"), NULL, 0, _T("cPong (*.pong)|*.pong|All Files (*.*)|*.*||"));
	CString filename;
	if (dlg.DoModal() == IDOK)
	{
		filename = dlg.GetPathName(); // return full path and filename
		CFile file(filename, CFile::modeRead);
		CArchive ar(&file, CArchive::load);
		initGame();
		ar >> level >> score;
		BackgdoundImage->Load(ImagesPath[level]);
		ball->Serialize(ar);
		paddle[0]->Serialize(ar);
		paddle[level]->Serialize(ar);
		wall[0]->Serialize(ar);
		wall[1]->Serialize(ar);
		ar.Close();
		file.Close();
		Invalidate();
	}
}

int CcpPongView::flipNum(int n)
{
	int remainder, rev = 0;
	while (n != 0) {
		remainder = n % 10;
		rev = rev * 10 + remainder;
		n /= 10;
	}
	return rev;
}

void CcpPongView::initPath()
{
	ImagesPath[0] = "GameOver.png";
	ImagesPath[1] = "lvl1Background.png";
	ImagesPath[2] = "lvl2Background.png";
	ImagesPath[3] = "lvl3Background.png";
	ImagesPath[4] = "NextLevel.png";
	ImagesPath[5] = "bossBall.png";
	ImagesPath[6] = "wallBoss.png";
	ImagesPath[7] = "SizeUp.png";
	ImagesPath[8] = "SizeDown.png";
	ImagesPath[9] = "LifeUp.png";
	ImagesPath[10] = "PauseGame.png";
	ImagesPath[11] = "StartGame.png";


	gameSoundsPath[0] = "playerHit.wav";
	gameSoundsPath[1] = "enemyHit.wav";

	numberImagesPath[0] = "0.png";
	numberImagesPath[1] = "1.png";
	numberImagesPath[2] = "2.png";
	numberImagesPath[3] = "3.png";
	numberImagesPath[4] = "4.png";
	numberImagesPath[5] = "5.png";
	numberImagesPath[6] = "6.png";
	numberImagesPath[7] = "7.png";
	numberImagesPath[8] = "8.png";
	numberImagesPath[9] = "9.png";
	numberImagesPath[10] = "10.png";
	for (int i = 0; i <= 10; i++)
	{
		numbersImage[i].Load(numberImagesPath[i]);
	}
}
