//
//  EiMacro.h
//  EvililluminationRas
//
//  Created by yang on 2018/12/13.
//  Copyright © 2018 Monster. All rights reserved.
//

#ifndef EiMacro_h
#define EiMacro_h

#define g_width (800)
#define g_height (600)

#define ColorRed vec4(1, 0, 0, 1);
#define ColorGreen vec4(0, 1, 0, 1);
#define ColorBlue vec4(0, 0, 1, 1);
#define ColorGray(x) vec4(x, x, x, 1)

#define MSAA4X (16)

#define reduceY (1.0f / (float)g_height)
#define reduceX (1.0f / (float)g_width)

#define WidthGapMSAA4X (1.0f / (float)(NDC2FrameWidth))
#define HeightGapMSAA4X (1.0f / (float)(NDC2FrameHeight))

#endif /* EiMacro_h */
