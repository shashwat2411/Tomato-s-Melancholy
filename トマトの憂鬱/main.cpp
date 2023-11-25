//���̃v���O�������������̂́C�Ȃ��Ɓi�V���V�����b�g �P�^���j�ł�
//���̃v���O�����́uTOMATOE'S MELANCHOLY�v�i�g�}�g�̗J�T�j�ł�
//HEW�̃v���W�F�N�g�ł�
//���s����Ƃ��͕K���t���X�N���[���ɂ��Ă�������

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include "conioex.h"
#include "key.h"

struct Shooter//�Q�[����ʂ̕��̂̍\����
{
    float angle;
    float lastAngle;
    float x, y;
    float lastX, lastY;
    bool life = true;
    bool complete = false;
    int HP;
};

struct Coordinates//���W�̍\����
{
    float x, y;
};

#define smallVOL 20
#define medVOL 25
#define highVOL 30
#define SoundLimit 14

#define THREE_D 2.5f

#define PI 3.1415926535897932

#define ANGLE (float)(PI*5/4)

#define X 90.0f
#define Y 24.0f

#define ANGLE_SPEED 0.05f
#define BULLET_SPEED 2.0f
#define ENEMY_SPEED 1.0f
#define ENEMY_SPEED_TOP 3.0f
#define ENEMY_SPEED_LEFT 7.0f

#define ENEMY_HP 3

#define ANGLE_LIMIT_LEFT 3.326992
#define ANGLE_LIMIT_RIGHT 5.576997

#define DEAD 100
#define WAVENUMBER 15

enum//�Q�[���̃X�e�[�^�X
{
    START = 1,
    GAME,
    EXIT,
    RESULT
};

char CutScene[14][50][200];//�X�g�[���[�̃A�X�L�[�A�[�g
char GamePlay[7][50][200];//�Q�[���̃A�X�L�[�A�[�g
char TomatoeLife[3][50][200];//�v���[���[��HP�̃A�X�L�[�A�[�g
char textBoxText[300];//�e�L�X�g�̕ۑ��p

bool exitFlag = false;
bool update = true;
bool win = false;

int enemyNumber = DEAD;
int enemyBreadth[3] = { 46,64,57 };
int enemyLength[3] = { 20,19,19 };
int count, countSide, enemyCounter = 0;
int score = 0, lastScore = 0;
int Wave = WAVENUMBER;
int ending = 1;
int hpBackUp;
int music[SoundLimit];
int finalX[3], finalY[3];
int killer = 0;

float Radius[3] =  { 1,1,1 };//���f�B�E�X
float RadiusLimit[3];//���f�B�E�X�̌��E
float distance = 0.0f;

Coordinates enemyCenter[3];//�G�̐^�񒆂̍��W

Shooter player;//�v���[���[
Shooter bullet;//�g�}�g�̒e��
Shooter enemy[3];//�l�Ԃ̔z��



//�v���g�^�C�v�錾
void Game();//�v���[�̗���

void AudioOpen();//���t�@�C�����J��
void AudioVolume();//���t�@�C���̉�������
void AudioClose();//���t�@�C�������
void StopAllSound();//�S�Ă̗�����Ă��鉹�t�@�C�����~

void Story();//�J�b�g�V�[��
void Lose();//������Ƃ�
void TextBox(char text[300], int color);//�Z���t�����锠
void EraseBox(int startX, int startY, int endX, int endY);//����̎l�p���폜
void Win();//�������̎��̉��o
void EndingTwo();//�G���f�B���O�Q
void Quit();//�Q�[��������Ƃ�

void Update();//�L�[����
void Draw();//�v���[���[�̕\��

void BulletUpdate();//�o���b�g�̌v�Z
void BulletDraw();//�o���b�g�̕\��
void BulletErase();//�o���b�g�̍폜
void BulletPlot();//�o���b�g������

void EnemyCreate();//�G�̍쐬
void EnemyUpdate();//�G�̌v�Z
void EnemyDraw();//�G�̕\��
void EnemyAnimation(float x, float y, int length, int breadth, bool down);//�G�̓����̃A�j���[�V����

void WaitFor(float timerLimit);//����̎��Ԃ�҂�
void ScreenChange();//��ʕϓ�
int Selection();//���C�����j���[�̃Z���N�V�����̕���

char ButtonPress();//�L�[���͑҂�
void EnterWait();//�G���^�[�̃L�[��҂�

void DisplayASCII(int x, int y, char ASCII_Art[50][200], int height, int breadth);//�A�X�L�[�A�[�g�̃t���\��
void DisplayASCII_One_Line(int x, int y, char ASCII_Art[50][200], int breadth, int i, int n, bool dot);//�A�X�L�[�A�[�g�̈�̃��C��������\��

int PlayerPointCalculator(float x, float y);//�v���[���[�̔��΂̊p�x�̌v�Z
float Collision(float x1, float y1, float x2, float y2);//�Փˊ��m
void RadiusCalculator();//���f�B�E�X�̌v�Z

void ASCII();//�A�X�L�[�A�[�g�̕ۑ�

//#define QUITTER
//#define TEST
//#define COLOR_TEST
//#define Video

//���s�f�[�^

int main()
{
    //AudioOpen();
    AudioVolume();
    highvideo();
    RadiusCalculator();
    textcolor(WHITE);
    highvideo();
    ASCII();
    setcursortype(NOCURSOR);
    bool exit = false;
    while (!exit)
    {
        ScreenChange();
        int selection = Selection();
        switch (selection)
        {
        case START:
            StopAllSound();
            Story();
        case GAME:
            StopAllSound();
            ScreenChange();
            Game();
            break;
        case EXIT:
            StopAllSound();
            ScreenChange();
            playsound(music[13], 1);
            Quit();
            textcolor(BLACK);
            gotoxy(11, 38);
            exit = true;
            break;
        }
    }
    AudioClose();
#ifdef COLOR_TEST
    int color = 0;
    char a = 'a';
    do
    {
        a = _getch();
        gotoxy(1, 1);
        if (color <= BLACK)
        {
            color = WHITE;
        }
        textcolor(color);
        
        color--;
        if (color < 10)
            printf("ABCD = 0%d", color);
        if (color >= 10)
            printf("ABCD = %d", color);
        textbackground(color);
        gotoxy(1, 3);
        printf(" ");
        textbackground(BLACK);
    } while (a != 'q');
#endif
}

void Game()
{
    setvolume(music[10], highVOL);
    int looper = 0;
    score = Wave;
    hpBackUp = player.HP;
    lastScore = Wave;
    srand((unsigned int)time(NULL));
    exitFlag = false;
    update = true;
    win = false;
    player.life = true;
    bullet.life = false;
    enemy[0].life = false;
    enemy[1].life = false;
    enemy[2].life = false;
    enemy[0].HP = ENEMY_HP;
    enemy[1].HP = ENEMY_HP;
    enemy[2].HP = ENEMY_HP;
    enemyNumber = DEAD;
    player.HP = 3;
    player.x =
        player.lastX = X;
    player.y =
        player.lastY = Y;
    player.angle =
        player.lastAngle = ANGLE;
    timeBeginPeriod(1);

    EnemyCreate();

    playsound(music[4], 1);
    int lastTime = timeGetTime(), currentTime = 0;
    DisplayASCII(86, 21, GamePlay[0], 23, 88);

    while (!exitFlag)
    {
        currentTime = timeGetTime();
        if ((currentTime - lastTime) >= (1000 / 60))
        {
            looper++;
            lastTime = currentTime;
            EnemyCreate();
            Update();
            BulletUpdate();
            EnemyUpdate();
            Draw();
            BulletDraw();
            if (looper == 20 || !enemy[enemyNumber].life)
            {
                if (enemy[enemyNumber].life)
                {
                    EnemyDraw();
                    looper = 0;
                }
                else if (!enemy[enemyNumber].life)
                {
                    if (killer == 0)
                    {
                        EnemyDraw();
                        killer++;
                        looper = 0;
                    }
                }
            }
            if (!player.life)
            {
                gotoxy(81, 17);
                textbackground(BLACK);
                textcolor(LIGHTMAGENTA);
                printf("You Lose");
                EnterWait();
                StopAllSound();
                Lose();
                ScreenChange();
                exitFlag = true;
            }
            else if (win)
            {
                gotoxy(81, 17);
                textbackground(BLACK);
                textcolor(BLUE);
                printf("You  Win");
                EnterWait();
                if (ending == 1)
                {
                    StopAllSound();
                    Win();
                    ending++;
                }
                else
                {
                    StopAllSound();
                    EndingTwo();
                }
                exitFlag = true;
            }
        }
    }
    StopAllSound();
}

void AudioOpen()
{
    music[0] = opensound("MainMenu.mp3");
    music[1] = opensound("CutSceneLight.mp3");
    music[2] = opensound("CutSceneDark.mp3");
    music[3] = opensound("Knife.mp3");
    music[4] = opensound("Battle.mp3");
    music[5] = opensound("button.mp3");
    music[6] = opensound("damage.mp3");
    music[7] = opensound("death.mp3");
    music[8] = opensound("Win1.mp3");
    music[9] = opensound("Win2.mp3");
    music[10] = opensound("Bullet.mp3");
    music[11] = opensound("ENEMYAPPEAR.mp3");
    music[12] = opensound("Lose.mp3");
    music[13] = opensound("Quit.mp3");
}
void AudioVolume()
{
    setvolume(music[0], medVOL);
    setvolume(music[1], smallVOL);
    setvolume(music[2], smallVOL);
    setvolume(music[3], highVOL);
    setvolume(music[4], smallVOL);
    setvolume(music[5], medVOL);
    setvolume(music[6], medVOL);
    setvolume(music[7], medVOL);
    setvolume(music[8], smallVOL);
    setvolume(music[9], smallVOL);
    setvolume(music[10], highVOL);
    setvolume(music[11], medVOL);
    setvolume(music[12], medVOL);
    setvolume(music[13], smallVOL);
}
void AudioClose()
{
    for (int i = 0; i < SoundLimit; i++)
    {
        closesound(music[i]);
    }
}
void StopAllSound()
{
    for (int i = 0; i < SoundLimit; i++)
    {
        stopsound(music[i]);
    }
}

