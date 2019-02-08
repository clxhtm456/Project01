#include "Unit.h"
#pragma once
class Linked_List
{
public:
	Linked_List* before;
	Unit* Value;
	Linked_List* next;
	Linked_List(Unit* _first = NULL);
	~Linked_List();
	void firstAdd(Unit* _first);
	void AddLink(Unit* _first);
	Unit* getValue();
	void Update();
	void Deleteall();
};