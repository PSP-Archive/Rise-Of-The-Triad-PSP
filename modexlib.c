/*
Copyright (C) 1994-1995 Apogee Software, Ltd.



This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/
#include <pspkernel.h>
#include <pspdebug.h>
#include <pspctrl.h>
#include <pspdisplay.h>
#include <psppower.h>
#include <pspgu.h>

#include <stdarg.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "SDL.h"

#ifdef DOS
#include <malloc.h>
#include <dos.h>
#include <conio.h>
#include <io.h>
#endif

#include <stdlib.h>
#include <sys/stat.h>
#include "modexlib.h"
//MED
#include "memcheck.h"
#include "rt_util.h"


// GLOBAL VARIABLES

static SDL_Surface *sdl_surface = NULL;

#if 0
int    screen=0;
int    brightness=0;
#endif

int    linewidth;
int    ylookup[MAXSCREENHEIGHT];
int    page1start;
int    page2start;
int    page3start;
int    screensize;
unsigned bufferofs;
unsigned displayofs;
boolean graphicsmode=false;

const static SDL_Rect destRect = { .x = 0, .y = 0, .w = 320, .h = 200 };

static byte scrnbuffer[MAXSCREENWIDTH * MAXSCREENHEIGHT * 3] __attribute__((aligned(16)));


void copyScreenBytes(byte *s) {
    int i,j;
    int x=0;
	int count=0;
	int *sp = (int *)s;
	int *dp = (int *)sdl_surface->pixels;

    for (i=0; i<200; i++) {
      	for (j=0; j<320/4; j++) {
			dp[x+j]= sp[count++];
		}
        x+=sdl_surface->pitch/4;
    }
	SDL_Flip(sdl_surface);
}

void clearScreen(long color) {
    memset((byte *)displayofs, color, MAXSCREENWIDTH * MAXSCREENHEIGHT);
	copyScreenBytes((byte *)displayofs);
}

#if 0
void setScreen(int screen_size) {
	clearScreen(0);
	screen=screen_size;
}

void setBrightness(int b) {
	brightness=b;
}
#endif

/*
====================
=
= GraphicsMode
=
====================
*/

void GraphicsMode ( void )
{
    Uint32 flags = SDL_SWSURFACE | SDL_HWPALETTE | SDL_FULLSCREEN;

	//printf("Init SDL\n");
	//wait();

	if (SDL_InitSubSystem (SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
	    Error ("Could not initialize SDL\n");
	}

    #if defined(PLATFORM_WIN32) || defined(PLATFORM_MACOSX)
        // FIXME: remove this.  --ryan.
        flags = SDL_FULLSCREEN;
        SDL_WM_GrabInput(SDL_GRAB_ON);
    #endif

    SDL_WM_SetCaption ("Rise of the Triad", "ROTT");
    SDL_ShowCursor (0);
    sdl_surface = SDL_SetVideoMode (320, 200, 8, flags);

	if (sdl_surface == NULL)
		Error ("Could not set video mode\n");
}

/*
====================
=
= SetTextMode
=
====================
*/
void SetTextMode ( void )
{
	if (SDL_WasInit(SDL_INIT_VIDEO) == SDL_INIT_VIDEO) {
		if (sdl_surface != NULL) {
			SDL_FreeSurface(sdl_surface);
			sdl_surface = NULL;
		}
		SDL_QuitSubSystem (SDL_INIT_VIDEO);
	}
}

/*
====================
=
= TurnOffTextCursor
=
====================
*/
void TurnOffTextCursor ( void )
{
}

/*
====================
=
= WaitVBL
=
====================
*/
void WaitVBL( void )
{
    sceDisplayWaitVblankStart();
	//SDL_Delay (16667/1000);
}

/*
=======================
=
= VL_SetVGAPlaneMode
=
=======================
*/

void VL_SetVGAPlaneMode ( void )
{
   int i,offset;

   GraphicsMode();

//
// set up lookup tables
//
   linewidth = MAXSCREENWIDTH;

   offset = 0;

   for (i=0;i<MAXSCANLINES;i++)
   {
      ylookup[i]=offset;
      offset += linewidth;
   }

   screensize = MAXSCREENHEIGHT*MAXSCREENWIDTH;

   memset(scrnbuffer, 0, sizeof(scrnbuffer));
   page1start=(int)&scrnbuffer[0];
   page2start=(int)&scrnbuffer[MAXSCREENWIDTH * MAXSCREENHEIGHT];
   page3start=(int)&scrnbuffer[MAXSCREENWIDTH * MAXSCREENHEIGHT * 2];
   displayofs = page1start;
   bufferofs = page2start;

   XFlipPage ();
}

/*
=======================
=
= VL_CopyPlanarPage
=
=======================
*/
void VL_CopyPlanarPage ( byte * src, byte * dest )
{
      memcpy(dest,src,screensize);
}

/*
=======================
=
= VL_CopyPlanarPageToMemory
=
=======================
*/
void VL_CopyPlanarPageToMemory ( byte * src, byte * dest )
{
      memcpy(dest,src,screensize);
}

/*
=======================
=
= VL_CopyBufferToAll
=
=======================
*/
void VL_CopyBufferToAll ( unsigned buffer )
{
   if (page1start != buffer)
      memcpy((byte *)page1start,(byte *)buffer,screensize);
   if (page2start != buffer)
      memcpy((byte *)page2start,(byte *)buffer,screensize);
   if (page3start != buffer)
      memcpy((byte *)page3start,(byte *)buffer,screensize);
}

/*
=======================
=
= VL_CopyDisplayToHidden
=
=======================
*/
void VL_CopyDisplayToHidden ( void )
{
   VL_CopyBufferToAll ( displayofs );
}

/*
=================
=
= VL_ClearBuffer
=
= Fill the entire video buffer with a given color
=
=================
*/

void VL_ClearBuffer (unsigned buf, byte color)
{
   memset((byte *)buf,color,screensize);
   if (buf == displayofs)
      copyScreenBytes((byte *)displayofs);
}

/*
=================
=
= VL_ClearVideo
=
= Fill the entire video buffer with a given color
=
=================
*/

void VL_ClearVideo (byte color)
{
  memset (sdl_surface->pixels, color, sdl_surface->pitch * sdl_surface->h);
  SDL_Flip(sdl_surface);
}

/*
=================
=
= VL_DePlaneVGA
=
=================
*/

void VL_DePlaneVGA (void)
{
}


/* C version of rt_vh_a.asm */

void VH_UpdateScreen (void)
{
   //copyScreenBytes((byte *)displayofs);
   XFlipPage();
}

/*
=================
=
= XFlipPage
=
=================
*/

void XFlipPage ( void )
{
   int temp = displayofs;
   displayofs = bufferofs;
   bufferofs = temp;
   copyScreenBytes((byte *)displayofs);
}

void XFlipPage1 ( void ) {
   XFlipPage();
}
