/* Emacs style mode select   -*- C++ -*-
 *-----------------------------------------------------------------------------
 *
 * $Id$
 *
 * Copyright (C) 1993-1996 by id Software, Inc.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * $Log$
 * Revision 1.3  2006/04/02 01:52:44  kkurbjun
 * Update adds prboom's high resolution support, also makes the scaling for platforms w/ resolution less then 320x200 much nicer.  IDoom's lookup table code has been removed.  Also fixed a pallete bug.  Some graphic errors are present in menu and status bar.  Also updates some headers and output formatting.
 *
 * Revision 1.2  2006-03-28 17:20:49  christian
 * added good (tm) button mappings for x5, and added ifdef for HAS_BUTTON_HOLD
 *
 * Revision 1.1  2006-03-28 15:44:01  dave
 * Patch #2969 - Doom!  Currently only working on the H300.
 *
 *
 * DESCRIPTION:
 * DOOM graphics and buttons. H300 Port by Karl Kurbjun
 *      IPOD port by Dave Chapman and Paul Louden
 *      Additional work by Thom Johansen
 *
 *-----------------------------------------------------------------------------
 */

#include "doomstat.h"
#include "i_system.h"
#include "v_video.h"
#include "m_argv.h"
#include "d_main.h"

#include "doomdef.h"

#include "rockmacros.h"
#if defined(CPU_COLDFIRE)
static char fastscreen[LCD_WIDTH*LCD_HEIGHT] IBSS_ATTR;
#endif
static fb_data palette[256] IBSS_ATTR;
static fb_data *paldata=NULL;

//
// I_ShutdownGraphics (NOT USED)
//
void I_ShutdownGraphics(void)
{
}

//
// I_StartFrame (NOT USED)
//
void I_StartFrame (void)
{
}

//
// I_GetEvent (NOT USED)
//
void I_GetEvent(void)
{
}

//
// I_StartTic
//

#if CONFIG_KEYPAD == IPOD_4G_PAD
//#define DOOMBUTTON_SCROLLWHEEL
#define DOOMBUTTON_UP         BUTTON_MENU
#define DOOMBUTTON_WEAPON     BUTTON_SELECT
#define DOOMBUTTON_LEFT       BUTTON_LEFT
#define DOOMBUTTON_RIGHT      BUTTON_RIGHT
#define DOOMBUTTON_SHOOT      BUTTON_PLAY
#define DOOMBUTTON_ENTER      BUTTON_SELECT
#define DOOMBUTTON_OPEN       BUTTON_MENU
#elif CONFIG_KEYPAD == IAUDIO_X5_PAD
#define DOOMBUTTON_UP      BUTTON_UP
#define DOOMBUTTON_DOWN    BUTTON_DOWN
#define DOOMBUTTON_LEFT    BUTTON_LEFT
#define DOOMBUTTON_RIGHT   BUTTON_RIGHT
#define DOOMBUTTON_SHOOT   BUTTON_SELECT
#define DOOMBUTTON_OPEN    BUTTON_PLAY
#define DOOMBUTTON_ESC     BUTTON_POWER
#define DOOMBUTTON_ENTER   BUTTON_SELECT
#define DOOMBUTTON_WEAPON  BUTTON_REC
#else
#define DOOMBUTTON_UP      BUTTON_UP
#define DOOMBUTTON_DOWN    BUTTON_DOWN
#define DOOMBUTTON_LEFT    BUTTON_LEFT
#define DOOMBUTTON_RIGHT   BUTTON_RIGHT
#define DOOMBUTTON_SHOOT   BUTTON_REC
#define DOOMBUTTON_OPEN    BUTTON_MODE
#define DOOMBUTTON_ESC     BUTTON_OFF
#define DOOMBUTTON_ENTER   BUTTON_SELECT
#define DOOMBUTTON_WEAPON  BUTTON_ON
#endif

