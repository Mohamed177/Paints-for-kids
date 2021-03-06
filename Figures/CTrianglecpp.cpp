#include "CTriangle.h"



CTriangle::CTriangle(Point P1 , Point P2 , Point P3 , GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
	p1 = P1;
	p2 = P2;
	p3 = P3;
}
void CTriangle::Draw(Output* pOut) const
{
	//Call Output::DraTRI to draw a rectangle on the screen	
	pOut->DrawTRI(p1 , p2 , p3 , FigGfxInfo, Selected);
}
bool CTriangle::Is_Selected(Point v) const 
{
	Point p1v = pPoint(p1, v);
	Point p2v = pPoint(p2, v);
	Point p3v = pPoint(p3, v);
	Point p1p2 = pPoint(p1, p2);
	Point p2p3 = pPoint(p2, p3);
	Point p3p1 = pPoint(p3, p1);
	int A = CrossProuct(p1v, p1p2);
	int B = CrossProuct(p2v, p2p3);
	int C = CrossProuct(p3v, p3p1);
	if ((A>=0 & B>=0 &C>=0 ) || (A <= 0 & B <= 0 &  C<= 0))
	{
		return true;
	}
	return false;
	
}

bool CTriangle::IsValid(Point P1, Point  P2, Point P3) 
{
	if (P1.y > UI.ToolBarHeight && P2.y > UI.ToolBarHeight && P3.y > UI.ToolBarHeight&& P1.y < (UI.height - UI.StatusBarHeight) && P2.y < (UI.height - UI.StatusBarHeight) && P1.y < (UI.height - UI.StatusBarHeight) && (p1.x>=0 && p1.x <=UI.width ) && (p2.x >= 0 && p2.x <= UI.width) && (p3.x >= 0 && p3.x <= UI.width))
	{
		return true;
	}
	return false;
}

CTriangle::~CTriangle()
{
}

void CTriangle::Zoom(float factor)
{
	Point wcenter, p, Center;
	Center = GetCenter();
	wcenter.x = UI.width / 2;
	wcenter.y = UI.height / 2;
	if (factor > 1)
	{
		p.x = Center.x - wcenter.x;
		p.y = Center.y - wcenter.y;
	}
	else
	{
		p.x = wcenter.x - Center.x;
		p.y = wcenter.y - Center.y;
		p.x *= 1.0 - factor;
		p.y *= 1.0 - factor;
	}
	ChngBrdWdt(ceil(FigGfxInfo.BorderWdth*factor));
	Resize(factor, true);
	Move(p);
}

void CTriangle::Save(ofstream &OutFile)
{
	OutFile << "TRIANG " << ID << ' ' << p1.x << ' ' << p1.y << ' ' << p2.x << ' ' << p2.y << ' ' << p3.x << ' ' << p3.y << ' ' << FigGfxInfo.BorderWdth << ' ';
	OutFile << (string)FigGfxInfo.DrawClr;
	if (FigGfxInfo.isFilled)
		OutFile << ' ' << (string)FigGfxInfo.FillClr << endl;
	else
		OutFile << " NO_FILL\n";
}

void CTriangle::PrintInfo(Output* pOut) 
{
	string info = "Triangle of ID : " + to_string(ID) + " Point 1 : ( " + to_string(p1.x) + " , " + to_string(p1.y);
	info += " ) Point 2 : ( " + to_string(p2.x) + " , " + to_string(p2.y);
	info += " ) Point 3 : ( " + to_string(p3.x) + " , " + to_string(p3.y) +" )  ";
	string Color = FigGfxInfo.DrawClr;
	if (!FigGfxInfo.isFilled)
		Color += " ,  No Fill.";
	else 
	{
		string color2 = FigGfxInfo.FillClr;
		Color += " , Fill color : "+ color2;
	}
	info += Color;
	pOut->PrintMessage(info);
}

