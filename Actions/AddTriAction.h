#pragma once
#include "Action.h"
class AddTriAction :
	public Action
{
	Point p1;
	Point p2;
	Point p3;
	GfxInfo triGfxInfo;
public:
	AddTriAction(ApplicationManager *pApp);
	//Reads trangle parameters
	virtual bool ReadActionParameters();

	//Add triangle to the ApplicationManager
	virtual void Execute();

	~AddTriAction();
};
