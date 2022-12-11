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
    std::string input_data_string = "";
    std::string tag_string = "";
    std::string rasterizer_mode_string = "";
    std::string blend_mode_string = "";
    std::string depth_stencil_mode = "";

    if(part_vector.size() == 6)
    {
        name_string = trim_copy(part_vector[0]);
        input_data_string = trim_copy(part_vector[1]);
        tag_string = trim_copy(part_vector[2]);
        rasterizer_mode_string = trim_copy(part_vector[3]);
        blend_mode_string = trim_copy(part_vector[4]);
        depth_stencil_mode = trim_copy(part_vector[5]);
    }
    else
    {
        cout<<"error shader code!"<<endl;
        return;
    }

    Shader* shader = new Shader();

    //  Get Name
    analyse_name_part(name_string, shader);

    //  Get InputData
    analyse_input_data_part(input_data_string, shader);

    //  Get TagsData
    analyse_tags_part(tag_string, shader);
}

void analyse_shader::erase_enter(std::string& str)
{
    str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
}

std::string analyse_shader::character_segmentation(std::string source) {
    int len = source.size();
    char buf[1024];
    char buf1[1024]={0};
    char tar1[10] = {"{"};
    char tar2[10] = {"}"};
    sprintf(buf ,"%s", source.c_str());
    int ib = 0;
    for (int i = 0; i < len; i++)
    {
        if ( buf[i] == tar1[0]) {

            for (int ii = i; i < len; i++)
            {
                if (buf[i + 1] == tar2[0])
                {
                    break;
                }
                if (buf[i + 1] != tar1[0])
                {
                    buf1[ib] = buf[i + 1];
                    ib++;
                }
            }
        }
    }
    return buf1;
}

void analyse_shader::analyse_name_part(std::string name_string, Shader* shader)
{
    //  Judge Content Name
    string::size_type stringIdx = name_string.find(shader_key_word[0]);
    //  Content "Name"
    if (stringIdx != string::npos)
    {
        vector<string> name_vector;
        //  Split (';')
        split(name_vector, name_string, is_any_of(";"), token_compress_on);
        if(name_vector.size() > 0)
        {
            //  Split ("=")
            name_string = name_vector[0];
            name_vector.clear();
            split(name_vector, name_string, is_any_of("="), token_compress_on);
            if(name_vector.size() > 1)
            {   //  Set Name
                shader->set_name(trim_copy(name_vector[1]));
            }
        }
    }
}

