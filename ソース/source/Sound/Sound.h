#pragma once

#define	Hertz	44100	/*サンプリング周波数*/

/*WAVファイル種類*/
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
//			Soundクラス				//
//////////////////////////////////////
class Sound
{
private:
	LPDSSTREAM ogg;	/*OGGファイル*/
public:
	/*生成*/
	bool Initialize();
	/*WAV読み込み*/
	void LoadWAV(int no, LPSTR filename);
	/*WAV再生*/
	void PlayWAV(int no, bool loop = false);
	/*WAV停止*/
	void StopWAV(int no);
	/*WAV音量設定*/
	void VolumeWAV(int no, int&vol);	//vol:0～10000
	/*WAV状態取得*/
	bool StateWAV(int no);
	/*OGG読み込み&再生*/
	void LoadOGG(LPSTR filename);
	/*OGG停止*/
	void StopOGG();

};

extern Sound*sound;