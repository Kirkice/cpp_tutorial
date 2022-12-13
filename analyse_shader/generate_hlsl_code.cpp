//
// Created by Administrator on 2022/12/11.
//

#include "generate_hlsl_code.h"

//const std::string

void generate_hlsl_code(std::vector<std::unique_ptr<Shader>>& shader_vector, int register_index)
{
    for(int a= 0; a < shader_vector.size(); a++)
    {
        std::unique_ptr<Shader>& shader = shader_vector[a];
        
        string struct_data_string = "";
        struct_data_string.append("struct ");
        struct_data_string.append(shader->get_name());
        struct_data_string.append("\n");
        struct_data_string.append("{\n");

        string texture_data_string = "";
        int texture_data_count = 0;
        for(int i = 0; i < shader->get_property_state_key_vector().size(); ++i)
        {
            std::string type_string = shader->get_property_state_map_value(shader->get_property_state_key_vector()[i]);

            //  Textures
            string::size_type TextureIdx = type_string.find("Texture");
            if(TextureIdx != string::npos)
                texture_data_count++;

            //  Color
            string::size_type ColorIdx = type_string.find("Color");
            if(ColorIdx != string::npos)
                struct_data_string.append("    ").append("float4").append("                    ").append(shader->get_property_state_key_vector()[i]).append(";\n");

            //  Int
            string::size_type IntIdx = type_string.find("Int");
            if(IntIdx != string::npos)
                struct_data_string.append("    ").append("int   ").append("                    ").append(shader->get_property_state_key_vector()[i]).append(";\n");

            //  Float
            string::size_type FloatIdx = type_string.find("Float");
            if(FloatIdx != string::npos)
                struct_data_string.append("    ").append("float ").append("                    ").append(shader->get_property_state_key_vector()[i]).append(";\n");
        }

        struct_data_string.append("};\n").append("\n").append("\n").append("\n").append("\n");

        texture_data_string.append("Texture2D ").append("g").append(shader->get_name()).append("Maps");
        texture_data_string.append("[").append(to_string(texture_data_count)).append("]").append("          ").append(": ");
        texture_data_string.append("register(t").append(to_string(register_index)).append(");\n");

        ofstream outfile;
        std::string file_name = "../shaders/";
        file_name.append(shader->get_name());
        file_name.append("_input.hlsl");
        outfile.open(file_name, ios::trunc);
        outfile<<struct_data_string.append(texture_data_string);
        outfile.close();
    }
}