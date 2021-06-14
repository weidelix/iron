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

	const glm::vec3 &Rotation::GetRotation() const
	{
		return m_rotation;
	}

	Rotation::Rotation(const glm::vec3 &rotation)
		:m_rotation(rotation)
	{

	}

	void Rotation::SetRotation(const glm::vec3 &rotation)
	{
		m_rotation = rotation;
	}

	void Rotation::SetRotation(const Rotation &rotation)
	{
		m_rotation = rotation.m_rotation;
	}

	void Rotation::RotateByX(float x) { m_rotation.x+=x; }
	void Rotation::RotateByY(float y) { m_rotation.y+=y; }
	void Rotation::RotateByZ(float z) { m_rotation.z+=z; }

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

	Transform::Transform()
		:m_position(glm::vec3(0, 0, 0)),
		 m_rotation(glm::vec3(0, 0, 0)),
		 m_scale(glm::vec3(1, 1, 1)),
		 m_mat(1.0)
	{
		m_front = glm::normalize(m_position.GetPosition() - m_front);
		m_right = glm::normalize(cross(m_up, m_front));
		m_up    = glm::cross(m_front, m_right);
	}


	Transform::~Transform()
	{
	}
	
	void Transform::SetPosition(const struct Position &position)
	{
		m_position = position;
		m_mat = glm::translate(glm::mat4(1.0), position.GetPosition());

		// glm::vec3 pos = m_mat * m_position.
		// IRON

		// m_front = glm::normalize(m_position.GetPosition() - m_front);
		// m_right = glm::normalize(cross(m_up, m_front));
		// m_up    = glm::cross(m_front, m_right);
	}

	void Transform::SetPosition(const glm::vec3 &position)
	{
		m_position.SetPosition(position);
		m_mat = glm::translate(glm::mat4(1.0), position);

		// m_front = glm::normalize(m_position.GetPosition() - m_front);
		// m_right = glm::normalize(cross(m_up, m_front));
		// m_up    = glm::cross(m_front, m_right);
	}

	void Transform::SetRotation(const struct Rotation &rotation)
	{
		m_rotation = rotation;		
		m_mat = glm::rotate(m_mat, m_rotation.GetRotation().x, { 1.0f, 0.0f, 0.0f });
		m_mat = glm::rotate(m_mat, m_rotation.GetRotation().y, { 0.0f, 1.0f, 0.0f });
		m_mat = glm::rotate(m_mat, m_rotation.GetRotation().z, { 0.0f, 0.0f, 1.0f });
	}

	void Transform::SetRotation(const glm::vec3 &rotation)
	{
		m_rotation.SetRotation(rotation);
		m_mat = glm::rotate(m_mat, rotation.x, { 1.0f, 0.0f, 0.0f });
		m_mat = glm::rotate(m_mat, rotation.y, { 0.0f, 1.0f, 0.0f });
		m_mat = glm::rotate(m_mat, rotation.z, { 0.0f, 0.0f, 1.0f });
	}
	
	void Transform::SetScale(const struct Scale &scale)
	{
		m_scale = scale;
		m_mat = glm::scale(m_mat, m_scale.GetScale());
	}

	void Transform::SetScale(const glm::vec3 &scale)
	{
		m_scale.SetScale(scale);
		m_mat = glm::scale(m_mat, scale);
	}

	struct Position &Transform::GetPosition()
	{
		return m_position;
	}
	
	struct Rotation &Transform::GetRotation()
	{
		return m_rotation;
	}
	
	struct Scale &Transform::GetScale()
	{
		return m_scale;
	}

	glm::mat4 &Transform::GetMatrix()
	{
		return m_mat;
	}

	void Transform::LookAt(const glm::vec3 &lookAt)
	{
		glm::vec3 up(0.0f, 1.0f, 0.0f);
		auto &pos = m_position.GetPosition();
		m_mat = glm::lookAt(pos, pos + lookAt, up);

		m_right = glm::vec3(m_mat[0][0], m_mat[1][0], m_mat[2][0]);
		m_up    = glm::vec3(m_mat[0][1], m_mat[1][1], m_mat[2][1]);
		m_front = glm::vec3(m_mat[0][2], m_mat[1][2], m_mat[2][2]);
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