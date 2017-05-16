#include "ResizeAction.h"
#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"


ResizeAction::ResizeAction(ApplicationManager *pApp):Action(pApp)
{
}

bool ResizeAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pOut->CreateResizeMenu();
	switch (pIn->ResizeFactor())
	{
	case 0 :
		factor = 4;
		break;
	case 1:
		factor = 2;
		break;
	case 2:
		factor = 0.5;
		break;
	case 3:
		factor = 0.25;
		break;
	case 4:
		pOut->ClearToolBar();
		pOut->CreateDrawToolBar();
		return false;
	default:
		break;
	}
	pOut->ClearToolBar();
	pOut->CreateDrawToolBar();
	pOut->ClearStatusBar();
	return true;
}

void ResizeAction::Execute()
{
	bool t = ReadActionParameters();
	if (!t)
		return;
	pManager->ResizeSelected(factor);
	pManager->Saved = false;
	pManager->first_zoom = true;
}

ResizeAction::~ResizeAction()
{
}
