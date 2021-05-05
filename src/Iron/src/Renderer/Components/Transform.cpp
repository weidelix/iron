#include "Renderer/Components/Transform.hpp"
#include "Renderer/Renderer.hpp"

namespace Iron
{
	Position::Position(const glm::vec3 &position)
		:m_position(position)
	{

	}

	glm::vec3 &Position::GetPosition()
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

	glm::vec3 &Rotation::GetRotation()
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

	Scale::Scale(const glm::vec3 &scale)
		:m_scale(scale)
	{

	}

	glm::vec3 &Scale::GetScale()
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

	LocalPosition::LocalPosition(const glm::vec3 &localPos)
		:m_localPosition(localPos)
	{

	}

	glm::vec3 &LocalPosition::GetLocalPosition()
	{
		return m_localPosition;
	}

	Transform::Transform()
		:m_position(glm::vec3(0, 0, 0)),
		 m_rotation(glm::vec3(0, 0, 0)),
		 m_scale(glm::vec3(0, 0, 0)),
		 m_shader(),
		 m_model(1.0)
	{
		m_shader->SetMat4x4("model", m_model);
	}

	Transform::Transform(const std::shared_ptr<Shader>& shader)
		:m_position(glm::vec3(0, 0, 0)),
		 m_rotation(glm::vec3(0, 0, 0)),
		 m_scale(glm::vec3(0, 0, 0)),
		 m_shader(shader),
		 m_model(1.0)
	{
		m_shader->SetMat4x4("model", m_model);
	}

	Transform::~Transform()
	{

	}
	
	void Transform::SetPosition(const struct Position &position)
	{
		m_position.SetPosition(position);
		m_model = glm::translate(m_model, m_position.GetPosition());
	
		m_shader->SetMat4x4("model", m_model);
	}
	
	void Transform::SetRotation(const struct Rotation &rotation)
	{
		m_rotation.SetRotation(rotation);
		m_model = glm::rotate(m_model, m_rotation.GetRotation().x, { 1.0f, 0.0f, 0.0f });
		m_model = glm::rotate(m_model, m_rotation.GetRotation().y, { 0.0f, 1.0f, 0.0f });
		m_model = glm::rotate(m_model, m_rotation.GetRotation().z, { 0.0f, 0.0f, 1.0f });
		
		m_shader->SetMat4x4("model", m_model);
	}
	
	void Transform::SetScale(const struct Scale &scale)
	{
		m_scale.SetScale(scale);
		m_model = glm::scale(m_model, m_scale.GetScale());
		
		m_shader->SetMat4x4("model", m_model);
	}

	struct Position &Transform::Transform::GetPosition()
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
}