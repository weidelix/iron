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
		Position() = default;
		Position(const glm::vec3 &position);
		void SetPosition(const glm::vec3 &position);
		void SetPosition(const Position &position);
		void MoveByX(float x);
		void MoveByY(float y);
		void MoveByZ(float z);
		const glm::vec3 &GetPosition() const;
	};

	struct IRON_API Rotation
	{
	private:
		glm::vec3 m_rotation;

	public:
		Rotation() = default;
		Rotation(const glm::vec3 &rotation);
		void SetRotation(const glm::vec3 &rotation);
		void SetRotation(const Rotation &rotation);
		void RotateByX(float x);
		void RotateByY(float y);
		void RotateByZ(float z);
		const glm::vec3 &GetRotation() const;
	};

	struct IRON_API Scale
	{
	private:
		glm::vec3 m_scale;

	public:
		Scale() = default;
		Scale(const glm::vec3 &scale);
		void SetScale(const glm::vec3& scale);
		void SetScale(const Scale &scale);
		void ScaleByX(float x);
		void ScaleByY(float y);
		void ScaleByZ(float z);
		const glm::vec3 &GetScale() const;
	};

	struct IRON_API LocalPosition
	{
	private:
		const glm::vec3 m_localPosition;
	
	public:
		LocalPosition(const glm::vec3 &localPos);
		const glm::vec3 &GetLocalPosition() const;
	};

	class IRON_API Transform
	{
	private:
		struct Position m_position;
		struct Rotation m_rotation;
		struct Scale m_scale;
		//struct LocalPosition m_localPosition;
		glm::mat4 m_mat;
		glm::vec3 m_up = glm::vec3(0.0f, 1.0f,  0.0f);
		glm::vec3 m_front = glm::vec3(0.0f, 0.0f, 1.0f);
		glm::vec3 m_right = glm::vec3(1.0f, 0.0f, 0.0f);

	public:
		Transform();
		Transform(const glm::vec3 &position);
		~Transform();

		struct Position &GetPosition();
		struct Rotation &GetRotation();
		struct Scale &GetScale();

		void SetPosition(const Position &position);
		void SetRotation(const Rotation &rotation);
		void SetScale(const Scale &scale);
		void SetPosition(const glm::vec3 &position);
		void SetRotation(const glm::vec3 &rotation);
		void SetScale(const glm::vec3 &scale);

		const glm::vec3 &Front();
		const glm::vec3 &Up();
		const glm::vec3 &Right();
		void LookAt(const glm::vec3 &lookAt);
		glm::mat4 &GetMatrix() ;
	};
}