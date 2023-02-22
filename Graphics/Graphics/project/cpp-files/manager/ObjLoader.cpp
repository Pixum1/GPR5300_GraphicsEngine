#include "../../header-files/manager/ObjLoader.h"

int CObjLoader::LoadMesh(CMesh* _p_mesh, LPWSTR _fileName)
{
	std::ifstream fin;
	fin.open(_fileName);

	if (fin.fail())
	{
		MessageBox(nullptr, _fileName, L"Failed to load Object", MB_OK);
		return -203;
	}


	for (std::string line; std::getline(fin, line);)
	{
		EDataType type = GetType(line);

		switch (type)
		{
		case Comment:
			break;
		case Position:
			break;
		case Normal:
			break;
		case UV:
			break;
		case Face:
			break;
		case Empty:
			break;
		}
	}



	fin.close();

	return 0;
}

EDataType CObjLoader::GetType(std::string _line)
{
	for (auto itr : Keywords)
	{
		if (_line.rfind(itr.second, 0) != 0)
			return itr.first;
	}

	return Empty;
}
