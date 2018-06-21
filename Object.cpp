#include "stdafx.h"
#include "Object.h"


Object::Object()
{
	m_vec3ModelPos			= glm::vec3(0.0f, 0.0f, 0.0f);
	m_vec3ModelRotate		= glm::vec3(0.0f, 0.0f, 0.0f);
	m_vec3ModelScaling		= glm::vec3(1.0f, 1.0f, 1.0f);

	m_mat4x4ModelPos		= glm::translate(glm::mat4(1.0f), m_vec3ModelPos);
	m_mat4x4ModelRotate		= glm::eulerAngleXYZ(m_vec3ModelRotate.x, m_vec3ModelRotate.y, m_vec3ModelRotate.z);
	m_mat4x4ModelScaling	= glm::scale(glm::mat4(1.0f), m_vec3ModelScaling);

	m_mat4x4ModelMatrix = m_mat4x4ModelScaling * m_mat4x4ModelRotate * m_mat4x4ModelPos;
}


Object::~Object()
{
}

void Object::Update()
{
	m_mat4x4ModelPos = glm::translate(glm::mat4(1.0f), m_vec3ModelPos);
	m_mat4x4ModelRotate = glm::eulerAngleXYZ(m_vec3ModelRotate.x, m_vec3ModelRotate.y, m_vec3ModelRotate.z);
	m_mat4x4ModelScaling = glm::scale(glm::mat4(1.0f), m_vec3ModelScaling);

	m_mat4x4ModelMatrix = m_mat4x4ModelScaling * m_mat4x4ModelRotate * m_mat4x4ModelPos;
}
