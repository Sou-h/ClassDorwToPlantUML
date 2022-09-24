#include "PlantUML.h"

char class_PlantUML::makafile(string fileName) {
	writing_file.open(fileName, std::ios::out);
	if (writing_file.fail()) {
		std::cerr << "ƒtƒ@ƒCƒ‹Opne‚ÉŽ¸”s‚µ‚Ü‚µ‚½B: " << fileName << "\n";
		exit(1);
	}
	return true;
}

char class_PlantUML::endfile() {
	writing_file << END_UML << endl;
	writing_file.close();
	return 1;
}

class_PlantUML::class_PlantUML(string fileName) {
	makafile(fileName);
	writing_file << STAR_TUML << endl;
}

class_PlantUML::~class_PlantUML() {
	writing_file << END_UML << endl;
	writing_file.close();
}

char class_PlantUML::writefile(string strData) {
	writing_file << strData << endl;
	return 1;
}

char class_PlantUML::ClassWriteToFile(string strData) {
	if (""!=strData) {
		writefile(("class " + strData + "{\n"));
		return 1;
	}
	else {
		printf("“n‚³‚ê‚½•¶Žš—ñ‚ªNULL‚Å‚·B‘€ì‚ðŒë‚Á‚Ä‚¢‚Ü‚·");
		return -1;
	}
}

char class_PlantUML::FunctionWriteToFile(string strData) {
	if ("" != strData) {
		writefile((strData + "\n"));
		return 1;
	}
	else {
		printf("“n‚³‚ê‚½•¶Žš—ñ‚ªNULL‚Å‚·B‘€ì‚ðŒë‚Á‚Ä‚¢‚Ü‚·");
		return -1;
	}
}

char class_PlantUML::strInheritWriteToFile(string ClassName, string strInheritName) {
	if ("" != ClassName && ""!= strInheritName) {
		writefile((strInheritName+"<|--"+ClassName+"\n"));
	}
	else {
		printf("“n‚³‚ê‚½•¶Žš—ñ‚ªNULL‚Å‚·B‘€ì‚ðŒë‚Á‚Ä‚¢‚Ü‚·");
		return -1;
	}
	return 1;
}

char class_PlantUML::	ClassEndWriteToFile(){
	writefile("}\n");
	return 1;
}