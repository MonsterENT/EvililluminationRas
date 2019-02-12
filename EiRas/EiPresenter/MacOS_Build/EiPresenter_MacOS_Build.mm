//
//  EiPresenter_MacOS_Build.m
//  EiRasiOSBuild
//
//  Created by MonsterENT on 2/10/19.
//  Copyright © 2019 yang. All rights reserved.
//

#import "EiPresenter_MacOS_Build.h"

#if (defined Ei_MacOS_Build) || (defined Ei_iOS_Build)

@implementation EiPresenter_MacOS_Build

+(void)present:(EiRas*)device target:(void*)target
{
    Byte* array = new Byte[EiRas::getFrameSize().x * EiRas::getFrameSize().y * 4];
    
    for(int i = 0; i < EiRas::getFrameSize().x * EiRas::getFrameSize().y; i++)
    {
        array[i * 4] = device->getFrameBuffer()[i].r * 255.0f;
        array[i * 4 + 1] = device->getFrameBuffer()[i].b * 255.0f;
        array[i * 4 + 2] = device->getFrameBuffer()[i].g * 255.0f;
        array[i * 4 + 3] = 255.0f;
    }
    CGDataProviderRef provider = CGDataProviderCreateWithData(NULL,
                                                              array,
                                                              1242 * 2688 * 4,
                                                              NULL);
    CGColorSpaceRef colorSpaceRef = CGColorSpaceCreateDeviceRGB();
    CGBitmapInfo bitmapInfo = kCGBitmapByteOrderDefault;
    CGColorRenderingIntent renderingIntent = kCGRenderingIntentDefault;
    CGImageRef imageRef = CGImageCreate(1242, 2688, 8, 32, 4 * 1242, colorSpaceRef, bitmapInfo,provider, NULL, NO, renderingIntent);
    
    UIImage *newImage = [UIImage imageWithCGImage:imageRef];
    
    CFRelease(imageRef);
    UIImageView* re_target = (__bridge UIImageView*)target;
    if([re_target isKindOfClass:[UIImageView class]])
    {
        dispatch_async(dispatch_get_main_queue(), ^{
            re_target.image = newImage;
        });
    }
}

@end
#endif
