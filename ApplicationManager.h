#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H

#include "DEFS.h"
#include "Figures\CFigure.h"
#include "GUI\input.h"
#include "GUI\output.h"
#include "Actions\Action.h"
#include <stack>
#include <vector>
using namespace std;


//Main class that manages everything in the application.
class ApplicationManager
{
	enum { MaxFigCount = 200 };	//Max no of figures

private:
	int FigCount;	//Actual number of figures
	CFigure* FigList[MaxFigCount];	//List of all figures (Array of pointers)
	int no_of_zoomed_figs;
	CFigure*CopyList[MaxFigCount];
	CFigure* ZoomList[MaxFigCount];
	CFigure* ScrambleList[MaxFigCount];
	stack<vector<CFigure*>> UndoFigList;
	stack<CFigure*>RedoFig;
	//Pointers to Input and Output classes
	Input *pIn;
	Output *pOut;

public:	
	int Ccount, Zcount,UndoCount; /// public or private(setter and getter) 
	bool Saved, first_zoom;
	stack<Action*> UndoList;
	stack<Action*> RedoList;
	ApplicationManager(); 
	~ApplicationManager();
	// -- Action-Related Functions
	//Reads the input command from the user and returns the corresponding action type
	ActionType GetUserAction() const;
	void ExecuteAction(ActionType) ; //Creates an action and executes it
	
	// -- Figures Management Functions
	void AddFigure(CFigure* pFig); //Adds a new figure to the FigList
	CFigure *GetFigure(int x, int y) const; //Search for a figure given a point inside the figure
	// -- Interface Management Functions
	Input *GetInput() const; //Return pointer to the input
	Output *GetOutput() const; //Return pointer to the output
	void UpdateInterface(ActionType act) const;	//Redraws all the drawing window	
	void SaveAll(ofstream &OutFile) const;
	void LoadAll(ifstream &OutFile) ;
	bool ResizeSelected(float factor);
	bool Delete_Figs();
	void ScrambleDelete();
	void Copy();
	void ZoomCopy();
	void ScrambleCopy();
	void Zoom(float factor);
	void Cut();
	bool move(Point v);
	void ScrambleMove();
	void switchtoplay();
	int ChngeBrdrWdth();
	color ChangeDrwColor();
	color ChangeFllColor();
	int getZ_No();
	void RandomOrder();
	void RandomPoint();
	int highlight();
	bool getScrmbleFig(Point, int z_id);
	void PickHideCopy(CFigure** ,int &);
	void printselected(int)const;
	CFigure* getzoomfig(int x, int y) const;
	// -- Get Fig Counter Management
	int GetFig_Counter();
	bool paste(Point p);
	void Undo(ActionType, color prev = BLACK, int brdr = 4);
	void Redo(ActionType, color prev = BLACK, int brdr = 4);
	Point GetFigCenter();
	bool Send( int x );
};

#endif


