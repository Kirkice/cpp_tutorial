//
// Created by Administrator on 2022/12/5.
//

#include "analyse_shader.h"

void analyse_shader::load(std::string folder_path)
{
    get_shader_files(folder_path,shader_file_paths);
}

void analyse_shader::analyse()
{
    if(shader_file_paths.size() <= 0)
        return;

    for (int i = 0; i < shader_file_paths.size(); ++i)
    {
        ifstream srcFile(shader_file_paths[i], ios::in);    //以文本模式打开txt文件
        string combine = "";
        string x;
        while (getline(srcFile, x))    //数字读取方式
        {
            combine.append(x);
            combine.append("!");
        }
        analyse_code(combine);
        srcFile.close();
    }
}

void analyse_shader::analyse_code(std::string combine)
{
    //  第一层关键字分割
    vector<string> part_vector;
    split(part_vector, combine, is_any_of("---"), token_compress_on);

    std::string name_string = "";
    std::string tag_string = "";
    std::string rasterizer_mode_string = "";
    std::string blend_mode_string = "";
    std::string depth_stencil_mode = "";
    
}