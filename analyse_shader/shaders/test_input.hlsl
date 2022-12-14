/* $Header: Assets/Shaders/test                                   11/14/22  20:29:59 KirkZhu $ */
/*--------------------------------------------------------------------------------------------*
*                                                                                             *
*                 Project Name : DistEngine                                                   *
*                                                                                             *
*                    File Name : test.hlsl                                                    *
*                                                                                             *
*                   Programmer : Kirk Zhu                                                     *
*--------------------------------------------------------------------------------------------*/

#ifndef DIST_TEST_INCLUDE
#define DIST_TEST_INCLUDE
#include "Core.hlsl"

struct testData
{
    int                       RenderingType;
    float                     NormalScale;
    float                     Smoothness;
    float                     Metallic;
    float                     OcclusionStrength;
};




Texture2D gtestMaps[4]          : register(t6);

 
 #endif