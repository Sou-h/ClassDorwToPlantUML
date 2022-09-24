///�R�~�b�g�e�X�g

#include <stdio.h>
#include <iostream>
//��������
#include<fstream>
#include<string>
#include <regex> //������u��
#include "Header.h"
#include "ClassList.h"
#include "PlantUML.h"


using namespace std;

//
int class_find(string& strData,FunctioList& inheritData) {
	int iFindResult;
	int iModifier_size = sizeof(modifier_list_string_not_colon) / sizeof(string);
	std::smatch results; //���K�\���Ńq�b�g�������ʂ���
	std::regex re("(((:)|(: ))private )|(((:)|(: ))public )|(((:)|(: ))protected )");//�p���̈ꕶ�����݂��邩�H
	std::regex re2("(((:)|(: ))private ([0-9a-zA-Z_]+))|(((:)|(: ))public ([0-9a-zA-Z_]+))|(((:)|(: ))protected ([0-9a-zA-Z_]+))");

	iFindResult = strData.find("class ");
	if (-1!=iFindResult) {
		strData=regex_replace(strData, regex("class"),"");
		strData = regex_replace(strData, regex("^ "), "");
		
		//�p�����鏈�������邩�H
		if (regex_search(strData, re)) {

			//���K�\���ŃO���[�v�𕪂��A������𒊏o
			regex_search(strData, results, re2);
			if (true==results[5].matched) {//PRIVATE
				inheritData.strFunctionName = results[5];
				inheritData.cModifier = PRIVATE;
			}
			else if (true == results[10].matched) {//PUBLIC
				inheritData.strFunctionName = results[10];
				inheritData.cModifier = PUBLIC;
			}
			else if (true == results[15].matched) {//PROTECTED
				inheritData.strFunctionName = results[15];
				inheritData.cModifier = PROTECTED;
			}
			else {
				//�q�b�g����
			}
				//�p���̕�������폜	
				strData = regex_replace(strData, regex("((:)|(: )).+"), "");
		}
		cout << strData << endl;
	}
	return iFindResult;
}

int type_sort(string& strData,char &cModifierData) {
	int iCount = 0;
	int iResult = 0;
	int iType_size = sizeof(type_list_string) / sizeof(string);
	int iModifier_size = sizeof(modifier_list_string) / sizeof(string);
	
	for (iCount = 0; iCount < iModifier_size; iCount++) {
		iResult = strData.find(modifier_list_string[iCount].c_str());
		if (-1!= iResult) {
			cModifierData = iCount+1;
			return -1;
		}
	}
	
//	printf("type_size:%d", sizeof(type_list_string));
	for (iCount = 0; iCount < iType_size;iCount++) {

		iResult = strData.find(type_list_string[iCount].c_str());

		if (-1 != iResult) {
			strData = regex_replace(strData, regex("(^ +)|(^\t+)"), "");//�擪��������󗓂��폜
			strData = regex_replace(strData, regex("( +$)|(\t+$)"), "");//������������󗓂��폜
			strData = regex_replace(strData, regex(";"), "");//������������󗓂��폜
			cout << strData << endl;
			break;
		}
	}
	return iResult;
}

int class_end(string& strData,bool &classFlag) {
	int iFindResult;
	iFindResult = strData.find(class_end_string);
	if (-1 != iFindResult) {
		classFlag = false;
		cout << "�N���X����܂�" << endl;
	}
	return iFindResult;
}


int main()
{


	fstream myFile;
	myFile.open("C:/Users/sou/Source/Repos/list2_2/list2_2/main_test.cpp", ios::in);//read
	//printf("%s\n",type_list_string[0].c_str());
	int cout = -1;
	Class_list ClassllistData[10];	//�N���X���X�g���Ǘ�
	bool bClassFlag = false;			//�N���X�̏I�����Ǘ�
	FunctioList strFunctionData;	//�擾�����֐��f�[�^���ꎞ�ۑ�
	FunctioList strInheritData;		//�p������t�@�C����
	class_PlantUML UmlFile("C:/Users/sou/Source/Repos/list2_2/list2_2/PlantUML_test.txt");

	if (myFile.is_open()) {
		string line;
		while (getline(myFile, line)) {
			if (-1 != class_find(line, strFunctionData)) {
				cout++;
				bClassFlag = true;
				ClassllistData[cout].cClassNameRegist(line);
				ClassllistData[cout].strInheritRegist(strFunctionData.cModifier,strFunctionData.strFunctionName);
			}
			class_end(line,bClassFlag);

			if ( (-1 != type_sort(line, ClassllistData[cout].cModifier) ) && (bClassFlag==true)) {
				ClassllistData[cout].cFuncionRegist(ClassllistData[cout].cModifier,line);
			}
		}

		printf("\n\n---�S�ĕ\��---\n");
		for (int c = 0; c <= cout;c++) {	
			ClassllistData[c].vShowAll();
			UmlFile.ClassWriteToFile(ClassllistData[c].strPutClassName());
			UmlFile.FunctionWriteToFile(ClassllistData[c].strPutFunctionPut());
			UmlFile.ClassEndWriteToFile();
		}
		UmlFile.endfile();
		myFile.close();
	}

	system("pause>0");
} 