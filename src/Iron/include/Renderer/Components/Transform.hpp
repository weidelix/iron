#pragma once

#include "pch.hpp"
#include "Core.hpp"
#include "Renderer/Shader.hpp"

namespace Iron
{
	struct IRON_API Position
	{
	private:
		glm::vec3 m_position;

	public:
		Position();
		Position(const glm::vec3 &position);
		void SetPosition(const glm::vec3 &position);
		void SetPosition(const Position &position);
		glm::vec3 &GetPosition();
	};

	struct IRON_API Rotation
	{
	private:
		glm::vec3 m_rotation;

	public:
		Rotation();
		Rotation(const glm::vec3 &rotation);
		void SetRotation(const glm::vec3 &rotation);
		void SetRotation(const Rotation &rotation);
		glm::vec3 &GetRotation();
	};

	struct IRON_API Scale
	{
	private:
		glm::vec3 m_scale;

	public:
		Scale();
		Scale(const glm::vec3 &scale);
		void SetScale(const glm::vec3& scale);
		void SetScale(const Scale &scale);
		glm::vec3 &GetScale();
		
	};

	struct IRON_API LocalPosition
	{
	private:
		glm::vec3 m_localPosition;
	
	public:
		LocalPosition(const glm::vec3 &localPos);
		glm::vec3 &GetLocalPosition();
	};

	class IRON_API Transform
	{
	private:
		std::shared_ptr<Shader> m_shader;
		glm::mat4 m_model;
		struct Position m_position;
		struct Rotation m_rotation;
		struct Scale m_scale;
		//struct LocalPosition m_localPosition;

	public:
		Transform();
		Transform(const std::shared_ptr<Shader> &shader, const glm::vec3 &position);
		Transform(const std::shared_ptr<Shader> &shader);
		~Transform();

		struct Position &GetPosition();
		struct Rotation &GetRotation();
		struct Scale &GetScale();

		void SetPosition(const Position &position);
		void SetRotation(const Rotation &rotation);
		void SetScale(const Scale &scale);
	};
}