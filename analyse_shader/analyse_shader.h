//
// Created by Administrator on 2022/12/5.
//

#ifndef RTTR_ANALYSE_SHADER_H
#define RTTR_ANALYSE_SHADER_H
#pragma once
#include "load_shader.h"
#include "shader_struct.h"
#include "Shader.h"
#include <boost/algorithm/string.hpp>

using namespace boost;

class analyse_shader {
public:
    analyse_shader() = default;
    ~analyse_shader() = default;

    void load(std::string path);
    void analyse();

private:
    void erase_enter(std::string& str);
    std::string character_segmentation(std::string source);
    void set_d3d12_blend(D3D12_BLEND& blend_mode, std::string compare_string, std::string key, std::string value);
    void set_d3d12_blend_op(D3D12_BLEND_OP& blend_mode, std::string compare_string, std::string key, std::string value);
    void set_d3d12_logic_op(D3D12_LOGIC_OP& blend_mode, std::string compare_string, std::string key, std::string value);
    void set_d3d12_color_write_enable(D3D12_COLOR_WRITE_ENABLE& write_enable, std::string compare_string, std::string key, std::string value);
private:
    void analyse_code(std::string combine);
    void analyse_name_part(std::string name_string, Shader* shader);
    void analyse_input_data_part(std::string input_data_string, Shader* shader);
    void analyse_tags_part(std::string tag_string, Shader* shader);
    void analyse_raster_mode_part(std::string raster_mode_string, Shader* shader);
    void analyse_blend_mode_part(std::string blend_mode_string, Shader* shader);
    void analyse_depth_stencil_mode_part(std::string depth_stencil_mode_string, Shader* shader);

private:
    std::vector<std::string> shader_file_paths;     //  Shader 文件路径
    std::unordered_map<std::string, std::vector<State>> shader_states;  //  Shader名称对应的ShaderState
};


#endif //RTTR_ANALYSE_SHADER_H
