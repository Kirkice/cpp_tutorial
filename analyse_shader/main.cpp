//
// Created by Administrator on 2022/12/6.
//

#include "analyse_shader.h"
#include "generate_hlsl_code.h"

int main()
{
    string path;
    cin >> path;

    std::vector<std::unique_ptr<Shader>> shader_vector;
    analyse_shader m_analyse_shader = analyse_shader();
    m_analyse_shader.load(path,shader_vector);

    generate_hlsl_code(shader_vector,6);

    return 0;
}