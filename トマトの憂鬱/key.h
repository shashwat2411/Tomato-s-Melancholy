#pragma once

struct KeyStatus
{
	int code;
	bool push;
	bool press;
	bool release;
	int pressCount;
};

// 1/60秒ごとに1回呼ぶ
// 登録したキーをスキャンして
// 各変数に入れる
void keyScan();
bool keyPush(int keyCode);//押した瞬間？
bool keyPress(int keyCode); // 押しっぱ？
int keyPressCount(int keyCode); // 押し続けた
								// フレーム数
void keyCountReset(int keyCode); // 押し続けカウントをリセット

bool keyRelease(int keyCode); // 離した瞬間？




