#pragma once
#include "_list.h"

namespace ChaosEngine {

	namespace ObjectList {

		Text::Text() {
			content;
			textFormat;
			pMousePos = &Property::Window::MousePos;
		}

		void Text::Init() {
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
