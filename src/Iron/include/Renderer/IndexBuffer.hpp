#pragma once

namespace Iron
{
	class IndexBuffer
	{
	private: 
		unsigned int m_rendererID;
		unsigned int m_Count;

	public:
		IndexBuffer(const unsigned int* data, unsigned int count);
		~IndexBuffer();

		void BufferData(const void* data, unsigned int count);
		void SetCount(unsigned int count);
		void Bind() const;
		void Unbind() const;
		inline unsigned int GetCount() const { return m_Count; }
	};
}