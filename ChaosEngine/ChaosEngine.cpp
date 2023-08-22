#pragma once
#include "ChaosEngine.h"

// void test() {
//     JsRuntimeHandle* hRuntime;
//     JsContextRef pContext;
//     JsRuntimeAttributes attri;
//     JsCreateRuntime(attri, NULL, hRuntime);
//     JsCreateContext(hRuntime, &pContext);

// }



// /* Define */

// #define empty (float)0xFFFFFFFF // 4 bytes

// #define SET_OPT(var, new_var) if(new_var != empty) var = new_var;   // Set optionally

// // Window Message
// #define WM_ENGINE_FRAME (WM_USER + 1)



// namespace ChaosEngine {

//     template <class T>
//     void SafeRelease(T** ppT) {
//         if (*ppT) {
//             (*ppT)->Release();
//             *ppT = NULL;
//         }
//     };



//     namespace Type {

//         struct WindowInitialProperty {
//             int width = 800, height = 600;
//             int x = CW_USEDEFAULT, y = CW_USEDEFAULT;
//             LPSTR WndTitle = "New Game";
//             HWND hWndParent = NULL;
//         };
//         struct EngineStartupProperty {
//             int FPS = 60;
//         };

//         struct SIZE {
//             float width, height;

//             SIZE() = default;

//             SIZE(float width, float height) : width(width), height(height) {};
//         };
//         struct SIZE_3D {
//             float length, width, height;

//             SIZE_3D() = default;

//             SIZE_3D(float length, float width, float height) : length(length), width(width), height(height) {};
//         };

//         struct POS {
//             float x, y;

//             POS() = default;

//             POS(float x, float y) : x(x), y(y) {};
//         };
//         struct POS_3D {
//             float x, y, z;

//             POS_3D() = default;

//             POS_3D(float x, float y, float z) : x(x), y(y), z(z) {};
//         };

//     }



//     /* Property */

// // It's used to store properties of Engine and Window at runtime.
// // 它用于在运行时储存 Engine 和 Window 的属性(Property)。
//     namespace Property {

//         /* Window */

//         namespace Window {
//             void BindWindow(HWND new_hWnd);

//             // Get the most attributes of window
//             bool GetWinAttris();

//         };



//         /* Engine */

//         namespace Engine {

//         };

//     }



//     namespace WindowX {

//         /* Function about DirectX */

//         // Global
//         ID2D1Factory* pD2DFactory = NULL;
//         ID2D1HwndRenderTarget* pHwndRenderTarget = NULL;

//         // Initialize DirectX
//         HRESULT InitDirectX(HWND hWnd) {

//             HRESULT hr = NULL;

//             /* D2D */

//             hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pD2DFactory);
//             if (FAILED(hr)) return hr;

//             D2D1_RENDER_TARGET_PROPERTIES RenderTarget_Properties{};
//             //float hWndDpi = GetDpiForWindow(hWnd);
//             //RenderTarget_Properties.dpiX = hWndDpi;
//             //RenderTarget_Properties.dpiY = hWndDpi;
//             RenderTarget_Properties.minLevel = D2D1_FEATURE_LEVEL_DEFAULT;
//             RenderTarget_Properties.pixelFormat = { DXGI_FORMAT_R8G8B8A8_UNORM ,D2D1_ALPHA_MODE_PREMULTIPLIED };

//             D2D1_HWND_RENDER_TARGET_PROPERTIES HwndRenderTarget_properties{};
//             HwndRenderTarget_properties.hwnd = hWnd;
//             HwndRenderTarget_properties.pixelSize = { (UINT32)Property::Window::Size.width,(UINT32)Property::Window::Size.height };
//             HwndRenderTarget_properties.presentOptions = D2D1_PRESENT_OPTIONS_NONE;

//             hr = pD2DFactory->CreateHwndRenderTarget(&RenderTarget_Properties, &HwndRenderTarget_properties, &pHwndRenderTarget);
//             if (FAILED(hr)) return hr;

//             return hr;
//         };

//         // Release DirectX
//         HRESULT ReleaseDirectX() {
//             /* D2D */
//             SafeRelease(&pD2DFactory);

//             return 0;
//         };



//         /* Function about Windows */

//         // Initialize Window
//         HWND InitWindow(Type::WindowInitialProperty* WndProp) {
//             HWND hWnd;
//             HINSTANCE hInst = GetModuleHandle(NULL);
//             LPSTR ClassName = "ChaosGameWin";

//             WNDCLASSEX WndClassEx{};
//             WndClassEx.cbSize = sizeof(WNDCLASSEX);
//             WndClassEx.hInstance = hInst;
//             WndClassEx.lpszClassName = (LPCSTR)ClassName;
//             WndClassEx.lpfnWndProc = WndProc;
//             WndClassEx.style = CS_SAVEBITS | CS_DROPSHADOW;
//             WndClassEx.cbClsExtra = 0;
//             WndClassEx.cbWndExtra = 0;
//             WndClassEx.hIcon = NULL;
//             WndClassEx.hCursor = NULL;
//             WndClassEx.hbrBackground = NULL;
//             WndClassEx.lpszMenuName = NULL;
//             WndClassEx.hIconSm = NULL;

//             RegisterClassEx(&WndClassEx);

//             hWnd = CreateWindowEx(
//                 (DWORD)NULL,
//                 (LPCSTR)ClassName,
//                 (LPCSTR)WndProp->WndTitle,
//                 WS_OVERLAPPEDWINDOW,
//                 WndProp->x, WndProp->y,
//                 WndProp->width, WndProp->height,
//                 WndProp->hWndParent,
//                 (HMENU)NULL,
//                 hInst,
//                 (LPVOID)NULL
//             );
//             if (hWnd == 0) {
//                 std::cout << "Initialize Window Failed! " << GetLastError() << std::endl;
//                 return 0;
//             };

