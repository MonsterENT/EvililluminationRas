//
//  EiRasObject.hpp
//  EvililluminationRas
//
//  Created by MonsterENT on 12/22/18.
//  Copyright © 2018 Monster. All rights reserved.
//

#ifndef EiRasObject_hpp
#define EiRasObject_hpp

class EiRasObject {
    
public:
    virtual int hashCode()
    {
        return -1;
    }
    
    virtual EiRasObject* copy()
    {
        EiRasObject* ret = new EiRasObject;
        return ret;
    }
};

#endif /* EiRasObject_hpp */
