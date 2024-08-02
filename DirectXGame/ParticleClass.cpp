#include "ParticleClass.h"

ParticleClass::ParticleClass() {}

ParticleClass::~ParticleClass() {
	for (int i = 0; i < kParticleNum; i++) {
		/*if (child[i] != nullptr) {

		}*/
		delete child[i];
	}
}

void ParticleClass::Init(Model* model, const Vector3& pos) {
	worldTransform_.Initialize();
	worldTransform_.translation_ = pos;
	model_ = model;

	worldTransform_.UpdateMatrix();
	currentTime = 0;
	isDead = false;
}
void ParticleClass::Update() {
	currentTime++;

	for (int i = 0; i < kParticleNum; i++) {

		if (child[i] == nullptr) {
			child[i] = new ParticleChildClass;

			Vector3 rotate = RandomValue(rotateMin, rotateMax);
			Vector3 move = RandomValue(moveMin, moveMax);
			child[i]->Init(model_, worldTransform_.translation_, rotate, move);
			break;
		} 
	}
	for (int i = 0; i < kParticleNum; i++) {
		if (child[i] != nullptr) {
			child[i]->Update();
			if (child[i]->GetIsDead()) {
				/*delete child[i];
				child[i] = nullptr;*/
			}
		}
	}
	if (currentTime > 60 * 4) {
		isDead = true;
	}
}

void ParticleClass::Draw(ViewProjection& viewProjection) {

	for (int i = 0; i < kParticleNum; i++) {

		if (child[i] != nullptr) {
			child[i]->Draw(viewProjection);
		}
	}
}

Vector3 ParticleClass::RandomValue(const Vector3& min, const Vector3& max) {
	std::random_device rd;
	std::mt19937 gen(rd());
	/*int ranX;
	int ranY;
	int ranZ;*/

	std::uniform_int_distribution<> ranX((int)min.x, (int)max.x);
	std::uniform_int_distribution<> ranY((int)min.y, (int)max.y);
	std::uniform_int_distribution<> ranZ((int)min.z, (int)max.z);

	return {(float)ranX(gen) / 100, (float)ranY(gen) / 100, (float)ranZ(gen) / 100};
}
