//
//  EiTexture2D.hpp
//  EvililluminationRas
//
//  Created by MonsterENT on 8/9/17.
//  Copyright © 2017 Monster. All rights reserved.
//

#ifndef EiTexture2D_hpp
#define EiTexture2D_hpp

#include "Eimath.h"
#include <string>
#include <vector>

using std::string;
using std::vector;

class EiTexture2D
{
    
public:
    
    
    vector<vec4*> tex2Dframe;
    
    int height,width;
    
    EiTexture2D(string fileName);
    
    ~EiTexture2D();
    
    vec4 getColorByUV(vec2 UV);
    
    
};


#endif /* EiTexture2D_hpp */
