//-------------------
// �L�[���͊Ǘ�
#include <stdio.h>
#define CONIOEX		// ����������conioex���̓������������d�����Ȃ�
#include "conioex.h"
#include "key.h"

static KeyStatus keyDic[] =
{
	{PK_LEFT,false,false,false,0},
	{PK_RIGHT,false,false,false,0},
	{PK_UP,false,false,false,0},
	{PK_DOWN,false,false,false,0},
	{PK_SP,false,false,false,0},
	{PK_ENTER,false,false,false,0},
	{PK_Q,false,false,false,0},
	{PK_ESC,false,false,false,0},
	{PK_R,false,false,false,0}
};
static int keyDicCount = sizeof(keyDic) / sizeof(KeyStatus);

int getIndexOfKeyCode(int keyCode);

//---------------- 
// 1/60�b���Ƃ�1��Ă�
// �o�^�����L�[���X�L��������
// �e�ϐ��ɓ����
void keyScan()
{
	// �o�^�S�L�[�ɂ���
	for (int i = 0; i < keyDicCount; i++)
	{
		if (inport(keyDic[i].code))// ������Ă���
		{
			keyDic[i].release = false;
			if (keyDic[i].press)// 1��O�ɉ�����Ă����H
			{
				keyDic[i].push = false;
				keyDic[i].pressCount++;
			}
			else
			{ // �O�񉟂���Ȃ������������ꂽ�u��
				keyDic[i].push = true;
				keyDic[i].press = true;
				keyDic[i].pressCount = 1;
			}
		}
		else // �Y���L�[��������Ă��Ȃ�
		{
			keyDic[i].push = false;
			if (keyDic[i].press)// 1��O�ɉ�����Ă����H
			{
				keyDic[i].release = true;
				keyDic[i].press = false;
			}
			else
			{
				keyDic[i].release = false;
				keyDic[i].pressCount = 0;
			}
		}
	}
}

bool keyPush(int keyCode)
{
	int index = getIndexOfKeyCode(keyCode);
	if (index >= 0)
	{
		return keyDic[index].push;
	}
	return false;
}

bool keyPress(int keyCode)
{
	int index = getIndexOfKeyCode(keyCode);
	if (index >= 0)
	{
		return keyDic[index].press;
	}
	return false;
}

int keyPressCount(int keyCode)
{
	int index = getIndexOfKeyCode(keyCode);
	if (index >= 0)
	{
		return keyDic[index].pressCount;
	}
	return 0;
}

void keyCountReset(int keyCode)
{
	int index = getIndexOfKeyCode(keyCode);
	if (index >= 0)
	{
		keyDic[index].pressCount = 0;
	}
}

bool keyRelease(int keyCode)
{
	int index = getIndexOfKeyCode(keyCode);
	if (index >= 0)
	{
		return keyDic[index].release;
	}
	return false;
}

int getIndexOfKeyCode(int keyCode)
{
	// ��̕ϐ�keyDic�ɃL�[���o�^����Ă���O��
	// �P���ɑS���T���B�ׂ��ȕ��@�B�x����B
	for (int i = 0; i < keyDicCount; i++)
	{
		if (keyDic[i].code == keyCode)
		{
			return i;
		}
	}
	// 
	printf("�L�[�R�[�h�w��~�X=%d\n", keyCode);
	return -1; // ������Ȃ�������
	// -1�Ƃ��A�G���[�I�Ȓl��Ԃ�
}