//             ShowWindow(hWnd, SW_SHOW);
//             UpdateWindow(hWnd);

//             return hWnd;
//         };

//         // Start Message Loop
//         DWORD StartMessageLoop() {
//             MSG Msg;
//             while (GetMessage(&Msg, NULL, 0, 0)) {
//                 TranslateMessage(&Msg);
//                 DispatchMessage(&Msg);
//             };

//             return (DWORD)Msg.wParam;
//         };

//         // Callback WndProc
//         LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
//             switch (uMsg) {

//             case WM_CREATE:
//                 Property::Window::BindWindow(hWnd);

//                 InitDirectX(hWnd);
//                 EngineX::EngineInit();

//                 SetTimer(hWnd, 0, 1, (TIMERPROC)TimerProc_GameFrameUpdate);
//                 break;
//             case WM_SIZE:
//                 Property::Window::Size.width = (float)LOWORD(lParam);
//                 Property::Window::Size.height = (float)HIWORD(lParam);

//                 break;
//             case WM_MOVE:
//                 Property::Window::Pos.x = (float)LOWORD(lParam);
//                 Property::Window::Pos.y = (float)HIWORD(lParam);

//                 break;
//             case WM_MOUSEMOVE:
//                 Property::Window::MousePos.x = (float)GET_X_LPARAM(lParam);
//                 Property::Window::MousePos.y = (float)GET_Y_LPARAM(lParam);

//                 break;
//             case WM_ENGINE_FRAME:
//                 EngineX::EngineUpdate();    // Update
//                 EngineX::EngineRender();    // Render

//                 break;
//             case WM_CLOSE:
//                 DestroyWindow(hWnd);

//                 break;
//             case WM_DESTROY:
//                 EngineX::EngineExit();  // Exit
//                 PostQuitMessage(0);

//                 break;
//             default:
//                 return DefWindowProc(hWnd, uMsg, wParam, lParam);
//             };

//             return 0;
//         };

//         VOID CALLBACK TimerProc_GameFrameUpdate(HWND hWnd, UINT p1, UINT_PTR p2, DWORD p3) {
//             SendMessage(hWnd, WM_ENGINE_FRAME, 0, 0);
//         };

//     }



//     /* EngineX for processing engine logic */
//     namespace EngineX {

//         // Global
//         Model::SceneModel* pCurrentScene = NULL;
//         Model::SceneModel* pNextScene = pCurrentScene;

//         LRESULT EngineInit() {
//             if (pCurrentScene != NULL)
//                 pCurrentScene->Init();

//             return 0;
//         };

//         LRESULT EngineUpdate() {
//             if (pCurrentScene != pNextScene) {
//                 pCurrentScene->Update();

//             } else if (pCurrentScene->OnClose()) {
//                 pCurrentScene = pNextScene;
//                 pCurrentScene->Init();
//             }

//             return 0;
//         };

//         LRESULT EngineRender() {
//             WindowX::pHwndRenderTarget->BeginDraw();
//             WindowX::pHwndRenderTarget->Clear({ 0,0,0,1 });

//             pCurrentScene->Render();

//             WindowX::pHwndRenderTarget->EndDraw();
//             return 0;
//         };

//         LRESULT EngineExit() {
//             std::cout << "Engine has exited!" << std::endl;

//             return 0;
//         };

//     }



//     namespace Model {

//         class Object {
//         private:
//             Type::SIZE self_size;
//             Type::POS self_pos;

//         public:
//             Object() {};

//             virtual int Init() { return -1; };
//             virtual int Update() { return -1; };
//             virtual int Render() { return -1; };
//             virtual int Release() { return -1; };

//         public:
//             void SetSize(Type::SIZE new_size) {
//                 SET_OPT(self_size.width, new_size.width);
//                 SET_OPT(self_size.height, new_size.height);
//             };
//             void SetSize(float width, float height) {
//                 SET_OPT(self_size.width, width);
//                 SET_OPT(self_size.height, height);
//             };

//             void SetPos(Type::POS new_pos) {
//                 SET_OPT(self_pos.x, new_pos.y);
//                 SET_OPT(self_pos.y, new_pos.y);
//             };
//             void SetPos(float x, float y) {
//                 SET_OPT(self_pos.x, x);
//                 SET_OPT(self_pos.y, y);
//             };

//         };



//     }


//     namespace Model {

//         class SceneModel : public Object {
//         public:
//             SceneModel() {};

//             int Init() {


//                 return -2;
//             };
//             int Update() {


//                 return -2;
//             };
//             int Render() {


//                 return -2;
//             };
//             int Release() {


//                 return -2;
//             };

//             virtual bool OnClose() {
//                 return true;    // true returned means confirmed to close.
//             };

//         };

//     }



//     /* Engine */
//     namespace Engine {

//         BOOL Start(Type::WindowInitialProperty* WndProp, Type::EngineStartupProperty* EngineProp) {
//             WindowX::InitWindow(WndProp);
//             Property::Engine::StartupProp = EngineProp;

//             WindowX::StartMessageLoop();

//             return true;
//         };

//         BOOL Release() {
//             WindowX::ReleaseDirectX();

//             return true;
//         };

//         namespace Stage {

//             void SwitchScene(Model::SceneModel* pTargetScene) {
//                 if (pTargetScene != NULL)
//                     EngineX::pNextScene = pTargetScene;

//             };

//         }

//     }

// }
