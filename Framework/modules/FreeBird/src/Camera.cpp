#include "Camera.h" 

#include <GLM/gtc/matrix_transform.hpp> 
#include <iostream>

namespace freebird
{
	Camera::Camera() :
		_isOrtho(false),
		_orthoHeight(10.0f),
		nearPlane(0.1f),
		farPlane(1000.0f),
		fovRads(glm::degrees(90.0f)),
		aspectRatio(1.0f),
		pos(glm::vec3(0.0f)),
		normal(glm::vec3(0.0f, 0.0f, 1.0f)),
		up(glm::vec3(0.0f, 1.0f, 0.0f)), // Using Y-up coordinate system by default 
		view(glm::mat4(1.0f)),
		projection(glm::mat4(1.0f)),
		viewProj(glm::mat4(1.0f)),
		isDirty(true)
	{
		__CalculateProjection();
	}

	void Camera::SetPosition(const glm::vec3& position) {
		pos = position;
		__CalculateView();
	}

	void Camera::SetForward(const glm::vec3& forward) {
		normal = forward;
		__CalculateView();
	}

	void Camera::LookAt(const glm::vec3& point) {
		normal = -glm::normalize(pos - point);
		__CalculateView();
	}

	void Camera::SetUp(const glm::vec3& up) {
		this->up = up;
		__CalculateView();
	}

	void Camera::ResizeWindow(int windowWidth, int windowHeight) {
		aspectRatio = static_cast<float>(windowWidth) / static_cast<float>(windowHeight);
		__CalculateProjection();
	}

	void Camera::SetFovRadians(float value) {
		fovRads = value;
		__CalculateProjection();
	}

	void Camera::SetFovDegrees(float value) {
		SetFovRadians(glm::radians(value));
	}

	void Camera::SetIsOrtho(bool isOrtho)
	{
		_isOrtho = isOrtho;
		__CalculateProjection();
	}

	const glm::mat4& Camera::GetViewProjection() const {
		if (isDirty) {
			viewProj = projection * view;
			isDirty = false;
		}
		return viewProj;
	}

	void Camera::__CalculateProjection()
	{
		if (_isOrtho) {
			projection = glm::ortho(
				-_orthoHeight * aspectRatio, _orthoHeight * aspectRatio,
				-_orthoHeight, _orthoHeight,
				nearPlane, farPlane);
		}
		else {
			projection = glm::perspective(fovRads, aspectRatio, nearPlane, farPlane);
		}
		isDirty = true;
	}

	void Camera::__CalculateView() {
		view = glm::lookAt(pos, pos + normal, up);;
		isDirty = true;
	}
}