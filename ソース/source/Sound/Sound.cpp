#include	"../IEX/iextreme.h"
#include	"Sound.h"

Sound*	sound = nullptr;

//////////////////////////////////////
//			�����E���				//
//////////////////////////////////////
/*����*/
bool Sound::Initialize()
{
	LoadWAV(BGM_TITLE, "DATA\\sound\\BGM.wav");
	LoadWAV(BGM_MAIN, "DATA\\sound\\BGM2.wav");
	LoadWAV(SE_SMASH, "DATA\\sound\\smash.wav");
	LoadWAV(SE_CATCH, "DATA\\sound\\catch.wav");
	LoadWAV(SE_GOAL, "DATA\\sound\\goal.wav");
	LoadWAV(SE_SELECT, "DATA\\sound\\select.wav");
	LoadWAV(SE_WHISTLE, "DATA\\sound\\whistle.wav");
	LoadWAV(SE_WIN, "DATA\\sound\\win.wav");
	LoadWAV(SE_DRAW, "DATA\\sound\\draw.wav");
	LoadWAV(SE_LOSE, "DATA\\sound\\lose.wav");

	return true;
}

//////////////////////////////////////
//			WAV�ǂݍ���				//
//////////////////////////////////////
/*WAV�ǂݍ���*/
void Sound::LoadWAV(int no, LPSTR filename)
{
	IEX_SetWAV(no, filename);
}

//////////////////////////////////////
//			WAV�Đ��E��~			//
//////////////////////////////////////
/*�Đ�*/
void Sound::PlayWAV(int no, bool loop)
{
	if (!StateWAV(no))
	{
		IEX_PlaySound(no, loop);
	}
}
/*��~*/
void Sound::StopWAV(int no)
{
	IEX_StopSound(no);
}

//////////////////////////////////////
//		WAV��Ԑݒ�E�擾			//
//////////////////////////////////////
/*�{�����[������*/
void Sound::VolumeWAV(int no, int&vol)
{
	if (vol > DSBVOLUME_MAX)
	{
		vol = DSBVOLUME_MAX;
		return;
	}
	if (vol < DSBVOLUME_MIN)
	{
		vol = DSBVOLUME_MIN;
		return;
	}

	IEX_SetSoundVolume(no, vol);
}
/*��Ԏ擾*/
bool Sound::StateWAV(int no)
{
	bool ret;

	if (IEX_GetSoundStatus(no))	ret = true;
	else	ret = false;

	return ret;
}

//////////////////////////////////////
//		OGG�ǂݍ��݁��Đ�			//
//////////////////////////////////////
/*OGG�ǂݍ���&�Đ�*/
void Sound::LoadOGG(LPSTR filename)
{
	ogg = IEX_PlayStreamSound(filename);
}

//////////////////////////////////////
//			OGG��~					//
//////////////////////////////////////
/*OGG��~*/
void Sound::StopOGG()
{
	if (ogg)
	{
		IEX_StopStreamSound(ogg);
		ogg = nullptr;
	}
}
