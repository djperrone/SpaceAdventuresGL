#include "sapch.h"
#include "GUI.h"
#include "Novaura/Renderer/BatchRenderer.h"
#include "Novaura/Renderer/Renderer.h"
#include <spdlog/spdlog.h>
#include "Novaura/Input/InputHandler.h"
#include "Novaura/Renderer/TextLoader.h"

namespace GUI {

	std::vector<std::unique_ptr<Button>> Interface::s_ButtonList;

	void Interface::AddToggleButton(const std::string& text, const glm::vec3& pos, const glm::vec3& scale, const glm::vec4& fillColor, const glm::vec4& outlineColor, Novaura::Command command)
	{
		s_ButtonList.emplace_back(std::make_unique<TextToggleButton>(text, pos, scale, fillColor, outlineColor, command));
	}
	void Interface::ClearButtons()
	{
		s_ButtonList.clear();
	}
	void Interface::Update()
	{
		for (auto& button : s_ButtonList)
		{
			button->Update();
		}
	}
	void Interface::Draw()
	{
		//float scale = 0.002f;
		float scale = 0.0027f;
		float aspectRatio = Novaura::InputHandler::GetCurrentWindow()->AspectRatio;
		//int test;
		std::vector<glm::vec2> lengths;
		float width = Novaura::InputHandler::GetCurrentWindow()->Width;
		float height = Novaura::InputHandler::GetCurrentWindow()->Height;
		float length = 0.0f;
		//Novaura::BatchRenderer::BeginScene();
		for (auto& button : s_ButtonList)
		{
			//spdlog::info(__FUNCTION__);
			//Novaura::BatchRenderer::DrawRectangle(button->GetRectangle());
			glm::vec2 tmpLength{ 0.0f,0.0f };
			float w;
			float h;

			for (const auto& ch : button->GetText())
			{
				const auto& currentChar = Novaura::TextLoader::LoadedCharacters[ch];
				//float xpos = x + ch.Bearing.x * scale;
				//float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;
				w = currentChar.Size.x;
				//if(aspectRatio >=1.0f)
				//length += (w / width);
				//length += (currentChar.Advance / 10.0f) / width;
				//else
				//	length += w / aspectRatio / width;

				h = currentChar.Size.y;

				tmpLength.x += (float)Novaura::TextLoader::LoadedCharacters[ch].Size.x;
				tmpLength.x += (float)Novaura::TextLoader::LoadedCharacters[ch].Bearing.x * 2.0f;
				//tmpLength.x += (float)(Novaura::TextLoader::LoadedCharacters[ch].Advance >>64) * scale;
				tmpLength.y += (float)Novaura::TextLoader::LoadedCharacters[ch].Size.y;
			}
			lengths.emplace_back(glm::vec2(tmpLength.x, tmpLength.y));

			Novaura::BatchRenderer::StencilDraw(button->GetRectangle().GetPosition(), button->GetRectangle().GetScale(), button->GetRectangle().GetColor(), button->GetOutlineColor());
			//Novaura::BatchRenderer::RenderText(button->GetText(), button->GetRectangle().GetPosition().x, button->GetRectangle().GetPosition().y, 0.005f, button->GetTextColor());
		}
		Novaura::BatchRenderer::EndScene();
		int i = 0;
		auto window = Novaura::InputHandler::GetCurrentWindow()->Window;
		float totallength = 0.0f;
		for (int i =0; i < lengths.size(); i++)
		{
			totallength += lengths[i].x;
		}
		for (auto& button : s_ButtonList)
		{
			float x = button->GetRectangle().GetPosition().x;
			float xsc = button->GetRectangle().GetScale().x;
			float y = button->GetRectangle().GetPosition().y;// -button->GetRectangle().GetScale().x * 0.5f;
			
			//x -= totallength / width;
			//x -= length;
			//y -= lengths[i].y / height;
			
			float tempx = lengths[i].x * scale;
			float tempy = lengths[i].y * scale;
			//spdlog::info("length{}", totallength / (width / aspectRatio));
			float maxHeight = 0.0f;
			for (int i = 0; i < lengths.size(); i++)
			{
				if (lengths[i].y > maxHeight) maxHeight = lengths[i].y / height;
			}

			x -= tempx * 0.5f;
			y -= tempy * 0.05f;
			Novaura::BatchRenderer::RenderText(button->GetText(), x, y, scale, button->GetTextColor());
			i++;
		}
	}
}