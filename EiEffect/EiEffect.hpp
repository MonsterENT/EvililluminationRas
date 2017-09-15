//
//  EiEffect.hpp
//  EvililluminationRas
//
//  Created by MonsterENT on 9/15/17.
//  Copyright © 2017 Monster. All rights reserved.
//

#ifndef EiEffect_hpp
#define EiEffect_hpp

#include "Eimath.h"
#include "EiRas.hpp"







class EiEffect
{
    
    
public:
    
    EiEffect()
    {
    
    }
    
    vec4* EiEffect_FullScreenBlur(int Radius,int blurtime);

    
private:
    vec4 getSrc(vec4* source,int x,int y);
    
};



#endif /* EiEffect_hpp */
