//
// Created by Administrator on 2022/12/6.
//

#include "analyse_shader.h"

int main()
{
    string path;
    cin >> path;

    std::vector<std::unique_ptr<Shader>> shader_vector;

    analyse_shader m_analyse_shader = analyse_shader();
    m_analyse_shader.load(path,shader_vector);

//    cout<<"Shader 数量"<<shader_vector.size()<<endl;
//    for (int l = 0; l < shader_vector.size(); ++l) {
//        cout<<shader_vector[l]->get_name()<<endl;
//
//        ShaderTags tags = shader_vector[l]->get_tag();
//        cout<<"RenderPass: "<<tags.RenderPass<<endl;
//        cout<<"RenderType: "<<tags.RenderType<<endl;
//
//        ShaderRasterizerMode rasterizer = shader_vector[l]->get_rasterizer_mode();
//        cout<<"FILL_MODE: "<<rasterizer.FILL_MODE<<endl;
//        cout<<"CULL_MODE: "<<rasterizer.CULL_MODE<<endl;
//
//        ShaderDepthStencilMode depth = shader_vector[l]->get_depth_stencil_mode();
//        cout<<"DepthEnable: "<<depth.DepthEnable<<endl;
//        cout<<"DepthWriteMask: "<<depth.DepthWriteMask<<endl;
//        cout<<"DepthFunc: "<<depth.DepthFunc<<endl;
//    }


    system("pause");
    return 0;
}