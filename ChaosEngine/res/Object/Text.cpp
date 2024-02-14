#pragma once
#include "_list.h"

namespace ChaosEngine {

	namespace ObjectList {

		Text::Text() {
			textFormat;
			pMousePos = &Property::Window::MousePos;
		}

		void Text::Init() {
		}
		void Text::Update() {
			
		}
		void Text::Render() {
			GraphicX::DrawTextRaw(textFormat, this->pos);
			
		}
		void Text::Release() {
		}

		void Text::Create() {

		}

		BOOL Text::HitTest() {
			DWRITE_HIT_TEST_METRICS w;
			BOOL is_trailing_hit;

			Type::POS pos = { pMousePos->x - this->pos.x, pMousePos->y - this->pos.y };
			textFormat.pLayout->HitTestPoint(pos.x, pos.y, &is_trailing_hit, nullptr, &w);
			return is_trailing_hit;
		}

		BOOL Text::IsInside() {
			DWRITE_HIT_TEST_METRICS w;
			BOOL is_inside;

			Type::POS pos = { pMousePos->x - this->pos.x, pMousePos->y - this->pos.y };
			textFormat.pLayout->HitTestPoint(pos.x, pos.y, nullptr, &is_inside, &w);
			return is_inside;
		}

	}

}
