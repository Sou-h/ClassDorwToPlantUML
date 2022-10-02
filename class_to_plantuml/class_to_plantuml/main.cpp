#include <stdio.h>
#include <iostream>
//文字検索
#include<fstream>
#include<string>
#include <regex> //文字列置換
#include "Header.h"
#include "ClassList.h"
#include "PlantUML.h"


using namespace std;

//
int class_find(string& strData,FunctionList& inheritData) {
	int iFindResult;
	int iModifier_size = sizeof(modifier_list_string_not_colon) / sizeof(string);
	std::smatch results; //正規表現でヒットした結果を代入
	std::regex re("(((:)|(: ))private )|(((:)|(: ))public )|(((:)|(: ))protected )");//継承の一文が存在するか？
	std::regex re2("(((:)|(: ))private ([0-9a-zA-Z_]+))|(((:)|(: ))public ([0-9a-zA-Z_]+))|(((:)|(: ))protected ([0-9a-zA-Z_]+))");

	iFindResult = strData.find("class ");
	if (-1!=iFindResult) {
		strData=regex_replace(strData, regex("class"),"");
		strData = regex_replace(strData, regex("^ "), "");
		
		//継承する処理があるか？
		if (regex_search(strData, re)) {

			//正規表現でグループを分け、文字列を抽出
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
				//ヒットせず
			}
				//継承の文字列を削除	
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
			strData = regex_replace(strData, regex("(^ +)|(^\t+)"), "");//先頭文字から空欄を削除
			strData = regex_replace(strData, regex("( +$)|(\t+$)"), "");//末尾文字から空欄を削除
			strData = regex_replace(strData, regex(";"), "");//末尾文字から空欄を削除
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
		cout << "クラスを閉じます" << endl;
	}
	return iFindResult;
}

char cFireOpen(fstream &fileDate,string &FileName) {
	cout << "絶対パスでファイル名を入力してください\n";
	cin >> FileName;
	fileDate.open(FileName, ios::in);
	if (!fileDate) {
		std::cerr << "ファイルを開けませんでした。" << std::endl;
		exit(1);
		return -1;
	}
	return 1;
}

char cOutPutFire(fstream &fileDate, string &FileName) {
	cout << "作成するファイル名を入力してください\n";
	cin >> FileName;
	fileDate.open(FileName, ios::in);
	if (!fileDate) {
		std::cerr << "ファイルを開けませんでした。" << std::endl;
		exit(1);
		return -1;
	}
	return 1;
}

int main()
{
	string strReadFileName;				//読み込むファイル名
	string strOutPutFileName;			//作成するファイル名
	fstream myFile;

	cFireOpen(myFile,strReadFileName);
	//printf("%s\n",type_list_string[0].c_str());
	int iCount = -1;							//classを発見したカウント数
	Class_list ClassllistData[10];	//クラスリストを管理
	bool bClassFlag = false;			//クラスの終了を管理
	FunctionList strFunctionData;	//取得した関数データを一時保存
	FunctionList strInheritData;		//継承するファイル名

	cout<<"作成するファイル名を入力してください"<<endl;
	cin >> strOutPutFileName;
	class_PlantUML UmlFile(strOutPutFileName);

	if (myFile.is_open()) {
		string line;
		while (getline(myFile, line)) {
			if (-1 != class_find(line, strFunctionData)) {
				iCount++;
				bClassFlag = true;
				ClassllistData[iCount].cClassNameRegist(line);
				ClassllistData[iCount].strInheritRegist(strFunctionData.cModifier,strFunctionData.strFunctionName);
			}
			class_end(line,bClassFlag);

			if ( (-1 != type_sort(line, ClassllistData[iCount].cModifier) ) && (bClassFlag==true)) {
				ClassllistData[iCount].cFuncionRegist(ClassllistData[iCount].cModifier,line);
			}
		}

		printf("\n\n---全て表示---\n");
		for (int c = 0; c <= iCount;c++) {
			ClassllistData[c].vShowAll();
			UmlFile.ClassWriteToFile(ClassllistData[c].strPutClassName());
			UmlFile.FunctionWriteToFile(ClassllistData[c].strPutFunctionPut());
			UmlFile.ClassEndWriteToFile();
			UmlFile.strInheritWriteToFile(ClassllistData[c].strPutClassName(), ClassllistData[c].strPutInherit());
		}
		UmlFile.endfile();
		myFile.close();
	}

	system("pause>0");
} 