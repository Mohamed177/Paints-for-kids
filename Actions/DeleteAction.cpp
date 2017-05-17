#include "DeleteAction.h"
#include "SelectAction.h"

DeleteAction::DeleteAction(ApplicationManager * p):Action(p)
{

}

bool DeleteAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	pOut->PrintMessage("Figures have been deleted");
	return 1;
}

void DeleteAction::Execute()
{
	pManager->Delete_Figs();
	Output* pOut = pManager->GetOutput();
	if (UI.InterfaceMode == MODE_ZOOM && SelectAction::getZoomSlctCount() > 0)
		pOut->CreateZoomToolBar();
	else if (UI.InterfaceMode == MODE_ZOOM)
		pOut->CreateSelcted_ZoomToolBar();
	else
		pOut->CreateDrawToolBar();
	pManager->Saved = false;
	if (UI.InterfaceMode == MODE_DRAW)
		pManager->first_zoom = true;

	
	pManager->Saved = false;

	if (1)
	{
		Output* pOut = pManager->GetOutput();
		pOut->Clickeffect("Delete", 976, 0, 61, 50);
	}
}

DeleteAction::~DeleteAction()
{
	
}
