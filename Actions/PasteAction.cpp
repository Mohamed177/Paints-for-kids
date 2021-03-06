#include "PasteAction.h"
#include "SelectAction.h"
PasteAction::PasteAction(ApplicationManager * pApp):Action(pApp)
{

}

bool PasteAction::ReadActionParameters()
{
	
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pOut->DrawIMAGE("PasteCE", ITM_PASTE * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);
	pOut->PrintMessage("Click To paste");
	pIn->GetPointClicked(P.x, P.y);
	mciSendString(TEXT("play click.wav"), NULL, 0, NULL);
	pOut->DrawIMAGE("Paste", ITM_PASTE * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);
	if (P.y > UI.ToolBarHeight && P.y > UI.ToolBarHeight && P.y < (UI.height - UI.StatusBarHeight))
	{
		return true;
	}
	return false;
}

bool PasteAction::Execute()
{
	if (ReadActionParameters())
	{
		if (pManager->paste(P))
		{
			count = pManager->Ccount;
			pManager->Saved = false;
			pManager->first_zoom = true;
			pManager->GetOutput()->ClearStatusBar();
			while (!pManager->RedoList.empty())
				pManager->RedoList.pop(); 
			return true;
		}
		pManager->GetOutput()->ClearStatusBar();
		return false;
	}
}

void PasteAction::Undo()
{
	pManager->Undo(PASTE, BLACK, count);
}

void PasteAction::Redo()
{
	pManager->paste(P);
}
