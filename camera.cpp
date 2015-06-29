#include "stdafx.h"
#include "camera.h"
#include "System.h"


Camera::Camera()
{
	m_projectionMatrix = math::createProjectionMatrix(systemptr->cameraSet.fov, (float)systemptr->displaySet.screenWidth,
		(float)systemptr->displaySet.screenHeight, systemptr->cameraSet.cameraZNear, systemptr->cameraSet.cameraZFar);
	m_forward = math::vec3(0, 0, -1);
	m_up = math::vec3(0, 1, 0);
}

Camera::Camera(const math::vec3& pos) : Camera()
{
	m_pos = pos;
}

void Camera::initPerspectiveProjectionMatrix(float screenw, float screenh, float fov, float znear, float zfar)
{
	m_projectionMatrix = math::createProjectionMatrix(fov, screenw, screenh, znear, zfar);
}

void Camera::initOrthoProjectionMatrix(float left, float right, float bottom, float top, float near_, float far_)
{
	m_projectionMatrix = math::createOrthoProjectionMatrix(left, right, bottom, top, near_, far_);
}

const math::mat4& Camera::matrix()
{
	return m_transformMatrix;
}

const math::mat4& Camera::projection()
{
	return m_projectionMatrix;
}

math::vec3 Camera::forwardVector()
{
	return m_forward;
}

math::vec3 Camera::leftVector()
{
	return math::cross(m_up, m_forward).normalize();
}

math::vec3 Camera::upVector()
{
	return m_up;
}

void Camera::flyAt(const math::vec3& direction, float amount)
{
	m_pos -= direction*amount;
}

void Camera::flyForwards(float distance)
{
	m_pos -= m_forward*distance;
}

void Camera::flyBackwards(float distance)
{
	m_pos += m_forward*distance;
}

void Camera::flyLeft(float distance)
{
	m_pos -= leftVector()*distance;
}

void Camera::flyRight(float distance)
{
	m_pos += leftVector()*distance;
}

void Camera::flyUp(float distance)
{
	m_pos.y -= distance;
}

void Camera::flyDown(float distance)
{
	m_pos.y += distance;
}

void Camera::lookLeft(float angle)
{
	math::Quaternion quat;
	math::vec3 hAxis = math::cross(math::vec3(0, 1, 0), m_forward).normalize();
	quat.fromAxisRotation(math::vec3(0, 1, 0), angle);
	quat.rotateVector(m_forward);
	m_forward.normalize();
	m_up = math::cross(m_forward, hAxis);
	m_up.normalize();
}

void Camera::lookRight(float angle)
{
	lookLeft(-angle);
}

void Camera::lookDown(float angle)
{
	math::Quaternion quat;
	math::vec3 hAxis = math::cross(math::vec3(0, 1, 0), m_forward).normalize();
	quat.fromAxisRotation(hAxis, angle);
	quat.rotateVector(m_forward);
	m_forward.normalize();
	m_up = math::cross(m_forward, hAxis);
	m_up.normalize();
}

void Camera::lookUp(float angle)
{
	lookDown(-angle);
}

void Camera::generateMatrix()
{
	m_rot.normalize();

	math::vec3 f = m_forward.normalize();
	math::vec3 r = math::cross(m_up.normalize(), f);
	math::vec3 u = math::cross(f, r);

	m_transformMatrix = math::mat4(r.x,r.y,r.z,0,
						u.x,u.y,u.z,0,
						f.x,f.y,f.z,0,
						0,0,0,1);

	m_transformMatrix *= m_rot.toMatrix();
	m_transformMatrix *= math::createTranslationMatrix(m_pos);	
}

void Camera::reset()
{
	m_forward.reset();
	m_up.reset();

	m_transformMatrix.reset();
}






/*

Camera::Camera(float x, float y, float z) : Camera()
{
position = math::vec3(x, y, z);
forward = math::vec3(1.0f, 0.0f, 0.0f);
up = math::vec3(0.0f, 1.0f, 0.0f);

pitch = yaw = roll = 0;
}

math::vec3 Camera::getForwardVector()
{
math::vec3 out = forward;
out.normalize();
return out;
}

math::vec3 Camera::getUpVector()
{
math::vec3 out = up;
out.normalize();
return out;
}
math::vec3 Camera::getRightVector() //or left...?
{
math::vec3 out = math::cross(forward,up);
out.normalize();
return out;
}



void Camera::moveAbsolute(float x, float y, float z)
{
position.x += x;
position.y += y;
position.z += z;
}


void Camera::setPosition(float x, float y, float z)
{
position.x = x;
position.y = y;
position.z = z;

}

void Camera::moveForwards(float distance)
{
math::vec3 tempforward = math::cross(forward, up);
position -= tempforward.rotate(-pitch, forward)*distance;
}

void Camera::moveBackwards(float distance)
{
moveForwards(-distance);
}

void Camera::moveLeft(float distance)
{
moveRight(-distance);
}

void Camera::moveRight(float distance)
{
position += forward*distance;
}

void Camera::moveUp(float distance)
{
position.y -= distance;
}
void Camera::moveDown(float distance)
{
position.y += distance;
}



//Takes in radians
void Camera::rotateRight(float angle)
{
rotateLeft(-angle);
}

void Camera::rotateLeft(float angle)
{
//forward.rotate(-angle, math::vec3(0, 1, 0));
//up.rotate(-angle, math::vec3(0, 1, 0));
roll -= angle;
forward.rotate(angle, math::vec3(0.f, 1.f, 0.f));
}


void Camera::rotateUp(float angle) //implement limiting?
{
//math::vec3 axis = cross(forward, up);
//pitch += angle;
//forward.rotate(angle, axis);
//up.rotate(angle, axis);
pitch += angle;
}

void Camera::rotateDown(float angle) //Dodgy
{
rotateUp(-angle);
}



void Camera::generateMatrix()
{
math::vec3 forward = this->forward;
math::vec3 up = this->up;

matrix.reset();
matrix *= math::createRotationMatrix(yaw, math::vec3(0.f, 0.f, 1.f));
matrix *= math::createRotationMatrix(pitch, math::vec3(1.f, 0.f, 0.f));
matrix *= math::createRotationMatrix(roll, math::vec3(0.f, 1.f, 0.f));

matrix *= math::createTranslationMatrix(position);


deltaMove = math::vec3(0, 0, 0);
}

void Camera::reset()
{
position = math::vec3(0.0f, 0.0f, 0.0f);
forward = math::vec3(1.0f, 0.0f, 0.0f);
up = math::vec3(0.0f, 1.0f, 0.0f);

pitch = yaw = roll = 0;
}
*/