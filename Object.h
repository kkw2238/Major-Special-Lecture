#pragma once
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtx\euler_angles.hpp"

class Object
{
public:
	Object();
	~Object();

public:
	void Rotate(float x, float y, float z) { m_vec3ModelRotate.x += x; m_vec3ModelRotate.y += y; m_vec3ModelRotate.z += z; }
	void Rotate(glm::vec3 angles) { m_vec3ModelRotate += angles; };

	void Move(float x, float y, float z) { m_vec3ModelPos.x += x; m_vec3ModelPos.y += y; m_vec3ModelPos.z += z; }
	void Move(glm::vec3 distance) { m_vec3ModelPos += distance; };

	void Scale(float x, float y, float z) { m_vec3ModelScaling.x += x; m_vec3ModelScaling.y += y; m_vec3ModelScaling.z += z; }
	void Scale(glm::vec3 size) { m_vec3ModelScaling += size; };

	void Update();

public:
	glm::mat4 Matrix() const { return m_mat4x4ModelMatrix; }
	glm::mat4 RotateMatrix() const { return m_mat4x4ModelRotate; }
private:
	glm::mat4 m_mat4x4ModelPos;
	glm::mat4 m_mat4x4ModelRotate;
	glm::mat4 m_mat4x4ModelScaling;
	glm::mat4 m_mat4x4ModelMatrix;

	glm::vec3 m_vec3ModelPos;
	glm::vec3 m_vec3ModelRotate;
	glm::vec3 m_vec3ModelScaling;
};