void Story()
{
    char b;
    bool press = false;
    ScreenChange();
    playsound(music[1], 1);
    DisplayASCII(49, 5, CutScene[0], 17, 68);//17,73
    EraseBox(170, 1, 171, 44);
#ifdef Video
    EraseBox(1, 35, 170, 43);
    EnterWait();
#endif
    sprintf(textBoxText, "�g�}�g : ���͂ǂ��ɂł����镁�ʂ̃g�}�g���C�����ŕ��}�ȓ��퐶���𑗂��Ă��邾����");
    TextBox(textBoxText, LIGHTRED);
    EnterWait();
    for (int i = 0; i < 300; i++)
        textBoxText[i] = ' ';
    sprintf(textBoxText, "�g�}�g : �����͂ǂ������āC����Ȃ̊ȒP���C�X�[�p�[�ȊO�ɂ��邩�I�I");
    TextBox(textBoxText, LIGHTRED);
    EnterWait();
    for (int i = 0; i < 300; i++)
        textBoxText[i] = ' ';
    sprintf(textBoxText, "�g�}�g : ���������ɂ��闝�R�͂�����C�������B��C�u��؂̊y���v�ƌĂ΂�Ă��郊�]�[�g�ɍs�����߂̓��ē�������C���ꂪ�l��");
    TextBox(textBoxText, LIGHTRED);
    EnterWait();
    for (int i = 0; i < 300; i++)
        textBoxText[i] = ' ';
    sprintf(textBoxText, "�g�}�g : �����āC���������I�΂���؂ƂȂ���");
    TextBox(textBoxText, LIGHTRED);
    EnterWait();
    for (int i = 0; i < 300; i++)
        textBoxText[i] = ' ';

    EraseBox(47, 3, 170, 30);

    DisplayASCII(1, 1, CutScene[1], 20, 147);
#ifdef Video
    EraseBox(1, 35, 170, 43);
    EnterWait();
#endif
    sprintf(textBoxText, "�g�}�g : ��������!!!�C���������]�[�g�C�X�Q�[�ȁC���O��͂ǂ��v��");
    TextBox(textBoxText, LIGHTRED);
    EnterWait();
    for (int i = 0; i < 300; i++)
        textBoxText[i] = ' ';
    sprintf(textBoxText, "�� : �����Ƃ��낾");
    TextBox(textBoxText, GREEN);
    EnterWait();
    for (int i = 0; i < 300; i++)
        textBoxText[i] = ' ';
    sprintf(textBoxText, "�֎q : �ԈႢ�Ȃ��y����");
    TextBox(textBoxText, CYAN);
    EnterWait();
    for (int i = 0; i < 300; i++)
        textBoxText[i] = ' ';
    sprintf(textBoxText, "�� : �������Ȃ�����C�����o�Ԃ�");
    TextBox(textBoxText, GREEN);
    EnterWait();
    for (int i = 0; i < 300; i++)
        textBoxText[i] = ' ';
    sprintf(textBoxText, "�g�}�g : �����܂����B");
    TextBox(textBoxText, LIGHTRED);
    EnterWait();
    for (int i = 0; i < 300; i++)
        textBoxText[i] = ' ';
    for (int i = 0; i < 3; i++)
    {
        if (i == 0)
            sprintf(textBoxText, "�B");
        else if (i == 1)
            sprintf(textBoxText, "�B�B");
        else if (i == 2)
            sprintf(textBoxText, "�B�B�B");
        TextBox(textBoxText, WHITE);
        EnterWait();
        for (int i = 0; i < 300; i++)
            textBoxText[i] = ' ';
    }
    stopsound(music[1]);
    DisplayASCII(150, 4, CutScene[2], 16, 15);
#ifdef Video
    EraseBox(1, 35, 170, 43);
    EnterWait();
#endif
    sprintf(textBoxText, "�g�}�g : ������Ƃ܂��āC����͉���");
    TextBox(textBoxText, LIGHTRED);
    EnterWait();
    playsound(music[2], 1);
    for (int i = 0; i < 300; i++)
        textBoxText[i] = ' ';
    sprintf(textBoxText, "�g�}�g : �������������C�����");
    TextBox(textBoxText, LIGHTRED);
    EnterWait();
    for (int i = 0; i < 300; i++)
        textBoxText[i] = ' ';

    DisplayASCII(1, 1, CutScene[3], 20, 147);
#ifdef Video
    EraseBox(1, 35, 170, 43);
    EnterWait();
#endif
    sprintf(textBoxText, "�� : ������C�����Ă˂����C��߂�C����������������������!�I�C�u���b�u���v");
    TextBox(textBoxText, GREEN);
    EnterWait();
    for (int i = 0; i < 300; i++)
        textBoxText[i] = ' ';


    EraseBox(150, 4, 166, 21);
    playsound(music[3], 0);
    DisplayASCII(1, 1, CutScene[4], 20, 152);
#ifdef Video
    EraseBox(1, 35, 170, 43);
    EnterWait();
#endif
    sprintf(textBoxText, "�g�}�g : �E���Ă��C��C�c�炸�C�쒀���Ă��");
    TextBox(textBoxText, RED);
    EnterWait();
    for (int i = 0; i < 300; i++)
        textBoxText[i] = ' ';

    EraseBox(1, 1, 153, 21);

    DisplayASCII(1, 1, CutScene[11], 34, 170);
#ifdef Video
    EraseBox(1, 35, 170, 43);
    EnterWait();
#endif
    sprintf(textBoxText, "�g�}�g : �������ɂ���l�Ԃ̐���");
    TextBox(textBoxText, RED);
    textbackground(BLACK);
    gotoxy(38, 40);
    printf("EASY");
    gotoxy(48, 40);
    printf("MEDIUM");
    gotoxy(60, 40);
    printf("HARD");
    gotoxy(37, 40);
    int selection = 1;
    int lastTime = timeGetTime(), currentTime = 0;
    bool selectUpdate = true;
    while (!press)
    {
        currentTime = timeGetTime();
        if ((currentTime - lastTime) >= 1000 / 60)
        {
            keyScan();
            if (selectUpdate)
            {
                if (selection == 1)
                {
                    Wave = 5;
                    gotoxy(46, 40);
                    printf("  ");
                    gotoxy(58, 40);
                    printf("  ");
                    gotoxy(36, 40);
                    printf(">>");
                }
                if (selection == 2)
                {
                    Wave = 15;
                    gotoxy(36, 40);
                    printf("  ");
                    gotoxy(58, 40);
                    printf("  ");
                    gotoxy(46, 40);
                    printf(">>");
                }
                if (selection == 3)
                {
                    Wave = 30;
                    gotoxy(36, 40);
                    printf("  ");
                    gotoxy(46, 40);
                    printf("  ");
                    gotoxy(58, 40);
                    printf(">>");
                }
                gotoxy(51, 38);
                printf("  ");
                gotoxy(51, 38);
                printf("%d", Wave);
                selectUpdate = false;
            }
            if (keyPush(PK_LEFT))
            {
                playsound(music[5], 0);
                if (selection >= 2)
                    selection--;
                selectUpdate = true;
            }
            if (keyPush(PK_RIGHT))
            {
                playsound(music[5], 0);
                if (selection < 3)
                    selection++;
                selectUpdate = true;
            }
            if (keyPush(PK_ENTER))
            {
                playsound(music[5], 0);
                press = true;
            }
        }
    }
    for (int i = 0; i < 300; i++)
        textBoxText[i] = ' ';

    sprintf(textBoxText, "�g�}�g : �ł��C����Ȃ̊֌W�Ȃ��C���̏�ɂ���S���𖕎E���邾����!!");
    TextBox(textBoxText, RED);
    EnterWait();
    for (int i = 0; i < 300; i++)
        textBoxText[i] = ' ';
    textcolor(WHITE);
    StopAllSound();
}
void Lose()
{
    ScreenChange();
    playsound(music[12], 0);
    DisplayASCII(28, 2, CutScene[5], 28, 114);
#ifdef Video
    EraseBox(1, 35, 170, 43);
    EnterWait();
#endif
    sprintf(textBoxText, "��������g�}�g�N�͖��c�ɐ������܂�܁C�^����ɐ؂��C�E���ꂽ");
    TextBox(textBoxText, WHITE);
    EnterWait();
    for (int i = 0; i < 300; i++)
        textBoxText[i] = ' ';
}
void TextBox(char text[300], int color)
{
    textcolor(LIGHTGRAY);
    textbackground(LIGHTGRAY);
    int startX = 1, startY = 35, endX = 170, endY = 43;
    for (int i = startX; i <= endX; i++)
    {
        gotoxy(i, startY);
        printf("_");
    }
    for (int i = startY; i <= endY; i++)
    {
        gotoxy(startX, i);
        printf("|");
    }
    for (int i = startX; i <= endX; i++)
    {
        gotoxy(i, endY);
        printf("_");
    }
    for (int i = startY; i <= endY; i++)
    {
        gotoxy(endX, i);
        printf("|");
    }
    textbackground(BLACK);
    EraseBox(startX + 1, startY + 1, endX - 1, endY - 1);
    int num = 0, y = 3;
    int length = strlen(text);
    if (length >= endX)
        y = 4;
    textcolor(color);
    for (int i = (startY + 3); i <= (startY + y); i++)
    {
        for (int j = (startX + 3); j < (endX - 3); j++)
        {
            gotoxy(j, i);
            if (i > (startY + 3))
                gotoxy(j, i + 1);
            printf("%c", text[num]);
            num++;
        }
    }
    textcolor(WHITE);
}
void EraseBox(int startX, int startY, int endX, int endY)
{
    for (int i = startY; i <= endY; i++)
    {
        for (int j = startX; j <= endX; j++)
        {
            gotoxy(j, i);
            printf(" ");
        }
    }
}
void Win()
{
    system("cls");
    playsound(music[8], 1);
    DisplayASCII(25, 1, CutScene[9], 34, 119);
#ifdef Video
    //EraseBox(1, 35, 170, 43);
    EnterWait();
#endif
    sprintf(textBoxText, "���܂Ȃ��ȁC�����܂ŕt�����킹�Ă������");
    TextBox(textBoxText, LIGHTRED);
    EnterWait();
    for (int i = 0; i < 300; i++)
        textBoxText[i] = ' ';
    sprintf(textBoxText, "���I�C�������C���O�ɂ����v���[���g������");
    TextBox(textBoxText, LIGHTRED);
    EnterWait();
    stopsound(music[8]);
    for (int i = 0; i < 300; i++)
        textBoxText[i] = ' ';
    playsound(music[9], 1);
    EraseBox(25, 1, 144, 34);
    
    DisplayASCII(25, 1, CutScene[7], 34, 119);
#ifdef Video
    EraseBox(1, 35, 170, 43);
    EnterWait();
#endif
    sprintf(textBoxText, "���˃b");
    TextBox(textBoxText, RED);
    for (int i = 0; i < 300; i++)
        textBoxText[i] = ' ';
    WaitFor(1);
    sprintf(textBoxText, "�͂̓n�n�n�n�n�͂��͂͂͂͂͂͂͂͂��͂͂͂͂́i�����j");
    TextBox(textBoxText, RED);
    
    WaitFor(0.8);
    for (int i = 0; i < 300; i++)
        textBoxText[i] = ' ';
    int x = 1, y = 1;
    int Tx, Ty;
    int counter = 44;
    do
    {
        if (counter >= 0)
        {
            Ty = y;
            for (int i = counter; i < 44; i++)
            {
                DisplayASCII_One_Line(x, Ty, CutScene[8], 169, i, 0, false);
                Ty++;
            }
            counter -= 6;
        }
    } while (counter >= 0);
    EnterWait();
    StopAllSound();
}
void EndingTwo()
{
    system("cls");
    playsound(music[8], 1);
    DisplayASCII(25, 1, CutScene[9], 34, 120);
#ifdef Video
    EraseBox(1, 35, 170, 43);
    EnterWait();
#endif
    sprintf(textBoxText, "���܂Ȃ��ȁC�����܂ŕt�����킹�Ă������");
    TextBox(textBoxText, LIGHTRED);
    EnterWait();
    for (int i = 0; i < 300; i++)
        textBoxText[i] = ' ';
    sprintf(textBoxText, "���I�C�������C���O�ɂ����v���[���g������");
    TextBox(textBoxText, LIGHTRED);
    EnterWait();
    stopsound(music[8]);
    for (int i = 0; i < 300; i++)
        textBoxText[i] = ' ';

    playsound(music[9], 1);
    EraseBox(25, 1, 144, 34);

    DisplayASCII(25, 1, CutScene[7], 34, 119);
#ifdef Video
    EraseBox(1, 35, 170, 43);
    EnterWait();
#endif
    sprintf(textBoxText, "���˃b");
    TextBox(textBoxText, RED);
    WaitFor(1);
    for (int i = 0; i < 300; i++)
        textBoxText[i] = ' ';
    sprintf(textBoxText, "�͂̓n�n�n�n�n�͂��͂͂͂͂͂͂͂͂��͂͂͂͂́i�����j");
    TextBox(textBoxText, RED);
    EnterWait();
    for (int i = 0; i < 300; i++)
        textBoxText[i] = ' ';

    ScreenChange();
    playsound(music[12], 0);
    DisplayASCII(10, 1, CutScene[12], 33, 149);
#ifdef Video
    EraseBox(1, 35, 170, 43);
    EnterWait();
#endif
    sprintf(textBoxText, "�v���[���[ : �������ȁC�g�}�g�ӂ������C���O���x�̂��ЂÂ��邱�Ƃ͛��ł��Ȃ�");
    TextBox(textBoxText, MAGENTA);
    EnterWait();
    for (int i = 0; i < 300; i++)
        textBoxText[i] = ' ';

    ScreenChange();

    DisplayASCII(28, 2, CutScene[5], 28, 114);
#ifdef Video
    EraseBox(1, 35, 170, 43);
    EnterWait();
#endif
    sprintf(textBoxText, "�g�}�g�N�͏���������ł������ǕԂ蓢���ɂ��킳��C���c�ɐ^����������I�I�I");
    TextBox(textBoxText, WHITE);
    EnterWait();
    for (int i = 0; i < 300; i++)
        textBoxText[i] = ' ';
}
void Quit()
{
    DisplayASCII(25, 1, CutScene[10], 34, 119);
#ifdef Video
    EraseBox(1, 35, 170, 43);
    EnterWait();
#endif
    sprintf(textBoxText, "�������͂��̓��C�������񂾁C�K�����Q������āC�ł�");
    TextBox(textBoxText, LIGHTRED);
    EnterWait();
    for (int i = 0; i < 300; i++)
        textBoxText[i] = ' ';
    sprintf(textBoxText, "�����C�����񂾁C���O�ɂ͑厖�ȉƑ����ł����C������");
    TextBox(textBoxText, LIGHTRED);
    EnterWait();
    for (int i = 0; i < 300; i++)
        textBoxText[i] = ' ';
    sprintf(textBoxText, "�T���i��");
    TextBox(textBoxText, WHITE);
    for (int i = 0; i < 300; i++)
        textBoxText[i] = ' ';
}

void RadiusCalculator()
{
    float x1, x2, x3, y1, y2, y3;//X = 18,19,13    Y = 8,7,8
    /*
    x1 = enemy[0].x + (enemyBreadth[0]/2);
    x2 = enemy[1].x + (enemyBreadth[1]/2);
    x3 = enemy[2].x + (enemyBreadth[2]/2);
    y1 = enemy[0].y + (enemyLength[0]/2);
    y2 = enemy[1].y + (enemyLength[1]/2);
    y3 = enemy[2].y + (enemyLength[2]/2);
    */
    x1 = 22;//enemy[0].x + 18;
    x2 = 22;//enemy[1].x + 19;
    x3 = 13;//enemy[2].x + 13;
    y1 = 8;//enemy[0].y + 8;
    y2 = 8;// enemy[1].y + 7;
    y3 = 8;// enemy[2].y + 8;
    RadiusLimit[0] = sqrt((x1 * x1) + (y1 * y1));
    RadiusLimit[1] = sqrt((x2 * x2) + (y2 * y2));
    RadiusLimit[2] = sqrt((x3 * x3) + (y3 * y3));

    enemyCenter[0].x = enemy[0].x + x1;
    enemyCenter[1].x = enemy[1].x + x2;
    enemyCenter[2].x = enemy[2].x + x3;

    enemyCenter[0].y = enemy[0].y + y1;
    enemyCenter[1].y = enemy[1].y + y2;
    enemyCenter[2].y = enemy[2].y + y3;

    /*x1 = enemy[0].x + 46;
    x2 = enemy[1].x + 54;
    x3 = enemy[2].x + 11;
    
    y1 = enemy[0].y + 9;
    y2 = enemy[1].y + 15;
    y3 = enemy[2].y + 17;

    enemyCenter[0].x = x1;
    enemyCenter[1].x = x2;
    enemyCenter[2].x = x3;

    enemyCenter[0].y = y1;
    enemyCenter[1].y = y2;
    enemyCenter[2].y = y3;*/

    for (int i = 0; i < 3; i++)
    {
        if (Radius[i] >= RadiusLimit[i])
            Radius[i] = RadiusLimit[i];
    }
}

void Update()
{
    keyScan();
    if (keyPush(PK_ESC))
    {
        exitFlag = true;
        return;
    }
    else if (keyPress(PK_LEFT))
    {
        update = true;
        player.angle -= ANGLE_SPEED;
        
        if (distance >= -1.0f)
        {
            player.x -= 0.15f;
            distance -= 0.15f;
        }
    }
    else if (keyPress(PK_RIGHT))
    {
        update = true;
        player.angle += ANGLE_SPEED;
        if (distance <= 5.0f)
        {
            player.x += 0.15f;
            distance += 0.15f;
        }
    }
    else if (keyPush(PK_SP) && bullet.life == false)
    {
        playsound(music[10], 0);
        bullet.x = 
        bullet.lastX = player.x;
        bullet.y =
        bullet.lastY = player.y;

        bullet.lastAngle =
        bullet.angle = player.angle;
        update = true;
        bullet.life = true;
    }
    if (keyPush(PK_ENTER) || score < lastScore)
    {
        for (int i = 0; i < 3; i++)
        {
            enemy[i].life = false;
            enemy[i].complete = false;
        }
        enemyNumber = DEAD;
    }
#ifdef QUITTER
    if (keyPush(PK_Q))
    {
        player.life = false;
    }
#endif

    if (player.angle >= ANGLE_LIMIT_RIGHT)
        player.angle = ANGLE_LIMIT_RIGHT;

    if (player.angle <= ANGLE_LIMIT_LEFT)
        player.angle = ANGLE_LIMIT_LEFT;

    if (player.HP <= 0)
    {
        player.life = false;
    }
    if (score <= 0)
    {
        win = true;
    }

}
void Draw()
{
    if (update)
    {
        for (float r = 0.0f; r < 10.0f; r += 1.0f)
        {
            Coordinates P;
            P.x = cosf(player.lastAngle) * r + player.lastX;
            P.y = (sinf(player.lastAngle) * r * 0.5f + (player.lastY * THREE_D) / THREE_D);
            int x, y;
            x = (int)(P.x + 0.5f);
            y = (int)(P.y + 0.5f);
            gotoxy(x, y);
            printf("  ");
        }
        textbackground(CYAN);
        for (float r = 0.0f; r < 10.0f; r += 1.0f)
        {
            Coordinates P;
            P.x = cosf(player.angle) * r + player.x;
            P.y = (sinf(player.angle) * r * 0.5f + (player.y * THREE_D) / THREE_D);
            int x, y;
#ifdef TEST
            textbackground(BLACK);
            textcolor(WHITE);
            gotoxy(1, 1);
            printf("\tPLAYER\nCos = %f\nSin = %f\nAngle = %f\nX = %f , Y = %f\n\nQ�Ŏ���\nSpace�őł�\nEsc�Ń��C�����j���[�ɖ߂�", cosf(player.angle), sinf(player.angle), player.angle, P.x, P.y);
            textbackground(CYAN);
#endif
            x = (int)(P.x + 0.5f);
            y = (int)(P.y + 0.5f);
            gotoxy(x, y);
            printf("  ");
        }
        textbackground(BLACK);
        player.lastX = player.x;
        player.lastY = player.y;
        player.lastAngle = player.angle;
        update = false;
    }
}

