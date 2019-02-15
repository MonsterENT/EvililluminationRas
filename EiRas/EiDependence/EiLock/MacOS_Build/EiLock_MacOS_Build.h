//
//  EiLock_MacOS_Build.h
//  EiRasMacBuild
//
//  Created by MonsterENT on 2/13/19.
//  Copyright © 2019 MonsterEntertainment. All rights reserved.
//

#include "../../../EiMacro.h"
#if (defined Ei_MacOS_Build) || (defined Ei_iOS_Build)

#import <Foundation/Foundation.h>
NS_ASSUME_NONNULL_BEGIN

@interface EiLock_MacOS_Build : NSObject

@property(strong, nonatomic)NSRecursiveLock* lock;

@property(strong,nonatomic,nullable)EiLock_MacOS_Build* self_retain_ptr;

@end

NS_ASSUME_NONNULL_END

#endif
