//
//  EiPresenter_MacOS_Build.h
//  EiRasiOSBuild
//
//  Created by MonsterENT on 2/10/19.
//  Copyright © 2019 yang. All rights reserved.
//

#include "../../EiMacro.h"

#if (defined Ei_MacOS_Build) || (defined Ei_iOS_Build)

#include "../../EiRasHeaders.h"
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN


@interface EiPresenter_MacOS_Build : NSObject

+(void)present:(EiRas*)device target:(void*)target;

@end

NS_ASSUME_NONNULL_END

#endif
