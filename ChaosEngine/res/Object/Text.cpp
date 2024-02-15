#pragma once
#include "_list.h"

namespace ChaosEngine {

	namespace ObjectList {

		Text::Text() {
			content;
			textFormat;
			pMousePos = &Properties::Window::MousePos;
		}

		void Text::Init() {
			textFormat.Init();
		}
		void Text::Update() {
			
		}
		void Text::Render() {
			GraphicX::DrawRawText(content, textFormat, this->pos);
			
		}
		void Text::Release() {
		}

		void Text::Create() {

		}

		void Text::SetContent(std::wstring new_content) {
			content = new_content;
		}

		BOOL Text::HitTest() {
			DWRITE_HIT_TEST_METRICS w;
			BOOL is_trailing_hit;
			BOOL is_inside;

			Type::POS pos = { pMousePos->x - this->pos.x, pMousePos->y - this->pos.y };
			textFormat.pLayout->HitTestPoint(pos.x, pos.y, &is_trailing_hit, &is_inside, &w);
			return is_trailing_hit;
		}

		BOOL Text::IsInside() {
			DWRITE_HIT_TEST_METRICS w;
			BOOL is_trailing_hit;
			BOOL is_inside;

			Type::POS pos = { pMousePos->x - this->pos.x, pMousePos->y - this->pos.y };
			textFormat.pLayout->HitTestPoint(pos.x, pos.y, &is_trailing_hit, &is_inside, &w);
			return is_inside;
		}

	}

}
