/////////////////////////////
//vector.h
//���F�N�^�֌W�̉]�X
/////////////////////////////
#pragma once

class vector {
public:
	vector(float, float, float);
	vector();
	float x, y, z;
	static vector zero;   //0�x�N�g��
	float norm();   //�����̃m����
	vector operator+=(vector);
	vector operator-=(vector);
	vector operator*=(float);
	vector operator/=(float);
	float operator*=(vector);
private:
};
vector operator+(vector, vector);
vector operator-(vector, vector);
vector operator*(float, vector);
vector operator*(vector, float);
vector operator/(vector, float);   //vector�̉����揜
float operator*(vector, vector);   //vector��vector�̓���
vector normalize(vector);   //�x�N�g���̐��K��
vector convert(vector);   //�O�����x�N�g����`�敽�ʂɕϊ�(z == -1 -> �`��͈͊O)
vector round(vector);   //x,y�v�f��round