bool CTriangle::Resize(float factor, bool zoom = false)
{
	Point mid;
	mid.x = (p1.x + p2.x + p3.x) / 3;
	mid.y = (p1.y + p2.y + p3.y) / 3;
	Point v1, v2, v3;
	v1 = p1;
	v2 = p2;
	v3 = p3;
	bool  t = true;
	if (factor>1)
	{
		for (int i = 0; i < factor/2; i++)
		{
			v1.x = v1.x * 2 - mid.x;
			v1.y = v1.y * 2 - mid.y;
			v2.x = v2.x * 2 - mid.x;
			v2.y = v2.y * 2 - mid.y;
			v3.x = v3.x * 2 - mid.x;
			v3.y = v3.y * 2 - mid.y;
		}
		if (!zoom)
		{
			if ((v1.y > UI.ToolBarHeight && v2.y > UI.ToolBarHeight && v3.y > UI.ToolBarHeight&& v1.y < (UI.height - UI.StatusBarHeight) && v2.y < (UI.height - UI.StatusBarHeight) && v3.y < (UI.height - UI.StatusBarHeight) && v1.x <= UI.width &&v2.x <= UI.width &&v3.x <= UI.width&& v1.x>=0 &&v2.x >=0 &&v3.x >=0))
			{
				p1 = v1;
				p2 = v2;
				p3 = v3;
				return true;
			}
			return false;
		}
		else 
		{
			p1 = v1;
			p2 = v2;
			p3 = v3;
		}
	}
	else 
	{
		int x = factor * 4;
		if (x == 1)
			x = 2;
		else
			x = 1;
		for (int  i = 0; i < x ; i++)
		{
			p1.x = (p1.x + mid.x) / 2;
			p1.y = (p1.y + mid.y) / 2;
			p2.x = (p2.x + mid.x) / 2;
			p2.y = (p2.y + mid.y) / 2;
			p3.x = (p3.x + mid.x) / 2;
			p3.y = (p3.y + mid.y) / 2;
		}
		return true;
	}
}

void CTriangle::Load(ifstream &Infile) 
{
	string drwColor, Fcolor;
	Infile >> ID >> p1.x >> p1.y >> p2.x >> p2.y >> p3.x >> p3.y >> FigGfxInfo.BorderWdth >> drwColor >> Fcolor;
	FigGfxInfo.DrawClr = drwColor;
	if (Fcolor == "NO_FILL")
		FigGfxInfo.isFilled = false;
	else
	{
		FigGfxInfo.isFilled = true;
		FigGfxInfo.FillClr = Fcolor;
	}
}
Point CTriangle::GetCenter() 
{
	Point mid;
	mid.x = (p1.x + p2.x + p3.x) / 3;
	mid.y = (p1.y + p2.y + p3.y) / 3;
	return mid;
}
bool CTriangle:: ValidMove(Point p, bool scramble = 0) 
{
	Point v1, v2, v3;
	v1.x = p1.x + p.x;
	v1.y = p1.y + p.y;
	v2.x = p2.x + p.x;
	v2.y = p2.y + p.y;
	v3.x = p3.x + p.x;
	v3.y = p3.y + p.y;
	int left_border = 0;
	if (scramble)
		left_border = UI.width / 2;
	if ((v1.y > UI.ToolBarHeight && v2.y > UI.ToolBarHeight && v3.y > UI.ToolBarHeight&& v1.y < (UI.height - UI.StatusBarHeight) && v2.y < (UI.height - UI.StatusBarHeight) && v3.y < (UI.height - UI.StatusBarHeight) && v1.x <= UI.width &&v2.x <= UI.width &&v3.x <= UI.width &&v1.x >=left_border &&v2.x >=left_border &&v3.x >=left_border))
	{
		return true;
	}
	return false;
}
CFigure * CTriangle ::copy() 
{
	CTriangle *T = new CTriangle(p1, p2, p3, FigGfxInfo);
	CFigure * v = T;
	return v;
}
void  CTriangle::Move(Point v ) 
{
	p1.x += v.x;
	p1.y += v.y;
	p2.x += v.x;
	p2.y += v.y;
	p3.x += v.x;
	p3.y += v.y;
}

char CTriangle::GetType()
{
	return 'T';
}

double CTriangle::GetArea()
{
	double T1 = (abs(p1.x - p2.x) * abs(p1.y - p2.y)) / 2;
	double T2 = (abs(p2.x - p3.x) * abs(p2.y - p3.y)) / 2;
	double T3 = (abs(p3.x - p1.x) * abs(p3.y - p1.y)) / 2;
	double R = (max(max(p1.x, p2.x), p3.x) - min(min(p1.x, p2.x), p3.x)) * (max(max(p1.y, p2.y), p3.y) - min(min(p1.y, p2.y), p3.y));
	return R-T1-T2-T3;
}
