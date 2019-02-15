//
//  EiLock_MacOS_Build.m
//  EiRasMacBuild
//
//  Created by MonsterENT on 2/13/19.
//  Copyright © 2019 MonsterEntertainment. All rights reserved.
//

#import "EiLock_MacOS_Build.h"

#if (defined Ei_MacOS_Build) || (defined Ei_iOS_Build)

@implementation EiLock_MacOS_Build

-(instancetype)init
{
    if(self = [super init])
    {
        _lock = [NSRecursiveLock new];
    }
    return self;
}

@end
#endif
