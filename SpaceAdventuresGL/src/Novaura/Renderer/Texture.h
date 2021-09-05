#pragma once

namespace Novaura {

	class Texture
	{
	public:
		Texture() = default;
		Texture(const std::string& path);				

		void Bind(unsigned int slot = 0) const;
		void UnBind() const;

		inline int GetWidth() const { return m_Width; }
		inline int GetHeight() const { return m_Height; }
		inline unsigned int GetID() const { return m_TextureID; }			

		void SetID(unsigned int id) { m_TextureID = id; }		
	
	private:
		unsigned int m_TextureID;
		int m_Width, m_Height, m_NumChannels;
		
		void LoadTexture(const std::string& path);	

	};

}