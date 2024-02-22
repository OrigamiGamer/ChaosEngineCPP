#pragma once
#include "_list.cpp"

namespace ChaosEngine {

	namespace ObjectList {

		Text::Text() {
			s_pTargetPos = &WindowX::Prop::MousePos;
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

		BOOL Text::HitTest() {
			DWRITE_HIT_TEST_METRICS metrics;
			BOOL is_trailing_hit;
			BOOL is_inside;

			Type::POS pos_hit = { s_pTargetPos->x - this->pos.x, s_pTargetPos->y - this->pos.y };
			textFormat.pLayout->HitTestPoint(pos_hit.x, pos_hit.y, &is_trailing_hit, &is_inside, &metrics);
			return is_trailing_hit;
		}

		BOOL Text::IsInside() {
			DWRITE_HIT_TEST_METRICS metrics;
			BOOL is_trailing_hit;
			BOOL is_inside;
			
			Type::POS pos_hit = { s_pTargetPos->x - this->pos.x, s_pTargetPos->y - this->pos.y };
			textFormat.pLayout->HitTestPoint(pos_hit.x, pos_hit.y, &is_trailing_hit, &is_inside, &metrics);
			return is_inside;
		}

	}

}
