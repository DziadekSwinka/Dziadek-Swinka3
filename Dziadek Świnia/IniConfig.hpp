#ifndef INICONFIG_HPP_INCLUDED
#define INICONFIG_HPP_INCLUDED

#include <windows.h>
#include <winbase.h>
#include <string>

void lineToSetup(std::string line ,int i);
void iniToSetup(char[][256]);
void config();
#endif // INICONFIG_HPP_INCLUDED
