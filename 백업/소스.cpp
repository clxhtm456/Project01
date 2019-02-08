#include <windows.h>
#include <atlstr.h>
#include <tchar.h>

#include "resource1.h"
#include <time.h>
#include "Unit.h"
#include "World.h"
#include "Player.h"
#include "missile.h"
#include "Monster.h"
#include "Sound.h"
#include "Camera.h"

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
void Player_movement(Unit* U, BOOL* Key);
void Stage_Check(int& stagenum,Unit* U,map* m, Unit* M[]);

HINSTANCE hInst;
HWND hwnd;

////////sprite





//투사체



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
	
	MSG msg;
	WNDCLASS WndClass;
	hInst = hInstance;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	WndClass.lpszClassName = _T("Class");
	RegisterClass(&WndClass);
	srand(time(NULL));

	hwnd = CreateWindow(
		_T("Class"),
		_T("window"),
		WS_VISIBLE,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		screensizeX,
		screensizeY,
		NULL,
		NULL,
		hInstance,
		NULL
	);
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	bool bDone = false;


	/*while (!bDone)
	{
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				bDone = true;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		InvalidateRect(hwnd, NULL, FALSE);
	}*/
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	static int gamestate;
	static int gamestage;
	static bool vmapdraw;
	static int test;
	HDC hdc,cdc, pdc,mdc,backMemDC;
	PAINTSTRUCT ps;
	static HBITMAP Cat, backgroundc
	,hBitmap, gameover,clear,clearmask;
	static BOOL keybuffer[256];
	static RECT rt;
	static map *m = new map(hInst);
	static Player *p1 = new Player(hInst,m,160,20);
	static Unit* b1[10];
	static Camera *Cam1 = new Camera(m);
	FILE* VMAP = NULL;
	 

	switch (iMsg)
	{
	case WM_CREATE:
		gamestate = 0;
		gamestage = 1;
		hBitmap = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_GAMESTART));
		gameover = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_GAMEOVER));
		Cat = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_OPENING));
		GetClientRect(hwnd, &rt);
		//SetTimer(hwnd, 1, 14, NULL);//60프레임
		break;
	case WM_TIMER:
		if (gamestate == 1)
		{
			
			/////유닛업데이트
			p1->UpdateAI();
			for (int i = 0; i < 10; i++)
			{
				if (b1[i])
					b1[i]->UpdateAI();
			}
			////키입력
			Player_movement(p1, keybuffer);


			if (keybuffer[VK_ESCAPE])
			{
				gamestate = 0;
				KillTimer(hwnd, 1);
			}
			///맵 갱신
			Stage_Check(gamestage, p1, m, b1);
			//카메라이동
			if (p1->getright())
				Cam1->Camtransport(p1->getxPos()+ Camera_distance, p1->getyPos());
			else
				Cam1->Camtransport(p1->getxPos()- Camera_distance, p1->getyPos());
		}
		InvalidateRgn(hwnd, NULL, FALSE);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case 'T':
			break;
		case 'C':
			p1->jump();
			break;
		case 'X':
			if (!keybuffer['X'])
				p1->spell_fireball();
			break;
		}
		keybuffer[wParam] = TRUE;
		break;
	case WM_KEYUP:
		keybuffer[wParam] = FALSE;
		break;
	case WM_MOUSEMOVE:
		if (vmapdraw)
			m->collision[int((LOWORD(lParam)+Cam1->getxPos()- mapsizeX / 2)/5)][int((HIWORD(lParam)- 820)/5)] = 1;
		break;
	case WM_LBUTTONUP:
		vmapdraw = false;
		break;
	case WM_LBUTTONDOWN:
		vmapdraw = true;
		if (gamestate == 0)
		{
			if (LOWORD(lParam) >= 800 && LOWORD(lParam) <= 1000 && HIWORD(lParam) >= 300 && HIWORD(lParam) <= 400)
			{
				gamestate = 1;
				PlaygSound(2);
				PlayBGM(3);
				SetTimer(hwnd, 1, int(1000.0/FPS), NULL);
				m->UpdateBitmap(IDB_MAP1,IDB_MAP1_COLL,IDB_MAP1_MASK,IDB_MAP4,IDB_MAP4_MASK,IDB_MAP3);
				ReadImage(m,_T("vmap"));
				b1[0] = new Monster(p1, hInst, m,700,20);
				b1[1] = new Monster(p1, hInst, m, 800, 20);
			}
			if (LOWORD(lParam) >= 800 && LOWORD(lParam) <= 1000 && HIWORD(lParam) >= 400 && HIWORD(lParam) <= 500)
			{
				DeleteObject(Cat);
				delete p1;
				KillTimer(hwnd, 1);
				if (wDeviceID)
					mciSendCommand(wDeviceID, MCI_CLOSE, 0, (DWORD)NULL);
				PostQuitMessage(0);
			}
		}
		if (gamestate == 2 || gamestate == 3)
		{
				DeleteObject(Cat);
				KillTimer(hwnd, 1);
				if (wDeviceID)
					mciSendCommand(wDeviceID, MCI_CLOSE, 0, (DWORD)NULL);
				PostQuitMessage(0);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		mdc = CreateCompatibleDC(hdc);
		cdc = CreateCompatibleDC(hdc);
		if (gamestate == 0)
		{
			SelectObject(mdc, Cat);
			BitBlt(hdc, 0, 0, 1000, 700, mdc, 0, 0, SRCCOPY);
			//게임시작
			SelectObject(mdc, hBitmap);
			BitBlt(hdc, 800, 300, 200, 100, mdc, 0, 0, SRCCOPY);
			//게임종료
			SelectObject(mdc, gameover);
			BitBlt(hdc, 800, 400, 200, 100, mdc, 0, 0, SRCCOPY);
		}
		if (gamestate == 1)
		{
			pdc = CreateCompatibleDC(hdc);
			backMemDC = CreateCompatibleDC(hdc);
			backgroundc = CreateCompatibleBitmap(hdc, rt.right, rt.bottom);
			SelectObject(backMemDC, backgroundc);

			//플레이어
			
			Cam1->UpdateCam(backMemDC, pdc,cdc);

			//더블버퍼링
			BitBlt(hdc, 0, 0, screensizeX, screensizeY, backMemDC, 0, 0, SRCCOPY);
			//오브젝트제거
			DeleteDC(backMemDC);
			DeleteDC(pdc);
			DeleteObject(backgroundc);
			DeleteDC(hdc);
			DeleteDC(cdc);
			EndPaint(hwnd, &ps);
		}
		if (gamestate == 2)
		{
			SelectObject(mdc, clearmask);
			BitBlt(hdc, 0, 0, 1000, 500, mdc, 0, 0, SRCAND);
			SelectObject(mdc, clear);
			BitBlt(hdc, 0, 0, 1000, 500, mdc, 0, 0, SRCPAINT);
		}
		if (gamestate == 3)
		{
			SelectObject(mdc, clearmask);
			BitBlt(hdc, 0, 0, 1000, 500, mdc, 0, 0, SRCAND);
			SelectObject(mdc, clear);
			BitBlt(hdc, 0, 0, 1000, 500, mdc, 0, 0, SRCPAINT);
		}
		DeleteDC(mdc);
		break;
	case WM_DESTROY:
		DeleteObject(Cat);
		KillTimer(hwnd, 1);
		if (wDeviceID)
			mciSendCommand(wDeviceID, MCI_CLOSE, 0, (DWORD)NULL);
		PostQuitMessage(0);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_TEST_TEST:
			WCHAR str[100];
				wsprintf(str, _T("x = %d 입니다. p1y = %d입니다, \n"),
					Cam1->getxPos(), p1->getyPos());
			MessageBox(hwnd, str, _T("test"), MB_OK);
			break;
		case ID_TEST_VMAP:
			switch (gamestage)
			{
			case 1:
				WriteVmap(m, _T("vmap"));
				break;
			case 2:
				WriteVmap(m, _T("vmap2"));
				break;
			}
			break;
		case ID_WEAPON:
			p1->setbullet(200);
			p1->setweapon(1);
			break;
		}
		break;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}

