//-------------------
// キー入力管理
#include <stdio.h>
#define CONIOEX		// これをつけるとconioex内の内部メモリが重複しない
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
// 1/60秒ごとに1回呼ぶ
// 登録したキーをスキャンして
// 各変数に入れる
void keyScan()
{
	// 登録全キーについて
	for (int i = 0; i < keyDicCount; i++)
	{
		if (inport(keyDic[i].code))// 押されている
		{
			keyDic[i].release = false;
			if (keyDic[i].press)// 1回前に押されていた？
			{
				keyDic[i].push = false;
				keyDic[i].pressCount++;
			}
			else
			{ // 前回押されなかったが押された瞬間
				keyDic[i].push = true;
				keyDic[i].press = true;
				keyDic[i].pressCount = 1;
			}
		}
		else // 該当キーが押されていない
		{
			keyDic[i].push = false;
			if (keyDic[i].press)// 1回前に押されていた？
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
	// 上の変数keyDicにキーが登録されている前提
	// 単純に全部探す。べたな方法。遅いよ。
	for (int i = 0; i < keyDicCount; i++)
	{
		if (keyDic[i].code == keyCode)
		{
			return i;
		}
	}
	// 
	printf("キーコード指定ミス=%d\n", keyCode);
	return -1; // 見つからなかったら
	// -1とか、エラー的な値を返す
}
