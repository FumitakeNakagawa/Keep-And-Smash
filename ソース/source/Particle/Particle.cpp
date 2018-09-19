#include	"../IEX/iextreme.h"

#include	"Particle.h"

void Particle::Collide(Vector3*pos1, Vector3*move1, float mass1, Vector3*pos2, Vector3*move2, float mass2, float repulsion, float time)
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

void Particle::Collide(Vector3*pos, Vector3*move, float mass, float repulsion, float time,Vector3*normal)
{
	// ���ˌ㑬�x���Z�o
	normal->Normalize();

	*move = *move - *normal*((1 + repulsion)*Vector3Dot(*normal, *move));

	// �ړ��ʒu���v�Z
	*pos = *pos + *move * time;
}

void Particle::Collide(Vector3*pos, Vector3*move1, Vector3*move2, float mass, float repulsion, float time, Vector3*normal)
{
	// ���ˌ㑬�x���Z�o
	normal->Normalize();

	*move1 = *move1 - *normal*((1 + repulsion)*Vector3Dot(*normal, (*move1 - *move2)));

	// �ړ��ʒu���v�Z
	*pos = *pos + *move1 * time;
}

float Particle::WallDistJudg(iexMesh* mesh, Vector3&pos, Vector3&v, float r)
{
	Vector3 out;
	float d = 50.0f;

	Vector3 p = pos;
	Vector3 m = -v;
	int n = mesh->RayPick(&out, &p, &v, &d);
	if (n < 0)return FLT_MAX;

	Vector3 vec = out - pos;
	d = vec.Length();

	return d;
}

Vector3 Particle::MoveWallJudg(iexMesh* mesh, const Vector3&pos, const Vector3&move, float r)
{
	Vector3 p = pos;
	//�����x�N�g���␳
	Vector3 m = move;
	float md = m.Length();
	//�ړ��x�N�g�����K��
	m.Normalize();

	//�ǔ���
	Vector3 v = m;

	//�ǂ܂ł̋���
	float d = WallDistJudg(mesh, p, v, r);

	if (d >= 0 && d < md)
	{
		//�@�����K��
		v.Normalize();
		float cc = (m.x*v.x + m.z*v.z);

		//�߂荞�ݗʂ̌v�Z
		d = md - d;
		//�K�؂Ȉʒu�̎Z�o(�]���ɉ����߂�)
		m = move - v*cc*d*1.05f;

		//�i�s�����ă`�F�b�N
		md = m.Length();
		v = m;
		v.Normalize();
		p = pos;
		d = WallDistJudg(mesh, p, v, r);
		if (d<.0f || d>md)p += m;
	}
	else
	{
		p += move;
	}
	return p;
}