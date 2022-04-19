#include "Shader/VertexShader.h"

namespace library
{
    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   VertexShader::VertexShader

      Summary:  Constructor

      Args:     PCWSTR pszFileName
                  Name of the file that contains the shader code
                PCSTR pszEntryPoint
                  Name of the shader entry point functino where shader
                  execution begins
                PCSTR pszShaderModel
                  Specifies the shader target or set of shader features
                  to compile against

      Modifies: [m_vertexShader].[m_vertexLayout]
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    VertexShader::VertexShader(_In_ PCWSTR pszFileName, _In_ PCSTR pszEntryPoint, _In_ PCSTR pszShaderModel) :
        Shader(pszFileName,pszEntryPoint,pszShaderModel),
        m_vertexLayout(nullptr),
        m_vertexShader(nullptr)
    {}

    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   VertexShader::Initialize

      Summary:  Initializes the vertex shader and the input layout

      Args:     ID3D11Device* pDevice
                  The Direct3D device to create the vertex shader

      Returns:  HRESULT
                  Status code
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    HRESULT VertexShader::Initialize(_In_ ID3D11Device* pDevice)
    {
        HRESULT hr = S_OK;
        ComPtr<ID3DBlob> VSBlob;
        //Compile a vertex shader
        hr = compile(VSBlob.GetAddressOf());
        if (FAILED(hr))
        {
            return hr;
        }
        //Create the Direct3D Vertex Shader object
        hr = pDevice->CreateVertexShader(VSBlob->GetBufferPointer(),
            VSBlob->GetBufferSize(),
            nullptr, 
            m_vertexShader.GetAddressOf()
        );
        if (FAILED(hr))
        {
            return hr;
        }
        // Define the input layout
        D3D11_INPUT_ELEMENT_DESC layout[] =
        {
            { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
            { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
            { "NORMAL",0,DXGI_FORMAT_R32G32B32_FLOAT,0,20,D3D11_INPUT_PER_VERTEX_DATA,0}
        };
        UINT numElements = ARRAYSIZE(layout);
        // Create the input layout
        hr = pDevice->CreateInputLayout(layout,
            numElements,
            VSBlob->GetBufferPointer(),
            VSBlob->GetBufferSize(),
            &m_vertexLayout
        );
        if (FAILED(hr))
            return hr;
        return hr;
    }

    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   VertexShader::GetVertexShader

      Summary:  Returns the vertex shader

      Returns:  ComPtr<ID3D11VertexShader>&
                  Vertex shader. Could be a nullptr
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    ComPtr<ID3D11VertexShader>& VertexShader::GetVertexShader()
    {
        return m_vertexShader;
    }
    /*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
      Method:   VertexShader::GetVertexLayout

      Summary:  Returns the vertex input layout

      Returns:  ComPtr<ID3D11InputLayout>&
                  Vertex input layout
    M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
    ComPtr<ID3D11InputLayout>& VertexShader::GetVertexLayout()
    {
        return m_vertexLayout;
    }
}
