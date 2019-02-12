//
//  EiPresenter_MacOS_Build.m
//  EiRasiOSBuild
//
//  Created by MonsterENT on 2/10/19.
//  Copyright © 2019 yang. All rights reserved.
//

#import "EiPresenter_MacOS_Build.h"
#if (defined Ei_MacOS_Build) || (defined Ei_iOS_Build)

#ifdef Ei_iOS_Build
#import <UIKit/UIKit.h>
#endif

#ifdef Ei_MacOS_Build
#import <Cocoa/Cocoa.h>
#endif

@implementation EiPresenter_MacOS_Build
Byte* backArray = 0;

+(void)present:(EiRas*)device target:(void*)target
{
    if(backArray)
    {
        delete[] backArray;
    }
    backArray = new Byte[EiRas::getFrameSize().x * EiRas::getFrameSize().y * 4];
    for(int i = 0; i < EiRas::getFrameSize().x * EiRas::getFrameSize().y; i++)
    {
        backArray[i * 4] = device->getFrameBuffer()[i].r * 255.0f;
        backArray[i * 4 + 1] = device->getFrameBuffer()[i].b * 255.0f;
        backArray[i * 4 + 2] = device->getFrameBuffer()[i].g * 255.0f;
        backArray[i * 4 + 3] = 255.0f;
    }
    
    CGDataProviderRef provider = CGDataProviderCreateWithData(NULL,
                                                              backArray,
                                                              device->getFrameSize().x * device->getFrameSize().y * 4,
                                                              NULL);
    CGColorSpaceRef colorSpaceRef = CGColorSpaceCreateDeviceRGB();
    CGImageRef imageRef = CGImageCreate(device->getFrameSize().x, device->getFrameSize().y, 8, 32, 4 * device->getFrameSize().x, colorSpaceRef, kCGBitmapByteOrderDefault, provider, NULL, NO, kCGRenderingIntentDefault);

    id newImage = 0;

#ifdef Ei_iOS_Build
    newImage = [UIImage imageWithCGImage:imageRef];
    UIImageView* re_target = (__bridge UIImageView*)target;
    if([re_target isKindOfClass:[UIImageView class]])
    {
        dispatch_async(dispatch_get_main_queue(), ^{
            re_target.image = newImage;
        });
    }
#endif

#ifdef Ei_MacOS_Build
    newImage = [[NSImage alloc]initWithCGImage:imageRef size:NSMakeSize(800, 600)];
    NSImageView* re_target = (__bridge NSImageView*)target;
    if([re_target isKindOfClass:[NSImageView class]])
    {
        dispatch_async(dispatch_get_main_queue(), ^{
            re_target.image = newImage;
        });
    }
#endif
    CGImageRelease(imageRef);
    CGDataProviderRelease(provider);
    CGColorSpaceRelease(colorSpaceRef);
}

@end
#endif
