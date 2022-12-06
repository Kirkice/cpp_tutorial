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
        std::cout<<combine<<std::endl;
        srcFile.close();
    }
}

void analyse_shader::analyse_code()
{

}