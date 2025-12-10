/*
 * Project: N|Watch
 * Author: Zak Kemble, contact@zakkemble.co.uk
 * Copyright: (C) 2013 by Zak Kemble
 * License: GNU GPL v3 (see License.txt)
 * Web: http://blog.zakkemble.co.uk/diy-digital-wristwatch/
 */
#include <stdlib.h>
#include <stdio.h>

#include "cmsis_os.h"
#include "FreeRTOS.h"                   // ARM.FreeRTOS::RTOS:Core
#include "task.h"                       // ARM.FreeRTOS::RTOS:Core
#include "event_groups.h"               // ARM.FreeRTOS::RTOS:Event Groups
#include "semphr.h"                     // ARM.FreeRTOS::RTOS:Core

#include "draw.h"
#include "resources.h"

#include "driver_lcd.h"
#include "driver_ir_receiver.h"
#include "driver_rotary_encoder.h"
#include "driver_mpu6050.h"


#define NOINVERT	false
#define INVERT		true


#define CAR_COUNT	3
#define CAR_WIDTH	12
#define CAR_LENGTH	15
#define ROAD_SPEED	6

static uint32_t g_xres, g_yres, g_bpp;
static uint8_t *g_framebuffer;


static const byte carImg[]  ={
	0x40,0xF8,0xEC,0x2C,0x2C,0x38,0xF0,0x10,0xD0,0x30,0xE8,0x4C,0x4C,0x9C,0xF0,
	0x02,0x1F,0x37,0x34,0x34,0x1C,0x0F,0x08,0x0B,0x0C,0x17,0x32,0x32,0x39,0x0F,
};


static const byte clearImg[30] ={0};

static const byte roadMarking[]  ={
	0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
};

void car_test(void)
{
	g_framebuffer = LCD_GetFrameBuffer(&g_xres, &g_yres, &g_bpp);
    draw_init();
    draw_end();

	  // Draw platform
    draw_bitmap(0, 0 , carImg, 15,16, NOINVERT, 0);
    draw_flushArea(0, 0, 15, 16);


	draw_bitmap(0, 16 , roadMarking, 8,1, NOINVERT, 0);
    draw_flushArea(0,16, 8, 1);

	while (1);
	

}




