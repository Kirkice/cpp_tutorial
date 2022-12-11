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

    //  Get Raster Mode
    analyse_raster_mode_part(rasterizer_mode_string, shader);

    //  Get Blend Mode
    analyse_blend_mode_part(blend_mode_string, shader);
}

void analyse_shader::set_d3d12_blend(D3D12_BLEND& blend_mode, std::string compare_string, std::string key, std::string value)
{
    if(equals(trim_copy(key),compare_string))
    {
        if(equals(trim_copy(value),"D3D12_BLEND_ZERO"))
            blend_mode = D3D12_BLEND_ZERO;
        else if(equals(trim_copy(value),"D3D12_BLEND_ONE"))
            blend_mode = D3D12_BLEND_ONE;
        else if(equals(trim_copy(value),"D3D12_BLEND_SRC_COLOR"))
            blend_mode = D3D12_BLEND_SRC_COLOR;
        else if(equals(trim_copy(value),"D3D12_BLEND_INV_SRC_COLOR"))
            blend_mode = D3D12_BLEND_INV_SRC_COLOR;
        else if(equals(trim_copy(value),"D3D12_BLEND_SRC_ALPHA"))
            blend_mode = D3D12_BLEND_SRC_ALPHA;
        else if(equals(trim_copy(value),"D3D12_BLEND_INV_SRC_ALPHA"))
            blend_mode = D3D12_BLEND_INV_SRC_ALPHA;
        else if(equals(trim_copy(value),"D3D12_BLEND_DEST_ALPHA"))
            blend_mode = D3D12_BLEND_DEST_ALPHA;
        else if(equals(trim_copy(value),"D3D12_BLEND_INV_DEST_ALPHA"))
            blend_mode = D3D12_BLEND_INV_DEST_ALPHA;
        else if(equals(trim_copy(value),"D3D12_BLEND_DEST_COLOR"))
            blend_mode = D3D12_BLEND_DEST_COLOR;
        else if(equals(trim_copy(value),"D3D12_BLEND_INV_DEST_COLOR"))
            blend_mode = D3D12_BLEND_INV_DEST_COLOR;
        else if(equals(trim_copy(value),"D3D12_BLEND_SRC_ALPHA_SAT"))
            blend_mode = D3D12_BLEND_SRC_ALPHA_SAT;
        else if(equals(trim_copy(value),"D3D12_BLEND_BLEND_FACTOR"))
            blend_mode = D3D12_BLEND_BLEND_FACTOR;
        else if(equals(trim_copy(value),"D3D12_BLEND_INV_BLEND_FACTOR"))
            blend_mode = D3D12_BLEND_INV_BLEND_FACTOR;
        else if(equals(trim_copy(value),"D3D12_BLEND_SRC1_COLOR"))
            blend_mode = D3D12_BLEND_SRC1_COLOR;
        else if(equals(trim_copy(value),"D3D12_BLEND_INV_SRC1_COLOR"))
            blend_mode = D3D12_BLEND_INV_SRC1_COLOR;
        else if(equals(trim_copy(value),"D3D12_BLEND_SRC1_ALPHA"))
            blend_mode = D3D12_BLEND_SRC1_ALPHA;
        else if(equals(trim_copy(value),"D3D12_BLEND_INV_SRC1_ALPHA"))
            blend_mode = D3D12_BLEND_INV_SRC1_ALPHA;
        else if(equals(trim_copy(value),"D3D12_BLEND_ALPHA_FACTOR"))
            blend_mode = D3D12_BLEND_ALPHA_FACTOR;
        else
            blend_mode = D3D12_BLEND_INV_ALPHA_FACTOR;
    }
}

