//
// Created by KirkH on 2022/12/4.
//

#include "property.h"

int main()
{
    State pbr_material_state;
    //  设置name
    pbr_material_state.add_property<string>("name");
    pbr_material_state.set_property<string>("name", "New Lit Material");

    //  设置RenderType    0:Opaque    1:Transparent
    pbr_material_state.add_property<int>("render_type");
    pbr_material_state.set_property<int>("redner_type",0);

    //  设置主图路径
    pbr_material_state.add_property<string>("main_tex_path");
    pbr_material_state.set_property<string>("main_tex_path","Asset/Textures/main_tex");

    //  设置mso纹理路径
    pbr_material_state.add_property<string>("mso_tex_path");
    pbr_material_state.set_property<string>("mso_tex_path","Asset/Textures/mso_tex");

    //  设置金属度
    pbr_material_state.add_property<float>("metallic");
    pbr_material_state.set_property<float>("metallic",0.5f);

    //  设置粗糙度
    pbr_material_state.add_property<float>("roughness");
    pbr_material_state.set_property<float>("roughness",0.5f);

    //  设置AO
    pbr_material_state.add_property<float>("occlusion");
    pbr_material_state.set_property<float>("occlusion",1.0f);

    //  设置法线纹理路径
    pbr_material_state.add_property<string>("normal_tex_path");
    pbr_material_state.set_property<string>("normal_tex_path","Asset/Textures/normal_tex");

    //  设置法线强度
    pbr_material_state.add_property<float>("normal_scale");
    pbr_material_state.set_property<float>("normal_scale",1.0f);

    cout << pbr_material_state.get_value<string>("name") << endl;

    vector<string> res = pbr_material_state.get_properties();
    for(string str:res)
    {
        cout << str << endl;
    }
    return 0;
}