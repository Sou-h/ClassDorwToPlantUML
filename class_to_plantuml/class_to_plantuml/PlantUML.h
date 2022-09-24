#pragma once
#include <iostream>
//ï∂éöåüçı
#include<string>
#include <fstream>
#include "ClassList.h"

using namespace std;

#define STAR_TUML "@startuml"
#define END_UML "@enduml"
#define CLASS "class"

class class_PlantUML{
private:
	std::ofstream writing_file;
	char makafile(string);
	char writefile(string);
public:
	char ClassWriteToFile(string);
	char ClassEndWriteToFile();
	char FunctionWriteToFile(string);
	char strInheritWriteToFile(string,string);
	char endfile();
	class_PlantUML(string);
	~class_PlantUML();
};