void analyse_shader::set_d3d12_blend_op(D3D12_BLEND_OP& blend_mode, std::string compare_string, std::string key, std::string value)
{
    if(equals(trim_copy(key),compare_string))
    {
        if(equals(trim_copy(value),"D3D12_BLEND_OP_ADD"))
            blend_mode = D3D12_BLEND_OP_ADD;
        else if(equals(trim_copy(value),"D3D12_BLEND_OP_SUBTRACT"))
            blend_mode = D3D12_BLEND_OP_SUBTRACT;
        else if(equals(trim_copy(value),"D3D12_BLEND_OP_REV_SUBTRACT"))
            blend_mode = D3D12_BLEND_OP_REV_SUBTRACT;
        else if(equals(trim_copy(value),"D3D12_BLEND_OP_MIN"))
            blend_mode = D3D12_BLEND_OP_MIN;
        else
            blend_mode = D3D12_BLEND_OP_MAX;
    }
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
                string::size_type fill_mode_Idx = raster_mode_vector[i].find(rasterizer_mode_key_word[0]);
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
                string::size_type cull_mode_Idx = raster_mode_vector[i].find(rasterizer_mode_key_word[1]);
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

void analyse_shader::analyse_blend_mode_part(std::string blend_mode_string, Shader* shader)
{
    //  Judge Content BlendMode
    string::size_type stringIdx = blend_mode_string.find(shader_key_word[4]);
    //  Content "BlendMode"
    if (stringIdx != string::npos) {
        //  Get{} String
        blend_mode_string = character_segmentation(blend_mode_string);

        vector <string> blend_mode_vector;
        //  Split (';')
        split(blend_mode_vector, blend_mode_string, is_any_of(";"), token_compress_on);
        if(blend_mode_vector.size() > 0)
        {
            vector <string> blend_mode_data_vector;
            ShaderBlendMode blend_mode;

            for(int i = 0; i < blend_mode_vector.size(); i++)
            {
                int blend_mode_key_word_index = 0;
                std::string current_line_string = blend_mode_vector[i];

                //  Content BlendEnable
                string::size_type blend_enable_Idx = blend_mode_vector[i].find(blend_mode_key_word[blend_mode_key_word_index++]);
                if(blend_enable_Idx != string::npos)
                {
                    //  Split ("=")
                    blend_mode_data_vector.clear();
                    split(blend_mode_data_vector, current_line_string, is_any_of("="), token_compress_on);
                    if(blend_mode_data_vector.size() > 0)
                    {
                        if(equals(trim_copy(blend_mode_data_vector[0]),"BlendEnable"))
                        {
                            if(equals(trim_copy(blend_mode_data_vector[1]),"true"))
                                blend_mode.BlendEnable = true;
                            else
                                blend_mode.BlendEnable = false;
                        }
                    }
                }

                //  Content LogicOpEnable
                string::size_type logic_op_enable_Idx = blend_mode_vector[i].find(blend_mode_key_word[blend_mode_key_word_index++]);
                if(logic_op_enable_Idx != string::npos)
                {
                    //  Split ("=")
                    blend_mode_data_vector.clear();
                    split(blend_mode_data_vector, current_line_string, is_any_of("="), token_compress_on);
                    if(blend_mode_data_vector.size() > 0)
                    {
                        if(equals(trim_copy(blend_mode_data_vector[0]),"LogicOpEnable"))
                        {
                            if(equals(trim_copy(blend_mode_data_vector[1]),"true"))
                                blend_mode.LogicOpEnable = true;
                            else
                                blend_mode.LogicOpEnable = false;
                        }
                    }
                }

                //  Content SrcBlend
                string::size_type src_blend_Idx = blend_mode_vector[i].find(blend_mode_key_word[blend_mode_key_word_index++]);
                if(src_blend_Idx != string::npos)
                {
                    //  Split ("=")
                    blend_mode_data_vector.clear();
                    split(blend_mode_data_vector, current_line_string, is_any_of("="), token_compress_on);
                    if(blend_mode_data_vector.size() > 0)
                        set_d3d12_blend(blend_mode.SrcBlend, "SrcBlend",blend_mode_data_vector[0], blend_mode_data_vector[1]);
                }

                //  Content DestBlend
                string::size_type dest_blend_Idx = blend_mode_vector[i].find(blend_mode_key_word[blend_mode_key_word_index++]);
                if(dest_blend_Idx != string::npos)
                {
                    //  Split ("=")
                    blend_mode_data_vector.clear();
                    split(blend_mode_data_vector, current_line_string, is_any_of("="), token_compress_on);
                    if(blend_mode_data_vector.size() > 0)
                        set_d3d12_blend(blend_mode.DestBlend, "DestBlend", blend_mode_data_vector[0], blend_mode_data_vector[1]);
                }

                //  Content BlendOp
                string::size_type blend_op_Idx = blend_mode_vector[i].find(blend_mode_key_word[blend_mode_key_word_index++]);
                if(blend_op_Idx != string::npos)
                {
                    //  Split ("=")
                    blend_mode_data_vector.clear();
                    split(blend_mode_data_vector, current_line_string, is_any_of("="), token_compress_on);
                    if(blend_mode_data_vector.size() > 0)
                        set_d3d12_blend_op(blend_mode.BlendOp, "BlendOp", blend_mode_data_vector[0], blend_mode_data_vector[1]);
                }

                //  Content SrcBlendAlpha
                string::size_type src_blend_alpha_Idx = blend_mode_vector[i].find(blend_mode_key_word[blend_mode_key_word_index++]);
                if(src_blend_alpha_Idx != string::npos)
                {
                    //  Split ("=")
                    blend_mode_data_vector.clear();
                    split(blend_mode_data_vector, current_line_string, is_any_of("="), token_compress_on);
                    if(blend_mode_data_vector.size() > 0)
                        set_d3d12_blend(blend_mode.SrcBlendAlpha, "SrcBlendAlpha", blend_mode_data_vector[0], blend_mode_data_vector[1]);
                }

                //  Content DestBlendAlpha
                string::size_type dest_blend_alpha_Idx = blend_mode_vector[i].find(blend_mode_key_word[blend_mode_key_word_index++]);
                if(dest_blend_alpha_Idx != string::npos)
                {
                    //  Split ("=")
                    blend_mode_data_vector.clear();
                    split(blend_mode_data_vector, current_line_string, is_any_of("="), token_compress_on);
                    if(blend_mode_data_vector.size() > 0)
                        set_d3d12_blend(blend_mode.DestBlendAlpha, "DestBlendAlpha", blend_mode_data_vector[0], blend_mode_data_vector[1]);
                }

                //  Content BlendOpAlpha
                string::size_type blend_op_alpha_Idx = blend_mode_vector[i].find(blend_mode_key_word[blend_mode_key_word_index++]);
                if(blend_op_alpha_Idx != string::npos)
                {
                    //  Split ("=")
                    blend_mode_data_vector.clear();
                    split(blend_mode_data_vector, current_line_string, is_any_of("="), token_compress_on);
                    if(blend_mode_data_vector.size() > 0)
                        set_d3d12_blend_op(blend_mode.BlendOpAlpha, "BlendOpAlpha", blend_mode_data_vector[0], blend_mode_data_vector[1]);
                }
            }

            shader->set_blend_mode(blend_mode);
        }
    }
}