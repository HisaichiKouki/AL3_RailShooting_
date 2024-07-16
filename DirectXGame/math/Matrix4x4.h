#pragma once
/// <summary>
/// 4x4行列
/// </summary>
struct Matrix4x4 final {
	float m[4][4];

	Matrix4x4 operator+(const Matrix4x4& m2) {
		Matrix4x4 resultMatrix = {};
		for (int row = 0; row < 4; row++) {
			for (int col = 0; col < 4; col++) {
				resultMatrix.m[row][col] = +m[row][col] + m2.m[row][col];
			}
		}
		return resultMatrix;
	}
	Matrix4x4 operator-(const Matrix4x4& m2) {
		Matrix4x4 resultMatrix = {};
		for (int row = 0; row < 4; row++) {
			for (int col = 0; col < 4; col++) {
				resultMatrix.m[row][col] = m[row][col] - m2.m[row][col];
			}
		}
		return resultMatrix;
	}
	Matrix4x4 operator*(const Matrix4x4& m2) {
		Matrix4x4 resultMatrix = {};
		for (int row = 0; row < 4; row++) {
			for (int col = 0; col < 4; col++) {
				for (int z = 0; z < 4; z++) {
					resultMatrix.m[row][col] += m[row][z] * m2.m[z][col];
				}
			}
		}
		return resultMatrix;
	}
};