void BulletUpdate()
{
    if (bullet.life == false)
    {
        return;
    }

    bullet.x = bullet.lastX + cosf(bullet.angle) * BULLET_SPEED;
    bullet.y = bullet.lastY + sinf(bullet.angle) * BULLET_SPEED * 0.5f;
#ifdef TEST
    textbackground(BLACK);
    textcolor(WHITE);
    gotoxy(1, 6);
    printf("\n\n\n\n\n\tBULLET\nCos = %f\nSin = %f\nAngle = %f\nX = %f, Y = %f", cosf(bullet.angle), sinf(bullet.angle), bullet.angle, bullet.x, bullet.y);
#endif
    if (bullet.y <= 1.0f)
    {
        bullet.life = false;
        BulletErase();
    }
    if (bullet.x <= 1.0f)
    {
        bullet.life = false;
        BulletErase();
    }
    if (bullet.x >= 169.0f)
    {
        bullet.life = false;
        BulletErase();
    }
    if (bullet.y >= 43.0f)
    {
        bullet.life = false;
        BulletErase();
    }
    if (enemyNumber == DEAD)
    {
        return;
    }
    if (enemy[enemyNumber].life == false)
    {
        return;
    }
    RadiusCalculator();
    if (enemyNumber == 0)
    {
        enemy[enemyNumber].x;
    }
    float D;
    if (enemyNumber == 0)
    {
        D = Collision(-countSide - 20 + enemyBreadth[enemyNumber], enemy[enemyNumber].y, bullet.x, bullet.y);
    }
    else if (enemyNumber == 1)
    {
        D = Collision(enemy[enemyNumber].x + 22, (enemyLength[enemyNumber] - count - 8), bullet.x, bullet.y);
    }
    else if (enemyNumber == 2)
    {
        D = Collision(enemy[enemyNumber].x + 25, (enemyLength[enemyNumber] - count - 9), bullet.x, bullet.y);
    }
    //D = Collision(enemyCenter[enemyNumber].x, enemyCenter[enemyNumber].y, bullet.x, bullet.y);
    if (D <= Radius[enemyNumber])
    {
        if (enemy[enemyNumber].HP >= 2)
            playsound(music[6], 0);
        BulletErase();
        bullet.life = false;
        enemy[enemyNumber].HP--;
    }
}
void BulletDraw()
{
    if (bullet.life == false)
    {
        return;
    }
    BulletErase();
    BulletPlot();
    bullet.lastAngle = bullet.angle;
    bullet.lastX = bullet.x;
    bullet.lastY = bullet.y;
    update = true;
}
void BulletErase()
{
    Coordinates B;
    B.x = bullet.lastX;
    B.y = bullet.lastY;
    int x, y;
    x = (int)(B.x + 0.5f);
    y = (int)(B.y + 0.5f);
    gotoxy(x, y);
    textbackground(BLACK);
    printf("  ");
}
void BulletPlot()
{
    Coordinates B;
    B.x = bullet.x;
    B.y = bullet.y;
    int x, y;
    x = (int)(B.x + 0.5f);
    y = (int)(B.y + 0.5f);
    gotoxy(x, y);
    textbackground(GREEN);
    printf("^^");
    textbackground(BLACK);
}

void EnemyCreate()
{
    for (int i = 0; i < 3; i++)
    {
        if (enemy[i].life == true)
        {
            enemyCounter = 1;
            return;
        }
    }
    if (enemyNumber == DEAD)
    {
        enemyNumber = rand() % 3;
        killer = 0;
        enemy[enemyNumber].life = true;
        lastScore = score;
        playsound(music[11], 0);
    }
    if (enemyNumber == 0)
    {
        enemy[enemyNumber].x =
            enemy[enemyNumber].lastX = 1.0f;
        enemy[enemyNumber].y =
            enemy[enemyNumber].lastY = 10.0f; 
    }
    else if (enemyNumber == 1)
    {
        enemy[enemyNumber].x =
            enemy[enemyNumber].lastX = 25.0f;
        enemy[enemyNumber].y =
            enemy[enemyNumber].lastY = 1.0f;
    }
    else if (enemyNumber == 2)
    {
        enemy[enemyNumber].x =
            enemy[enemyNumber].lastX = 100.0f;
        enemy[enemyNumber].y =
            enemy[enemyNumber].lastY = 1.0f;
    }

    enemy[enemyNumber].angle =
        enemy[enemyNumber].lastAngle = PlayerPointCalculator(enemy[enemyNumber].x, enemy[enemyNumber].y);
    count = enemyLength[enemyNumber];
    countSide = enemyBreadth[enemyNumber];
}
void EnemyUpdate()
{
    if (enemyNumber == DEAD)
    {
        return;
    }
    if (enemy[enemyNumber].life == false)
    {
        if (enemyCounter <= 1)
        {
            playsound(music[7], 0);
            Radius[enemyNumber] = 1;
            /*if (enemyNumber == 0)
            {
                for (int i = countSide; i <= enemyBreadth[enemyNumber]; i++)
                {
                    for (int j = 0; j <= enemyLength[enemyNumber]; j++)
                    {
                        DisplayASCII_One_Line(enemy[enemyNumber].x, enemy[enemyNumber].y + j, GamePlay[4], enemyBreadth[enemyNumber] - 1, i, j, true);
                    }
                }
            }
            else if (enemyNumber == 1)
                DisplayASCII(finalX[enemyNumber], finalY[enemyNumber] - enemyLength[enemyNumber], GamePlay[4], enemyLength[enemyNumber] - count, enemyBreadth[enemyNumber]);
            else if (enemyNumber == 2)
                DisplayASCII(finalX[enemyNumber], finalY[enemyNumber] - enemyLength[enemyNumber], GamePlay[4], enemyLength[enemyNumber] - count, enemyBreadth[enemyNumber]);

            EnterWait();//WaitFor(1);*/
            BulletErase();
            WaitFor(0.2);
            EraseBox(enemy[enemyNumber].x, enemy[enemyNumber].y, (enemy[enemyNumber].x + enemyBreadth[enemyNumber] + 25), (enemy[enemyNumber].y + enemyLength[enemyNumber] + 3));
            enemyCounter++;
            enemy[enemyNumber].HP = ENEMY_HP;
            if (player.HP == 3)
            {
                DisplayASCII(86, 21, GamePlay[0], 23, 88);
            }
            else
            {
                DisplayASCII(86, 21, TomatoeLife[player.HP], 23, 88);
            }
            Radius[enemyNumber] = 1;
            score--;
        }
        return;
    }
    if (enemy[enemyNumber].HP <= 0)
    {
        enemy[enemyNumber].life = false;
    }
    if (enemy[enemyNumber].complete == false)
    {
        if (enemyNumber == 1 || enemyNumber == 2)
        {
            enemy[enemyNumber].x = enemy[enemyNumber].lastX + cosf(enemy[enemyNumber].angle) * ENEMY_SPEED;
        }
        else if (enemyNumber == 0)
        {
            enemy[enemyNumber].y = enemy[enemyNumber].lastY + sinf(enemy[enemyNumber].angle) * ENEMY_SPEED * 0.5f;
        }
    }
    else if (enemy[enemyNumber].complete == true)
    {
        enemy[enemyNumber].x = enemy[enemyNumber].x + cosf(enemy[enemyNumber].angle) * ENEMY_SPEED;
        enemy[enemyNumber].y = enemy[enemyNumber].y + sinf(enemy[enemyNumber].angle) * ENEMY_SPEED * 0.5f;
    }
    /*if (enemy[enemyNumber].y + enemyLength[enemyNumber] > 44)
    {
        EraseBox(enemy[enemyNumber].x, enemy[enemyNumber].y, (enemy[enemyNumber].x + enemyBreadth[enemyNumber] + 6), (enemy[enemyNumber].y + enemyLength[enemyNumber] + 1));
    }
    if (enemy[enemyNumber].x + enemyBreadth[enemyNumber] > 170)
    {
        EraseBox(enemy[enemyNumber].x, enemy[enemyNumber].y, (enemy[enemyNumber].x + enemyBreadth[enemyNumber] + 6), (enemy[enemyNumber].y + enemyLength[enemyNumber] + 1));
    }*/
    float x, y, D;
    if (enemyNumber == 0)
    {
        x = 95 - (enemyBreadth[enemyNumber] - countSide);
        y = 24 - enemy[enemyNumber].y;
        D = sqrt((x * x) + (y * y));
        if (D <= 15)
        {
            stopsound(music[7]);
            playsound(music[3], 0);
            player.HP--;
            EraseBox(-countSide - 2, enemy[enemyNumber].y, (enemyBreadth[enemyNumber] - countSide - 2), (enemy[enemyNumber].y + enemyLength[enemyNumber]));
            enemy[enemyNumber].life = false;
            DisplayASCII(86, 21, TomatoeLife[player.HP], 23, 88);
            countSide = enemyBreadth[enemyNumber];
            killer = 1;
        }
    }
    if (enemyNumber == 1)
    {
        x = 93 - enemy[enemyNumber].x;
        y = 29 - (enemyLength[enemyNumber] - count);
        D = sqrt((x * x) + (y * y));
        if (D <= 57)
        {
            stopsound(music[7]);
            playsound(music[3], 0);
            player.HP--;
            EraseBox(enemy[enemyNumber].x, -count - 2, (enemy[enemyNumber].x + enemyBreadth[enemyNumber] + 6), (enemyLength[enemyNumber] - count - 2));
            enemy[enemyNumber].life = false;
            DisplayASCII(86, 21, TomatoeLife[player.HP], 23, 88);
            count = enemyLength[enemyNumber];
            killer = 2;
        }
    }
    if (enemyNumber == 2)
    {
        x = 93 - enemy[enemyNumber].x;
        y = 25 - (enemyLength[enemyNumber] - count);
        D = sqrt((x * x) + (y * y));
        if (D <= 12)
        {
            stopsound(music[7]);
            playsound(music[3], 0);
            player.HP--;
            EraseBox(enemy[enemyNumber].x, -count - 2, (enemy[enemyNumber].x + enemyBreadth[enemyNumber] + 6), (enemyLength[enemyNumber] - count - 2));
            enemy[enemyNumber].life = false;
            DisplayASCII(86, 21, TomatoeLife[player.HP], 23, 88);
            count = enemyLength[enemyNumber];
            killer = 3;
        }
    }


}
void EnemyDraw()
{
    if (enemyNumber == DEAD)
    {
        return;
    }
    bool down = true;
    if (enemyNumber == 1 || enemyNumber == 2)
    {
        down = true;
    }
    else if (enemyNumber == 0)
    {
        down = false;
    }
    EnemyAnimation(enemy[enemyNumber].x, enemy[enemyNumber].y, enemyLength[enemyNumber], enemyBreadth[enemyNumber], down);

    enemy[enemyNumber].lastX = enemy[enemyNumber].x;
    enemy[enemyNumber].lastY = enemy[enemyNumber].y;
    enemy[enemyNumber].lastAngle = enemy[enemyNumber].angle;
}
void EnemyAnimation(float x, float y, int length, int breadth, bool down)
{
    int DX = (int)(x + 0.5f);
    int DY = (int)(y + 0.5f);
    int Cx = enemy[enemyNumber].x, Cy = enemy[enemyNumber].y;
    char blank[100] = "                                                                        ";
    if (enemy[enemyNumber].complete == false)
    {
        if (!down)
        {
            if (countSide != 0)
            {
                Cx = DX;
                for (int i = countSide; i <= breadth; i++)
                {
                    for (int j = 0; j <= length; j++)
                    {
                        if (enemy[enemyNumber].life == true)
                            DisplayASCII_One_Line(Cx, (DY + j), GamePlay[enemyNumber + 1], enemyBreadth[enemyNumber] - 1, j, i, true);
                        else
                            DisplayASCII_One_Line(Cx, (DY + j), GamePlay[enemyNumber + 4], enemyBreadth[enemyNumber] - 1, j, i, true);
                    }
                    Cx++;
                }
                //if (Radius[enemyNumber] <= RadiusLimit[enemyNumber])
                {
                    Radius[enemyNumber] = Radius[enemyNumber] + ENEMY_SPEED_LEFT;
                }
                countSide -= ENEMY_SPEED_LEFT;
            }
            else
            {
                if (Radius[enemyNumber] <= RadiusLimit[enemyNumber])
                {
                    Radius[enemyNumber] = RadiusLimit[enemyNumber];
                }
                enemy[enemyNumber].complete = true;
            }
        }
        else if (down)
        {
            if (count != 0)
            {
                Cy = DY;
                for (int i = count; i <= length; i++)
                {
                    if (enemy[enemyNumber].life == true)
                        DisplayASCII_One_Line(DX, Cy, GamePlay[enemyNumber + 1], enemyBreadth[enemyNumber], i, 0, false);
                    else
                        DisplayASCII_One_Line(DX, Cy, GamePlay[enemyNumber + 4], enemyBreadth[enemyNumber], i, 0, false);
                    Cy++;
                }
                //if (Radius[enemyNumber] <= RadiusLimit[enemyNumber])
                {
                    Radius[enemyNumber] = Radius[enemyNumber] + ENEMY_SPEED_TOP;
                }
                count -= ENEMY_SPEED_TOP;
            }
            else
            {
                enemy[enemyNumber].complete = true;
            }
        }
        finalX[enemyNumber] = Cx;
        finalY[enemyNumber] = Cy;
    }
    else if (enemy[enemyNumber].complete == true)
    {
        if (!down)
        {

        }
        else if (down)
        {
            Cy = DY - enemy[enemyNumber].lastY;
            textbackground(BLACK);
            for (int i = Cy; i < DY; i++)
            {
                gotoxy(DX + i, Cy);
                printf("%s", blank);
            }
            Cy = DY;
            for (int i = 0; i <= length; i++)
            {
                DisplayASCII_One_Line(DX, Cy, GamePlay[enemyNumber + 1], enemyBreadth[enemyNumber], i, 0, false);
                Cy++;
            }
        }
    }
}

int PlayerPointCalculator(float x, float y)
{
    float l, b, h, cos, sin, angle = 0.0f;
    b = player.x - x;
    l = player.y - y;
    h = sqrt((l * l) + (b * b));
    cos = b / h;
    sin = l / h;
    cos = acos(cos);
    sin = asin(sin);
    angle = cos;
    return angle;
}

float Collision(float x1, float y1, float x2, float y2)
{
    Coordinates distance;
    float H;
    distance.x = (x2 - x1);
    distance.y = (y2 - y1);
    H = sqrt(distance.x * distance.x + distance.y * distance.y);
    return H;
}

