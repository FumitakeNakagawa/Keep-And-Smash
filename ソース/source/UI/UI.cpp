#include "../../IEX/iextreme.h"
#include "..\\UI\UI.h"




//*****************************************************************************************************************************
//
//	UIsceneMain
//
//*****************************************************************************************************************************
//初期化
void UISceneMain::Initialize()
{
	frame = std::make_unique<iex2DObj>((char*)"DATA\\UI\\frame.png");
	fontScore = std::make_unique<iex2DObj>((char*)"DATA\\UI\\font_score.png");
	fontTime = std::make_unique<iex2DObj>((char*)"DATA\\UI\\font_time.png");
	subject = std::make_unique<iex2DObj>((char*)"DATA\\UI\\main_subject.png");

	scorePlayer = 0;
	scoreEnemy = 0;
	time = 90 * 60;
}

//更新
void UISceneMain::Update(int scorePlayer, int scoreEnemy, int time, int t_player, int t_enemy)
{
	this->time--;
	timePlayer = t_player;
	timeEnemy = t_enemy;
}

//描画
void UISceneMain::Render(iexView* view, const Vector3& posPlayer, const Vector3& posEnemy)
{
	//背景
	subject->Render(0, 0, 2048, 1080, 0, 0, 2048, 1024, RS_COPY, 0xFFFFFFFF, 9999.0f);

	//スコア(飾り)
	frame->Render(0, 0, 480, 480, 0, 0, 512, 512, RS_COPY, 0xFFFFFFFF, 9999.0f);
	frame->Render(1920 - 480, 0, 480, 480, 0, 0, 512, 512, RS_COPY, 0xFFFFFFFF, 9999.0f);
	//プレイヤースコア(飾り)
	fontScore->Render((int)(480*0.5 - 198*0.5),           35, 198, 198, 128*3,                                        128*2,                                        128, 128, RS_COPY, 0xFFFFFFFF, 9999.0f);
	fontScore->Render((int)(480*0.5 - 128*0.5),          210, 128, 128, 128*2,                                        128*2,                                        128, 128, RS_COPY, 0xFFFFFFFF, 9999.0f);
	//プレイヤースコア
	fontScore->Render((int)(480*0.5 - 96*0.5 - 116*0.5), 296,  96,  96, 128*((int)(scorePlayer*0.01) % 4),            128*((int)(scorePlayer*0.01) / 4),            128, 128, RS_COPY, 0xFFFFFFFF, 9999.0f);
	fontScore->Render((int)(480*0.5 - 96*0.5),           296,  96,  96, 128*((int)((int)(scorePlayer*0.1) % 10) % 4), 128*((int)((int)(scorePlayer*0.1) % 10) / 4), 128, 128, RS_COPY, 0xFFFFFFFF, 9999.0f);
	fontScore->Render((int)(480*0.5 - 96*0.5 + 116*0.5), 296,  96,  96, 128*((int)(scorePlayer % 10) % 4),            128*((int)(scorePlayer % 10) / 4),            128, 128, RS_COPY, 0xFFFFFFFF, 9999.0f);
	//エネミー(AI)スコア(飾り)
	fontScore->Render(1920 - (int)(480*0.5 + 198*0.5),           35, 198, 198, 128*0,                                       128*3,                                       128, 128, RS_COPY, 0xFFFFFFFF, 9999.0f);
	fontScore->Render(1920 - (int)(480*0.5 + 128*0.5),          210, 128, 128, 128*2,                                       128*2,                                       128, 128, RS_COPY, 0xFFFFFFFF, 9999.0f);
	//エネミー(AI)スコア
	fontScore->Render(1920 - (int)(480*0.5 + 96*0.5 + 116*0.5), 296,  96,  96, 128*((int)(scoreEnemy*0.01) % 4),            128*((int)(scoreEnemy*0.01) / 4),            128, 128, RS_COPY, 0xFFFFFFFF, 9999.0f);
	fontScore->Render(1920 - (int)(480*0.5 + 96*0.5),           296,  96,  96, 128*((int)((int)(scoreEnemy*0.1) % 10) % 4), 128*((int)((int)(scoreEnemy*0.1) % 10) / 4), 128, 128, RS_COPY, 0xFFFFFFFF, 9999.0f);
	fontScore->Render(1920 - (int)(480*0.5 + 96*0.5 - 116*0.5), 296,  96,  96, 128*((int)(scoreEnemy % 10) % 4),            128*((int)(scoreEnemy % 10) / 4),            128, 128, RS_COPY, 0xFFFFFFFF, 9999.0f);

	//残り時間
	fontTime->Render(1920 - 200,           1080 - 220, 220, 220, 128*(((int)(time / 60) % 10) % 4), 128*(((int)(time / 60) % 10) / 4), 128, 128, RS_COPY, 0xFFFFFFFF, 9999.0f);
	fontTime->Render(1920 - (220+240*0.5), 1080 - 220, 220, 220, 128*(((int)(time / 60) / 10) % 4), 128*(((int)(time / 60) / 10) / 4), 128, 128, RS_COPY, 0xFFFFFFFF, 9999.0f);

	D3DCAPS9 caps;
	HRESULT result = iexSystem::Device->GetDeviceCaps(&caps);
	if (FAILED(result))OutputDebugString("Error: キャプスの取得に失敗");

	unsigned long shoudAlphaTest = caps.AlphaCmpCaps & D3DPCMPCAPS_GREATEREQUAL;
	if (shoudAlphaTest)
	{
		iexSystem::Device->SetRenderState(D3DRS_ALPHAREF, (DWORD)0x000000A0);
		iexSystem::Device->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		iexSystem::Device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);
	}

	//描画
	iexSystem::Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);	//カリングオフ

	//くっつきゲージ
	Vector3 out;
	//プレイヤー
	view->ConversionScreen(out, posPlayer);
	//枠
	subject->Render(out.x - 150, out.y - 220, 300, 200, 0, 1080, 500, 500, RS_COPY, 0xFFFFFFFF, out.z);
	//ゲージ
	int a = 300 * (timePlayer / 120.0f);
	if (timePlayer <= 0)
	{
		a = 0;
	}
	subject->Render(out.x - 150 + (300 - (300 * timePlayer / 120.0f))*0.26, out.y - 220, a, 200, 500, 1080, 500, 500, RS_COPY, 0xFFFFFFFF, out.z);

	//エネミー
	//view->ConversionScreen(out, posEnemy);
	////枠
	//subject->Render(out.x - 150, out.y - 200, 300, 200, 0, 1080, 500, 500, RS_COPY, 0xFFFFFFFF, out.z);
	////ゲージ
	//subject->Render(out.x - 150 + (300 - (300 * timeEnemy / 60.0f))*0.26, out.y - 200, 300 * (timeEnemy / 60.0f), 200, 500, 1080, 500, 500, RS_COPY, 0xFFFFFFFF, out.z);

	//アルファテストオフ
	if (shoudAlphaTest)
		iexSystem::Device->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}



