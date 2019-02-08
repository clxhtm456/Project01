#include "Sound.h"
MCI_OPEN_PARMS mciOpen;
MCI_PLAY_PARMS mciPlay;
MCI_SEEK_PARMS mciSeek;
UINT wDeviceID;
DWORD sound1 = LoadWAV(0, knifesound);
DWORD sound2 = LoadWAV(0, mission1_se);
DWORD sound3 = LoadWAV(0, mission1_bgm);
DWORD sound4 = LoadWAV(0, clashsound);
DWORD sound5 = LoadWAV(0, handgunsound);
DWORD sound6 = LoadWAV(0, screamsound);
DWORD sound7 = LoadWAV(0, machinegun);
DWORD sound8 = LoadWAV(0, hitsound);
DWORD LoadWAV(HWND hWnd, LPCTSTR lpszWave) 
{
	DWORD Result;

	mciOpen.lpstrDeviceType = _T("mpegvideo");
	//WaveAudio 대신 MPEGVideo를 사용하면 mp3 형식을 재생합니다.

	mciOpen.lpstrElementName = lpszWave;

	Result = mciSendCommand(wDeviceID, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT, (DWORD)(LPVOID)&mciOpen);

	if (Result)
		return Result;

	wDeviceID = mciOpen.wDeviceID;

	mciPlay.dwCallback = (DWORD)hWnd;

	if (Result)
		return Result;

	return 0;
}
void PlaygSound(int soundnum)
{
	mciSendCommand(soundnum, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
	mciSendCommand(soundnum, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&mciPlay);
}
void PlayBGM(int soundnum)
{
	mciSendCommand(soundnum, MCI_PLAY, MCI_NOTIFY | MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)&mciPlay);
}