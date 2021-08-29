
#include <iostream>
#include <combaseapi.h>
#include <ShObjIdl.h>
#include <algorithm>

class PathHelper
{
public:
	static std::string GetUserDirectory();
	static std::string GetRootPath();
};

