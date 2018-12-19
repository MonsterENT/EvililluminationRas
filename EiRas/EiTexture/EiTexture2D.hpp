//
//  EiTexture2D.hpp
//  EvililluminationRas
//
//  Created by MonsterENT on 8/9/17.
//  Copyright © 2017 Monster. All rights reserved.
//

#ifndef EiTexture2D_hpp
#define EiTexture2D_hpp

#include "../EiMacro.h"
#include "../EiMath/EiMath.hpp"
#include <string>
#include <vector>

using std::string;
using std::vector;

#define MAX_mipmapCount (16)

enum EiTexAddressingMode
{
    AddressingMode_Warp,
    AddressingMode_Mirror,
};


class EiTexture2D
{
    
public:
    vector<vec4*> tex2Dframe;
    
    int height,width;
    
    EiTexture2D(string fileName);
    
    ~EiTexture2D();
    
    vec4 getColorByUV(vec2 UV, EiTexAddressingMode mode, int mipmapLevel = 0, vec2 OffsetXY = vec2());
    
    void enableMipmap();
    
    int getMipmapCount();
    
    
private:
    struct mipmap
    {
        int height,width;
        vector<vec4*> tex2D;
    };

    bool isEnableMipmap;
    int MipmapCount;
    
    vector<mipmap> mipmapLine;
    vec4 isSampleTex(float x, float y, int mipmapLevel = 0);
    void createMipmap();
    

    
};


#endif /* EiTexture2D_hpp */
