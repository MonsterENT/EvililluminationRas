//
//  EiMacro.h
//  EvililluminationRas
//
//  Created by yang on 2018/12/13.
//  Copyright © 2018 Monster. All rights reserved.
//

#ifndef EiMacro_h
#define EiMacro_h

#define Ei_DEBUG
//#define Ei_RELEASE

//platform define \ chose one of these platforms to build the project
#define Ei_MacOS_Build
//#define Ei_iOS_Build
//#define Ei_Android_Build
//#define Ei_Windows_Build

#define  _PI (3.1415926)
#define  _ESP0X1 (1e-1)
#define  _ESP0X2 (1e-2)
#define  _ESP0X5 (1e-5)
#define  _ESP0X10 (1e-10)

#define ColorRed vec4(1, 0, 0, 1);
#define ColorGreen vec4(0, 1, 0, 1);
#define ColorBlue vec4(0, 0, 1, 1);
#define ColorGray(x) vec4(x, x, x, 1)

#define MSAA4X (4)

#define WidthGapMSAA4X (1.0f / (float)(NDC2FrameWidth))
#define HeightGapMSAA4X (1.0f / (float)(NDC2FrameHeight))

#ifndef MAXFLOAT
#define MAXFLOAT 0x1.fffffep+127f
#endif

#endif /* EiMacro_h */