void analyse_shader::analyse_input_data_part(std::string input_data_string, Shader* shader)
{
//    State shader_state;

    //  Judge Content InputData
    string::size_type stringIdx = input_data_string.find(shader_key_word[1]);
    //  Content "InputData"
    if (stringIdx != string::npos)
    {
        //  Get{} String
        input_data_string = character_segmentation(input_data_string);

        vector<string> input_data_vector;
        //  Split (';')
        split(input_data_vector, input_data_string, is_any_of(";"), token_compress_on);
        if(input_data_vector.size() > 0)
        {
            vector<string> property_data_vector;

            for(int i = 0; i < input_data_vector.size(); i++)
            {
                std::string current_line_string = input_data_vector[i];
                //  Content Texture
                string::size_type texIdx = current_line_string.find(input_data_key_word[0]);
                if(texIdx != string::npos)
                {
                    //  Split (":")
                    property_data_vector.clear();
                    split(property_data_vector, current_line_string, is_any_of(":"), token_compress_on);
                    if(property_data_vector.size() > 0)
                    {
                        //  Split ("=")
                        std::string new_current_line_string = property_data_vector[1];
                        property_data_vector.clear();
                        split(property_data_vector, new_current_line_string, is_any_of("="), token_compress_on);
                        if(property_data_vector.size() > 1)
                        {
                            std::cout<< trim_copy(property_data_vector[0]) << ":  ";
                            std::cout<< trim_copy(property_data_vector[1]) << std::endl;
                            //  set state
//                            shader_state.add_property<string>(trim_copy(property_data_vector[0]));
//                            shader_state.set_property<string>(trim_copy(property_data_vector[0]),trim_copy(property_data_vector[1]));
                        }
                    }
                }

                //  Content Color
                string::size_type colorIdx = current_line_string.find(input_data_key_word[1]);
                if(colorIdx != string::npos)
                {
                    //  Split (":")
                    property_data_vector.clear();
                    split(property_data_vector, current_line_string, is_any_of(":"), token_compress_on);
                    if(property_data_vector.size() > 0)
                    {
                        //  Split ("=")
                        std::string new_current_line_string = property_data_vector[1];
                        property_data_vector.clear();
                        split(property_data_vector, new_current_line_string, is_any_of("="), token_compress_on);
                        if(property_data_vector.size() > 1)
                        {
                            std::cout<< trim_copy(property_data_vector[0]) << ":  ";
                            std::cout<< trim_copy(property_data_vector[1]) << std::endl;
                            //  set state
//                            shader_state.add_property<string>(trim_copy(property_data_vector[0]));
//                            shader_state.set_property<string>(trim_copy(property_data_vector[0]),trim_copy(property_data_vector[1]));
                        }
                    }
                }

                //  Content Int
                string::size_type intIdx = input_data_vector[i].find(input_data_key_word[2]);
                if(intIdx != string::npos)
                {
                    //  Split (":")
                    property_data_vector.clear();
                    split(property_data_vector, current_line_string, is_any_of(":"), token_compress_on);
                    if(property_data_vector.size() > 0)
                    {
                        //  Split ("=")
                        std::string new_current_line_string = property_data_vector[1];
                        property_data_vector.clear();
                        split(property_data_vector, new_current_line_string, is_any_of("="), token_compress_on);
                        if(property_data_vector.size() > 1)
                        {
                            std::cout<< trim_copy(property_data_vector[0]) << ":  ";
                            std::cout<< trim_copy(property_data_vector[1]) << std::endl;
                            //  set state
//                            shader_state.add_property<string>(trim_copy(property_data_vector[0]));
//                            shader_state.set_property<string>(trim_copy(property_data_vector[0]),trim_copy(property_data_vector[1]));
                        }
                    }
                }

                //  Content Float
                string::size_type floatIdx = input_data_vector[i].find(input_data_key_word[3]);
                if(floatIdx != string::npos)
                {
                    //  Split (":")
                    property_data_vector.clear();
                    split(property_data_vector, current_line_string, is_any_of(":"), token_compress_on);
                    if(property_data_vector.size() > 0)
                    {
                        //  Split ("=")
                        std::string new_current_line_string = property_data_vector[1];
                        property_data_vector.clear();
                        split(property_data_vector, new_current_line_string, is_any_of("="), token_compress_on);
                        if(property_data_vector.size() > 1)
                        {
                            std::cout<< trim_copy(property_data_vector[0]) << ":  ";
                            std::cout<< trim_copy(property_data_vector[1]) << std::endl;
                            //  set state
//                            shader_state.add_property<string>(trim_copy(property_data_vector[0]));
//                            shader_state.set_property<string>(trim_copy(property_data_vector[0]),trim_copy(property_data_vector[1]));
                        }
                    }
                }

            }
        }
    }
}

