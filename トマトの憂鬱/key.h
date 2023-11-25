#pragma once

struct KeyStatus
{
	int code;
	bool push;
	bool press;
	bool release;
	int pressCount;
};

// 1/60�b���Ƃ�1��Ă�
// �o�^�����L�[���X�L��������
// �e�ϐ��ɓ����
void keyScan();
bool keyPush(int keyCode);//�������u�ԁH
bool keyPress(int keyCode); // �������ρH
int keyPressCount(int keyCode); // ����������
								// �t���[����
void keyCountReset(int keyCode); // ���������J�E���g�����Z�b�g

bool keyRelease(int keyCode); // �������u�ԁH




