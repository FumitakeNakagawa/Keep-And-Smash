#include	"Player.h"
#include	"../Particle/Particle.h"

#define GRAVITY -0.05f

//-----------------------------------------------------------------------------------------
//
//		初期化
//	
//----------------------------------------------------------------------------------------
void Player::Initialize()
{
	SetCursorPos(960, 300);

	GetCursorPos(&mousePoint);
	mouseReverse = GetSystemMetrics(SM_SWAPBUTTON);
	pos = Vector3(0.0f, 6.0f, 18.0f);
	move = Vector3(0.0f, 0.0f, 0.0f);
	scale = Vector3(1.0f, 1.0f, 1.0f);
	rot = Vector3(0.0f, 0.0f, 0.0f);
	obj = std::make_unique<iexMesh>((char*)"DATA\\Mullet\\01.imo");
	pow = 1.0f;

	sphere.center = pos;
	sphere.radius = 2.0f;

	state = State::MOVE;

	smash = false;
	gather = false;
	smashTimer = 90;
	gatherTimer = 120;
	smashStep = 0;
}

//	スマッシュ関数
void Player::Smash()
{
	if (state == State::SMASH_WAIT)
	{
		smashTimer--;
		if (smashTimer < 0)
		{
			smashTimer = 45;
			state = State::MOVE;
		}
		return;
	}

	if (GetKeyState(VK_LBUTTON) < 0 && state != State::SMASH_WAIT)
	{
		state = State::SMASH;
		pow = 1.75f;
	}
	else
		state = State::MOVE;

}


//	くっつき関数
void Player::Gathers()
{
	if (GetKeyState(VK_RBUTTON) < 0)
	{
		state = State::GATHER;
		gatherTimer--;
		if (gatherTimer <= 0)
		{
			state = State::GATHER_WAIT;
			pow = 0.8f;
		}

	}
	if (!(GetKeyState(VK_RBUTTON) < 0) && state == State::GATHER)
	{
		pow = 1.2f;
		state = State::MOVE;
		gatherTimer = 120;
		gather = true;
	}
	if (state == State::GATHER_WAIT)
	{
		if (!(GetKeyState(VK_RBUTTON) < 0))
			state = State::MOVE;
	}

}

//--------------------------------------------------------
//
//		更新
//
//-------------------------------------------------------
float Player::Update(iexMesh* mesh)
{
	GetCursorPos(&mousePoint);
	oldMousePoint = mousePoint;
	POINT p;
	SetCursorPos(960, 540);
	GetCursorPos(&mousePoint);

	p.x = oldMousePoint.x - mousePoint.x;
	p.y = oldMousePoint.y - mousePoint.y;

#ifdef _DEBUG

	if (KEY_Get(KEY_DOWN))	move.z += 0.03125f;
	if (KEY_Get(KEY_UP))	move.z -= 0.03125f;
	if (KEY_Get(KEY_LEFT))	move.x += 0.03125f;
	if (KEY_Get(KEY_RIGHT))	move.x -= 0.03125f;

#endif // _DEBUG


	Smash();
	if (state != State::SMASH&& state != State::SMASH_WAIT)
		Gathers();
	if (state == State::MOVE)
		gatherTimer = 120;


	move = Vector3(-p.x*0.005f, 0.0f, p.y*0.005f);
	float dist = 3.0f;

	if (move.x > dist)move.x = dist;
	if (move.x < -dist)move.x = -dist;
	if (move.z > dist)move.z = dist;
	if (move.z < -dist)move.z = -dist;
	
	//壁判定
	pos = Particle::MoveWallJudg(mesh, pos, move, sphere.radius);
	if (pos.z < .0f)pos.z = 0.0f;

	pos.y = 6.0f;

	sphere.center = pos;

	return pow;
}


//------------------------------------------------------
//
//		描画
//
//------------------------------------------------------
void Player::Render()
{
	obj->SetPos(pos);
	obj->SetAngle(rot);
	obj->SetScale(scale);

	obj->Update();
	obj->Render();

#ifdef _DEBUG
	char str[256];
	switch (state)
	{
	case Base_Player::State::MOVE:
		wsprintf(str, "State:Move");
		break;
	case Base_Player::State::SMASH:
		wsprintf(str, "State:Smash");
		break;
	case Base_Player::State::GATHER:
		wsprintf(str, "State:Gather");
		break;
	}

	IEX_DrawText(str, 10, 200, 100, 100, 0xFFFFFFFF);

	wsprintf(str, "%d,%d", mousePoint.x, mousePoint.y);
	IEX_DrawText(str, 10, 300, 100, 100, 0xFFFFFFFF);

	sprintf(str, "%.1f,%.1f", move.x, move.z);
	IEX_DrawText(str, 10, 400, 100, 100, 0xFFFFFFFF);
#endif // 

}
