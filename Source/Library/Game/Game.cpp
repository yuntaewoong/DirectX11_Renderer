#include "Game/Game.h"

namespace library
{
    const wchar_t CLASS_NAME[] = L"First Window Class";
    HINSTANCE               g_hInst = nullptr;
    HWND                    g_hWnd = nullptr;
    D3D_DRIVER_TYPE         g_driverType = D3D_DRIVER_TYPE_NULL;
    D3D_FEATURE_LEVEL       g_featureLevel = D3D_FEATURE_LEVEL_11_0;
    Microsoft::WRL::ComPtr<ID3D11Device> g_pD3dDevice;
    Microsoft::WRL::ComPtr<IDXGISwapChain> g_pSwapChain;
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView> g_pRenderTargetView;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> g_pImmediateContext;
    /*--------------------------------------------------------------------
      Global Variables
    --------------------------------------------------------------------*/
    /*--------------------------------------------------------------------
      Forward declarations
    --------------------------------------------------------------------*/

    /*F+F+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
      Function: WindowProc

      Summary:  Defines the behavior of the window—its appearance, how
                it interacts with the user, and so forth

      Args:     HWND hWnd
                  Handle to the window
                UINT uMsg
                  Message code
                WPARAM wParam
                  Additional data that pertains to the message
                LPARAM lParam
                  Additional data that pertains to the message

      Returns:  LRESULT
                  Integer value that your program returns to Windows
    -----------------------------------------------------------------F-F*/
    LRESULT CALLBACK WindowProc(_In_ HWND hWnd, _In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam)
    {
        PAINTSTRUCT ps;
        HDC hdc;
        switch (uMsg)
        {
        case WM_PAINT:
            hdc = BeginPaint(hWnd, &ps);
            EndPaint(hWnd, &ps);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
        }
        return 0;
    }
    HRESULT InitWindow(_In_ HINSTANCE hInstance, _In_ INT nCmdShow)
    {
        /*--------------------------------------------Make Window Class*/
        WNDCLASS wc = { };
        wc.lpfnWndProc = WindowProc;
        wc.hInstance = hInstance;
        wc.lpszClassName = CLASS_NAME;
        /*--------------------------------------------*/
        /*--------------------------------------------Register Window Class*/
        if (!RegisterClass(&wc))
        {
            DWORD dwError = GetLastError();
            MessageBox(
                nullptr,
                L"Call to RegisterClassEx failed!",
                L"Game Graphics Programming",
                NULL
            );
            if (dwError != ERROR_CLASS_ALREADY_EXISTS)
            {
                return HRESULT_FROM_WIN32(dwError);
            }
            return E_FAIL;
        }
        /*-----------------------------------------*/
        /*-----------------------------------------Create Window*/
        g_hInst = hInstance;
        RECT rc = { 0, 0, 800, 600 };
        AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
        g_hWnd = CreateWindow(
            CLASS_NAME,        // name of window class 
            L"Game Graphics Programming Lab 01: Direct3D 11 Basics",            // title-bar string 
            WS_OVERLAPPEDWINDOW, // top-level window 
            CW_USEDEFAULT,       // default horizontal position 
            CW_USEDEFAULT,       // default vertical position 
            CW_USEDEFAULT,       // default width 
            CW_USEDEFAULT,       // default height 
            (HWND)NULL,         // no owner window 
            (HMENU)NULL,        // use class menu 
            hInstance,           // handle to application instance 
            (LPVOID)NULL
        );       
        if (!g_hWnd)
        {
            DWORD dwError = GetLastError();
            MessageBox(
                nullptr,
                L"Call to CreateWindow failed!",
                L"Game Graphics Programming",
                NULL
            );
            if (dwError != ERROR_CLASS_ALREADY_EXISTS)
            {
                return HRESULT_FROM_WIN32(dwError);
            }
            return E_FAIL;
        }
        /*-------------------------------------*/
        /*-------------------------------------Show Window*/
        ShowWindow(g_hWnd, nCmdShow);
        /*------------------------------------*/
    }
    HRESULT InitDevice()
    {
        /*-------------------------------------Create Direct3d device,context*/
        D3D_FEATURE_LEVEL levels[] = {
            D3D_FEATURE_LEVEL_9_1,
            D3D_FEATURE_LEVEL_9_2,
            D3D_FEATURE_LEVEL_9_3,
            D3D_FEATURE_LEVEL_10_0,
            D3D_FEATURE_LEVEL_10_1,
            D3D_FEATURE_LEVEL_11_0,
            D3D_FEATURE_LEVEL_11_1
        };
        RECT rc;
        GetClientRect(g_hWnd, &rc);
        UINT width = rc.right - rc.left;
        UINT height = rc.bottom - rc.top;

        // This flag adds support for surfaces with a color-channel ordering different
        // from the API default. It is required for compatibility with Direct2D.
        UINT deviceFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

        #if defined(DEBUG) || defined(_DEBUG)
        deviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
        #endif

        // Create the Direct3D 11 API device object and a corresponding context.
        D3D_FEATURE_LEVEL featureLevel;
        HRESULT hr = D3D11CreateDevice(
            nullptr,                    // Specify nullptr to use the default adapter.
            D3D_DRIVER_TYPE_HARDWARE,   // Create a device using the hardware graphics driver.
            0,                          // Should be 0 unless the driver is D3D_DRIVER_TYPE_SOFTWARE.
            deviceFlags,                // Set debug and Direct2D compatibility flags.
            levels,                     // List of feature levels this app can support.
            ARRAYSIZE(levels),          // Size of the list above.
            D3D11_SDK_VERSION,          // Always set this to D3D11_SDK_VERSION for Windows Store apps.
            g_pD3dDevice.GetAddressOf(),                    // Returns the Direct3D device created.
            &featureLevel,            // Returns feature level of device created.
            g_pImmediateContext.GetAddressOf()                   // Returns the device immediate context.
        );
        if (FAILED(hr))
        {
            return hr;
        }
        /*--------------------------------------------*/
        /*-----------------------------------------Get DXGI FACTORY*/
        Microsoft::WRL::ComPtr<IDXGIDevice> pDXGIDevice;
        hr = g_pD3dDevice.As(&pDXGIDevice);
        if(FAILED(hr))
        {
            return hr;
        }
        Microsoft::WRL::ComPtr<IDXGIAdapter> pDXGIAdapter;
        hr = pDXGIDevice->GetAdapter(pDXGIAdapter.GetAddressOf());
        if (FAILED(hr))
        {
            return hr;
        }
        Microsoft::WRL::ComPtr<IDXGIFactory> pIDXGIFactory;
        pDXGIAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&pIDXGIFactory);
        if (FAILED(hr))
        {
            return hr;
        }
        /*----------------------------------------*/
        /*-------------------------------------------Create Swap Chain*/
        DXGI_SWAP_CHAIN_DESC desc;
        ZeroMemory(&desc, sizeof(DXGI_SWAP_CHAIN_DESC));
        desc.Windowed = TRUE; // Sets the initial state of full-screen mode.
        desc.BufferCount = 2;
        desc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
        desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        desc.SampleDesc.Count = 1;      //multisampling setting
        desc.SampleDesc.Quality = 0;    //vendor-specific flag
        desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
        desc.OutputWindow = g_hWnd;

