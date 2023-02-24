#include "../../../header-files/gameobjects/materials/Cubemap.h"

int Cubemap::Init(ID3D11Device* _p_dxdevice, ID3D11DeviceContext* _p_dxcontext)
{
    p_dxdevice = _p_dxdevice;
    p_dxcontext = _p_dxcontext;

    Start();

    return 0;
}

int Cubemap::Start()
{
    D3DX11_IMAGE_LOAD_INFO loadInfo = {};
    loadInfo.MiscFlags = D3D11_RESOURCE_MISC_TEXTURECUBE;

    // load and create cubemap dds texture
    HRESULT hr = D3DX11CreateTextureFromFile(p_dxdevice, fileName, &loadInfo, nullptr, (ID3D11Resource**)&p_texture, &hr);
    if (FAILED(hr))
    {
        MessageBox(WDS.WindowHandle, fileName, L"Failed to create cubemap texture", MB_OK);
        return -105;
    }

    D3D11_TEXTURE2D_DESC texDesc;
    p_texture->GetDesc(&texDesc);

    D3D11_SHADER_RESOURCE_VIEW_DESC viewDesc = {};
    viewDesc.Format = texDesc.Format;
    viewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBE;
    viewDesc.TextureCube.MipLevels = texDesc.MipLevels;
    viewDesc.TextureCube.MostDetailedMip = 0;

    // create shader ressource view
    hr = p_dxdevice->CreateShaderResourceView(p_texture, &viewDesc, &p_shaderResourceView);
    if (FAILED(hr))
    {
        MessageBox(WDS.WindowHandle, fileName, L"Failed to create cubemap shader resourceview", MB_OK);
        return -106;
    }

    // set sampler desription properties
    D3D11_SAMPLER_DESC samplerDesc = {};
    samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;

    hr = p_dxdevice->CreateSamplerState(&samplerDesc, &p_textureSampler);
    if (FAILED(hr))
    {
        MessageBox(WDS.WindowHandle, fileName, L"Failed to create cubemap sampler state", MB_OK);
        return -107;
    }

    return 0;
}

int Cubemap::Update()
{
    p_dxcontext->PSSetSamplers(0, 1, &p_textureSampler);
    p_dxcontext->PSSetShaderResources(0, 1, &p_shaderResourceView);

    return 0;
}

int Cubemap::DeInit()
{
    SafeRelease(p_dxdevice);
    SafeRelease(p_dxcontext);
    SafeRelease(p_texture);
    SafeRelease(p_shaderResourceView);
    SafeRelease(p_textureSampler);

    return 0;
}
