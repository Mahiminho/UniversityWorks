#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <Windows.h>
#include <io.h>

#define IsOperation(k) (k < 12)

using namespace std;

enum TypeOfLex
{
	LAdd,
	LSub,
	LMul,
	LDiv,
	LMod,
	LEqu,
	LNotEqu,
	LGreate,
	LLess,
	LNot,
	LAnd,
	LOr,

	LBegProg,
	LProgram,
	LProgramName,
	LStart,
	LData,
	LVarType,
	LIdentifier,
	LEnd,

	LScan,
	LPrint,

	LIf,
	LGoto,
	LLabel,
	LTarget,

	LNewValue,

	LDLine,
	LLBraket,
	LRBraket,
	LNumber,
	LDDot,
	LSeparator,
	LComma,
	LEOF,
	LLComentar,
	LRComentar,
	LUnknown
};

struct LexAndName
{
	TypeOfLex type;
	std::string name;
};

//DATA
typedef struct Lexem
{
	string name;
	int value;
	int line;
	TypeOfLex type;
}Lexema;

typedef struct L
{
	vector<Lexema> LexTable;			//Таблиця лексем

	vector<string> IdTable;		//Таблиця ідентифікаторів
	string ftype = "p16";
	string TName = "xxxxxxxx";
	vector<LexAndName> LexName =
	{
		{LAdd,"add"},
		{LSub,"sub"},
		{LMul,"*" },
		{LDiv,"/"},
		{LMod,"%"},
		{LEqu,"="},
		{LNotEqu,"<>"},
		{LGreate,">="},
		{LLess,"<="},
		{LNot,"!"},
		{LAnd,"&"},
		{LOr,"|"},

		{LBegProg,""},
		{LProgram,"#program"},
		{LProgramName,""},
		{LStart,"start"},
		{LData,"variable"},
		{LVarType,"integer16"},
		{LIdentifier,""},
		{LEnd,"stop"},

		{LScan,"get"},
		{LPrint,"put"},

		{LIf,"if"},
		{LGoto,"goto"},
		{LLabel,""},
		{LTarget,""},

		{LNewValue,"::"},

		{LLBraket,"("},
		{LRBraket,")"},
		{LDLine,"_"},
		{LNumber,""},
		{LDDot,":"},
		{LSeparator,";"},
		{LComma,","},
		{LLComentar,"//"},
		{LRComentar,""},
		{LEOF,"EndFile"}
	};

	bool IsPresentInput,					//Ознаки присутності операторів
		IsPresentOutput,
		IsPresentMod,
		IsPresentAnd,
		IsPresentOr,
		IsPresentNot,
		IsPresentEqu,
		IsPresentGreate,
		IsPresentLess,
		IsPresentDiv;

	bool EnableProgN = 1, PosLStart = 0;

	int numberErrors;

	std::string InputFileName;
	std::string OutputFileName;
}DataType;

bool directory_exists(const std::string& directory);