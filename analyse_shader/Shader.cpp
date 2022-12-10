//
// Created by Administrator on 2022/12/10.
//

#include "Shader.h"

Shader::Shader(string name)
{
    this->name = name;
}

Shader::~Shader()
{
}

void Shader::set_name(std::string name)
{
    this->name = name;
}

const std::string& Shader::get_name()const
{
    return this->name;
}

void Shader::set_property_state(State state)
{
    this->property_state = &state;
}

const State* Shader::get_property_state()const
{
    return this->property_state;
}

void Shader::set_tag(ShaderTags tag)
{
    this->tags = &tag;
}

const ShaderTags* Shader::get_tag()const
{
    return this->tags;
}

void Shader::set_rasterizer_mode(ShaderRasterizerMode mode)
{
    this->rasterizer_mode = &mode;
}

const ShaderRasterizerMode* Shader::get_rasterizer_mode()const
{
    return this->rasterizer_mode;
}

void Shader::set_blend_mode(ShaderBlendMode mode)
{
    this->blend_mode = &mode;
}

const ShaderBlendMode* Shader::get_blend_mode()const
{
    return this->blend_mode;
}