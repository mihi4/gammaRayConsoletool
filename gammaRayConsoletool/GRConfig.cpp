#include "GRConfig.h"
#include <string>
#include <iostream>

void GRConfig::readConfigFile(std::string filepath) {

}

key2send GRConfig::getConfigValue(int index)
{
	return config[index];
}
