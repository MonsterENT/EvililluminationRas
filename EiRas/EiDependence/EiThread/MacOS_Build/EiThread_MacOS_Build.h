//
//  EiThread_MacOS_Build.h
//  EvililluminationRas
//
//  Created by yang on 2018/12/25.
//  Copyright © 2018 Monster. All rights reserved.
//

#include "../../../EiMacro.h"
#if (defined Ei_MacOS_Build) || (defined Ei_MacOS_Build)

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef void(^EiThread_MacOSBlock)(void);

@interface EiThread_MacOS_Build : NSObject

@property(strong,nonatomic,nullable)EiThread_MacOS_Build* self_retain_ptr;

-(void)runWithBlock:(EiThread_MacOSBlock)block;

@end

NS_ASSUME_NONNULL_END

#endif
