//
// Created by KirkH on 2022/12/3.
//
#include <cstdio>
#include <iostream>
#include <sstream>
#include "static_reflect.h"

template<typename T>
void serializeObj(std::ostream& out, const T& obj,
                  const char* fieldName = "", int depth = 0) {
    auto indent = [&] {
        for (int i = 0; i < depth; ++i)
        { out << "    "; }
    };

    if constexpr(IsReflected_v<T>) {
        indent();
        out << fieldName << (*fieldName ? ": {" : "{") << std::endl;
        forEach(obj,
                [&](auto&& fieldName, auto&& value)
                { serializeObj(out, value, fieldName, depth + 1); });
        indent();
        out << "}" << std::endl;
    } else {
        indent();
        out << fieldName << ": " << obj << std::endl;
    }
}

template<typename T>
void deserializeObj(std::istream& in, T& obj,
                    const char* fieldName = "") {
    if constexpr(IsReflected_v<T>) {
        std::string token;
        in >> token; // eat '{'
        if (*fieldName) {
            in >> token; // WARNING: needs check fieldName valid
        }

        forEach(obj,
                [&](auto&& fieldName, auto&& value)
                { deserializeObj(in, value, fieldName); });

        in >> token; // eat '}'
    } else {
        if (*fieldName) {
            std::string token;
            in >> token; // WARNING: needs check fieldName valid
        }
        in >> obj; // dump value
    }
}

DEFINE_STRUCT(DirectionLight,
              (float) position_x,
              (float) position_y,
              (float) position_z,
              (float) euler_angle_x,
              (float) euler_angle_y,
              (float) euler_angle_z,
              (float) local_scale_x,
              (float) local_scale_y,
              (float) local_scale_z,
              (float) color_r,
              (float) color_g,
              (float) color_b,
              (std::string) name,
              (bool) caster_shadow
);

DEFINE_STRUCT(LightSetting,
              (float) color_r,
              (float) color_g,
              (float) color_b,
              (float) exposure,
              (float) rotation,
              (std::string) material_path
);

DEFINE_STRUCT(Render,
              (std::string) name,
              (int) render_type,
              (std::string) material_path,
              (std::string) mesh_path,
              (float) position_x,
              (float) position_y,
              (float) position_z,
              (float) euler_angle_x,
              (float) euler_angle_y,
              (float) euler_angle_z,
              (float) local_scale_x,
              (float) local_scale_y,
              (float) local_scale_z
);

DEFINE_STRUCT(SceneData,
              (DirectionLight) dLight,
              (LightSetting) light_setting,
              (Render) render
);

int main(int argc, char **argv) {
    std::stringstream result; // serialize result
    {
        SceneData scene_data{

                {-20.0f, 30.0f, 20.0f,
                        30.0f, -60.0f, -50.0f,
                        1.0f, 1.0f, 1.0f,
                        1.0f, 0.957f, 0.839f,
                        "Direction Light",
                        true},

                {1.0f, 1.0f, 1.0f,
                        1.0f,
                        0.0f,
                        "Asset/Materials/sky.mat"},

                {"ak47",
                        0,
                        "Asset/Materials/ak47.mat",
                        "Asset/Mesh/ak47.obj",
                        6.0f, 10.0f, 0.0f,
                        0.0f, 0.0f, 0.0f,
                        1.0f, 1.0f, 1.0f}

        };
        serializeObj(result, scene_data);
    }
    std::cout << "serialize scene result:" << std::endl
              << result.str() << std::endl;

    SceneData scene_data;
    deserializeObj(result, scene_data);
    std::cout << "deserialize scene result:" << std::endl;
    serializeObj(std::cout, scene_data);

    return 0;
}
