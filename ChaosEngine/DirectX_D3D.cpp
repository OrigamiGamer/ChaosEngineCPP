//#pragma once
//#include "ChaosEngine.h"
//
//namespace ChaosEngine {
//
//    namespace DirectX {
//        using namespace Microsoft::WRL;
//
//        ComPtr<IDXGIFactory1> I_DXGI_Factory;
//        ComPtr<IDXGISwapChain> I_DXGI_SwapChain;
//        ComPtr<IDXGIDevice> I_DXGI_Device;
//        ComPtr<ID3D12Debug> I_D3D_Debug;
//        ComPtr<ID3D12Device> I_D3D_Device;
//        ComPtr<ID3D12CommandQueue> I_D3D_CommandQueue;
//
//        HRESULT Initialize(HWND hWnd) {
//            Property::Window::BindWindow(hWnd);
//            Property::Window::GetWinAttris();
//
//            HRESULT hr = NULL;
//            hr = D3D12GetDebugInterface(IID_PPV_ARGS(&I_D3D_Debug));    if (!SUCCEEDED(hr)) return hr;
//            I_D3D_Debug->EnableDebugLayer();
//
//            hr = CreateDXGIFactory1(IID_PPV_ARGS(&I_DXGI_Factory));     if (!SUCCEEDED(hr)) return hr;
//
//            hr = D3D12CreateDevice(NULL, D3D_FEATURE_LEVEL_12_0, IID_PPV_ARGS(&I_D3D_Device));      if (!SUCCEEDED(hr)) return hr;
//
//            D3D12_COMMAND_QUEUE_DESC _cmd_queue_desc{};
//            _cmd_queue_desc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
//            _cmd_queue_desc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
//            _cmd_queue_desc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
//            _cmd_queue_desc.NodeMask = 0;
//            hr = I_D3D_Device->CreateCommandQueue(&_cmd_queue_desc, IID_PPV_ARGS(&I_D3D_CommandQueue));     if (!SUCCEEDED(hr)) return hr;
//
//
//            // SwapChain //
//
//            DXGI_MODE_DESC _DXGI_Mode_Desc{};
//            _DXGI_Mode_Desc.Width = (UINT)Property::Window::size.width;
//            _DXGI_Mode_Desc.Height = (UINT)Property::Window::size.height;
//            _DXGI_Mode_Desc.RefreshRate = { 1,60 }; // { Numerator, Denominator }
//            _DXGI_Mode_Desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
//            _DXGI_Mode_Desc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
//            _DXGI_Mode_Desc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
//
//            DXGI_SWAP_CHAIN_DESC _DXGI_SwapChain_Desc{};
//            _DXGI_SwapChain_Desc.BufferDesc = _DXGI_Mode_Desc;
//            _DXGI_SwapChain_Desc.Flags = DXGI_SWAP_CHAIN_FLAG_DISPLAY_ONLY;
//            _DXGI_SwapChain_Desc.OutputWindow = hWnd;
//            _DXGI_SwapChain_Desc.Windowed = true;
//            _DXGI_SwapChain_Desc.BufferCount = 1;
//            _DXGI_SwapChain_Desc.BufferUsage = 1;
//            _DXGI_SwapChain_Desc.SampleDesc = { 1,1 };  // { Count, Quality }
//            _DXGI_SwapChain_Desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
//
//            hr = I_DXGI_Factory->CreateSwapChain(I_D3D_CommandQueue.Get(), &_DXGI_SwapChain_Desc, &I_DXGI_SwapChain);
//
//
//
//            return hr;
//        };
//
//        bool Release() {
//            return true;
//        };
//    }
//
//}
