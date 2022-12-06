//
// Created by Administrator on 2022/12/6.
//

#include "analyse_shader.h"

int main()
{
    string path;
    cin >> path;

    analyse_shader m_analyse_shader = analyse_shader();
    m_analyse_shader.load(path);
    m_analyse_shader.analyse();

    system("pause");
    return 0;
}