        hr = pIDXGIFactory->CreateSwapChain(
            g_pD3dDevice.Get(),
            &desc,
            g_pSwapChain.GetAddressOf()
        );
        if (FAILED(hr))
        {
            return hr;
        }
        /*------------------------------------------*/
        /*-------------------------------------------Create Render Target*/
        Microsoft::WRL::ComPtr<ID3D11Texture2D> pBackBuffer;
        hr = g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(pBackBuffer.GetAddressOf()));
        if (FAILED(hr))
            return hr;

        hr = g_pD3dDevice->CreateRenderTargetView(pBackBuffer.Get(), nullptr, g_pRenderTargetView.GetAddressOf());
        if (FAILED(hr))
            return hr;
        pBackBuffer.Reset();

        g_pImmediateContext->OMSetRenderTargets(1, g_pRenderTargetView.GetAddressOf(), nullptr);
        
        D3D11_VIEWPORT vp;
        vp.Width = (FLOAT)width;
        vp.Height = (FLOAT)height;
        vp.MinDepth = 0.0f;
        vp.MaxDepth = 1.0f;
        vp.TopLeftX = 0;
        vp.TopLeftY = 0;
        g_pImmediateContext->RSSetViewports(1, &vp);
        /*-------------------------------------------*/
        return S_OK;
    }
    void CleanupDevice()
    {
        if (g_pImmediateContext) g_pImmediateContext.Reset();
        if (g_pRenderTargetView) g_pRenderTargetView.Reset();
        if (g_pSwapChain) g_pSwapChain.Reset();
        if (g_pD3dDevice) g_pD3dDevice.Reset();
    }
    void Render()
    {
        g_pImmediateContext->ClearRenderTargetView(g_pRenderTargetView.Get(), Colors::MidnightBlue);
        g_pSwapChain->Present(0, 0);
    }
}