void WaitFor(float timerLimit)
{
    bool exit = false;
    float lastTime = timeGetTime(), currentTime = 0, frameCount = 0, secondCount = 0;
    while (!exit)
    {
        currentTime = timeGetTime();
        if ((currentTime - lastTime) >= (1000 / 60))
        {
            lastTime = currentTime;
            frameCount++;
            if (frameCount == 6)
            {
                secondCount += 0.1;
                frameCount = 0;
            }
            if (secondCount >= timerLimit)
            {
                exit = true;
            }
        }
    }
}
void ScreenChange()
{
    for (int i = 1; i <= 44; i++)
    {
        for (int j = 1; j <= 170; j++)
        {
            gotoxy(j, i);
            printf(" ");
        }
    }
}
int Selection()
{
    playsound(music[0], 1);
    DisplayASCII(1, 1, CutScene[6], 38, 152);
    textcolor(MAGENTA);
    textbackground(BLACK);
    for (int i = 0; i <= 7; i++)
    {
        for (int j = 0; j <= 100; j++)
        {
            if (CutScene[13][i][j] == ' ')
                continue;
            else if (CutScene[13][i][j] == '&')
                textbackground(MAGENTA);
            else
                textbackground(BLACK);
            gotoxy(34 + j, 1 + i);
            printf("%c", CutScene[13][i][j]);
        }
    }
    bool selectUpdate = true, end = false;
    int selectX = 125, selectY = 30;
    int lastTime = timeGetTime(), currentTime = 0;
    textcolor(WHITE);
    textbackground(BLACK);
    int selection = 1;
    gotoxy(selectX, selectY);
    printf("START");
    gotoxy(selectX, selectY + 2);
    printf("STORY SKIP");
    gotoxy(selectX, selectY + 4);
    printf("EXIT");
    gotoxy(1, 1);
    while(!end)
    {
        currentTime = timeGetTime();
        if ((currentTime - lastTime) >= 1000 / 60)
        {
            keyScan();
            if (selectUpdate)
            {
                if (selection == 1)
                {
                    gotoxy(wherex() - 2, wherey());
                    printf("  ");
                    gotoxy(selectX - 2, selectY);
                    printf(">>");
                }
                if (selection == 2)
                {
                    gotoxy(wherex() - 2, wherey());
                    printf("  ");
                    gotoxy(selectX - 2, selectY + 2);
                    printf(">>");
                }
                if (selection == 3)
                {
                    gotoxy(wherex() - 2, wherey());
                    printf("  ");
                    gotoxy(selectX - 2, selectY + 4);
                    printf(">>");
                }
                selectUpdate = false;
            }
            if (keyPush(PK_UP))
            {
                playsound(music[5], 0);
                if (selection >= 2)
                    selection--;
                selectUpdate = true;
            }
            if (keyPush(PK_DOWN))
            {
                playsound(music[5], 0);
                if (selection < 3)
                    selection++;
                selectUpdate = true;
            }
            if (keyPush(PK_ENTER))
            {
                playsound(music[5], 0);
                end = true;
            }
        }
    }
    return selection--;
    ScreenChange();
    stopsound(music[0]);
}

char ButtonPress()
{
    playsound(music[5], 0);
    char a = _getch();
    rewind(stdin);
    return a;
}
void EnterWait()
{
    bool con = false;
    do
    {
        keyScan();
        if (keyPush(PK_ENTER))
        {
            playsound(music[5], 0);
            con = true;
        }
    } while (!con);
}

void DisplayASCII(int x, int y, char ASCII_Art[50][200], int height, int breadth)
{
    for (int i = 0; i <= height; i++)
    {
        for (int j = 0; j <= breadth; j++)
        {
            bool blank = false;
            if (ASCII_Art[i][j] == ' ')
            {
                textbackground(BLACK);
                blank = true;
            }
            else if (ASCII_Art[i][j] == '1')
            {
                textbackground(BLACK);
                textcolor(BLACK);
            }
            else if (ASCII_Art[i][j] == '!')
            {
                textcolor(GREEN);
                textbackground(GREEN);
            }
            else if (ASCII_Art[i][j] == '#')
            {
                textcolor(RED);
                textbackground(RED);
            }
            else if (ASCII_Art[i][j] == '@')
            {
                textcolor(BLACK);
                textbackground(BLACK);
            }
            else if (ASCII_Art[i][j] == '&')
            {
                textcolor(BLUE);
                textbackground(BLUE);
            }
            else if (ASCII_Art[i][j] == '_')
            {
                textcolor(BROWN);
                textbackground(BROWN);
            }
            else if (ASCII_Art[i][j] == '.')
            {
                textcolor(LIGHTGRAY);
                textbackground(LIGHTGRAY);
            }
            else if (ASCII_Art[i][j] == '*')
            {
                textcolor(CYAN);
                textbackground(CYAN);
            }
            else if (ASCII_Art[i][j] == '-')
            {
                textcolor(MAGENTA);
                textbackground(MAGENTA);
            }
            else if (ASCII_Art[i][j] == '?')
            {
                break;
                break;
            }
            if (blank == false)
            {
                gotoxy(x + j, y + i);
                printf("%c", ASCII_Art[i][j]);
            }
            else
            {
                continue;
            }
        }
    }
    textbackground(BLACK);
    textcolor(BLACK);
}
void DisplayASCII_One_Line(int x, int y, char ASCII_Art[50][200], int breadth, int i, int n, bool dot)
{
    if (!dot)
    {
        for (int j = 0; j <= breadth; j++)
        {
            bool blank = false;
            if (ASCII_Art[i][j] == ' ')
            {
                textbackground(BLACK);
                blank = true;
            }
            else if (ASCII_Art[i][j] == '1')
            {
                textbackground(BLACK);
                textcolor(BLACK);
            }
            else if (ASCII_Art[i][j] == '!')
            {
                textcolor(GREEN);
                textbackground(GREEN);
            }
            else if (ASCII_Art[i][j] == '#')
            {
                textcolor(RED);
                textbackground(RED);
            }
            else if (ASCII_Art[i][j] == '@')
            {
                textcolor(BLACK);
                textbackground(BLACK);
            }
            else if (ASCII_Art[i][j] == '&')
            {
                textcolor(BLUE);
                textbackground(BLUE);
            }
            else if (ASCII_Art[i][j] == '_')
            {
                textcolor(BROWN);
                textbackground(BROWN);
            }
            else if (ASCII_Art[i][j] == '.')
            {
                textcolor(LIGHTGRAY);
                textbackground(LIGHTGRAY);
            }
            else if (ASCII_Art[i][j] == '*')
            {
                textcolor(CYAN);
                textbackground(CYAN);
            }
            else if (ASCII_Art[i][j] == '-')
            {
                textcolor(MAGENTA);
                textbackground(MAGENTA);
            }
            else if (ASCII_Art[i][j] == '?')
            {
                break;
                break;
            }
            if (blank == false)
            {
                gotoxy(x + j, y);
                printf("%c", ASCII_Art[i][j]);
            }
            else
            {
                continue;
            }
        }
    }
    else if (dot)
    {
        bool blank = false;
        if (ASCII_Art[i][n] == ' ')
        {
            textbackground(BLACK);
            blank = true;
        }
        else if (ASCII_Art[i][n] == '1')
        {
            textbackground(BLACK);
            textcolor(BLACK);
        }
        else if (ASCII_Art[i][n] == '!')
        {
            textcolor(GREEN);
            textbackground(GREEN);
        }
        else if (ASCII_Art[i][n] == '#')
        {
            textcolor(RED);
            textbackground(RED);
        }
        else if (ASCII_Art[i][n] == '@')
        {
            textcolor(BLACK);
            textbackground(BLACK);
        }
        else if (ASCII_Art[i][n] == '&')
        {
            textcolor(BLUE);
            textbackground(BLUE);
        }
        else if (ASCII_Art[i][n] == '_')
        {
            textcolor(BROWN);
            textbackground(BROWN);
        }
        else if (ASCII_Art[i][n] == '.')
        {
            textcolor(LIGHTGRAY);
            textbackground(LIGHTGRAY);
        }
        else if (ASCII_Art[i][n] == '*')
        {
            textcolor(CYAN);
            textbackground(CYAN);
        }
        else if (ASCII_Art[i][n] == '-')
        {
            textcolor(MAGENTA);
            textbackground(MAGENTA);
        }
        if (blank == false)
        {
            gotoxy(x, y);
            printf("%c", ASCII_Art[i][n]);
        }
        else
        {
            return;
        }
    }
}

