#include	"./iextreme.h"
#include	"../Player/Player.h"
#include	"../Pack/Pack.h"
#include	"Enemy.h"
#include	"../Particle/Particle.h"


float radian = 0.0f;
Vector3 axis1;
//初期化
void AI::Initialize()
{
	pos = Vector3(0.0f, 6.0f, -15.0f);
	move = Vector3(0.0f, 0.0f, 0.0f);
	scale = Vector3(1.0f,1.0f,1.0f);
	rot = Vector3(0.0f, 0.0f, 0.0f);
	obj = std::make_unique<iexMesh>((char*)"DATA\\Mullet\\02.imo");
	pow =0.0f;

	sphere.center = pos;
	sphere.radius = 0.25f;
	state = State::MOVE;
	gatherTimer = 0;
	smashTimer = 0;
	speed = 0.4f;
	posGoal = Vector3(0.0f, 4.0f, -21.0f);

	sphere.radius = 3.0f;
}

//更新
float AI::Update(iexMesh* mesh)
{
	return pow;
}

void AI::Update(iexMesh* mesh, Base_Player* player, PackManager* pack)
{
	if (smashTimer > 0)
	{
		smashTimer--;
	}

	Move(mesh, player, pack);
}

//移動
void AI::Move(iexMesh* mesh, Base_Player* player, PackManager* pack)
{
	//移動処理準備
	float cost = GoalRange;
	int num = -1;
	int i = 0;
	Vector3 packMove;
	Vector3 packPos;
	Vector3 front(0.0f, 0.0f, -1.0f);

	//一番近いパックを探す
	for (auto it = pack->GetList().begin(); it != pack->GetList().end(); it++)
	{
		//Vector3 vec = (*it)->GetPos() - pos;
		Vector3 vec = posGoal - (*it)->GetPos();
		//反対方向にボールが移動しているとき場合は無視
		if (Vector3Dot((*it)->GetMove(), front) < 0.0f) continue;
		if (vec.Length() < cost)
		{
			num = i;
			cost = vec.Length();
			packMove = (*it)->GetMove();
			packMove.y = 0.0f;
			packPos = (*it)->GetPos();
		}
		i++;
	}

	//こっちに向かってくる玉が無い場合
	if (num == -1) return;

	float packSpeed = packMove.Length();
	packMove.Normalize();
	Vector3 v = packPos - pos;
	v.Normalize();
	float dot = Vector3Dot(packMove, v);
	Vector3 axis;
	Vector3Cross(axis, packMove, -v);
	//反対方向にボールが移動しているときは反応しない
	if (Vector3Dot(packMove, Vector3(0.0f, 0.0f, -1.0f)) > 0.0f)
	{
		if (dot < 0.0)
		{
			Vector3 future = packPos + packMove * packSpeed * 20.0f;		//20フレーム先
			move = future - pos;
			Vector3 v1 = move;
			v1.Normalize();
			Vector3 v = future - packPos;
			if (move.LengthSq() < v.LengthSq() && Vector3Dot(packMove, v1) > 0.5f)
			{
				move = packPos - pos;
			}
			if (move.Length() > 1.0f) move.Normalize();
			//プロックが相手側に行かないようにする
			if (pos.z + move.z > 0.0f) move.z = 0.0f;
			//ボールの移動向きに到達していたら移動しない
			if (dot > -1.0f)
			{
				move *= speed;
				pos += move;
			}
			else
			{
				//if (axis.y > 0.0f)
				{
					move *= speed;
					pos += move;
				}
			}
		}
		//対象物の進む方向とかなり一致しているとき
		else
		{
			Vector3 v = packPos - pos;
			v.Normalize();
			float addrad = 1.047f;					//60°
			//if (Vector3Dot(Vector3(0.0f, 0.0f, 1.0f), v) < 0.0f) addrad = -addrad;
			if (Vector3Dot(Vector3(0.0f, 0.0f, 1.0f), packMove) < 0.0f) addrad = -addrad;
			radian = acosf(Vector3Dot(Vector3(0.0f, 0.0f, 1.0f), v));
			Vector3Cross(axis1, Vector3(0.0f, 0.0f, 1.0f), v);
			{
				if (axis1.y < 0.0f)
				{
					radian = -radian;
					//radian -= 0.5236f;             //30°ずらす
					radian += addrad;
				}
				else
				{
					//radian += 0.5236f;
					radian -= addrad;
				}
			}

			move = Vector3(sinf(radian), 0.0f, cosf(radian));
			move.Normalize();
			if (pos.z + move.z > 0.0f) move.z = 0.0f;
			move *= speed;
			pos += move;
		}
		//if (dot > 0.0f)
		//{
		//	Vector3 v = packPos - pos;
		//	v.Normalize();
		//	//radian = acosf(Vector3Dot(Vector3(0.0f, 0.0f, -1.0f), v));
		//	//Vector3Cross(axis1, Vector3(0.0f, 0.0f, -1.0f), v);
		//	//if (Vector3Dot(Vector3(0.0f, 0.0f, -1.0f), v) < 0.0f)
		//	//{
		//	//	if (axis1.y < 0.0f)
		//	//	{
		//	//		radian = -radian;
		//	//		//radian -= 0.5236f;             //30°ずらす
		//	//		radian -= 1.047f;
		//	//	}
		//	//	else
		//	//	{
		//	//		//radian += 0.5236f;
		//	//		radian += 1.047f;
		//	//	}
		//	//}
		//	float addrad = 1.047f;
		//	//if (Vector3Dot(Vector3(0.0f, 0.0f, 1.0f), v) < 0.0f) addrad = -addrad;
		//	if (Vector3Dot(Vector3(0.0f, 0.0f, 1.0f), packMove) < 0.0f) addrad = -addrad;
		//	radian = acosf(Vector3Dot(Vector3(0.0f, 0.0f, 1.0f), v));
		//	Vector3Cross(axis1, Vector3(0.0f, 0.0f, 1.0f), v);
		//	//if (Vector3Dot(Vector3(0.0f, 0.0f, 1.0f), v) < 0.0f)
		//	{
		//		if (axis1.y < 0.0f)
		//		{
		//			radian = -radian;
		//			//radian -= 0.5236f;             //30°ずらす
		//			radian += addrad;
		//		}
		//		else
		//		{
		//			//radian += 0.5236f;
		//			radian -= addrad;
		//		}
		//	}

		//	move = Vector3(sinf(radian), 0.0f, cosf(radian));
		//	move.Normalize();
		//	if (pos.z + move.z > 0.0f) move.z = 0.0f;
		//	move *= speed;
		//	pos += move;
		//}
	}

	//当たり判定
	Vector3 out;
	float dist = 3.0f;
	v = move;
	v.Normalize();
	
	//壁判定
	if (mesh->RayPick(&out, &pos, &v, &dist) > -1)
	{
		Particle::Collide(&pos, &move, 1.0f, 0.9f, 1.0f, &v);
	}
	if (mesh->RayPick(&out, &pos, &Vector3(0.0f, -1.0f, 0.0f), &dist) > -1)
	{
		pos.y = out.y;
		move.y = 0.0f;
	}

	//玉との判定
	for (auto it = pack->GetList().begin(); it != pack->GetList().end(); it++)
	{
		if (ColCircle(pos, sphere.radius, (*it)->GetPos(), (*it)->GetSphere().radius))
		{
			//玉分裂
			if (smashTimer <= 0)
			{
				if ((*it)->GetLevel() < 2)
				{
					state = State::SMASH;
					pack->BreakUp(&it, sphere, state);
					smashTimer = SmashTime;
					state = State::MOVE;
				}
			}

			//玉反射
			//Particle::Collide(&pos, &move, 1.0f, &(*it)->GetPos(), &(*it)->GetMove(), 1.0f, 0.9, 1.0f);
			Vector3 v = move;
			v.Normalize();
			Particle::Collide(&(*it)->GetPos(), &(*it)->GetMove(), &move, 1.0f, 0.1f, 1.0f, &v);
		}
	}
	sphere.center = pos;
}

