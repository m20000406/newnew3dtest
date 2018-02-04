/////////////////////////////
//vector.h
//���F�N�^�֌W�̉]�X
/////////////////////////////
#ifndef INCLUDE_VECTOR_H
#define INCLUDE_VECTOR_H

class vector {
public:
	vector(float, float, float);
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
const float alpha = 5;   //�`�敽�ʂ��ǂ̂��炢�悩

#endif