//*****************************************************************************************************************************
//
//	UISceneTitle
//
//*****************************************************************************************************************************
//初期化
void UISceneTitle::Initialize()
{
	subject1 = std::make_unique<iex2DObj>((char*)"DATA\\UI\\title_subject1.png");
	subject2 = std::make_unique<iex2DObj>((char*)"DATA\\UI\\title_subject2.png");

	pushBotton = false;
}

//更新
void UISceneTitle::Update(bool botton, POINT mousePoint)
{
	pushBotton = botton;
	this->mousePoint = mousePoint;
}

//描画
void UISceneTitle::Render()
{
	//背景
	subject1->Render(0, 0, 1920, 1080, 0, 0, 1920, 1024);
	//タイトル
	subject2->Render(-160, -380, 2048, 1600, 0, 0, 2048, 2048);
	//ボタン
	if (pushBotton) subject1->Render(1920 - 660 - 100, 660, 660, 500, 500 + 660, 1080, 660, 500);
	else            subject1->Render(1920 - 660 - 100, 660, 660, 500, 500, 1080, 660, 500);
	//マウスポインタ
	subject1->Render(mousePoint.x, mousePoint.y, 100, 100, 200, 1268, 117, 139);
}


//*****************************************************************************************************************************
//
//	UISceneResult
//
//*****************************************************************************************************************************
//初期化
void UISceneResult::Initialize(int ps,int es)
{
	subject1 = std::make_unique<iex2DObj>((char*)"DATA\\UI\\result_subject1.png");
	subject2 = std::make_unique<iex2DObj>((char*)"DATA\\UI\\result_subject2.png");
	subject3 = std::make_unique<iex2DObj>((char*)"DATA\\UI\\title_subject1.png");
	fontScore = std::make_unique<iex2DObj>((char*)"DATA\\UI\\font_score.png");
	character = std::make_unique<iex2DObj>((char*)"DATA\\UI\\result_char.png");

	botton = NON;

	scorePlayer = ps;
	scoreEnemy = es;
}