void AI::NearObject()
{
	
}

void AI::FarObject()
{

}

//描画
void AI::Render()
{
	obj->SetPos(pos);
	obj->SetAngle(rot);
	obj->SetScale(scale);

	obj->Update();
	obj->Render();

#ifdef _DEBUG
	char	str[64];
	sprintf(str, "Enemy pos : %f %f %f\n", pos.x, pos.y, pos.z);
	IEX_DrawText(str, 10, 50, 400, 20, 0xFFFFFF00);
	sprintf(str, "Enemy rad : %f", radian);
	IEX_DrawText(str, 10, 70, 400, 20, 0xFFFFFF00);
	sprintf(str, "axis : %f %f %f", axis1.x, axis1.y, axis1.z);
	IEX_DrawText(str, 10, 110, 400, 20, 0xFFFFFF00);
#endif // _DEBUG

}

//円同士のあたり判定
bool AI::ColCircle(const Vector3& pos_A, const float rad_A, const Vector3& pos_B, const float rad_B)
{
	float  Dir_x = pos_B.x - pos_A.x;
	float  Dir_z = pos_B.z - pos_A.z;
	float  Dir = Dir_x * Dir_x + Dir_z * Dir_z;
	float  Rad = rad_A + rad_B;
	Rad = Rad * Rad;

	if (Dir < Rad)	return true;

	return  false;		//  当たっていない
}