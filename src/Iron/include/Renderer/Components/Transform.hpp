#pragma once

#include "pch.hpp"
#include "Core.hpp"
#include "Renderer/Shader.hpp"
#include "gtx/quaternion.hpp"
#include "gtx/euler_angles.hpp"
#include "type_traits"

template <typename Condition, typename T = void>
using EnableIf = typename std::enable_if<Condition::value, T>::type;

template <typename Condition, typename T = void>
using DisableIf = typename std::enable_if<!Condition::value, T>::type;

namespace Iron
{
	struct IRON_API Vector3 
	{
	private:
		friend class Transform;
		friend class Quaternion;

		glm::vec3 m_vec;
		explicit Vector3(const glm::vec3 &vec);
	
	public:
		Vector3();
		explicit Vector3(float v);
		explicit Vector3(float x, float y, float z);
		Vector3(const Vector3 &vec);

		inline void SetX(float x) { m_vec.x = x; }
		inline void SetY(float y) { m_vec.y = y; }
		inline void SetZ(float z) { m_vec.z = z; }
		inline float GetX() { return m_vec.x; }
		inline float GetY() { return m_vec.y; }
		inline float GetZ() { return m_vec.z; }

		static Vector3 Normalize(const Vector3 &vec);

		Vector3 &operator+= (const Vector3 &rhs);
		Vector3 &operator-= (const Vector3 &rhs);
		Vector3 &operator*= (const Vector3 &rhs);
		Vector3 &operator/= (const Vector3 &rhs);

		template<typename T, typename = EnableIf<std::is_arithmetic<T>>> 
		friend IRON_API Vector3 operator+ (const Vector3 &lhs, const T &rhs)
		{
			return Vector3(lhs.m_vec + rhs);
		}

		template<typename T, typename = EnableIf<std::is_arithmetic<T>>> 
		friend IRON_API Vector3 operator+ (const T &lhs, const Vector3 &rhs)
		{
			return Vector3(rhs.m_vec + lhs);
		}

		template<typename T, typename = EnableIf<std::is_arithmetic<T>>> 
		friend IRON_API Vector3 operator- (const Vector3 &lhs, const T &rhs)
		{
			return Vector3(lhs.m_vec - rhs);
		}

		template<typename T, typename = EnableIf<std::is_arithmetic<T>>> 
		friend IRON_API Vector3 operator- (const T &lhs, const Vector3 &rhs)
		{
			return Vector3(rhs.m_vec - lhs);
		}

		template<typename T, typename = EnableIf<std::is_arithmetic<T>>> 
		friend IRON_API Vector3 operator* (const Vector3 &lhs, const T &rhs)
		{
			return Vector3(lhs.m_vec * rhs);
		}

		template<typename T, typename = EnableIf<std::is_arithmetic<T>>> 
		friend IRON_API Vector3 operator* (const T &lhs, const Vector3 &rhs)
		{
			return Vector3(rhs.m_vec * lhs);
		}

		template<typename T, typename = EnableIf<std::is_arithmetic<T>>> 
		friend IRON_API Vector3 operator/ (const Vector3 &lhs, const T &rhs)
		{
			return Vector3(lhs.m_vec / rhs);
		}

		template<typename T, typename = EnableIf<std::is_arithmetic<T>>> 
		friend IRON_API Vector3 operator/ (const T &lhs, const Vector3 &rhs)
		{
			return Vector3(rhs.m_vec / lhs);
		}
		
		friend IRON_API Vector3 operator+ (Vector3 lhs, const Vector3 &rhs);
		friend IRON_API Vector3 operator- (Vector3 lhs, const Vector3 &rhs);
		friend IRON_API Vector3 operator* (Vector3 lhs, const Vector3 &rhs);
		friend IRON_API Vector3 operator/ (Vector3 lhs, const Vector3 &rhs);
	};

	class IRON_API Quaternion
	{
	private:
		friend class Transform;
		glm::quat m_rotation;
		Quaternion(glm::quat &quat)
		{
			m_rotation = quat;
		}

		void SetRotation(const glm::mat4 &rotation);

	public:
		Quaternion() = default;
		Quaternion(const Vector3 &rotation);
		// void SetRotation(const glm::quat &rotation);
		void SetRotation(const Quaternion &rotation);
		const Quaternion &GetQuaternion() const;
		static Vector3 ToEuler(const Quaternion &quat);
		static Quaternion ToQuat(const Vector3 &euler);
	};

	class IRON_API Transform
	{
	private:
		//struct LocalPosition m_localPosition;
		glm::mat4 m_model;
		Vector3 m_up = Vector3(0.0f, 1.0f,  0.0f);
		Vector3 m_front = Vector3(0.0f, 0.0f, 1.0f);
		Vector3 m_right = Vector3(-1.0f, 0.0f, 0.0f);

	public:
		struct Vector3 position;
		struct Quaternion rotation;
		struct Vector3 eulerAngle;
		struct Vector3 scale;
		
		Transform();
		Transform(const glm::vec3 &position);
		~Transform();

		struct Vector3 &GetPosition();
		struct Quaternion &GetRotation();
		struct Vector3 &GetEulerAngle();
		struct Vector3 &GetScale();

		void SetPosition(const Vector3 &position);
		void SetRotation(const Quaternion &rotation);
		void SetScale(const Vector3 &scale);

		const Vector3 &Front();
		const Vector3 &Up();
		const Vector3 &Right();
		void LookAt(const Vector3 &lookAt);
		glm::mat4 &GetMatrix();
	};
}