void Player_movement(Unit* U, BOOL* Key)
{
	if (*(Key+VK_LEFT))
	{
		U->leftmove(Player_speed);
	}

	if (*(Key + VK_RIGHT))
	{
		U->rightmove(Player_speed);
	}
	if (*(Key + VK_UP))
	{
		U->looktop();
	}else if (*(Key + VK_DOWN))
	{
		U->crouching();
	}
}

void Stage_Check(int& stagenum,Unit* U, map* m, Unit* M[])
{
	if (U->getxPos() >= 4280)
	{
		U->setxPos(20);
		stagenum++;
	}
	else if (U->getxPos() <= 10)
	{
		U->setxPos(4270);
		stagenum--;
	}
	else
		return;

	for (int i = 0; i < 10; i++)
	{
		delete M[i];
		M[i] = NULL;
	}

	switch (stagenum)
	{
	case 1:
		m->UpdateBitmap(IDB_MAP1, IDB_MAP1_COLL);
		ReadImage(m, _T("vmap"));
		M[0] = new Monster(U, hInst, m, 1000, 100);
		M[1] = new Monster(U, hInst, m, 1700, 100);
		break;
	case 2:
		m->UpdateBitmap(IDB_MAP2, IDB_MAP1_COLL);
		ReadImage(m, _T("vmap2"));
		M[0] = new Monster(U, hInst, m, 1700, 100);
		break;
	}
}