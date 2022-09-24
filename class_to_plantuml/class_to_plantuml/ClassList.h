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
	FunctioList strInherit;//�p����
	std::string strClassName= "";	//�N���X��
	FunctioList strFunctionList;
	FunctioList* const PstrFunctionList=&strFunctionList;	//�֐�/�ϐ����̃��X�g�B���I�Ɋm�ۂ����
	int iLintCount=-1;			//�֐�/�ϐ����̃J�E���g��
	char cModifierCheck(char cData);

public:
	void vShowAll();					//�o�^���Ă���S�Ă̕\������
	char cClassNameRegist(std::string);	//�N���X����o�^
	char cFuncionRegist(char,string);	//�֐���/�ϐ�����o�^
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
