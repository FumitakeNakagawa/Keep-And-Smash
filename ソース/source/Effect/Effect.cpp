#include	"iextreme.h"
#include	"Effect.h"
#include	<stdlib.h>
#include	<time.h>


void Effect::Initialize()
{
	srand((unsigned)time(nullptr));
	iexParticle::Initialize("DATA\\particle.png", 10000);
}

void Effect::Update()
{
	iexParticle::Update();
}

void Effect::Render()
{
	iexParticle::Render();
}

void Effect::Smash(const Vector3& pos, const Vector3& move)
{
	Vector3 Pos, Move, Power;

	for (int i = 0; i < 25; i++)
	{
		Pos.x = pos.x + ((float)rand() / RAND_MAX);
		Pos.y = pos.y;
		Pos.z = pos.z + ((float)rand() / RAND_MAX);

		Move.x = move.x*0.5f + ((float)rand() / RAND_MAX) * 1.0f - 0.5f;
		Move.y = ((float)rand() / RAND_MAX) * 1.0f - 0.5f;
		Move.z = move.z*0.5f + ((float)rand() / RAND_MAX) * 1.0f - 0.5f;

		Power.x = 0.0f;
		Power.y = -0.02f;
		Power.z = 0.0f;

		iexParticle::Set(3, 0, 0xFFFFFF00, 60, 0, 40, 0xFFFFFF00, &Pos, &Move, &Power, 1, 1, 0.5f, RS_ADD);
	}
}
