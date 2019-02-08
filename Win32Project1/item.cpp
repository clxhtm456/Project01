#include "item.h"

void item::UpdateAI()
{
	landing(weight, World);
	weight += gravity_speed;
	if (weight > gravity_max)
		weight = gravity_max;


	deactcount--;//일정시간후 투사체는 작동멈춤

	
}
void item::UpdateAnimation(HDC deshdc, HDC sourcehdc)
{
	//Boxbit = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BOX));
	//Boxmask = (HBITMAP)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BOXMASK));
	SelectObject(sourcehdc, Boxmask);
	StretchBlt(deshdc, getxPos() - 62, getyPos() - 44, 124, 89, sourcehdc, 0, 0, 124, 89, SRCAND);
	SelectObject(sourcehdc, Boxbit);
	StretchBlt(deshdc, getxPos() - 62, getyPos() - 44, 124, 89, sourcehdc, 0, 0, 124, 89, SRCPAINT);
};