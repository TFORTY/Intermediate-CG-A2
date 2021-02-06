#include "Door.h"

freebird::Door::Door()
{
	isOpen = false;
}

void freebird::Door::Update()
{
}

void freebird::Door::SetOpen(bool open)
{
	isOpen = open;
}

bool freebird::Door::GetOpen()
{
	return isOpen;
}
