#pragma once
#include <WorldTransform.h>
#include <ViewProjection.h>
#include <Model.h>
#ifdef _DEBUG

#include <imgui.h>
#endif
class SkyDome
{
public:
	~SkyDome();
	void Init(Model* model);
	void Update();
	void Draw(const ViewProjection& viewProjection);

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;

	WorldTransform worldTransform2_;
	float moveSpeed= 0.5f;
	
};

