#include "iextreme.h"
#include "..\\system\Framework.h"

#include "sceneTitle.h"
#include"sceneMain.h"

#include	"../Sound/Sound.h"

//*****************************************************************************************************************************
//
//	������
//
//*****************************************************************************************************************************
bool sceneTitle::Initialize()
{
	//	���ݒ�
	iexLight::SetFog(800, 1000, 0);

	//	�J�����ݒ�
	view = std::make_unique<iexView>();
	//view->Set(Vector3(0.0f, 40.0f, 50.0f), Vector3(0.0f, -10.0f, -30.0f));

	ui = std::make_unique<UISceneTitle>();
	ui->Initialize();

	pushBotton = false;

	//�}�E�X�ݒ�
	ShowCursor(FALSE);
	GetCursorPos(&mousePoint);
	mouseReverse = GetSystemMetrics(SM_SWAPBUTTON);

	sound->PlayWAV(BGM_TITLE, true);

	return true;
}



//*****************************************************************************************************************************
//
//	���
//
//*****************************************************************************************************************************
sceneTitle::~sceneTitle()
{

}



//*****************************************************************************************************************************
//
//	�X�V
//
//*****************************************************************************************************************************
void sceneTitle::Update()
{
	//�}�E�X�ݒ�
	GetCursorPos(&mousePoint);
	mouseReverse = GetSystemMetrics(SM_SWAPBUTTON);

	if (mousePoint.x <= 1780 && mousePoint.x >= 1208 && mousePoint.y <= 1058 && mousePoint.y >= 772) pushBotton = true;
	else pushBotton = false;

	//UI�X�V
	ui->Update(pushBotton, mousePoint);

	//�V�[���؂�ւ�
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000 && pushBotton)
	{
		sound->StopWAV(BGM_TITLE);

		sound->PlayWAV(SE_SELECT);
		MainFrame->ChangeScene(new sceneMain());
	}
}



//*****************************************************************************************************************************
//
//	������
//
//*****************************************************************************************************************************
void sceneTitle::Render()
{
	//��ʃN���A
	view->Activate();
	view->Clear();

	//UI�`��
	ui->Render();

#ifdef _DEBUG
	char	str[64];
	wsprintf(str, "Mouse pos : %d %d", mousePoint.x, mousePoint.y);
	IEX_DrawText(str, 10, 30, 400, 20, 0xFF000000);
#endif // _DEBUG

}
