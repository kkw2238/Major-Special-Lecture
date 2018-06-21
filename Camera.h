#pragma once
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"

class Camera
{
public:
	Camera(float winWidth, float winHeight);
	~Camera();

public:
	glm::vec3 Pos() const		{ return m_vec3Position; }
	glm::vec3 LookAt() const	{ return m_vec3LookAt; }
	glm::vec3 Up() const		{ return m_vec3Up; }
	glm::mat4x4 ProjView() const{ return m_mat4x4ProjView; }

private:
	glm::vec3	m_vec3Position;
	glm::vec3	m_vec3LookAt;
	glm::vec3	m_vec3Up;

	glm::mat4x4 m_mat4x4Proj;
	glm::mat4x4 m_mat4x4View;
	glm::mat4x4 m_mat4x4ProjView;
};

