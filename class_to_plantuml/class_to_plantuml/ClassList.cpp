#include <stdio.h>
#include <iostream>
//��������
#include<fstream>
#include<string>

#include "ClassList.h"

string Class_list::strPutClassName() {
	if (-1 != iLintCount) {
		return strClassName;
	}
	else {
		printf("�o�^����Ă���f�[�^������܂���\n");
	}
	return NULL;
}

string Class_list::strPutFunctionPut() {
	if (-1 != iLintCount) {
		FunctioList *PstrFunctionData = PstrFunctionList;
		string strFunctionData="";
		do
		{
			strFunctionData+= PstrFunctionData->cModifier;
			strFunctionData += PstrFunctionData->strFunctionName;
			strFunctionData += "\n";
			PstrFunctionData = reinterpret_cast <FunctioList *>(PstrFunctionData->PvNextName);
		} while ((NULL != PstrFunctionData));
		return strFunctionData;
	}
	else {
		printf("�o�^����Ă���f�[�^������܂���\n");
	}
	return NULL;
}

string Class_list::strPutInherit() {
	if ("" == strInherit.strFunctionName) {
		return strInherit.strFunctionName;
	}
	else {
		printf("�o�^����Ă���f�[�^������܂���\n");
	}
	return NULL;
}

void Class_list::vShowAll() {
	if (-1!=iLintCount) {
		FunctioList *PstrFunctionData = PstrFunctionList;
		cout<<strClassName<<endl;
		if ("" != strInherit.strFunctionName) {
			printf("�A�N�Z�X�C���q:%d\t",strInherit.cModifier);
			cout << "�p��class�̖���:" << strInherit.strFunctionName << endl;
		}
		do
		{
			printf("�A�N�Z�X�C���q:%d\t", PstrFunctionData->cModifier);
			cout<<"�֐���:"<< PstrFunctionData->strFunctionName<<endl;
			PstrFunctionData = reinterpret_cast <FunctioList *>(PstrFunctionData->PvNextName);
		} while ((NULL != PstrFunctionData));
		printf("-----------------\n\n");
	}
	else {	
		printf("�o�^����Ă���f�[�^������܂���\n");
	}
}

//�N���X����o�^
char Class_list::cClassNameRegist(string strData) {
	if ("" == strClassName) {
		strClassName = strData;
		cout << "�N���X��\""<<strClassName<<"\"��o�^���܂���\n" << endl;
	}
	else {
		cout << "���ɃN���X�����o�^����Ă��܂�:" << strClassName << endl;
		printf("������@���ӂ��Ă��܂��B�m�F���Ă�������");
		return -1;
	}
	return 0;
}

char Class_list::strInheritRegist(char cModifierData,string strData) {
	strInherit.cModifier= cModifierCheck(cModifierData);
	strInherit.strFunctionName = strData;
	return 0;
}

//�֐���/�N���X����o�^
char Class_list::cFuncionRegist(char cModifierData,string strFunctionNameData) {
	if (-1 == iLintCount) {//����̓o�^
		strFunctionList.cModifier = cModifierCheck(cModifierData);
		strFunctionList.strFunctionName = strFunctionNameData;
		strFunctionList.PvNextName=NULL;
		iLintCount = 0;
		return 0;
	}

	FunctioList **PstrNextFunctionList= &PstrFunctionList->PvNextName;
	FunctioList *strNextFunctionList = new FunctioList;
	strNextFunctionList->cModifier= cModifierCheck(cModifierData);
	strNextFunctionList->strFunctionName = strFunctionNameData;
	strNextFunctionList->PvNextName = NULL;
	while (NULL != *PstrNextFunctionList)
	{
		PstrNextFunctionList = &((*PstrNextFunctionList)->PvNextName);
		//printf("PstrFunctionList->PvNextName:%p\n", strNextFunctionList->PvNextName);
	}

	*PstrNextFunctionList = strNextFunctionList;

	iLintCount++;
	return 0;
}

char Class_list::cModifierCheck(char  cModifierData) {
	if (PRIVATE == cModifierData) {
		return '-';
	}
	else if (PUBLIC == cModifierData) {
		return '+';
	}
	else if (PROTECTED == cModifierData) {
		return '#';
	}
	else{
		return NONMODIFIER;
	}

}

