#include	"Pack.h"
#include	<iostream>
#include	<string>

#include	<stdlib.h>
#include	<time.h>
#include	"../Particle/Particle.h"
#include	"../UI/UI.h"
#include	"../Effect/Effect.h"

#include	"../Sound/Sound.h"

void PackManager::Initialize()
{
	padList.push_back(std::make_unique<Pack>());

	for (auto it = padList.begin(); it != padList.end(); it++)
		it->get()->Initialize();

	offset[0].pos = Vector3(-10.0f, 30.0f, 17.0f);
	offset[0].move = Vector3(0.1f, 0.0f, -0.1f);

	offset[1].pos = Vector3(12.0f, 14.0f, -20.0f);
	offset[1].move = Vector3(-0.1f, 0.0f, 0.1f);

	offset[2].pos = Vector3(10.0f, 14.0f, 17.0f);
	offset[2].move = Vector3(-0.1f, 0.0f, -0.1f);

	offset[3].pos = Vector3(-12.0f, 14.0f, -20.0f);
	offset[3].move = Vector3(0.1f, 0.0f, 0.1f);

	nextAppend = 0;

	timer = 0;

}

void PackManager::Append()
{
	padList.push_back(std::make_unique<Pack>());
	padList.back()->Initialize(offset[nextAppend].pos, offset[nextAppend].move);

	nextAppend++;
	if (nextAppend > 4)nextAppend = 0;
}

//�ʒǉ�
//����: 
/*
1:�C�e���[�^�[�̃|�C���^
2:���􂷂�ۂ�1�ڂ̏o���ʒu
3:���􂷂�ۂ�2�ڂ̏o���ʒu
*/
void PackManager::Append(std::list<std::unique_ptr<Pack>>::iterator* it, Vector3 p1, Vector3 p2, Vector3 m1, Vector3 m2)
{
	//1��
	padList.push_back(std::make_unique<Pack>());
	padList.back()->Initialize(p1, m1, (*it)->get()->GetLevel());

	//2��
	padList.push_back(std::make_unique<Pack>());
	padList.back()->Initialize(p2, m2, (*it)->get()->GetLevel());

	//���̋ʍ폜
	(*it) = padList.erase((*it));
}

//-------------------------------------------------------------------------------
//
//		�X�V
//
//------------------------------------------------------------------------------
void PackManager::Update(Vector3 move, Sphere sphere, Base_Player::State* state, iexMesh* mesh, UISceneMain& ui)
{

#ifdef _DEBUG

	if (KEY_Get(KEY_ENTER) == 3)
		Append(&padList.begin(), Vector3(), Vector3(-10.0f, 0.0f, 0.0f), Vector3(), Vector3());

#endif // _DEBUG
	ui.GetTime();
	timer++;
	if (timer % 90 == 0)Append();

	for (auto it = padList.begin(); it != padList.end(); )
	{
		bool goal = it->get()->Update(mesh);
		if (it->get()->GetPos().x > 13 || it->get()->GetPos().x < -13 ||
			it->get()->GetPos().z > 22 || it->get()->GetPos().z < -22)
		{
			it = padList.erase(it);
		}
		else if (goal)
		{
			if (!sound->StateWAV(SE_GOAL))sound->PlayWAV(SE_GOAL);

			if (it->get()->GetPos().z < .0f)
			{
				ui.SetPlayerScore(ui.GetPlayerScore() + it->get()->GetLevel());
			}
			if (it->get()->GetPos().z > .0f)
			{
				ui.SetEnemyScore(ui.GetEnemyScore() + it->get()->GetLevel());
			}
			it = padList.erase(it);
		}
		else
		{
			for (auto it2 = padList.begin(); it2 != padList.end(); ++it2)
			{
				if (it == it2)continue;

				//Pack���m�̓����蔻��
				if (ColCircle(it->get()->GetPos(), it->get()->GetSphere().radius * 5, it2->get()->GetPos(), it2->get()->GetSphere().radius * 5))
				{
					if (it->get()->GetMove().Length() >= (it->get()->GetPos() - it2->get()->GetPos()).Length() ||
						it2->get()->GetMove().Length() >= (it->get()->GetPos() - it2->get()->GetPos()).Length())
					{
						//���˕Ԃ�
						Collide(&it->get()->GetPos(), &it->get()->GetMove(), 1.0f, &it2->get()->GetPos(), &it2->get()->GetMove(), 1.0f, 0.9f, 1.0f);
					}
					else if (ColCircle2(it->get()->GetPos(), it->get()->GetSphere().radius, it2->get()->GetPos(), it2->get()->GetSphere().radius))
					{
						//���˕Ԃ�
						Collide(&it->get()->GetPos(), &it->get()->GetMove(), 1.0f, &it2->get()->GetPos(), &it2->get()->GetMove(), 1.0f, 0.9f, 1.0f);
					}
					if (*state == Base_Player::State::GATHER)
						it->get()->Gather(sphere, *it2->get());
				}
			}

			//Player��Pack�̓����蔻��
			if (ColCircle(sphere.center, sphere.radius * 5, it->get()->GetPos(), it->get()->GetSphere().radius * 5))
			{
				if (move.Length() >= (sphere.center - it->get()->GetPos()).Length() ||
					it->get()->GetMove().Length() >= (sphere.center - it->get()->GetPos()).Length())
				{
					BreakUp(&it, sphere, *state);

					//���˕Ԃ�
					Collide(&sphere.center, &move, 2.0f, &it->get()->GetPos(), &it->get()->GetMove(), 1.0f, 0.9f, 1.0f);
				}
				else if (ColCircle(sphere.center, sphere.radius, it->get()->GetPos(), it->get()->GetSphere().radius))
				{
					BreakUp(&it, sphere, *state);

					//���˕Ԃ�
					Collide(&sphere.center, &move, 2.0f, &it->get()->GetPos(), &it->get()->GetMove(), 1.0f, 0.9f, 1.0f);
				}
			}

			++it;
		}
	}
}

