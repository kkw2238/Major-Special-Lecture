#include "stdafx.h"
#include "Camera.h"


Camera::Camera(float winWidth, float winHeight)
{
	m_vec3Position = glm::vec3(0.0f, 0.0f, 5.0f);
	m_vec3LookAt = glm::vec3(0.0f, 0.0f, 0.0f);
	m_vec3Up = glm::vec3(0.0f, 1.0f, 0.0f);

	m_mat4x4View = glm::lookAt(m_vec3Position, m_vec3LookAt, m_vec3Up);
	//m_mat4x4Proj = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 2.0f);
	m_mat4x4Proj = glm::perspectiveFovRH(45.0f, winWidth, winHeight, 0.0f, 10.0f);
	m_mat4x4ProjView = m_mat4x4Proj * m_mat4x4View;
	// Test
}


Camera::~Camera()
{
}
