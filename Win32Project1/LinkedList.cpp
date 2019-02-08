#include "LinkedList.h"

Linked_List::Linked_List(Unit* _first = NULL)
	{
		Value = _first;
	}
Linked_List::~Linked_List()
	{
		Deleteall();
	}
void Linked_List::firstAdd(Unit* _first)
	{
		Value = _first;
	}
	void Linked_List::AddLink(Unit* _first)
	{
		Linked_List* Add = new Linked_List(_first);
		Linked_List* temp = this;
		{
			while (temp->next != NULL)
			{
				temp = temp->next;
			}
			Add->before = temp;
			temp->next = Add;
		}
	}
	Unit* Linked_List::getValue()
	{
		return Value;
	}
	void Linked_List::Update()
	{
		Linked_List* temp = this;
		while (temp != NULL)
		{
			if (temp->getValue()->getdead())
			{
				temp->before->next = temp->next;
				temp->next->before = temp->before;
			}
			else
				temp->getValue()->UpdateAI();
			temp = temp->next;
		}
	}
	void Linked_List::Deleteall()
	{
		Linked_List* temp = this;
		if (temp->next != NULL)
			temp->next->Deleteall();
		delete temp;
	}