void analyse_shader::analyse_tags_part(std::string tag_string, Shader* shader) {
    //  Judge Content TagsData
    string::size_type stringIdx = tag_string.find(shader_key_word[2]);
    //  Content "TagsData"
    if (stringIdx != string::npos) {
        //  Get{} String
        tag_string = character_segmentation(tag_string);

        vector <string> tag_vector;
        //  Split (';')
        split(tag_vector, tag_string, is_any_of(";"), token_compress_on);
        if(tag_vector.size() > 0)
        {
            vector <string> tags_data_vector;
            ShaderTags tags;

            for(int i = 0; i < tag_vector.size(); i++)
            {
                std::string current_line_string = tag_vector[i];

                //  Content RenderPass
                string::size_type render_pass_Idx = tag_vector[i].find(tags_key_word[0]);
                if(render_pass_Idx != string::npos)
                {
                    //  Split ("=")
                    tags_data_vector.clear();
                    split(tags_data_vector, current_line_string, is_any_of("="), token_compress_on);
                    if(tags_data_vector.size() > 0)
                    {
                        if(equals(trim_copy(tags_data_vector[0]),"RenderPass"))
                            tags.RenderPass = trim_copy(tags_data_vector[1]);
                    }
                }

                //  Content RenderType
                string::size_type render_type_Idx = tag_vector[i].find(tags_key_word[1]);
                if(render_type_Idx != string::npos)
                {
                    //  Split ("=")
                    tags_data_vector.clear();
                    split(tags_data_vector, current_line_string, is_any_of("="), token_compress_on);
                    if(tags_data_vector.size() > 0)
                    {
                        if(equals(trim_copy(tags_data_vector[0]),"RenderType"))
                            tags.RenderType = trim_copy(tags_data_vector[1]);
                    }
                }
            }

            shader->set_tag(tags);
        }
    }
}

void analyse_shader::analyse_raster_mode_part(std::string raster_mode_string, Shader* shader)
{
    //  Judge Content RasterizerMode
    string::size_type stringIdx = raster_mode_string.find(shader_key_word[3]);
    //  Content "RasterizerMode"
    if (stringIdx != string::npos) {
        //  Get{} String
        raster_mode_string = character_segmentation(raster_mode_string);

        vector <string> raster_mode_vector;
        //  Split (';')
        split(raster_mode_vector, raster_mode_string, is_any_of(";"), token_compress_on);
        if(raster_mode_vector.size() > 0)
        {
            vector <string> raster_mode_data_vector;
            ShaderRasterizerMode rasterizer_mode;

            for(int i = 0; i < raster_mode_vector.size(); i++)
            {
                std::string current_line_string = raster_mode_vector[i];

                //  Content FillMode
                string::size_type fill_mode_Idx = raster_mode_vector[i].find(tags_key_word[0]);
                if(fill_mode_Idx != string::npos)
                {
                    //  Split ("=")
                    raster_mode_data_vector.clear();
                    split(raster_mode_data_vector, current_line_string, is_any_of("="), token_compress_on);
                    if(raster_mode_data_vector.size() > 0)
                    {
                        if(equals(trim_copy(raster_mode_data_vector[0]),"FillMode"))
                        {
                            if(equals(trim_copy(raster_mode_data_vector[1]),"D3D12_FILL_MODE_WIREFRAME"))
                                rasterizer_mode.FILL_MODE = D3D12_FILL_MODE_WIREFRAME;
                            else
                                rasterizer_mode.FILL_MODE = D3D12_FILL_MODE_SOLID;
                        }
                    }
                }

                //  Content CullMode
                string::size_type cull_mode_Idx = raster_mode_vector[i].find(tags_key_word[1]);
                if(cull_mode_Idx != string::npos)
                {
                    //  Split ("=")
                    raster_mode_data_vector.clear();
                    split(raster_mode_data_vector, current_line_string, is_any_of("="), token_compress_on);
                    if(raster_mode_data_vector.size() > 0)
                    {
                        if(equals(trim_copy(raster_mode_data_vector[0]),"CullMode"))
                        {
                            if(equals(trim_copy(raster_mode_data_vector[1]),"D3D12_CULL_MODE_NONE"))
                                rasterizer_mode.CULL_MODE = D3D12_CULL_MODE_NONE;
                            else if(equals(trim_copy(raster_mode_data_vector[1]),"D3D12_CULL_MODE_FRONT"))
                                rasterizer_mode.CULL_MODE = D3D12_CULL_MODE_FRONT;
                            else
                                rasterizer_mode.CULL_MODE = D3D12_CULL_MODE_BACK;
                        }
                    }
                }
            }

            shader->set_rasterizer_mode(rasterizer_mode);
        }
    }
}