//����
bool PackManager::BreakUp(std::list<std::unique_ptr<Pack>>::iterator* it, Sphere s1, Base_Player::State state)
{
	if (state == Base_Player::State::SMASH)
	{
		if(sound->StateWAV(SE_SMASH))sound->PlayWAV(SE_SMASH);
		Effect::Smash((*it)->get()->GetPos(), (*it)->get()->GetMove());

		if ((*it)->get()->GetLevel() <= 2)
		{
			Vector3 n = (*it)->get()->GetPos() - s1.center;
			n.Normalize();
			Vector3 m1 = Vector3(sinf(100 * 0.01745f)*n.x - cos(100 * 0.01745f)*n.z, 0, cosf(100 * 0.01745f)*n.x + sin(100 * 0.01745f)*n.z);
			Vector3 m2 = Vector3(sinf(-50 * 0.01745f)*n.x - cos(-50 * 0.01745f)*n.z, 0, cosf(-50 * 0.01745f)*n.x + sin(-50 * 0.01745f)*n.z);

			m1.Normalize();
			m2.Normalize();

			Append(it, (*it)->get()->GetPos() + m1 * 3, (*it)->get()->GetPos() + m2 * 3, m1, m2);
			return true;
		}
	}
	else
		return false;
}

//-----------------------------------------------------------------
//
//		�`��
//
//-----------------------------------------------------------------
void PackManager::Render()
{
	for (auto it = padList.begin(); it != padList.end(); it++)
		it->get()->Render();

#ifdef _DEBUG
	std::string str = "PackSize:" + std::to_string(padList.size());
	IEX_DrawText((char*)str.c_str(), 10, 100, 200, 100, 0xFFFFFFFF);

#endif // DEBUG

}


void PackManager::Collide(Vector3*pos1, Vector3*move1, float mass1, Vector3*pos2, Vector3*move2, float mass2, float repulsion, float time)
{
	//���ʍ��v
	float totalWeight = mass1 + mass2;

	//������
	float repRate = (1 + repulsion*repulsion);

	//�Փˎ��x�N�g��
	Vector3 n = *pos2 - *pos1;
	n.Normalize();

	//���ώZ�o
	float dot = Vector3Dot((*move1 - *move2), n);

	//�萔�x�N�g��
	Vector3 constVec = n * (repRate*dot / totalWeight);

	//�Փˌ㑬�x�x�N�g��
	*move1 = constVec * -mass2 + *move1;
	*move2 = constVec * mass1 + *move2;

	//�Փˌ�ʒu
	*pos1 = *pos1 + *move1*time;
	*pos2 = *pos2 + *move2*time;

}

//�~���m�̂����蔻��
bool PackManager::ColCircle(Vector3 pos_A, const float rad_A, Vector3 pos_B, const float rad_B)
{
	float  Dir_x = pos_B.x - pos_A.x;
	float  Dir_z = pos_B.z - pos_A.z;
	float  Dir = Dir_x * Dir_x + Dir_z * Dir_z;
	float  Rad = rad_A + rad_B;
	Rad = Rad * Rad;

	if (Dir < Rad)	return true;

	return  false;		//  �������Ă��Ȃ�
}

//�~���m�̂����蔻��(���������߂�)
bool PackManager::ColCircle2(Vector3& pos_A, const float rad_A, Vector3& pos_B, const float rad_B)
{
	float  Dir_x = pos_B.x - pos_A.x;
	float  Dir_z = pos_B.z - pos_A.z;
	float  Dir = Dir_x * Dir_x + Dir_z * Dir_z;
	float  Rad = rad_A + rad_B;
	Rad = Rad * Rad;

	if (Dir < Rad)
	{
		Vector3	mid = (pos_A + pos_B) * 0.5f;
		Vector3	v = pos_A - pos_B;
		v.y = 0.0f;
		v.Normalize();
		float	d = (rad_A + rad_B) * 0.5f;


		pos_A = mid - v * d;
		pos_B = mid + v * d;

		return true;
	}

	return  false;		//  �������Ă��Ȃ�
}