void ASCII()
{
    sprintf(CutScene[0][0],  "         _____________________________________________________________");
    sprintf(CutScene[0][1],  "     ____________________________________________________________     ");
    sprintf(CutScene[0][2],  " ___________________________________________________________          ");
    sprintf(CutScene[0][3],  "                                                                      ");
    sprintf(CutScene[0][4],  "                       !!!!!!!!!   !!!   !!!!!!                       ");
    sprintf(CutScene[0][5],  "                   ###########!!!!!!!!!!!!#######                     ");
    sprintf(CutScene[0][6],  "                ########!!!!!!!!#####!!!!!!!!!!!!###                  ");
    sprintf(CutScene[0][7],  "              ########################################                ");
    sprintf(CutScene[0][8],  "             #####......##################......#######               ");
    sprintf(CutScene[0][9],  "            ######..@@@..################..@@@..########              ");
    sprintf(CutScene[0][10], "            ######..@@@..################..@@@..########              ");
    sprintf(CutScene[0][11], "            #######..@@..################..@@..#########              ");
    sprintf(CutScene[0][12], "             ########...##################...##########               ");
    sprintf(CutScene[0][13], "              ############@@#########@@###############                ");
    sprintf(CutScene[0][14], "               ############@@@@@@@@@@@###############                 ");
    sprintf(CutScene[0][15], "          ________################################____________________");
    sprintf(CutScene[0][16], "     __________________######################_____________________    ");
    sprintf(CutScene[0][17], "_____________________________________________________________         ");


    sprintf(CutScene[1][0],  "      !                                                                                                                     ___                    ");
    sprintf(CutScene[1][1],  "     !!!                                                                                                                    ___                    ");
    sprintf(CutScene[1][2],  "  !!!!!!!!!                                          !!!!!!!!!!                !!!!!!                                    !!!___!!!                 ");
    sprintf(CutScene[1][3],  "  !&&!&&!&&!                                        #######!!!!!!!!!!!!!!!!!!!!!!!###                                  !!!!!___!!!!!               ");
    sprintf(CutScene[1][4],  " &&&&&&&&&&&&                                   ############!!!!!!!!##!!!!!!!############                             !!!!!!!_!!!!!!!              ");
    sprintf(CutScene[1][5],  " &&&&&&&&&&&&&                                ########!!!!!!!!!##########!!!!!!!!!#########                          !!!!!!!!!!!!!!!!!             ");
    sprintf(CutScene[1][6],  " &&....&&....&&                             ###################################!!!!!#########                    !!!!!!!!!!!!!!!!!!!!!!!!!         ");
    sprintf(CutScene[1][7],  " &&.@@..&&.@@..&                           #######......########################......########                !!!!!!!!!!!!!!!!!!!!!!!....!!!!      ");
    sprintf(CutScene[1][8],  " &&..@@.&&..@@.&&&                        #######...@@@...####################...@@@...########             !!!!.........!!!!!!!!!.........!!!!    ");
    sprintf(CutScene[1][9],  " &&&..@.&&&..@.&&&&                       ########...@@@...##################...@@@...#########            !!!!....@@@@....!!!!!!....@@@....!!!!   ");
    sprintf(CutScene[1][10], " &&&&...&&&&...&&&&&&&&&&                 #########..@@@..####################..@@@..##########           !!!!....@@@@@@....!!!!....@@@@....!!!!!  ");
    sprintf(CutScene[1][11], " &&&&&&&&&&&&&&&&&&&&&&&&&&&&&            ##########.....######################.....###########          !!!!!.....@@@@...!!!!!!....@@@...!!!!!!!! ");
    sprintf(CutScene[1][12], " &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&          ###################################################           !!!!!!!!.......!!!!!!!!!!......!!!!!!!!!! ");
    sprintf(CutScene[1][13], "  &&&&&&&&&&&&&&&&&&&&&&&&&&&@@&&&          #################################################            !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! ");
    sprintf(CutScene[1][14], "   &&&&&&&&&&&&&&&&&&&&&&&&&&@@&&&&          #################@@#########@@#################             !!!!!!!!!@@!!!!!!!!!!!!!!!!!!@@!!!!!!!!!! ");
    sprintf(CutScene[1][15], "    &&&&&&&&&&&&&&&&&&&&&&&&@@&&&&&           #################@@@@@@@@@@@################                !!!!!!!!@@!!!!!!!!!!!!!!!!!!@@!!!!!!!!!  ");
    sprintf(CutScene[1][16], "     &&&&&&&&&&&&&&&&&&&&&&@@&&&&&&             #######################################                    !!@@@@@@@!!!!!!!!!!!!!!!!!!@@@@@@@!!!   ");
    sprintf(CutScene[1][17], "      &&&&&@@&&&&&&&&&&&@@@&&&&&&&                 ################################                         !!!!!!!@@!!!!!!!!!!!!!!!@@!!!!!!!!!    ");
    sprintf(CutScene[1][18], "        &&&&&@@@@@@@@@@@@&&&&&&&                                                                             !!!!!!!!@@@@@@@@@@@@@@@!!!!!!!!!!     ");
    sprintf(CutScene[1][19], "           &&&&&&&&&&&&&&&&&&                                                                                  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!       ");
    sprintf(CutScene[1][20], "                                                                                                                   !!!!!!!!!!!!!!!!!!!!!           ");


    
    sprintf(CutScene[2][0],  ".              ");
    sprintf(CutScene[2][1],  "..             ");
    sprintf(CutScene[2][2],  "...            ");
    sprintf(CutScene[2][3],  "....           ");
    sprintf(CutScene[2][4],  ".....          ");
    sprintf(CutScene[2][5],  "......         ");
    sprintf(CutScene[2][6],  ".......        ");
    sprintf(CutScene[2][7],  "........       ");
    sprintf(CutScene[2][8],  ".........      ");
    sprintf(CutScene[2][9],  "..........     ");
    sprintf(CutScene[2][10], "...........    ");
    sprintf(CutScene[2][11], "............   ");
    sprintf(CutScene[2][12], " .........&&   ");
    sprintf(CutScene[2][13], "   ......&&&&  ");
    sprintf(CutScene[2][14], "          &&&& ");
    sprintf(CutScene[2][15], "           &&&&");
    sprintf(CutScene[2][16], "            &&&");

    sprintf(CutScene[3][0],  "      !                                                                                                                     ___                    ");
    sprintf(CutScene[3][1],  "     !!!                                                                                                                    ___                    ");
    sprintf(CutScene[3][2],  "  !!!!!!!!!                                          !!!!!!!!!!                !!!!!!                                    !!!___!!!                 ");
    sprintf(CutScene[3][3],  "  !&&!&&!&&!                                        #######!!!!!!!!!!!!!!!!!!!!!!!###                                  !!!!!___!!!!!               ");
    sprintf(CutScene[3][4],  " &&&&&&&&&&&&                                   ############!!!!!!!!##!!!!!!!############                             !!!!!!!_!!!!!!!              ");
    sprintf(CutScene[3][5],  " &&&&&&&&&&&&&                                ########!!!!!!!!!##########!!!!!!!!!#########                          !!!!!!!!!!!!!!!!!             ");
    sprintf(CutScene[3][6],  " &&....&&....&&                             ###################################!!!!!#########                    !!!!!!!!!!!!!!!!!!!!!!!!!         ");
    sprintf(CutScene[3][7],  " &&.@@..&&.@@..&                           #######......########################......########                !!!!......!!!!!!!!!!......!!!!!      ");
    sprintf(CutScene[3][8],  " &&..@@.&&..@@.&&&                        #######...@@@...####################...@@@...########             !!!!!....@@@!!!!!!!!!....@@@!!!!!!!!   ");
    sprintf(CutScene[3][9],  " &&&..@.&&&..@.&&&&                       ########...@@@...##################...@@@...#########            !!!!!.....@@@@!!!!!!!.....@@@@!!!!!!!!  ");
    sprintf(CutScene[3][10], " &&&&...&&&&...&&&&&&&&&&                 #########..@@@..####################..@@@..##########           !!!!!......@@@@@!!!!!......@@@@@!!!!!!!  ");
    sprintf(CutScene[3][11], " &&&&&&&&&&&&&&&&&&&&&&&&&&&&&            ##########.....######################.....###########          !!!!!!!......@@@@!!!!!!......@@@@!!!!!!!! ");
    sprintf(CutScene[3][12], " &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&          ###################################################           !!!!!!!!........!!!!!!!!!........!!!!!!!! ");
    sprintf(CutScene[3][13], "  &&&&&&&&&&&&&&&&&&&&&&&&&&&@@&&&          #################################################            !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! ");
    sprintf(CutScene[3][14], "   &&&&&&&&&&&&&&&&&&&&&&&&&&@@&&&&          #################@@#########@@#################             !!!!!!!!!!!!!!!!@@@@@@@@!!!!!!!!!!!!!!!!! ");
    sprintf(CutScene[3][15], "    &&&&&&&&&&&&&&&&&&&&&&&&@@&&&&&           #################@@@@@@@@@@@################                !!!!!!!!!!!!!@@@@@@@@@@@@!!!!!!!!!!!!!!  ");
    sprintf(CutScene[3][16], "     &&&&&&&&&&&&&&&&&&&&&&@@&&&&&&             #######################################                    !!!!!!!!!!!@@@@@@@@@@@@@@!!!!!!!!!!!!   ");
    sprintf(CutScene[3][17], "      &&&&&@@&&&&&&&&&&&@@@&&&&&&&                 ################################                         !!!!!!!!!@@@@@@@@@@@@@@@@!!!!!!!!!!    ");
    sprintf(CutScene[3][18], "        &&&&&@@@@@@@@@@@@&&&&&&&                                                                             !!!!!!!!@@@@@@@@@@@@@@@@!!!!!!!!!     ");
    sprintf(CutScene[3][19], "           &&&&&&&&&&&&&&&&&&                                                                                  !!!!!!@@!!!!!!!!!!!!@@!!!!!!!       ");
    sprintf(CutScene[3][20], "                                                                                                                   !!!!!!!!!!!!!!!!!!!!!           ");
    

    sprintf(CutScene[4][0],  "      !                                                                                                                     ___                         ");
    sprintf(CutScene[4][1],  "     !!!                                                                                                                    ___                         ");
    sprintf(CutScene[4][2],  "  !!!!!!!!!                                          !!!!!!!!!!                !!!!!!                                    !!!___!!!                      ");
    sprintf(CutScene[4][3],  "  !&&!&&!&&!                                        #######!!!!!!!!!!!!!!!!!!!!!!!###                                  !!!!!___!!!!!                    ");
    sprintf(CutScene[4][4],  " &&&&&&&&&&&&                                   ############!!!!!!!!##!!!!!!!############                             !!!!!!!_!!!!!*@@@@!!              ");
    sprintf(CutScene[4][5],  " &&&&&&&&&&&&&                                ########!!!!!!!!!##########!!!!!!!!!#########                          !!!!!!!!!!!!!*@@@@!!!!             ");
    sprintf(CutScene[4][6],  " &&....&&....&&                             ###################################!!!!!#########                    !!!!!!!!!!!!!!!!!*@@@@!!!!!!!!         ");
    sprintf(CutScene[4][7],  " &&...@@&&...@@&                           ########.@@####################@@.##################                !!!!......!!!!!!!!!**@@@!......!!!!!      ");
    sprintf(CutScene[4][8],  " &&...@@&&...@@&&&                        #########.@@@@################@@@@.##################             !!!!!....@@@!!!!!!!!***@@!....@@@!!!!!!!!   ");
    sprintf(CutScene[4][9],  " &&&...@&&&...@&&&&                       #########.@@@@@@############@@@@@@.##################            !!!!!.....@@@@!!!!!!***@@!.....@@@@!!!!!!!!  ");
    sprintf(CutScene[4][10], " &&&&...&&&&...&&&&&&&&&&                 #########.@@@@@.############.@@@@@.##################           !!!!!......@@@@@!!!!***@@!......@@@@@!!!!!!!  ");
    sprintf(CutScene[4][11], " &&&&&&&&&&&&&&&&&&&&&&&&&&&&&            #########.@@@...############...@@@.##################          !!!!!!!......@@@@!!!!***@@!!......@@@@!!!!!!!! ");
    sprintf(CutScene[4][12], " &&&&&&&&&&&&&&&&&@@@@@@@@@@&&&&&          #######***.....############.....***################           !!!!!!!!........!!!!!***@@!!!!........!!!!!!!! ");
    sprintf(CutScene[4][13], "  &&&&&&&&&&&&&&&&@@@@@@@@@@&&&&&&          #################@@@@@@@#########################            !!!!!!!!!!!!!!!!!!!!!***@@!!!!!!!!!!!!!!!!!!!! ");
    sprintf(CutScene[4][14], "   &&&&&&&&&&&&&&&@@@@@@@@@@&&&&&&&          ###############@@@@@@@@@#######################             !!!!!!!!!!!!!!!!@@@@@***@@@@@!!!!!!!!!!!!!!!!! ");
    sprintf(CutScene[4][15], "    &&&&&&&&&&&&&&@@@@@@@@@@&&&&&&&           #############@@@@@@@@@@@####################                !!!!!!!!!!!!!@@@@@@@***@@@@@@@!!!!!!!!!!!!!!  ");
    sprintf(CutScene[4][16], "     &&&&&&&&&&&&&@@@@@@@@@@&&&&&&&             ##########@@@@@@@@@@@@@################                    !!!!!!!!!!!@@@@@@@@***@@@@@@@@!!!!!!!!!!!!   ");
    sprintf(CutScene[4][17], "      &&&&&&&&&&&&@@@@@@@@@@&&&&&&                 ################################                         !!!!!!!!!@@@@@@@@@@**@@@@@@@@@!!!!!!!!!!    ");
    sprintf(CutScene[4][18], "        &&&&&&&&&&&&&&&&&&&&&&&&                                                                             !!!!!!!!@@@@@@@@@@@*@@@@@@@@@!!!!!!!!!     ");
    sprintf(CutScene[4][19], "           &&&&&&&&&&&&&&&&&&                                                                                  !!!!!!@@!!!!!!!!!!*@@@!!@@!!!!!!!        ");
    sprintf(CutScene[4][20], "                                                                                                                   !!!!!!!!!!!!!!!*@@@@!!!!!!           ");

    
    sprintf(CutScene[5][0],   "                                                              .                                                   ");
    sprintf(CutScene[5][1],   "                                                           ....                                                   ");
    sprintf(CutScene[5][2],   "                                                         .....                                                    ");
    sprintf(CutScene[5][3],   "                                                      .......                                                     ");
    sprintf(CutScene[5][4],   "                                                    ........                                                      ");
    sprintf(CutScene[5][5],   "                                                 ...........                                                      ");
    sprintf(CutScene[5][6],   "                                               ............                                                       ");
    sprintf(CutScene[5][7],   "                             ###############..............                                                        ");
    sprintf(CutScene[5][8],   "                           ###############...............                                                         ");
    sprintf(CutScene[5][9],   "                         ##############.................                                                          ");
    sprintf(CutScene[5][10],  "                        #############.................-                                                           ");
    sprintf(CutScene[5][11],  "                       ###########...................--                                                           ");
    sprintf(CutScene[5][12],  "                      #########.....................---                                                           ");
    sprintf(CutScene[5][13],  "                      #######......................---                                                            ");
    sprintf(CutScene[5][14],  "                      ######.....................-----                                                            ");
    sprintf(CutScene[5][15],  "                      ######&&&................#------                                                            ");
    sprintf(CutScene[5][16],  "                       ###&&&&&&&............###------                                       ---####              ");
    sprintf(CutScene[5][17],  "                       &&&&&&&#####.......######------                                    -----######             ");
    sprintf(CutScene[5][18],  "                    &&&&&&&##########...########------                                  ------########            ");
    sprintf(CutScene[5][19],  "                 &&&&&&& #######!!###############-----                               -------##########            ");
    sprintf(CutScene[5][20],  "                   &&     ##!!!!#################-----                            --------############            ");
    sprintf(CutScene[5][21],  "                        !!!!!!!###################-----                       ---------###############            ");
    sprintf(CutScene[5][22],  "                    !!!!!!!!____####################---___________________----------#################_____________");
    sprintf(CutScene[5][23],  "      !!!!!!!!!!!!!!!!!!!!!!!!!!!!___################--____________-------------####################__________    ");
    sprintf(CutScene[5][24],  "!!!!!!!!!!!!!!!!!!____!!!!!!!!!!!_____________##########_________##################################________       ");
    sprintf(CutScene[5][25],  "         _!!!!!!!__________________________________________________###############################______          ");
    sprintf(CutScene[5][26],  "     ___!!!!!!________________________________________________________#########################____               ");
    sprintf(CutScene[5][27],  "  ___!!!!!!____________________________________________________________________________________                   ");
    sprintf(CutScene[5][28],  "    !!!                                                                                                           ");
    
    
    sprintf(CutScene[6][0],   "                                                                                              !!!      !                 !!!!!!!!!       !!!!!!         ");
    sprintf(CutScene[6][1],   "                                                                                             !!!                      !!!!!!!!!!!!!!   !!!!!!!!!!       ");
    sprintf(CutScene[6][2],   "                                                                                            !!!!    !!!!              !     !!!!!!!!!!!!!!!!!!!!!!!     ");
    sprintf(CutScene[6][3],   "                                                                                           !!!!!  !!!!!!!                 !!!!!!!!!!!!!!!!!!!!    !     ");
    sprintf(CutScene[6][4],   "                                                                                  !!!!!!    !!!!!!!!!!!!!!              !!!!!     !!!!!!!!!!!!!!        ");
    sprintf(CutScene[6][5],   "                                                                                 !!!!!!!!!!!!!!!!!!    !!!             !!          !!!!!       !        ");
    sprintf(CutScene[6][6],   "                                                                                !!!!!!!!!!!!!!!!!!!___________________________________________@__       ");
    sprintf(CutScene[6][7],   "                                                                               !!!!!!!!!!!!!!!!!!____________________________________________@&&&__     ");
    sprintf(CutScene[6][8],   "                                                                               !!  !!!!!!!  !!!_____________________________________________@&&&&&__    ");
    sprintf(CutScene[6][9],   "                                                                               !   !!!!!!    ______________________________________________@&&*&&&&__   ");
    sprintf(CutScene[6][10],  "                                         .                                         !!!!        !!&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&@&&&&***&&&     ");
    sprintf(CutScene[6][11],  "                                       &..                                         !!!!         !&&&&&&&&&&&&&&&&&&.&.&&&&&&&&&&&&&&&&&&@&&&&&*&&&&     ");
    sprintf(CutScene[6][12],  "                                     ..&&.                                          !!           &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&@&&&&&&&&&&     ");
    sprintf(CutScene[6][13],  "                                   ....&&..                                          !           &&&&.&&&.&&&.&&&&.&&&&&&&&&&&&&&.&&&&&&@&&&_____&&     ");
    sprintf(CutScene[6][14],  "                                 .......&&.                                                      &&&&.&&&.&&&.&&&&.&&&......&&&&&.&.&&&&@&&&_____&&     ");
    sprintf(CutScene[6][15],  "                               .........&&.                                                      &&&&&&&&.&&&&&&..&&&&&&&&&&&&&&&.&&&&&&@&&&_____&&     ");
    sprintf(CutScene[6][16],  "                              &..........&&.                                                     &&&&&...&&&&...&&&&&&&&&&&&&&&&&.&&&&&&@&&&_____&&     ");
    sprintf(CutScene[6][17],  "                            ..&&.........&&.                                                     &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&@&&&_____&&     ");
    sprintf(CutScene[6][18],  "                             ..&&.........&&.                   .  .                             &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&@&&&_____&&     ");
    sprintf(CutScene[6][19],  "                              ..&&........&&..                 .@ .@.                            &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&@&&&_____&&     ");
    sprintf(CutScene[6][20],  "                               ..&&........&&.           ########!###                            &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&@&&&_____&&     ");
    sprintf(CutScene[6][21],  "********************************..&&.......&&.*********##!#####!!!#####*************************                                                        ");
    sprintf(CutScene[6][22],  "*********************************..&&.......&&.******###!!!!!!!!########**********                                                                      ");
    sprintf(CutScene[6][23],  "**********************************..&&.......&..@....##!!!####!!!########                                                                               ");
    sprintf(CutScene[6][24],  "***********************************..&&.......@..&&&&#!##########!#######                                                                               ");
    sprintf(CutScene[6][25],  "************************************..&&....@.........##################...........                                                                     ");
    sprintf(CutScene[6][26],  "*************************************..&&.@............################.&&&&&&&&&&&...                                                                  ");
    sprintf(CutScene[6][27],  "*******************************       ..@&&&&&............###########..............&&&                                                                  ");
    sprintf(CutScene[6][28],  "***********************                .....&&&&&&&..................................._                                                                 ");
    sprintf(CutScene[6][29],  "***************                        __     ......&&&&&&&..........................._                                                                 ");
    sprintf(CutScene[6][30],  "*********                               __       __   ......&&&&&&&...................                                                                  ");
    sprintf(CutScene[6][31],  "*****                                   __                  .......&&&&&&&............                                                                  ");
    sprintf(CutScene[6][32],  "**                                                                .......&&&&&&&......                                                                  ");
    sprintf(CutScene[6][33],  "*                                                                        .......&&&&&&                                                                  ");
    sprintf(CutScene[6][34],  "                                                                               .......                                                                  ");
    sprintf(CutScene[6][35],  "                                                                                   __                                                                   ");
    sprintf(CutScene[6][36],  "                                                                                   __                                                                   ");
    sprintf(CutScene[6][37],  "                                                                                    __                                                                  ");
    sprintf(CutScene[6][38],  "                                                                                    __                                                                  ");
    
    
    sprintf(CutScene[7][0],   "                        !!!!!!!!!!!!!!!!                                                                               ");
    sprintf(CutScene[7][1],   "                          !!!!!!!!!!!!!!!!!!!!!!!!                        !!!!!!!!!!!!!!!!!                            ");
    sprintf(CutScene[7][2],   "                            ###!!!!!!!!!!!!!!!!!!!!!!!!!!!       !!!!!!!!!!!!!!!!!!!!!!!                               ");
    sprintf(CutScene[7][3],   "                      ################!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!#########                           ");
    sprintf(CutScene[7][4],   "                  ##############################!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!##################                       ");
    sprintf(CutScene[7][5],   "               #######################!!!!!!!!!!!!!!!!!!!####!!!!!!!!!!!!!#########################                    ");
    sprintf(CutScene[7][6],   "             ###################!!!!!!!!!!!!!!!!!!#############!!!!!!!!!!!!!!!!!#####################                  ");
    sprintf(CutScene[7][7],   "           ##########@@@@@##!!!!!!!!!!!!!!!!!!####################!!!!!!!!!!!!!!!!!#########@@@########                ");
    sprintf(CutScene[7][8],   "        ##########@@@@@@@@@!!!!!!!!!!!!!!!###########################!!!!!!!!!!!!!!!!!###@@@@@@@########               ");
    sprintf(CutScene[7][9],   "      ##########@@@@@@@@@@@@@############################################!!!!!!!!!!!!!@@@@@@@@@@@########              ");
    sprintf(CutScene[7][10],  "     ##########@@@@@@@@@@@@@@@@@####################################################@@@@@@@@@@@@@@########             ");
    sprintf(CutScene[7][11],  "    ############@@@@@@@@@@@@@@@@@@@##############################################@@@@@@@@@@@@@@@@@@#######  @!!!!@     ");
    sprintf(CutScene[7][12],  "   #################@@@@@@@@@@@@@@@@@##########################################@@@@@@@@@@@@@@@@@##########@!!!!!!!!@   ");
    sprintf(CutScene[7][13],  "  ######################@@@@@@@@@@@@@@@@####################################@@@@@@@@@@@@@@@@############@@@@@@@@@@@@@@ ");
    sprintf(CutScene[7][14],  " #######################....@@@@@@@@@@@@@@################################@@@@@@@@@@@@@@...############@!!!!!!!!!!!!!!@");
    sprintf(CutScene[7][15],  " #######################......@@@@@@@@@@@@@@@##########################@@@@@@@@@@@@@.......############@!!@@@@@@@@@@!!@");
    sprintf(CutScene[7][16],  " #######################.....@@@@@@@@@@@@@@@@@@######################@@@@@@@@@@@@@@@@......############@!!@@@@@@@@@@!!@");
    sprintf(CutScene[7][17],  " #######################.....@@@@@@@@@@@@@@@@@@@@@################@@@@@@@@@@@@@@@@@@@@.....############@!!@@@@@@@@@@!!@");
    sprintf(CutScene[7][18],  " #######################.....@@@@@@@@@@@@...#@@@@@@#############@@@@@@@@.@@@@@@@@@@@@@.....############@!!@@@@@@@@@@!!@");
    sprintf(CutScene[7][19],  " #######################.....@@@@@@@@@@@@...#####@@#############@@@@###..@@@@@@@@@@@@@.....############@!!@@@@@@@@@@!!@");
    sprintf(CutScene[7][20],  " #######################.....@@@@@@@@@@@@...###########################...@@@@@@@@@@@......############@!!@@@@@@@@@@!!@");
    sprintf(CutScene[7][21],  " #######################......@@@@@@@@@@....###########################....@@@@@@@@@.......############@!!@@@@@@@@@@!!@");
    sprintf(CutScene[7][22],  "  ######################.......@@@@@@@@....#############################.....@@@@@@........############@!!@@@@@@@@@@!!@");
    sprintf(CutScene[7][23],  "   ######################.................###############################.................#############@!!@@@@@@@@@@!!@");
    sprintf(CutScene[7][24],  "    ######################...............#################################...............##############@!!@@@@@@@@@@!!@");
    sprintf(CutScene[7][25],  "     #######################...........########@@@@@@@@@@@@@@@@@@@@#########...........################@!!@@@@@@@@@@!!@");
    sprintf(CutScene[7][26],  "      ########################################@@@@@@@@@@@@@@@@@@@@@@###################################@!!@@@@@@@@@@!!@");
    sprintf(CutScene[7][27],  "       ######################################@@@@@@@@@@@@@@@@@@@@@@@@##################################@!!!!!!!!!!!!!!@");
    sprintf(CutScene[7][28],  "         ###################################@@@@@@@@@@@@@@@@@@@@@@@@@@#################################@!!!!!!!!!!!!!!@");
    sprintf(CutScene[7][29],  "          #################################@@@@@@@@@@@@@@@@@@@@@@@@@@@@#############################                   ");
    sprintf(CutScene[7][30],  "            ##############################@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@##########################                     ");
    sprintf(CutScene[7][31],  "               ##########################@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@######################                        ");
    sprintf(CutScene[7][32],  "                   #####################@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@###################                          ");
    sprintf(CutScene[7][33],  "                       ################################################################                                ");
    sprintf(CutScene[7][34],  "                             ##################################################                                        ");
    
    
    sprintf(CutScene[8][0],    "#########################################################################################################################################################################");
    sprintf(CutScene[8][1],    "#########################################################################################################################################################################");
    sprintf(CutScene[8][2],    "#########################################################################################################################################################################");
    sprintf(CutScene[8][3],    "#########################################################################################################################################################################");
    sprintf(CutScene[8][4],    "#########################################################################################################################################################################");
    sprintf(CutScene[8][5],    "#########################################################################################################################################################################");
    sprintf(CutScene[8][6],    "#########################################################################################################################################################################");
    sprintf(CutScene[8][7],    "#########################################################################################################################################################################");
    sprintf(CutScene[8][8],    "#########################################################################################################################################################################");
    sprintf(CutScene[8][9],    "#########################################################################################################################################################################");
    sprintf(CutScene[8][10],   "#########################################################################################################################################################################");
    sprintf(CutScene[8][11],   "#########################################################################################################################################################################");
    sprintf(CutScene[8][12],   "#########################################################################################################################################################################");
    sprintf(CutScene[8][13],   "#########################################################################################################################################################################");
    sprintf(CutScene[8][14],   "#########################################################################################################################################################################");
    sprintf(CutScene[8][15],   "#########################################################################################################################################################################");
    sprintf(CutScene[8][16],   "#########################################################################################################################################################################");
    sprintf(CutScene[8][17],   "#########################################################################################################################################################################");
    sprintf(CutScene[8][18],   "#########################################################################################################################################################################");
    sprintf(CutScene[8][19],   "#########################################################################################################################################################################");
    sprintf(CutScene[8][20],   "#########################################################################################################################################################################");
    sprintf(CutScene[8][21],   "#########################################################################################################################################################################");
    sprintf(CutScene[8][22],   "#########################################################################################################################################################################");
    sprintf(CutScene[8][23],   "#################@@@@@@##################################################################################################################################################");
    sprintf(CutScene[8][24],   "################@     @##################################################################################################################################################");
    sprintf(CutScene[8][25],   "##############@       @##################################################################################################################################################");
    sprintf(CutScene[8][26],   "#############@        @##################################################################################################################################################");
    sprintf(CutScene[8][27],   "###########@           @###########################################################@@@@@#################################################################################");
    sprintf(CutScene[8][28],   "##########@            @##########################################################@       @#######################################################@@@@@@@@@##############");
    sprintf(CutScene[8][29],   "########@              @########################################################@            @#############@@@@@@@##############################@            @###########");
    sprintf(CutScene[8][30],   "######@                @#######################################################@                 @#####@           @###########################@                @########");
    sprintf(CutScene[8][31],   "####@                   @#############################@@@@####################@                    @@@               @########################@                   @######");
    sprintf(CutScene[8][32],   "##@                     @############################@    @##################@                                         @#####################@                        @##");
    sprintf(CutScene[8][33],   "#@                      @###########################@      @################@                                              @##############@                            @#");
    sprintf(CutScene[8][34],   "@                       @##########################@         @#############@                                                    @#######@                                ");
    sprintf(CutScene[8][35],   "                         @#########################@          @##########@                                                        @@@@@                                  ");
    sprintf(CutScene[8][36],   "                         @########################@             @######@                                                                                                 ");
    sprintf(CutScene[8][37],   "                         @#######################@                @@@@                                                                                                   ");
    sprintf(CutScene[8][38],   "                         @#######################@                                                                                                                       ");
    sprintf(CutScene[8][39],   "                          @#####################@                                                                                                                        ");
    sprintf(CutScene[8][40],   "                          @####################@                                                                                                                         ");
    sprintf(CutScene[8][41],   "                          @##################@                                                                                                                           ");
    sprintf(CutScene[8][42],   "                           @###############@                                                                                                                             ");
    sprintf(CutScene[8][43],   "                             @##########@                                                                                                                                ");
    sprintf(CutScene[8][44],   "                               @@@@@@@                                                                                                                                   ");
    
    sprintf(CutScene[9][0],  "                        !!!!!!!!!!!!!!!!                                                                               ");
    sprintf(CutScene[9][1],  "                          !!!!!!!!!!!!!!!!!!!!!!!!                        !!!!!!!!!!!!!!!!!                            ");
    sprintf(CutScene[9][2],  "                            ###!!!!!!!!!!!!!!!!!!!!!!!!!!!       !!!!!!!!!!!!!!!!!!!!!!!                               ");
    sprintf(CutScene[9][3],  "                      ################!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!#########                           ");
    sprintf(CutScene[9][4],  "                  ##############################!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!##################                       ");
    sprintf(CutScene[9][5],  "               #######################!!!!!!!!!!!!!!!!!!!####!!!!!!!!!!!!!#########################                    ");
    sprintf(CutScene[9][6],  "             ###################!!!!!!!!!!!!!!!!!!#############!!!!!!!!!!!!!!!!!#####################                  ");
    sprintf(CutScene[9][7],  "           #################!!!!!!!!!!!!!!!!!!####################!!!!!!!!!!!!!!!!!####################                ");
    sprintf(CutScene[9][8],  "        ###################!!!!!!!!!!!!!!!###########################!!!!!!!!!!!!!!!!!##################               ");
    sprintf(CutScene[9][9],  "      ###################################################################!!!!!!!!!!!!!###################              ");
    sprintf(CutScene[9][10], "     #####################################################################################################             ");
    sprintf(CutScene[9][11], "    #######################################################################################################            ");
    sprintf(CutScene[9][12], "   ###########################.........#####################################.........#######################           ");
    sprintf(CutScene[9][13], "  #########################..............#################################..............####################           ");
    sprintf(CutScene[9][14], " ########################.......@@@@@@.....#############################.....@@@@@@.......##################           ");
    sprintf(CutScene[9][15], " #######################......@@@@@@@@@@....###########################....@@@@@@@@@@......#################           ");
    sprintf(CutScene[9][16], " #######################.....@@@@@@@@@@@@...###########################...@@@@@@@@@@@@.....#################           ");
    sprintf(CutScene[9][17], " #######################.....@@@@@@@@@@@@...###########################...@@@@@@@@@@@@.....#################           ");
    sprintf(CutScene[9][18], " #######################.....@@@@@@@@@@@@...###########################...@@@@@@@@@@@@.....#################           ");
    sprintf(CutScene[9][19], " #######################.....@@@@@@@@@@@@...###########################...@@@@@@@@@@@@.....#################           ");
    sprintf(CutScene[9][20], " #######################.....@@@@@@@@@@@@...###########################...@@@@@@@@@@@@.....#################           ");
    sprintf(CutScene[9][21], " #######################......@@@@@@@@@@....###########################....@@@@@@@@@@......#################           ");
    sprintf(CutScene[9][22], "  ######################.......@@@@@@@@....#############################....@@@@@@@@.......#################           ");
    sprintf(CutScene[9][23], "   ######################.................###############################.................#################            ");
    sprintf(CutScene[9][24], "    ######################...............#################################...............#################             ");
    sprintf(CutScene[9][25], "     #######################...........#####################################...........##################              ");
    sprintf(CutScene[9][26], "      ##################################################################################################               ");
    sprintf(CutScene[9][27], "       #################################@@##############################@@#############################                ");
    sprintf(CutScene[9][28], "         ################################@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#############################                 ");
    sprintf(CutScene[9][29], "          ###############################@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@###########################                   ");
    sprintf(CutScene[9][30], "            ###############################@@@@@@@@@@@@@@@@@@@@@@@@@@@@###########################                     ");
    sprintf(CutScene[9][31], "               #############################@@@@@@@@@@@@@@@@@@@@@@@@@@#########################                        ");
    sprintf(CutScene[9][32], "                   ###########################@@@@@@@@@@@@@@@@@@@@@@#########################                          ");
    sprintf(CutScene[9][33], "                       ###########################@@@@@@@@@@@@@@#######################                                ");
    sprintf(CutScene[9][34], "                             ##################################################                                        ");

    sprintf(CutScene[10][0],  "                        !!!!!!!!!!!!!!!!                                                                               ");
    sprintf(CutScene[10][1],  "                          !!!!!!!!!!!!!!!!!!!!!!!!                        !!!!!!!!!!!!!!!!!                            ");
    sprintf(CutScene[10][2],  "                            ###!!!!!!!!!!!!!!!!!!!!!!!!!!!       !!!!!!!!!!!!!!!!!!!!!!!                               ");
    sprintf(CutScene[10][3],  "                      ################!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!#########                           ");
    sprintf(CutScene[10][4],  "                  ##############################!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!##################                       ");
    sprintf(CutScene[10][5],  "               #######################!!!!!!!!!!!!!!!!!!!####!!!!!!!!!!!!!#########################                    ");
    sprintf(CutScene[10][6],  "             ###################!!!!!!!!!!!!!!!!!!#############!!!!!!!!!!!!!!!!!#####################                  ");
    sprintf(CutScene[10][7],  "           #################!!!!!!!!!!!!!!!!!!####################!!!!!!!!!!!!!!!!!####################                ");
    sprintf(CutScene[10][8],  "        ###################!!!!!!!!!!!!!!!###########################!!!!!!!!!!!!!!!!!##################               ");
    sprintf(CutScene[10][9],  "      ###################################################################!!!!!!!!!!!!!###################              ");
    sprintf(CutScene[10][10], "     #####################################################################################################             ");
    sprintf(CutScene[10][11], "    ###################@@@@@@@@@@@@@@@@@@@@@@#########################@@@@@@@@@@@@@@@@@@@@#################            ");
    sprintf(CutScene[10][12], "   ################@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#################@@@@@@@@@@@@@@@@@@@@@@@@@@@@##############           ");
    sprintf(CutScene[10][13], "  ################@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@###############@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#############           ");
    sprintf(CutScene[10][14], " ########################..................#############################..................##################           ");
    sprintf(CutScene[10][15], " #######################.......@@@@@@@@.....###########################.....@@@@@@@@.......#################           ");
    sprintf(CutScene[10][16], " #######################......@@@@@@@@@@....###########################....@@@@@@@@@@......#################           ");
    sprintf(CutScene[10][17], " #######################.....@@@@@@@@@@@@...###########################...@@@@@@@@@@@@.....#################           ");
    sprintf(CutScene[10][18], " #######################.....@@@@@@@@@@@@...###########################...@@@@@@@@@@@@.....#################           ");
    sprintf(CutScene[10][19], " #######################.....@@@@@@@@@@@@...###########################...@@@@@@@@@@@@.....#################           ");
    sprintf(CutScene[10][20], " #######################.....@@@@@@@@@@@@...###########################...@@@@@@@@@@@@.....#################           ");
    sprintf(CutScene[10][21], " #######################.....@@@@@@@@@@@@...###########################...@@@@@@@@@@@@.....#################           ");
    sprintf(CutScene[10][22], "  ######################......@@@@@@@@@@...#############################...@@@@@@@@@@......#################           ");
    sprintf(CutScene[10][23], "   ######################......@@@@@@@@...###############################...@@@@@@@@......#################            ");
    sprintf(CutScene[10][24], "    ######################...............#################################...............#################             ");
    sprintf(CutScene[10][25], "     #######################...........#####################################...........##################              ");
    sprintf(CutScene[10][26], "      ##################################################################################################               ");
    sprintf(CutScene[10][27], "       ####################################@@@@@@@@@@@@@@@@@@@@@@@@@@@@################################                ");
    sprintf(CutScene[10][28], "         ##################################@@@@@@@@@@@@@@@@@@@@@@@@@@@@###############################                 ");
    sprintf(CutScene[10][29], "          #################################@@@@@@@@@@@@@@@@@@@@@@@@@@@@#############################                   ");
    sprintf(CutScene[10][30], "            ###############################@@@@@@@@@@@@@@@@@@@@@@@@@@@@###########################                     ");
    sprintf(CutScene[10][31], "               ############################@@@@@@@@@@@@@@@@@@@@@@@@@@@@########################                        ");
    sprintf(CutScene[10][32], "                   ########################@@@@@@@@@@@@@@@@@@@@@@@@@@@@######################                          ");
    sprintf(CutScene[10][33], "                       ################################################################                                ");
    sprintf(CutScene[10][34], "                             ##################################################                                        ");

    
    sprintf(CutScene[11][0],  "_________________@                    ___________________________                                                                               @_________________________");
    sprintf(CutScene[11][1],  "_________________@                    ___________________________                                                                               @_________________________");
    sprintf(CutScene[11][2],  "_________________@                     _________________________                                                                                 @________________________");
    sprintf(CutScene[11][3],  "_______@@@@@_____@                      __________@@@@@________                                                                                   @______@@@@@@___________");
    sprintf(CutScene[11][4],  "@@@@___@___@____@                        ________@_____@______                                                                                     @____@_____@_________@@");
    sprintf(CutScene[11][5],  "______@_____@__@                            ____@_______@___                                                                                         @__@______@______@___");
    sprintf(CutScene[11][6],  "________@____@                                  _________               !!!!!!!!!!!!!!!                     !!!!!!!!!!                                 @___________@______");
    sprintf(CutScene[11][7],  "___________@                                                             ###!!!!!!!!!!!!!!!!!!!    !!!!!!!!!!!!!!!!                                       @@@@@@@@____@___");
    sprintf(CutScene[11][8],  "__________@__@                                                      ###################!!!!!!!!!!!!!!!!!!!!!!!!!########                                        @___@@____");
    sprintf(CutScene[11][9],  "__________.@__@                                                  #################!!!!!!!!!!!!###!!!!!!!!!#################                                    @__@@@.____");
    sprintf(CutScene[11][10], "__________..@@_@                                              #######@@#######!!!!!!!!!!!!!#########!!!!!!!!!!!##############                                 @__@@@@.____");
    sprintf(CutScene[11][11], "__________..@@__@                                           ########@@@@@##!!!!!!!!!!##################!!!!!!!!!!####@@@@######                               @___@@@.____");
    sprintf(CutScene[11][12], "__________..@@___@                                         #######@@@@@@@@@@###############################!!!!!!##@@@@@@@@######                             @____@..____");
    sprintf(CutScene[11][13], "__________..@@___@                                        #######@@@@@@@@@@@@@##################################@@@@@@@@@@@@######                            @_____..____");
    sprintf(CutScene[11][14], "__________...____@                                       ############@@@@@@@@@@@@#############################@@@@@@@@@@@@#########                           @___________");
    sprintf(CutScene[11][15], "_________________@                                      ###############..@@@@@@@@@@########################@@@@@@@@@@@##############                           @@@________");
    sprintf(CutScene[11][16], "_________________@                                     ################....@@@@@@@@@@@###################@@@@@@@@@....##############                            @_@_______");
    sprintf(CutScene[11][17], "_____________@@@@                                      ################....@@@@@@@@@@@@@##############@@@@@@@@@@@@....##############                             @_@@_____");
    sprintf(CutScene[11][18], "____________@@__@                                      ################....@@@@@@@@..@@@@@#########@@@@@@@@@@@@@@@....##############                               @______");
    sprintf(CutScene[11][19], "___________@@__@                                       ################....@@@@@@@@..###@@@#######@@@###..@@@@@@@@....##############                                  @___");
    sprintf(CutScene[11][20], "______________@                                        ################....@@@@@@@@..###################..@@@@@@@@....##############                                      ");
    sprintf(CutScene[11][21], "____________@                                           ###############.....@@@@@@...####################..@@@@@@.....##############                                      ");
    sprintf(CutScene[11][22], "________@                                                ###############............######################...........##############                                       ");
    sprintf(CutScene[11][23], "                                                          #############****.......######@@@@@@@@@@@@@#######.......****###########                                        ");
    sprintf(CutScene[11][24], "                                                           ############################@@@@@@@@@@@@@@@###########################                                 ________");
    sprintf(CutScene[11][25], "                                                            ##########################@@@@@@@@@@@@@@@@@########################                              _____________");
    sprintf(CutScene[11][26], "_____                                                         #######################@@@@@@@@@@@@@@@@@@@#####################                             ________________");
    sprintf(CutScene[11][27], "_______                              ____________________        ###################@@@@@@@@@@@@@@@@@@@@@##################                             __________________");
    sprintf(CutScene[11][28], "_________                        ____________________________       ###############@@@@@@@@@@@@@@@@@@@@@@@##############                              ____________________");
    sprintf(CutScene[11][29], "__________                    __________________________________         ##########################################                                  _____________________");
    sprintf(CutScene[11][30], "___________                 ______________________________________                                                                                  ______________________");
    sprintf(CutScene[11][31], "____________               ________________________________________                                                                                 ______________________");
    sprintf(CutScene[11][32], "____________              __________________________________________                                                                                ______________________");
    sprintf(CutScene[11][33], "____________             ____________________________________________                                                                               ______________________");
    sprintf(CutScene[11][34], "____________             ____________________________________________                                                                                _____________________");
    

    sprintf(CutScene[12][0], "                                                    .................                                    !!!!!!   !!!!!!! @!!!!!!!                   ");
    sprintf(CutScene[12][1], "                                                  ...................                                  !!!!@   !!!!!!!@!!!!!!!                       ");
    sprintf(CutScene[12][2], "                                                ....................                                 !!!!@  @!!!!@@!!!!!!!     !!!!!!!!!!!!!         ");
    sprintf(CutScene[12][3], "                                              ......................            #######            !!!!@ @!!!@@!!!!!!!@!!!!!!!!!!!!!!!!!             ");
    sprintf(CutScene[12][4], "                                             ......................     #####################     !!!@@@!!!@!!!!@!!@!!!!!!!!!!!!!!!##                ");
    sprintf(CutScene[12][5], "                                           ........................###############......########@@!@@@@@!@@!@!!!!!!!!!!!################             ");
    sprintf(CutScene[12][6], "                                         ..........................############...........#######################.......##################           ");
    sprintf(CutScene[12][7], "                                       ...........................###########.....@@.......###################...........###################         ");
    sprintf(CutScene[12][8], "                                      ............................#########.....@@@@@.......################..............####################       ");
    sprintf(CutScene[12][9], "                                    .............................#########....@@@@@@@@......###############................####################      ");
    sprintf(CutScene[12][10], "                                  ...............................########....@@@@@@@@@......#############..................######################    ");
    sprintf(CutScene[12][11], "                                ................................########....@@@@@@@@@@......############...................#######################   ");
    sprintf(CutScene[12][12], "                               .................................#######....@@@@@@@@@@@......###########........@@..........########################  ");
    sprintf(CutScene[12][13], "                             ..................................########....@@@@@@@@@@@......##########.......@@@@@.........######################### ");
    sprintf(CutScene[12][14], "                           ....................................########....@@@@@@@@@@......###########........@@@..........##########################");
    sprintf(CutScene[12][15], "                         .....................................#########....@@@@@@@@@......############....................###########################");
    sprintf(CutScene[12][16], "                        .....................................##########....@@@@@@@.......#############...................############################");
    sprintf(CutScene[12][17], "                      ......................................############.....@@@........##############..................#############################");
    sprintf(CutScene[12][18], "                    .......................................##############.............#################................##############################");
    sprintf(CutScene[12][19], "                  ........................................#################........#####################.............################################");
    sprintf(CutScene[12][20], "                 ........................................################################################.........###################################");
    sprintf(CutScene[12][21], "                   .....................................#############################################################################################");
    sprintf(CutScene[12][22], "                    *****.............................#####################@@@@@@@@###########################@@@@@@@############################### ");
    sprintf(CutScene[12][23], "                  *********.......................... ###################@@@@@@@@@@@@@@@###################@@@@@@@@@@@@############################  ");
    sprintf(CutScene[12][24], "                ***********  .....................    #################@@@@@@@@@@@@@@@@@@@@############@@@@@@@@@@@@@@@@@##########################   ");
    sprintf(CutScene[12][25], "              ***********       ................       ###############@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@########################    ");
    sprintf(CutScene[12][26], "            ***********             ..........           #############@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#######################     ");
    sprintf(CutScene[12][27], "          ***********                  .....              #############@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@######################       ");
    sprintf(CutScene[12][28], "        ***********                       .                 ############@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#####################         ");     
    sprintf(CutScene[12][29], "      ***********                                              ###########@@@@@@@@@@@@@@@@@#########@@@@@@@@@@@@@@@@@@####################           ");
    sprintf(CutScene[12][30], "    ***********                                                   ##########@@@@@@@@@####################@@@@@@@@@@@###################              ");
    sprintf(CutScene[12][31], "  ***********                                                         #############################################################                  ");
    sprintf(CutScene[12][32], " **********                                                                 #################################################                        ");
    sprintf(CutScene[12][33], "    *****                                                                                                                                            ");

     sprintf(CutScene[13][0], " _______                    _            (&)      __  __      _                  _           _       ");
     sprintf(CutScene[13][1], "|&&&&&&&|                  |&|           |/      |&&|/&&|    |&|                |&|         |&|      ");
     sprintf(CutScene[13][2], "   |&| ___  _ __ ___   __ _|&|_ ___   ___   ___  |&||&/&| ___|&| __ _ _ __   ___|&|__   ___ |&|_   _ ");
     sprintf(CutScene[13][3], "   |&|/&&&||&'&&`&&&&|/&&&&|&&&/&&&| /&_&| / __| |&||/|&|/&_&|&|/&&&&|&'&&&|/&&&|&'&&&|/&&&||&|&| |&|");
     sprintf(CutScene[13][4], "   |&|&(_)&|&| |&| |&|&(_|&|&||&(_)&|&&__/ -__ . |&|  |&|&&__|&|&(_|&|&| |&|&(__|&| |&|&(_)&|&|&|_|&|");
     sprintf(CutScene[13][5], "   |&||&&&/|&| |&| |&||&&,&|&&&|&&&/ |&&&| |&&_/ |&|  |&||&&&|&||&&,&|&| |&||&&&|&| |&||&&&/|&|.&&,&|");
     sprintf(CutScene[13][6], "                                                                                                __/&|");
     sprintf(CutScene[13][7], "                                                                                               |&&&/ ");

    sprintf(GamePlay[0][0],   "                                                           !!!!             ##  ##   ");
    sprintf(GamePlay[0][1],   "                 !!!!!!!!!!                        !!!!!!!!!!               ##  ##   ");
    sprintf(GamePlay[0][2],   "                     !!!!!!!!!!!!!!!!!!!#####!!!!!!!!!!!!!               #####  #####");
    sprintf(GamePlay[0][3],   "                      ########!!!!!!!!!!!!!!!!!!!!##############                     ");
    sprintf(GamePlay[0][4],   "                   ##############!!!!!!!###!!!!!!!!!!!!!!!!##########    #####  #####");
    sprintf(GamePlay[0][5],   "   @!@!!!!!!!!@@##############!!!!!!!!#############!!!!!!!!!!!!!#######     ##  ##   ");
    sprintf(GamePlay[0][6],   "    @!!@!!!!!!##########!!!!!!!!!!######################################    ##  ##   ");
    sprintf(GamePlay[0][7],   "    @!!!!!@!!#############################################################           ");
    sprintf(GamePlay[0][8],   "     @!!!!!################################################################          ");
    sprintf(GamePlay[0][9],   "     @!!!!!################################################################          ");
    sprintf(GamePlay[0][10],  "      @!!!!################################################################          ");
    sprintf(GamePlay[0][11],  "      @!!!!################################################################          ");
    sprintf(GamePlay[0][12],  "       @!!!!###############################################################          ");
    sprintf(GamePlay[0][13],  "       @!!!!###############################################################          ");
    sprintf(GamePlay[0][14],  "         @!!!#############################################################           ");
    sprintf(GamePlay[0][15],  "           @!############################################################            ");
    sprintf(GamePlay[0][16],  "              ##########################################################             ");
    sprintf(GamePlay[0][17],  "               ########################################################              ");
    sprintf(GamePlay[0][18],  "                 ####################################################                ");
    sprintf(GamePlay[0][19],  "                   ################################################                  ");
    sprintf(GamePlay[0][20],  "                      ###########################################                    ");
    sprintf(GamePlay[0][21],  "                         #####################################                       ");
    sprintf(GamePlay[0][22],  "                             #############################                           ");
    sprintf(GamePlay[0][23],  "                                     #############                                   ");

    
    sprintf(GamePlay[1][0],   "1111111111111111@@@@@@@@@@@@@@@@@@            ");
    sprintf(GamePlay[1][1],   "111111111111@______________________@@         ");
    sprintf(GamePlay[1][2],   "11111111@______________________________@@@  . ");
    sprintf(GamePlay[1][3],   "111111@_________________@________________.... ");
    sprintf(GamePlay[1][4],   "11111@__________________.@@@@_________......@ ");
    sprintf(GamePlay[1][5],   "1111@___________________...@@@@@___........@@.");
    sprintf(GamePlay[1][6],   "111@____________________...@@@@...........@@@.");
    sprintf(GamePlay[1][7],   "111@____________________..@@@............__@@.");
    sprintf(GamePlay[1][8],   "11@_____________________.@..............____@.");
    sprintf(GamePlay[1][9],   "1@@___________________................________");
    sprintf(GamePlay[1][10],  "1@________@@@@@@___.................__________");
    sprintf(GamePlay[1][11],  "@@______@@______@@@**.............____________");
    sprintf(GamePlay[1][12],  "@_____@____________@@*..........______________");
    sprintf(GamePlay[1][13],  "@___@@_______________@......_____________@@__@");
    sprintf(GamePlay[1][14],  "1@__@________________@___________@@@@@@@@_@__@");
    sprintf(GamePlay[1][15],  "11@__@_______________@___________@@_______@_@ ");
    sprintf(GamePlay[1][16],  "111@@__*@_________@@____________@@________@   ");
    sprintf(GamePlay[1][17],  "1111111@___@@@@@________________@@______@@    ");
    sprintf(GamePlay[1][18],  "1111111111@@____________________@@____@@      ");
    sprintf(GamePlay[1][19],  "1111111111111@@@_______________@@             ");
    sprintf(GamePlay[1][20],  "111111111111111111@@@@@@@@@@                  ");
    //X = 18, Y = 8

    
    sprintf(GamePlay[2][0],   "1111111111111111@________________@11111111111111111111111111.111");
    sprintf(GamePlay[2][1],   "1111111111111@________________________@11111111111111111111..@11");
    sprintf(GamePlay[2][2],   "1111111111@______________________________@1111111111111111....@1");
    sprintf(GamePlay[2][3],   "1111111@____________________________________@11111111111.......@");
    sprintf(GamePlay[2][4],   "111111@____@@@@__________________________@@__@111111111........@");
    sprintf(GamePlay[2][5],   "11111@______..@@@@@____________________@@@.__@11111111.........@");
    sprintf(GamePlay[2][6],   "1111@_______..@@@@@@@@_______________@@@@@.___@111111..........@");
    sprintf(GamePlay[2][7],   "111@________..@@@@@.__________________.@@@.___@11111...........@");
    sprintf(GamePlay[2][8],   "11@_________..@@@@.___________________.@@@.___@1111...........@ ");
    sprintf(GamePlay[2][9],   "1@__________..@@@._____________________.@@.___@111...........@  ");
    sprintf(GamePlay[2][10],  "1@___________...._______________________...___@1111.........@   ");
    sprintf(GamePlay[2][11],  "@______________________________________________@_____***..@     ");
    sprintf(GamePlay[2][12],  "@______________________@@_______@@_____________@_______@        ");
    sprintf(GamePlay[2][13],  " @_____________________@@@@@@@@@@@____________@________@        ");
    sprintf(GamePlay[2][14],  "    @_________________@@@________@___________@_______@          ");
    sprintf(GamePlay[2][15],  "        @_____________@@_________@________@  ***                ");
    sprintf(GamePlay[2][16],  "           @_________@@__________@_____@                        ");
    sprintf(GamePlay[2][17],  "               @____________________@                           ");
    sprintf(GamePlay[2][18],  "                   @_____________@                              ");
    sprintf(GamePlay[2][19],  "                       @_____@                                  ");
    //X = 19 , Y = 7

    sprintf(GamePlay[3][0],   "1@.11111111111111111111111111111111111111111111111111111");
    sprintf(GamePlay[3][1],   "@...1111111111111111111111111111111111111111111111111111");
    sprintf(GamePlay[3][2],   "@....1111111111111111111111@@@@_____________@@1111111111");
    sprintf(GamePlay[3][3],   "@.....1111111111111111@@_______________________@11111111");
    sprintf(GamePlay[3][4],   "@......1111111111111@____________________________@111111");
    sprintf(GamePlay[3][5],   "@........1111111111@______________________________@11111");
    sprintf(GamePlay[3][6],   " @........11111111@____________________@@@_________@@111");
    sprintf(GamePlay[3][7],   " @.........111111@___@@@@___________@@@..___________@@11");
    sprintf(GamePlay[3][8],   " @..........1111@____..@@@@@@_____@@@@...____________@@1");
    sprintf(GamePlay[3][9],   "  @..........111@____......_________....._____________@1");
    sprintf(GamePlay[3][10],  "   @..........11@____..@@@___________@@@.______________@");
    sprintf(GamePlay[3][11],  "    @......***11@____..@@_____________@@.______________@");
    sprintf(GamePlay[3][12],  "       @_______@_______________________________________@");
    sprintf(GamePlay[3][13],  "      @_________@__________@@@@@@@@____________________@");
    sprintf(GamePlay[3][14],  "      @@________@__________@@_____@@__________________@ ");
    sprintf(GamePlay[3][15],  "        @________@_________@@______@@________________@  ");
    sprintf(GamePlay[3][16],  "           @@@***@@@_______@_______@@______________@    ");
    sprintf(GamePlay[3][17],  "                    @@____@@________@@__________@       ");
    sprintf(GamePlay[3][18],  "                       @@___________________@@          ");
    sprintf(GamePlay[3][19],  "                           @@________@@@                ");
    // X = 13, Y = 8

    sprintf(GamePlay[4][0],  "1111111111111111@@@@@@@@@@@@@@@@@@                ");
    sprintf(GamePlay[4][1],  "111111111111@______________________@@             ");
    sprintf(GamePlay[4][2],  "11111111@______________________________@@@ 1      ");
    sprintf(GamePlay[4][3],  "111111@____________________________________@      ");
    sprintf(GamePlay[4][4],  "11111@_________________________@____________@     ");
    sprintf(GamePlay[4][5],  "1111@_____________________@@@..__________@___@    ");
    sprintf(GamePlay[4][6],  "111@___________________@@@@@@..__________.@@@@    ");
    sprintf(GamePlay[4][7],  "111@___________________#.@@@@..__________#.@@@    ");
    sprintf(GamePlay[4][8],  "11@____________________#.@@@@..___________#.@@    ");
    sprintf(GamePlay[4][9],  "1@@_____________________#.@@@..____________#..    ");
    sprintf(GamePlay[4][10], "1@________@@@@@@_________#....________________    ");
    sprintf(GamePlay[4][11], "@@______@@______@@@___________________________    ");
    sprintf(GamePlay[4][12], "@_____@____________@@________________@@@@@@@__    ");
    sprintf(GamePlay[4][13], "@___@@_______________@____________@@@@@@@@@@_@    ");
    sprintf(GamePlay[4][14], "1@__@________________@___________@@@@@@@@@@@_@    ");
    sprintf(GamePlay[4][15], "11@__@_______________@___________@@@@@@@@___@     ");
    sprintf(GamePlay[4][16], "111@@___@_________@@_____________@@@@_____@       ");
    sprintf(GamePlay[4][17], "1111111@___@@@@@_________________@@@____@@        ");
    sprintf(GamePlay[4][18], "1111111111@@_____________________###__@@          ");
    sprintf(GamePlay[4][19], "1111111111111@@@_______________@#####             ");
    sprintf(GamePlay[4][20], "111111111111111111@@@@@@@@@@     ###              ");

    sprintf(GamePlay[5][0],  "1111111111111111@________________@111111111111111111111111111111");
    sprintf(GamePlay[5][1],  "1111111111111@________________________@1111111111111111111111111");
    sprintf(GamePlay[5][2],  "1111111111@______________________________@1111111111111111111111");
    sprintf(GamePlay[5][3],  "1111111@_______________________@@@__________@1111111111111111111");
    sprintf(GamePlay[5][4],  "111111@________________@________..@@@@@______@111111111111111111");
    sprintf(GamePlay[5][5],  "11111@_____________@@@..________..@@@@@@@@___@111111111111111111");
    sprintf(GamePlay[5][6],  "1111@__________@@@@@@@..________..@@@@@.-_____@11111111111111111");
    sprintf(GamePlay[5][7],  "111@____________..@@@@..________..@@@@@.-_____@11111111111111111");
    sprintf(GamePlay[5][8],  "11@_____________..@@@@..________..@@@@.-______@11111111111111111");
    sprintf(GamePlay[5][9],  "1@_______________..@@@.._________..@@.-_______@11111111111111111");
    sprintf(GamePlay[5][10], "1@________________.....___________....________@11111111111111111");
    sprintf(GamePlay[5][11], "@____________________________________****______@_____11111111111");
    sprintf(GamePlay[5][12], "@______________________________________****____@_______@        ");
    sprintf(GamePlay[5][13], " @_______________________@@@@@@@@_____________@________@        ");
    sprintf(GamePlay[5][14], "    @__________________@@@@@@@@@@@@__________@_______@          ");
    sprintf(GamePlay[5][15], "        @_____________@@@@@@@@@@@@@@_______@                    ");
    sprintf(GamePlay[5][16], "           @__________@@@________@@@____@                       ");
    sprintf(GamePlay[5][17], "               @______@____________@_@                          ");
    sprintf(GamePlay[5][18], "                   @_____________@                              ");
    sprintf(GamePlay[5][19], "                       @_____@                                  ");

    sprintf(GamePlay[6][0],  "11111111111111111111111111111111111111111111111111111111");
    sprintf(GamePlay[6][1],  "11111111111111111111111111111111111111111111111111111111");
    sprintf(GamePlay[6][2],  "111111111111111111111111111@@@@_____________@@1111111111");
    sprintf(GamePlay[6][3],  "!111111111111111111111@@_______________________@11111111");
    sprintf(GamePlay[6][4],  "11111111111111111111@____________________________@111111");
    sprintf(GamePlay[6][5],  "1111111111111111111@_____________@@_______________@11111");
    sprintf(GamePlay[6][6],  "111111111111111111@________@@____..@@@@____________@@111");
    sprintf(GamePlay[6][7],  "11111111111111111@_____@@@@@.____..@@@@@@@__________@@11");
    sprintf(GamePlay[6][8],  "1111111111111111@____@@.@@@@.____..@@@@._____________@@1");
    sprintf(GamePlay[6][9],  "1111111111111111@______..@@@.____..@@@@.______________@1");
    sprintf(GamePlay[6][10], "1111111111111111@_______....______..@@.________________@");
    sprintf(GamePlay[6][11], "1111111111111111@__________________..._________________@");
    sprintf(GamePlay[6][12], "       @_______@_______________________________________@");
    sprintf(GamePlay[6][13], "      @_________@__________@@@@@@@@____________________@");
    sprintf(GamePlay[6][14], "      @@________@________@@@@@@@@@@@@_________________@ ");
    sprintf(GamePlay[6][15], "        @________@_______@@@@@@@@@@@@@_______________@  ");
    sprintf(GamePlay[6][16], "           @@@   @@@______@@@@@@@@@@@@@____________@    ");
    sprintf(GamePlay[6][17], "                    @@_____@@@#######@@@________@       ");
    sprintf(GamePlay[6][18], "                       @@__#############____@@          ");
    sprintf(GamePlay[6][19], "                           @##__####_##@                ");

    sprintf(TomatoeLife[2][0], "                                                           !!!!             ##  ##   ");
    sprintf(TomatoeLife[2][1], "                 !!!!!!!!!!                        !!!!!!!!!!               ##  ##   ");
    sprintf(TomatoeLife[2][2], "                     !!!!!!!!!!!!!!!!!@-##!!!!!!!!!!!!!!!!               #####  #####");
    sprintf(TomatoeLife[2][3], "                      ########!!!!!!!!#@-!!!!!!!################                     ");
    sprintf(TomatoeLife[2][4], "                   ##############!!!!!!!!--!!!!!!!!!!!!!!!!##########    #####  #####");
    sprintf(TomatoeLife[2][5], "   @!@!!!!!!!!@@##############!!!!!!!####--########!!!!!!!!!!!!!#######     ##  ##   ");
    sprintf(TomatoeLife[2][6], "    @!!@!!!!!!##########!!!!!!!!!!########--############################    ##  ##   ");
    sprintf(TomatoeLife[2][7], "    @!!!!!@!!#############################--##############################           ");
    sprintf(TomatoeLife[2][8], "     @!!!!!################################################################          ");
    sprintf(TomatoeLife[2][9], "     @!!!!!################################################################          ");
    sprintf(TomatoeLife[2][10], "      @!!!!################################################################          ");
    sprintf(TomatoeLife[2][11], "      @!!!!################################################################          ");
    sprintf(TomatoeLife[2][12], "       @!!!!###############################################################          ");
    sprintf(TomatoeLife[2][13], "       @!!!!###############################################################          ");
    sprintf(TomatoeLife[2][14], "         @!!!#############################################################           ");
    sprintf(TomatoeLife[2][15], "           @!############################################################            ");
    sprintf(TomatoeLife[2][16], "              ##########################################################             ");
    sprintf(TomatoeLife[2][17], "               ########################################################              ");
    sprintf(TomatoeLife[2][18], "                 ####################################################                ");
    sprintf(TomatoeLife[2][19], "                   ################################################                  ");
    sprintf(TomatoeLife[2][20], "                      ###########################################                    ");
    sprintf(TomatoeLife[2][21], "                         #####################################                       ");
    sprintf(TomatoeLife[2][22], "                             #############################                           ");
    sprintf(TomatoeLife[2][23], "                                     #############                                   ");

    sprintf(TomatoeLife[1][0], "                                                           !!!!             ##  ##   ");
    sprintf(TomatoeLife[1][1], "                 !!!!!!!!!!                        !!!!!!!!!!               ##  ##   ");
    sprintf(TomatoeLife[1][2], "                     !!!!!!!!!!!!!!!!!@-##!!!!!!!!!!!!!!!!               #####  #####");
    sprintf(TomatoeLife[1][3], "                      ########!!!!!!!!#@-!!!!!!!################                     ");
    sprintf(TomatoeLife[1][4], "                   ##############!!!!!!!!--!!!!!!!!!!!!!!!!##########    #####  #####");
    sprintf(TomatoeLife[1][5], "   @!@!!!!!!!!@@##############!!!!!!!####--########!!!!!!!!!!!!!#######     ##  ##   ");
    sprintf(TomatoeLife[1][6], "    @!!@!!!!!!##########!!!!!!!!!!########--############################    ##  ##   ");
    sprintf(TomatoeLife[1][7], "    @!!!!!@!!#############################--##############################           ");
    sprintf(TomatoeLife[1][8], "     @!!!!!###############################--###############################          ");
    sprintf(TomatoeLife[1][9], "     @!!!!!################################--##############################          ");
    sprintf(TomatoeLife[1][10], "      @!!!!################################--##############################          ");
    sprintf(TomatoeLife[1][11], "      @!!!!################################--##############################          ");
    sprintf(TomatoeLife[1][12], "       @!!!!###############################--##############################          ");
    sprintf(TomatoeLife[1][13], "       @!!!!###############################--##############################          ");
    sprintf(TomatoeLife[1][14], "         @!!!##############################--#############################           ");
    sprintf(TomatoeLife[1][15], "           @!############################################################            ");
    sprintf(TomatoeLife[1][16], "              ##########################################################             ");
    sprintf(TomatoeLife[1][17], "               ########################################################              ");
    sprintf(TomatoeLife[1][18], "                 ####################################################                ");
    sprintf(TomatoeLife[1][19], "                   ################################################                  ");
    sprintf(TomatoeLife[1][20], "                      ###########################################                    ");
    sprintf(TomatoeLife[1][21], "                         #####################################                       ");
    sprintf(TomatoeLife[1][22], "                             #############################                           ");
    sprintf(TomatoeLife[1][23], "                                     #############                                   ");

    sprintf(TomatoeLife[0][0],  "                                                           !!!!             ##  ##   ");
    sprintf(TomatoeLife[0][1],  "                 !!!!!!!!!!                        !!!!!!!!!!               ##  ##   ");
    sprintf(TomatoeLife[0][2],  "                     !!!!!!!!!!!!!!!!!@-##!!!!!!!!!!!!!!!!               #####  #####");
    sprintf(TomatoeLife[0][3],  "                      ########!!!!!!!!#@-!!!!!!!################                     ");
    sprintf(TomatoeLife[0][4],  "                   ##############!!!!!!!!--!!!!!!!!!!!!!!!!##########    #####  #####");
    sprintf(TomatoeLife[0][5],  "   @!@!!!!!!!!@@##############!!!!!!!####--########!!!!!!!!!!!!!#######     ##  ##   ");
    sprintf(TomatoeLife[0][6],  "    @!!@!!!!!!##########!!!!!!!!!!########--############################    ##  ##   ");
    sprintf(TomatoeLife[0][7],  "    @!!!!!@!!#############################--##############################           ");
    sprintf(TomatoeLife[0][8],  "     @!!!!!###############################--###############################          ");
    sprintf(TomatoeLife[0][9],  "     @!!!!!################################--##############################          ");
    sprintf(TomatoeLife[0][10], "      @!!!!################################--##############################          ");
    sprintf(TomatoeLife[0][11], "      @!!!!################################--##############################          ");
    sprintf(TomatoeLife[0][12], "       @!!!!###############################--##############################          ");
    sprintf(TomatoeLife[0][13], "       @!!!!###############################--##############################          ");
    sprintf(TomatoeLife[0][14], "         @!!!##############################--#############################           ");
    sprintf(TomatoeLife[0][15], "           @!##############################--############################            ");
    sprintf(TomatoeLife[0][16], "              #############################--###########################             ");
    sprintf(TomatoeLife[0][17], "               ############################--##########################              ");
    sprintf(TomatoeLife[0][18], "                 ##########################--########################                ");
    sprintf(TomatoeLife[0][19], "                   ########################--######################                  ");
    sprintf(TomatoeLife[0][20], "                      ####################--#####################                    ");
    sprintf(TomatoeLife[0][21], "                         #################--##################                       ");
    sprintf(TomatoeLife[0][22], "                             ############--###############                           ");
    sprintf(TomatoeLife[0][23], "                                     ###-#########                                   ");
}

//Colour Palette
/*
_ = brown
# = red
@ = black
! = green
. = white
& = blue
* = cyan
- = magenta
1 = Space(Black)
*/