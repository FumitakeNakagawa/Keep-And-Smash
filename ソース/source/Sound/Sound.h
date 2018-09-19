#pragma once

#define	Hertz	44100	/*�T���v�����O���g��*/

/*WAV�t�@�C�����*/
enum
{
	BGM_TITLE,
	BGM_MAIN,
	SE_SMASH,
	SE_CATCH,
	SE_GOAL,
	SE_SELECT,
	SE_WHISTLE,
	SE_WIN,
	SE_DRAW,
	SE_LOSE,
};

//////////////////////////////////////
//			Sound�N���X				//
//////////////////////////////////////
class Sound
{
private:
	LPDSSTREAM ogg;	/*OGG�t�@�C��*/
public:
	/*����*/
	bool Initialize();
	/*WAV�ǂݍ���*/
	void LoadWAV(int no, LPSTR filename);
	/*WAV�Đ�*/
	void PlayWAV(int no, bool loop = false);
	/*WAV��~*/
	void StopWAV(int no);
	/*WAV���ʐݒ�*/
	void VolumeWAV(int no, int&vol);	//vol:0�`10000
	/*WAV��Ԏ擾*/
	bool StateWAV(int no);
	/*OGG�ǂݍ���&�Đ�*/
	void LoadOGG(LPSTR filename);
	/*OGG��~*/
	void StopOGG();

};

extern Sound*sound;