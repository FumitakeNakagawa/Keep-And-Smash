#include	"iextreme.h"
#include	"..\\system\Framework.h"
#include	"..\\system/system.h"

#include	"sceneMain.h"
#include	"sceneResult.h"

#include	"../Sound/Sound.h"

//*****************************************************************************************************************************
//
//	�O���[�o���ϐ�
//
//*****************************************************************************************************************************
//	�J�����p

//	�X�e�[�W�p




//*****************************************************************************************************************************
//
//	������
//
//*****************************************************************************************************************************

bool sceneMain::Initialize()
{
	ShowCursor(FALSE);
	//	���ݒ�
	iexLight::SetFog(800, 1000, 0);

	manual = std::make_unique<iex2DObj>((char*)"DATA\\UI\\manual.png");

	//	���s��
	mesh = std::make_unique<iexMesh>((char*)"DATA\\stage\\stage.imo");
	mesh2 = std::make_unique<iexMesh>((char*)"DATA\\stage\\stage_.imo");

	//	�J�����ݒ�
	view = std::make_unique<iexView>();
	view->Set(Vector3(0.0f, 35.0f, 40.0f), Vector3(0.0f, -20.0f, -20.0f));

	//	�v���C���[������
	pl = std::make_unique<Player>();
	pl->Initialize();

	//	�p�b�N������
	Pack::ResizeModelContainer(3);
	Pack::LoadMesh("DATA\\Packs\\01.imo", 0);
	Pack::LoadMesh("DATA\\Packs\\02.imo", 1);
	Pack::LoadMesh("DATA\\Packs\\03.imo", 2);
	pad = std::make_unique<PackManager>();
	pad->Initialize();

	char str[32];

	chappy.resize(15);
	for (int i = 0; i < chappy.size(); i++)
	{
		sprintf(str, "DATA\\Chappy\\chappy_%d.png", i);
		chappy[i] = std::make_unique<iex2DObj>(str);
	}


	ai = std::make_unique<AI>();
	ai->Initialize();

	//UI������
	ui = std::make_unique<UISceneMain>();
	ui->Initialize();

	step = 0;

	effect = std::make_unique<Effect>();
	effect->Initialize();

	sound->PlayWAV(BGM_MAIN, true);

	num = 0;
	result = std::make_unique<sceneResult>();
	return true;
}

sceneMain::~sceneMain()
{
	Pack::ReleaseMesh(0);
	Pack::ReleaseMesh(1);
	Pack::ReleaseMesh(2);
}

//*****************************************************************************************************************************
//
//		�X�V
//
//*****************************************************************************************************************************

void	sceneMain::Update()
{
	switch (step)
	{
	case 0:
		if (GetKeyState(VK_LBUTTON) < 0)
		{
			sound->PlayWAV(SE_SELECT);

			step++;
		}
		break;
	case 1:
		//�T�E���h
		sound->PlayWAV(SE_WHISTLE);
		//�T�E���h�I�������
		if(sound->StateWAV(SE_WHISTLE))step++;
		break;
	case 2:

		frame++;
		if (frame % 5==0)
		{
			num++;
			if (num >= chappy.size())
				num = 0;
		}
		//	�v���C���[�X�V
		pl->Update(mesh2.get());

		//	�J�����X�V
		ai->Update(mesh2.get(), pl.get(), pad.get());

		//	�G�X�V
		pad->Update(pl->GetMove()*pl->GetPow(), pl->GetSphere(), pl->GetStateB(), mesh2.get(), *ui.get());

		ui->Update(ui->GetPlayerScore(), ui->GetEnemyScore(), ui->GetTime(), pl->GetGatherTimer(), ai->GetGatherTimer());

		effect->Update();

		if (ui->GetTime() < 0)
			step++;
		break;
	case 3:
		//�T�E���h
		sound->PlayWAV(SE_WHISTLE);
		//�T�E���h�I�������
		if (sound->StateWAV(SE_WHISTLE))step++;
		break;
	case 4:
		sound->StopWAV(BGM_MAIN);

		result->Initialize(ui->GetPlayerScore(),ui->GetEnemyScore());
		//���U���g��ʂ�
		step++;
		break;
	case 5:
		result->Update();
	default:
		break;
	}

	
}

//*****************************************************************************************************************************
//
//		�`��֘A
//
//*****************************************************************************************************************************

void	sceneMain::Render()
{
	//	��ʃN���A
	view->Activate();
	view->Clear();

	if (step == 0)
		manual->Render(0, 0, 1920, 1080, 0, 0, 1920, 1080);
	
	
	
	//	�X�e�[�W�`��
	mesh->Render();

	ai->Render();
	//	�v���C���[�`��
	pl->Render();

	//	�G�`��
	pad->Render();

	//UI�`��

	ui->Render(view.get(), pl->GetPos(), ai->GetPos());
	if (step == 2)
		chappy[num]->Render(0, 570, 512, 512, 0, 0, 1024, 1024, RS_COPY, 0xFFFFFFFF, 9999.0f);
	effect->Render();


	if (step == 5)
	{
		iexPolygon::Rect(0, 0, 1920, 1080, RS_COPY, 0xCC000000);
		result->Render();
	}
}
