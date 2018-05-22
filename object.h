#pragma once
#include <string>
#include <memory>
#include <tuple>
#include <map>
#include <vector>

typedef std::map<std::string, std::string> Attr;   //addInf�̈����p

//�I�u�W�F�N�g�̂��߂̉��z�N���X
class IObject {
public:
	virtual void draw() = 0;   //�`��p�֐�
	virtual ~IObject() {};   //�f�X�g���N�^
	virtual void addInf(std::string, std::string, Attr = Attr() ) = 0;   //���ݒ�p�̊֐�
	std::vector<std::string> tags;
};

//object�I�u�W�F�N�g�̃t�@�N�g��
std::shared_ptr<IObject> objFactory(std::string);