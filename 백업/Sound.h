#include <windows.h>
#include <atlstr.h>
#pragma comment(lib, "winmm.lib" )
#include "Mmsystem.h"
#include "Digitalv.h"
#pragma once

#define knifesound _T("..\\Sound\\se\\knife.mp3")
#define handgunsound _T("..\\Sound\\se\\handgun.mp3")
#define screamsound _T("..\\Sound\\se\\scream.mp3")
#define machinegun _T("..\\Sound\\se\\heavymachine.mp3")
#define clashsound _T("..\\Sound\\se\\clash.wav")
#define hitsound _T("..\\Sound\\se\\hit.mp3")
#define mission1_se _T("..\\Sound\\se\\NARRATOR 1 (1).mp3")
#define mission1_bgm _T("..\\Sound\\bgm\\mission1_bgm.mp3")  
extern MCI_OPEN_PARMS mciOpen;
extern MCI_PLAY_PARMS mciPlay;
extern MCI_SEEK_PARMS mciSeek;
extern UINT wDeviceID;
DWORD LoadWAV(HWND hWnd, LPCTSTR lpszWave);
extern DWORD sound1;
extern DWORD sound2;
extern DWORD sound3;
extern DWORD sound4;
extern DWORD sound5;
extern DWORD sound6;
extern DWORD sound7;
extern DWORD sound8;

void PlaygSound(int soundnum);
void PlayBGM(int soundnum);