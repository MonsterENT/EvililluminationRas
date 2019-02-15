//
//  EiLock.hpp
//  EvililluminationRas
//
//  Created by MonsterENT on 2/13/19.
//  Copyright © 2019 Monster. All rights reserved.
//

#ifndef EiLock_hpp
#define EiLock_hpp

#include "../../EiRasObject.hpp"

class EiLock : public EiRasObject{
public:
    virtual ~EiLock(){}
    virtual void lock(){}
    virtual void unlock(){}
};
#endif /* EiLock_hpp */