int getkey(event_t * event)
{
   // Same button handling as rockboy
   static unsigned int oldbuttonstate = 0, newbuttonstate=0;

   static int released, pressed;

#ifdef HAS_BUTTON_HOLD
   static unsigned int holdbutton=0;
   static int hswitch=0;
   if (rb->button_hold()&~holdbutton)
   {
      if(hswitch==0)
      {
         event->type = ev_keydown;
         hswitch=1;
      }
      else
      {
         event->type = ev_keyup;
         hswitch=0;
      }
      event->data1=KEY_RSHIFT;
      D_PostEvent(event);
   }
   holdbutton=rb->button_hold();
#endif

   newbuttonstate = rb->button_status();
   released = ~newbuttonstate & oldbuttonstate;
   pressed = newbuttonstate & ~oldbuttonstate;
   oldbuttonstate = newbuttonstate;
   if(released)
   {
      event->type = ev_keyup;
      if(released & DOOMBUTTON_LEFT)
      {
         event->data1=KEY_LEFTARROW;
         D_PostEvent(event);
      }
      if(released & DOOMBUTTON_RIGHT)
      {
         event->data1=KEY_RIGHTARROW;
         D_PostEvent(event);
      }
#ifdef DOOMBUTTON_DOWN
      if(released & DOOMBUTTON_DOWN)
      {
         event->data1=KEY_DOWNARROW;
         D_PostEvent(event);
      }
#endif
      if(released & DOOMBUTTON_UP)
      {
         event->data1=KEY_UPARROW;
         D_PostEvent(event);
      }
      if(released & DOOMBUTTON_SHOOT)
      {
         event->data1=KEY_RCTRL;
         D_PostEvent(event);
      }
      if(released & DOOMBUTTON_OPEN)
      {
         event->data1=' ';
         D_PostEvent(event);
      }
#ifdef DOOMBUTTON_ESC
      if(released & DOOMBUTTON_ESC)
      {
         event->data1=KEY_ESCAPE;
         D_PostEvent(event);
      }
#endif
#ifdef DOOMBUTTON_ENTER
      if(released & DOOMBUTTON_ENTER)
      {
         event->data1=KEY_ENTER;
         D_PostEvent(event);
      }
#endif
#ifdef DOOMBUTTON_WEAPON
      if(released & DOOMBUTTON_WEAPON)
      {
         event->data1 ='w';
         D_PostEvent(event);
      }
#endif
   }
   if(pressed)
   {
      event->type = ev_keydown;
      if(pressed & DOOMBUTTON_LEFT)
      {
         event->data1=KEY_LEFTARROW;
         D_PostEvent(event);
      }
      if(pressed & DOOMBUTTON_RIGHT)
      {
         event->data1=KEY_RIGHTARROW;
         D_PostEvent(event);
      }
#ifdef DOOMBUTTON_DOWN
      if(pressed & DOOMBUTTON_DOWN)
      {
         event->data1=KEY_DOWNARROW;
         D_PostEvent(event);
      }
#endif
      if(pressed & DOOMBUTTON_UP)
      {
         event->data1=KEY_UPARROW;
         D_PostEvent(event);
      }
      if(pressed & DOOMBUTTON_SHOOT)
      {
         event->data1=KEY_RCTRL;
         D_PostEvent(event);
      }
      if(pressed & DOOMBUTTON_OPEN)
      {
         event->data1=' ';
         D_PostEvent(event);
      }
#ifdef DOOMBUTTON_ESC
      if(pressed & DOOMBUTTON_ESC)
      {
         event->data1=KEY_ESCAPE;
         D_PostEvent(event);
      }
#endif
#ifdef DOOMBUTTON_ENTER
      if(pressed & DOOMBUTTON_ENTER)
      {
         event->data1=KEY_ENTER;
         D_PostEvent(event);
      }
#endif
#ifdef DOOMBUTTON_WEAPON
      if(pressed & DOOMBUTTON_WEAPON)
      {
         event->data1='w';
         D_PostEvent(event);
      }
#endif
   }
   if(pressed || released)
      return 1;
   else
      return 0;
}

