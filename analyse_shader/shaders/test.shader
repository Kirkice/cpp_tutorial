Name = test;
---
InputData
{
    Texture:MainTex = whtie;
    Color:MainColor = white;
    Int:RenderingType = 0;
    Texture:MsoTexture = white;
    Float:Smoothness = 0.5;
    Float:Metallic = 0.0;
    Float:OcclusionStrength = 1.0;
}
---
Tags
{
    RenderPass = PBR;
    RenderType = Opaque;
}
---
RasterizerMode
{
    FillMode = D3D12_FILL_MODE_SOLID;
    CullMode = D3D12_CULL_MODE_BACK;
}
---
BlendMode
{
	BlendEnable = true;
	LogicOpEnable = false;
	SrcBlend = D3D12_BLEND_SRC_ALPHA;
	DestBlend = D3D12_BLEND_INV_SRC_ALPHA;
	BlendOp = D3D12_BLEND_OP_ADD;
	SrcBlendAlpha = D3D12_BLEND_ONE;
	DestBlendAlpha = D3D12_BLEND_ZERO;
	BlendOpAlpha = D3D12_BLEND_OP_ADD;
	LogicOp = D3D12_LOGIC_OP_NOOP;
	RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;
}
---
DepthStencilMode
{
    DepthEnable = TRUE;
    DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
    DepthFunc = D3D12_COMPARISON_FUNC_LESS;
    StencilEnable = FALSE;
    StencilReadMask = D3D12_DEFAULT_STENCIL_READ_MASK;
    StencilWriteMask = D3D12_DEFAULT_STENCIL_WRITE_MASK;
}