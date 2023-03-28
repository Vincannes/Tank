#include "utils.h"

std::vector<std::string> splitPath(const std::string& path) {
	char delimiter = '\\';

	std::vector<std::string> result;
	std::stringstream ss(path);
	std::string token;
	while (std::getline(ss, token, delimiter)) {
		result.push_back(token);
	}
	return result;
}


std::string joinListWithSeparator(std::vector<std::string> list, char separator) {
	std::string result = "";
	for (int i = 0; i < list.size(); i++) {
		if (i > 0) {
			result += separator;
		}
		result += list[i];
	}
	return result;
}
