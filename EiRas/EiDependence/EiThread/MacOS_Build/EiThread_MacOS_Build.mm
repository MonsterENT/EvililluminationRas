//
//  EiThread_MacOS_Build.m
//  EvililluminationRas
//
//  Created by yang on 2018/12/25.
//  Copyright © 2018 Monster. All rights reserved.
//

#import "EiThread_MacOS_Build.h"

#if (defined Ei_MacOS_Build) || (defined Ei_iOS_Build)

@implementation EiThread_MacOS_Build

-(instancetype)init
{
    if(self = [super init])
    {
#ifdef Ei_DEBUG
        NSLog(@"EiThread_MacOS_Build Init");
#endif
    }
    return self;
}

-(void)runWithBlock:(EiThread_MacOSBlock)block
{
    if(block)
    {
        dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), block);
    }
}

-(void)dealloc
{
#ifdef Ei_DEBUG
    NSLog(@"EiThread_MacOS_Build Dealloc");
#endif
}
@end
#endif
