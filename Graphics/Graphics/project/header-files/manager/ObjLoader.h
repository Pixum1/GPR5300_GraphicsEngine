#pragma once
#include "../misc/GraphicsPCH.h"
#include <map>
#include <sstream>
#include <string>
#include "..\gameobjects\components\Mesh.h"

enum EDataType
{
	Empty,
	Comment,
	Position,
	Normal,
	UV,
	Face
};

class CObjLoader
{
public:
	int LoadMesh(CMesh* _p_mesh, LPWSTR _fileName);

private:
	EDataType GetType(std::string _line);

private:
	std::map<EDataType, std::string> Keywords
	{
		{ Comment,	"#"	 },
		{ Position, "v"	 },
		{ Normal,	"vn" },
		{ UV,		"vt" },
		{ Face,		"f"	 },
	};
};

