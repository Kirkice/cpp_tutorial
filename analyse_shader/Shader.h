//
// Created by Administrator on 2022/12/10.
//

#ifndef ANALYSE_SHADER_SHADER_H
#define ANALYSE_SHADER_SHADER_H
#pragma once
#include "shader_struct.h"

class Shader {

public:
    Shader(std::string name = "New Shader");
    ~Shader();

    //	set name
    void set_name(std::string name);
    //	get name
    const std::string& get_name()const;

    //  set property state
    void set_property_state(State& state);
    //  get property state
    const State get_property_state()const;

    //  set tags
    void set_tag(ShaderTags& tag);
    //  get tags
    const ShaderTags get_tag()const;

    //  set rasterizer
    void set_rasterizer_mode(ShaderRasterizerMode& mode);
    //  get rasterizer
    const ShaderRasterizerMode get_rasterizer_mode()const;

    //  set blend
    void set_blend_mode(ShaderBlendMode& mode);
    //  get blend
    const ShaderBlendMode get_blend_mode()const;

    //  set depth stencil
    void set_depth_stencil_mode(ShaderDepthStencilMode& mode);
    //  get depth stencil
    const ShaderDepthStencilMode get_depth_stencil_mode()const;
private:
    //  name
    std::string name;
    //  property
    State property_state;
    //  tags
    ShaderTags tags;
    //  rasterizer
    ShaderRasterizerMode rasterizer_mode;
    //  blend
    ShaderBlendMode blend_mode;
    // depth stencil
    ShaderDepthStencilMode depth_stencil_mode;
};


#endif //ANALYSE_SHADER_SHADER_H
