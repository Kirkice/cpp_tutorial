//
// Created by Administrator on 2022/12/5.
//

#ifndef RTTR_ANALYSE_SHADER_H
#define RTTR_ANALYSE_SHADER_H
#include "load_shader.h"
#include "shader_struct.h"
#include "property.h"
#include <boost/algorithm/string.hpp>

using namespace boost;

class analyse_shader {
public:
    analyse_shader() = default;
    ~analyse_shader() = default;

    void load(std::string path);
    void analyse();

private:
    void analyse_code(std::string combine);

private:
    std::vector<std::string> shader_file_paths;     //  Shader 文件路径
    std::unordered_map<std::string, std::vector<State>> shader_states;  //  Shader名称对应的ShaderState
};


#endif //RTTR_ANALYSE_SHADER_H
