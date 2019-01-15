//
//  EiRasObject.hpp
//  EvililluminationRas
//
//  Created by MonsterENT on 12/22/18.
//  Copyright © 2018 Monster. All rights reserved.
//

#ifndef EiRasObject_hpp
#define EiRasObject_hpp

typedef unsigned int ClassIdentifier;
#define CI_EiRasObject 100

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

	virtual ClassIdentifier cls()
	{
		return CI_EiRasObject;
	}
};

#endif /* EiRasObject_hpp */
