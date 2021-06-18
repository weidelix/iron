#include "Renderer/Components/Transform.hpp"
#include "Renderer/Renderer.hpp"

namespace Iron
{
	Position::Position(const glm::vec3 &position)
		:m_position(position)
	{

	}

	const glm::vec3 &Position::GetPosition() const
	{
		return m_position;
	}

	void Position::SetPosition(const glm::vec3 &position)
	{
		m_position = position;
	}

	void Position::SetPosition(const Position &position)
	{
		m_position = position.m_position;
	}

	void Position::MoveByX(float x) { m_position.x+=x; }
	void Position::MoveByY(float y) { m_position.y+=y; }
	void Position::MoveByZ(float z) { m_position.z+=z; }

	const glm::quat &Quaternion::GetQuaternion() const
	{
		return m_rotation;
	}

	Quaternion::Quaternion(const glm::vec3 &rotation)
		:m_rotation(rotation)
	{

	}

	void Quaternion::SetRotation(const glm::quat &rotation)
	{
		m_rotation = rotation;
	}

	void Quaternion::SetRotation(const Quaternion &rotation)
	{
		m_rotation = rotation.m_rotation;
	}

	Scale::Scale(const glm::vec3 &scale)
		:m_scale(scale)
	{

	}

	const glm::vec3 &Scale::GetScale() const
	{
		return m_scale;
	}

	void Scale::SetScale(const glm::vec3 &scale)
	{
		m_scale = scale;
	}

	void Scale::SetScale(const Scale &scale)
	{
		m_scale = scale.m_scale;
	}

	void Scale::ScaleByX(float x) { m_scale.x+=x; }
	void Scale::ScaleByY(float y) { m_scale.y+=y; }
	void Scale::ScaleByZ(float z) { m_scale.z+=z; }

	LocalPosition::LocalPosition(const glm::vec3 &localPos)
		:m_localPosition(localPos)
	{

	}

	const glm::vec3 &LocalPosition::GetLocalPosition() const
	{
		return m_localPosition;
	}

	glm::vec3 Quaternion::ToEuler(glm::quat &quat) 
	{
		return glm::eulerAngles(quat);
	}

	glm::quat Quaternion::ToQuat(glm::vec3 &euler) 
	{
		return glm::quat(euler);
	}

	Transform::Transform()
		:m_position(glm::vec3(0, 0, 0)),
		 m_rotation(glm::vec3(0, 0, 0)),
		 m_scale(glm::vec3(1, 1, 1)),
		 m_model(1.0)
	{
		
	}

	Transform::~Transform() { }
	
	void Transform::SetPosition(const struct Position &position)
	{
		m_position = position;

		m_model = glm::translate(glm::mat4(1.0), m_position.GetPosition());
		m_model = m_model * glm::toMat4(m_rotation.GetQuaternion());
		m_model = glm::scale(m_model, m_scale.GetScale());

		m_right = glm::rotate(m_rotation.GetQuaternion(), glm::vec3(1.0f, 0.0f, 0.0f));
		m_up    = glm::rotate(m_rotation.GetQuaternion(), glm::vec3(0.0f, 1.0f, 0.0f));
		m_front = glm::rotate(m_rotation.GetQuaternion(), glm::vec3(0.0f, 0.0f, 1.0f));
	}

	void Transform::SetPosition(const glm::vec3 &position)
	{
		m_position.SetPosition(position);

		m_model = glm::translate(glm::mat4(1.0), m_position.GetPosition());
		m_model = m_model * glm::toMat4(m_rotation.GetQuaternion());
		m_model = glm::scale(m_model, m_scale.GetScale());

		m_right = glm::rotate(m_rotation.GetQuaternion(), glm::vec3(1.0f, 0.0f, 0.0f));
		m_up    = glm::rotate(m_rotation.GetQuaternion(), glm::vec3(0.0f, 1.0f, 0.0f));
		m_front = glm::rotate(m_rotation.GetQuaternion(), glm::vec3(0.0f, 0.0f, 1.0f));
	}

	void Transform::SetRotation(const struct Quaternion &rotation)
	{
		m_rotation = rotation;
		
		m_model = glm::translate(glm::mat4(1.0), m_position.GetPosition());
		m_model = m_model * glm::toMat4(m_rotation.GetQuaternion());
		m_model = glm::scale(m_model, m_scale.GetScale());

		m_right = glm::rotate(m_rotation.GetQuaternion(), glm::vec3(1.0f, 0.0f, 0.0f));
		m_up    = glm::rotate(m_rotation.GetQuaternion(), glm::vec3(0.0f, 1.0f, 0.0f));
		m_front = glm::rotate(m_rotation.GetQuaternion(), glm::vec3(0.0f, 0.0f, 1.0f));
	}

	void Transform::SetRotation(const glm::quat &rotation)
	{
		m_rotation.SetRotation(rotation);
		
		m_model = glm::translate(glm::mat4(1.0), m_position.GetPosition());
		m_model = m_model * glm::toMat4(m_rotation.GetQuaternion());
		m_model = glm::scale(m_model, m_scale.GetScale());

		m_right = glm::rotate(m_rotation.GetQuaternion(), glm::vec3(1.0f, 0.0f, 0.0f));
		m_up    = glm::rotate(m_rotation.GetQuaternion(), glm::vec3(0.0f, 1.0f, 0.0f));
		m_front = glm::rotate(m_rotation.GetQuaternion(), glm::vec3(0.0f, 0.0f, 1.0f));

		m_eulerAngle = glm::eulerAngles(m_rotation.GetQuaternion());
	}
	
	void Transform::SetScale(const struct Scale &scale)
	{
		m_scale = scale;
		
		m_model = glm::translate(glm::mat4(1.0), m_position.GetPosition());
		m_model = m_model * glm::toMat4(m_rotation.GetQuaternion());
		m_model = glm::scale(m_model, m_scale.GetScale());
	}

	void Transform::SetScale(const glm::vec3 &scale)
	{
		m_scale.SetScale(scale);
		
		m_model = glm::translate(glm::mat4(1.0), m_position.GetPosition());
		m_model = m_model * glm::toMat4(m_rotation.GetQuaternion());
		m_model = glm::scale(m_model, m_scale.GetScale());
	}

	struct Position &Transform::GetPosition()
	{
		return m_position;
	}
	
	struct Quaternion &Transform::GetRotation()
	{
		return m_rotation;
	}

	glm::vec3 &Transform::GetEulerAngle()
	{
		return m_eulerAngle;
	}
	
	struct Scale &Transform::GetScale()
	{
		return m_scale;
	}

	glm::mat4 &Transform::GetMatrix()
	{
		return m_model;
	}

	void Transform::LookAt(const glm::vec3 &lookAt)
	{
		auto &pos = m_position.GetPosition();

		glm::mat4 mat = glm::lookAt(pos, pos + lookAt, { 0.0f, 1.0f, 0.0f });

		m_model = glm::inverse(mat);
		m_rotation.SetRotation(m_model);
		m_eulerAngle = glm::eulerAngles(m_rotation.GetQuaternion());

		m_front = glm::vec3(-mat[0][2], -mat[1][2], -mat[2][2]);
		m_up    = glm::vec3( mat[0][1],  mat[1][1],  mat[2][1]);
		m_right = glm::vec3(-mat[0][0], -mat[1][0], -mat[2][0]);
	}
	
	const glm::vec3 &Transform::Front() 
	{
		return m_front;
	}

	const glm::vec3 &Transform::Up() 
	{
		return m_up;
	}

	const glm::vec3 &Transform::Right() 
	{
		return m_right;
	}
}