#pragma once
#include "_list.cpp"

namespace ChaosEngine {

	namespace ObjectList {

		Text::Text() {
			s_pCursorPos = &WindowX::Prop::MousePos;
			color = { D2D1::ColorF::LightPink, 1 };
			textFormat;
		}

		void Text::Init() {
			textFormat.Init();
		}
		void Text::Update() {
			
		}
		void Text::Render() {
			if (textFormat.GetLayoutSize() != this->size) textFormat.SetLayoutSize(this->size);
			GraphicX::PushColor(color);
			GraphicX::DrawRawText(textFormat, this->pos);
			GraphicX::PopColor();

			// DEBUG //
			GraphicX::DrawRectangle(this->pos, this->size, { 0,0 });	// Draw Box

		}
		void Text::Release() {
			textFormat.Release();
		}

		void Text::Create() {

		}

		BOOL Text::OnHover() {
			DWRITE_HIT_TEST_METRICS metrics;
			BOOL is_trailing_hit;	// hadn't ever been used //
			BOOL is_inside;
			
			Type::POS pos_hit = { s_pCursorPos->x - this->pos.x, s_pCursorPos->y - this->pos.y };
			textFormat.pLayout->HitTestPoint(pos_hit.x, pos_hit.y, &is_trailing_hit, &is_inside, &metrics);
			return is_inside;
		}

	}

}
