#include "Renderer/Components/Transform.hpp"
#include "Renderer/Renderer.hpp"

namespace Iron
{
	Vector3::Vector3(const glm::vec3 &vec)
		: m_vec(vec)
	{ }

	Vector3::Vector3()
		: m_vec(0.0f, 0.0f, 0.0f)
	{ }

	Vector3::Vector3(const Vector3 &vec)
		: m_vec(vec.m_vec)
	{ }

	Vector3::Vector3(float x, float y, float z)
		: m_vec(x, y, z)
	{ }

	Vector3 Vector3::Normalize(const Vector3 &vec)
	{
		return Vector3(glm::normalize(vec.m_vec));
	}

	Quaternion::Quaternion(const Vector3 &rotation)
		:m_rotation(glm::quat(rotation.m_vec))
	{

	}

	void Quaternion::SetRotation(const glm::mat4 &rotation)
	{
		m_rotation = glm::quat(rotation);
	}

	Vector3 Quaternion::ToEuler(const Quaternion &quat) 
	{
		return Vector3(glm::eulerAngles(quat.m_rotation));
	}

	Quaternion Quaternion::ToQuat(const Vector3 &euler) 
	{
		return Quaternion(euler.m_vec);
	}

	Transform::Transform()
		:position(0, 0, 0),
		 rotation(Vector3(0, 0, 0)),
		 eulerAngle(Quaternion::ToEuler(rotation.m_rotation)),
		 scale(1, 1, 1),
		 m_model(1.0)
	{
		
	}

	Transform::~Transform() { }
	
	void Transform::SetPosition(const struct Vector3 &position)
	{
		this->position = position;

		m_model = glm::translate(glm::mat4(1.0), position.m_vec);
		m_model = m_model * glm::toMat4(rotation.m_rotation);
		m_model = glm::scale(m_model, scale.m_vec);

		m_right = glm::rotate(rotation.m_rotation, glm::vec3(1.0f, 0.0f, 0.0f));
		m_up    = glm::rotate(rotation.m_rotation, glm::vec3(0.0f, 1.0f, 0.0f));
		m_front = glm::rotate(rotation.m_rotation, glm::vec3(0.0f, 0.0f, 1.0f));
	}

	void Transform::SetRotation(const struct Quaternion &rotation)
	{
		this->rotation = rotation;
		
		m_model = glm::translate(glm::mat4(1.0), position.m_vec);
		m_model = m_model * glm::toMat4(rotation.m_rotation);
		m_model = glm::scale(m_model, scale.m_vec);

		m_right = glm::rotate(rotation.m_rotation, glm::vec3(1.0f, 0.0f, 0.0f));
		m_up    = glm::rotate(rotation.m_rotation, glm::vec3(0.0f, 1.0f, 0.0f));
		m_front = glm::rotate(rotation.m_rotation, glm::vec3(0.0f, 0.0f, 1.0f));
	}
	
	void Transform::SetScale(const struct Vector3 &scale)
	{
		this->scale = scale;
		
		m_model = glm::translate(glm::mat4(1.0), position.m_vec);
		m_model = m_model * glm::toMat4(rotation.m_rotation);
		m_model = glm::scale(m_model, scale.m_vec);
	}

	struct Vector3 &Transform::GetPosition()
	{
		return position;
	}
	
	struct Quaternion &Transform::GetRotation()
	{
		return rotation;
	}

	struct Vector3 &Transform::GetEulerAngle()
	{
		return eulerAngle;
	}
	
	struct Vector3 &Transform::GetScale()
	{
		return scale;
	}

	glm::mat4 &Transform::GetMatrix()
	{
		return m_model;
	}

	void Transform::LookAt(const Vector3 &lookAt)
	{
		auto &pos = position.m_vec;

		glm::mat4 mat = glm::lookAt(pos, pos + lookAt.m_vec, { 0.0f, 1.0f, 0.0f });

		m_model = glm::inverse(mat);
		rotation.SetRotation(m_model);
		eulerAngle = Quaternion::ToEuler(rotation.m_rotation);

		m_front = Vector3(-mat[0][2], -mat[1][2], -mat[2][2]);
		m_up    = Vector3( mat[0][1],  mat[1][1],  mat[2][1]);
		m_right = Vector3(-mat[0][0], -mat[1][0], -mat[2][0]);
	}
	
	const Vector3 &Transform::Front() 
	{
		return m_front;
	}

	const Vector3 &Transform::Up() 
	{
		return m_up;
	}

	const Vector3 &Transform::Right() 
	{
		return m_right;
	}
}