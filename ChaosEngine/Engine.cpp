#pragma once
#include "Engine.h"

namespace ChaosEngine {

    using namespace std;


    Engine::Engine() {
        cout << "ChaosEngine run successfully!" << endl;

    };

    BOOL Engine::Init(HWND hWnd) {
        DirectX::Initialize(hWnd);

        return true;
    };

}
