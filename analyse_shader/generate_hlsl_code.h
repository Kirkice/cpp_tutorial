//
// Created by Administrator on 2022/12/11.
//

#ifndef ANALYSE_SHADER_GENERATE_HLSL_CODE_H
#define ANALYSE_SHADER_GENERATE_HLSL_CODE_H

#pragma once
#include <io.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Shader.h"

void generate_hlsl_code(std::vector<std::unique_ptr<Shader>>& shader_vector, int register_index);

#endif //ANALYSE_SHADER_GENERATE_HLSL_CODE_H