//更新
void UISceneResult::Update(int b, POINT mousePoint)
{
	botton = b;
	this->mousePoint = mousePoint;
}

//描画
void UISceneResult::Render()
{
	//ボタン
	if (botton == NON)
	{
		subject1->Render(60, 700, 650, 300, 0, 300, 650, 300);			//リトライ
		subject1->Render(800, 700, 650, 300, 650, 300, 650, 300);			//タイトル
	}
	else if (botton == RETRY)
	{
		subject1->Render(60, 700, 650, 300, 0, 600, 650, 300);
		subject1->Render(800, 700, 650, 300, 650, 300, 650, 300);
	}
	else if (botton == TITLE)
	{
		subject1->Render(60, 700, 650, 300, 0, 300, 650, 300);
		subject1->Render(800, 700, 650, 300, 650, 600, 650, 300);
	}

	//プレイヤースコア
	fontScore->Render((int)(600 - 198 * 0.5), 300, 198, 198, 128 * 3, 128 * 2, 128, 128);
	fontScore->Render((int)(950 - 198 * 0.5 - 213 * 0.5), 300, 198, 198, 128 * ((int)(scorePlayer*0.01) % 4), 128 * ((int)(scorePlayer*0.01) / 4), 128, 128);
	fontScore->Render((int)(950 - 198 * 0.5), 300, 198, 198, 128 * ((int)((int)(scorePlayer*0.1) % 10) % 4), 128 * ((int)((int)(scorePlayer*0.1) % 10) / 4), 128, 128);
	fontScore->Render((int)(950 - 198 * 0.5 + 213 * 0.5), 300, 198, 198, 128 * ((int)(scorePlayer % 10) % 4), 128 * ((int)(scorePlayer % 10) / 4), 128, 128);

	//エネミー(AI)スコア
	fontScore->Render((int)(600 - 198 * 0.5), 500, 198, 198, 128 * 0, 128 * 3, 128, 128);
	fontScore->Render((int)(950 - 198 * 0.5 - 213 * 0.5), 500, 198, 198, 128 * ((int)(scoreEnemy*0.01) % 4), 128 * ((int)(scoreEnemy*0.01) / 4), 128, 128);
	fontScore->Render((int)(950 - 198 * 0.5), 500, 198, 198, 128 * ((int)((int)(scoreEnemy*0.1) % 10) % 4), 128 * ((int)((int)(scoreEnemy*0.1) % 10) / 4), 128, 128);
	fontScore->Render((int)(950 - 198 * 0.5 + 213 * 0.5), 500, 198, 198, 128 * ((int)(scoreEnemy % 10) % 4), 128 * ((int)(scoreEnemy % 10) / 4), 128, 128);

	//勝敗
	if (scorePlayer > scoreEnemy)		//勝利
	{
		subject1->Render(800 - 650 * 0.5, 0, 650, 300, 0, 0, 650, 300);
		character->Render(1920 - 1024, 1080 - 1240, 1024, 1260, 1024, 0, 1024, 1260);
	}
	else if (scorePlayer < scoreEnemy)	//敗北
	{
		subject1->Render(800 - 810 * 0.5, 0, 810, 300, 650, 0, 810, 300);
		character->Render(1920 - 1024, 1080 - 1240, 1024, 1240, 0, 0, 1024, 1260);
	}
	else if (scorePlayer == scoreEnemy)	//引き分け
	{
		subject2->Render(800 - 1000 * 0.5, 0, 1000, 300, 0, 800, 1000, 400);
		character->Render(1920 - 1024, 1080 - 1240, 1024, 1260, 2048, 0, 1024, 1260);
	}

	//マウスポインタ
	subject3->Render(mousePoint.x, mousePoint.y, 100, 100, 200, 1268, 117, 139);

}
