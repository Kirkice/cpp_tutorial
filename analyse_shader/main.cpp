//
// Created by Administrator on 2022/12/6.
//

#include "property.h"

int main()
{
//    string path;
//    cin >> path;
//
//    analyse_shader m_analyse_shader = analyse_shader();
//    m_analyse_shader.load(path);
//    m_analyse_shader.analyse();
//
//    system("pause");

    State pbr_material_state;
    //  设置name
    pbr_material_state.add_property<string>("name");
    pbr_material_state.set_property<string>("name", "New Lit Material");
    return 0;
}