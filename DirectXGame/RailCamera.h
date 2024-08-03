#pragma once
#include <WorldTransform.h>
#include <ViewProjection.h>
#ifdef _DEBUG
#include <imgui.h>

#endif // _DEBUG
#include <Input.h>

#include "ShakeClass.h"
class RailCamera
{
public:
	void Init(const Vector3& worldPos,const Vector3& rotate);
	void Update();
	
	const ViewProjection& GetViewProjection() { return viewprojection_; }
	const WorldTransform& GetWorldTransform() { return worldTransfome_; }
	void ShakeStart();

private:
	WorldTransform worldTransfome_;
	ViewProjection viewprojection_;

	Vector3 velocity_ = { 0,0,0 };
	Vector3 rotate_ = { 0.0f,0.000f,0.0f };
	float rotateSpeed = 0.05f;
	Input* input_ = nullptr;
	ShakeClass* shake = nullptr;

};

