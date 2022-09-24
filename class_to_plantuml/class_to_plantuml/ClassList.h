using namespace std;

#pragma once

#define PRIVATE			1
#define PUBLIC				2
#define PROTECTED		3
#define NONMODIFIER	0

typedef struct FunctioList {
	char cModifier = -1;
	std::string strFunctionName = "";
	FunctioList *PvNextName=NULL;
}FunctioList;

class  Class_list {
private:
	FunctioList strInherit;//継承元
	std::string strClassName= "";	//クラス名
	FunctioList strFunctionList;
	FunctioList* const PstrFunctionList=&strFunctionList;	//関数/変数名のリスト。動的に確保される
	int iLintCount=-1;			//関数/変数名のカウント数
	char cModifierCheck(char cData);

public:
	void vShowAll();					//登録している全ての表示する
	char cClassNameRegist(std::string);	//クラス名を登録
	char cFuncionRegist(char,string);	//関数名/変数名を登録
	char strInheritRegist(char,string);
	char cModifier = 0;
	string strPutClassName();
	string strPutFunctionPut();
	string strPutInherit();
	string strInheritWriteToFile();

	Class_list() {

		strFunctionList.cModifier = -1;
		strFunctionList.strFunctionName = "";
		strFunctionList.PvNextName = NULL;
		
	}
};
