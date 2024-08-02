#pragma once
#include <WorldTransform.h>
#include <stdlib.h>
#include <string>
//#include "Vector3AndMatrix4x4.h"
class Collider
{
public :
	float GetRadius() { return radius_; }
	void SetRadius(float radius) { radius_ = radius; }

	virtual void OnCollision(Collider *other);
	virtual void ExitCollision(Collider *other);
	virtual Vector3 GetWorldPosition() = 0;
	std::string GetName() { return name; }
	void SetName(const std::string& name_) { name = name_; }

private:
	float radius_ = 10.0f;
	std::string name;
};

