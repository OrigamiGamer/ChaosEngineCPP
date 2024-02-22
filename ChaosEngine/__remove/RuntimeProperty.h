#pragma once
#include "ChaosEngine.h"

namespace ChaosEngine {

    namespace RuntimeProperty {

        class WindowRuntimeProperty {
        public:
            HWND hWnd;
            Type::SIZE size{};
            Type::POS pos{};
            Type::POS mousePos{};
            Type::VirtualKeyState VirtKeyStateBuffer[254];
            std::vector<int> VirtKeyInputBuffer;

            void BindWindow(HWND new_hWnd);

            WindowRuntimeProperty();
        };

        class EngineRuntimeProperty {
        public:
            Type::EngineStartupProperty* pStartupProp;
            long double lastTime;
            long double deltaTime;

            EngineRuntimeProperty();
        };

    }

}