event_t event;
void I_StartTic (void)
{
   getkey(&event);
}


///////////////////////////////////////////////////////////
// Palette stuff.
//
static void I_UploadNewPalette(int pal)
{
  // This is used to replace the current 256 colour cmap with a new one
  // Used by 256 colour PseudoColor modes
  static int cachedgamma;
  static size_t num_pals;

  if ((paldata == NULL) || (cachedgamma != usegamma)) {
    int lump = W_GetNumForName("PLAYPAL");
    const byte *pall = W_CacheLumpNum(lump);
    register const byte *const gtable = gammatable[cachedgamma = usegamma];
    register int i;

    num_pals = W_LumpLength(lump) / (3*256);
    num_pals *= 256;

    if (!paldata) {
      // First call - allocate and prepare colour array
      paldata = malloc(sizeof(*paldata)*num_pals);
    }

    // set the colormap entries
    for (i=0 ; (size_t)i<num_pals ; i++) {
      int r = gtable[pall[0]];
      int g = gtable[pall[1]];
      int b = gtable[pall[2]];
      pall+=3;
      paldata[i] = LCD_RGBPACK(r,g,b);
    }

    W_UnlockLumpNum(lump);
    num_pals/=256;
  }

#ifdef RANGECHECK
  if ((size_t)pal >= num_pals)
    I_Error("I_UploadNewPalette: Palette number out of range (%d>=%d)",
      pal, num_pals);
#endif
   memcpy(palette,paldata+256*pal,256*sizeof(fb_data));
}

//
// I_UpdateNoBlit
//
void I_UpdateNoBlit (void)
{
}

//
// I_FinishUpdate
//

void I_FinishUpdate (void)
{
#if defined(CPU_COLDFIRE) && !defined(SIMULATOR)
   /*
      Lookup tables are no longer needed
   */

   // Start the write
   *(volatile unsigned short *) 0xf0000000 = 0x21; // register
   *(volatile unsigned short *) 0xf0000002 = 0;    // value
   *(volatile unsigned short *) 0xf0000000 = 0x22; // GRAM

   unsigned char *screenptr=screens[0];
   int wcnt=0, hcnt=0;

   while(hcnt<LCD_HEIGHT)
   {
      while(wcnt<LCD_WIDTH)
      {
         *(volatile unsigned short *)0xf0000002 = palette[*screenptr];
         screenptr++;
         wcnt++;
      }
      wcnt=0;
      hcnt++;
   }
#else
   unsigned char paletteIndex;
   int x, y;

   for (y = 0; y < LCD_HEIGHT; y++)
   {
      for (x = 0; x < LCD_WIDTH; x++)
      {
         paletteIndex = screens[0][y*SCREENWIDTH + x];
         rb->lcd_framebuffer[y * LCD_WIDTH + x] = palette[paletteIndex];
      }
   }
   rb->lcd_update();
#endif
}

//
// I_ReadScreen
//
void I_ReadScreen (byte* scr)
{
   memcpy (scr, screens[0], SCREENWIDTH*SCREENHEIGHT);
}

//
// I_SetPalette
//
void I_SetPalette (int pal)
{
   I_UploadNewPalette(pal);
}

//
// I_InitGraphics
//
void I_InitGraphics(void)
{
   static int  firsttime=1;

   if (!firsttime)
      return;
   firsttime = 0;

   printf("Starting Graphics engine\n");

   /* Note: The other screens are initialized later */

#if defined(CPU_COLDFIRE) && !defined(SIMULATOR)
   coldfire_set_macsr(EMAC_FRACTIONAL | EMAC_SATURATE);
   screens[0] = fastscreen;
#else
   // Don't know if this will fit in other IRAMs
   screens[0] = malloc (SCREENWIDTH * SCREENHEIGHT * sizeof(unsigned char));
#endif
}
