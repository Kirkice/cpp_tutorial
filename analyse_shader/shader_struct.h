//
// Created by Administrator on 2022/12/6.
//

#ifndef ANALYSE_SHADER_SHADER_STRUCT_H
#define ANALYSE_SHADER_SHADER_STRUCT_H
#include <string>

const std::vector<std::string> shader_key_word
{
    "Name",
    "InputData",
    "Tags",
    "RasterizerMode",
    "BlendMode",
    "DepthStencilMode"
};

const std::vector<std::string> input_data_key_word
{
    "Texture",
    "Color",
    "Int",
    "Float"
};

const std::vector<std::string>  tags_key_word
{
    "RenderPass",
    "RenderType"
};

const std::vector<std::string>  rasterizer_mode_key_word
{
    "FillMode",
    "CullMode"
};

const std::vector<std::string>  blend_mode_key_word
{
    "BlendEnable",
    "LogicOpEnable",
    "SrcBlend",
    "DestBlend",
    "BlendOp",
    "SrcBlendAlpha",
    "DestBlendAlpha",
    "BlendOpAlpha",
    "LogicOp",
    "RenderTargetWriteMask"
};

const std::vector<std::string>  depth_stencil_mode_key_word
{
    "DepthEnable",
    "DepthWriteMask",
    "DepthFunc",
    "StencilEnable",
    "StencilReadMask",
    "StencilWriteMask"
};

#endif //ANALYSE_SHADER_SHADER_STRUCT_H
