#include "Functions.h"

bool lycee::Path::isExists(const std::string &path) {
	std::ifstream fi;
	fi.open(path);
	return fi.is_open();
}

bool lycee::Path::isExists(const std::wstring &path) {
	std::ifstream fi;
	fi.open(path);
	return fi.is_open();
}

