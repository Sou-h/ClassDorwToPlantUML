#include <stdio.h>
#include <iostream>
//文字検索
#include<fstream>
#include<string>

#include "ClassList.h"

string Class_list::strPutClassName() {
	if (-1 != iLintCount) {
		return strClassName;
	}
	else {
		printf("登録されているデータがありません\n");
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
		printf("登録されているデータがありません\n");
	}
	return NULL;
}

string Class_list::strPutInherit() {
	if ("" == strInherit.strFunctionName) {
		return strInherit.strFunctionName;
	}
	else {
		printf("登録されているデータがありません\n");
	}
	return NULL;
}

void Class_list::vShowAll() {
	if (-1!=iLintCount) {
		FunctioList *PstrFunctionData = PstrFunctionList;
		cout<<strClassName<<endl;
		if ("" != strInherit.strFunctionName) {
			printf("アクセス修飾子:%d\t",strInherit.cModifier);
			cout << "継承classの名称:" << strInherit.strFunctionName << endl;
		}
		do
		{
			printf("アクセス修飾子:%d\t", PstrFunctionData->cModifier);
			cout<<"関数名:"<< PstrFunctionData->strFunctionName<<endl;
			PstrFunctionData = reinterpret_cast <FunctioList *>(PstrFunctionData->PvNextName);
		} while ((NULL != PstrFunctionData));
		printf("-----------------\n\n");
	}
	else {	
		printf("登録されているデータがありません\n");
	}
}

//クラス名を登録
char Class_list::cClassNameRegist(string strData) {
	if ("" == strClassName) {
		strClassName = strData;
		cout << "クラス名\""<<strClassName<<"\"を登録しました\n" << endl;
	}
	else {
		cout << "既にクラス名が登録されています:" << strClassName << endl;
		printf("操作方法が謝っています。確認してください");
		return -1;
	}
	return 0;
}

char Class_list::strInheritRegist(char cModifierData,string strData) {
	strInherit.cModifier= cModifierCheck(cModifierData);
	strInherit.strFunctionName = strData;
	return 0;
}

//関数名/クラス名を登録
char Class_list::cFuncionRegist(char cModifierData,string strFunctionNameData) {
	if (-1 == iLintCount) {//初回の登録
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

