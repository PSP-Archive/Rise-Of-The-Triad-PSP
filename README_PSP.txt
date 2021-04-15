Rise Of The Triad PSP v1.01
---------------------------
This is a PSP adoptation of Rise Of The Triad, 1st person shooter, originally developed by 3drealms/Apogee.
(http://www.3drealms.com/rott/)
Special thanks to people @ http://icculus.org/rott/, who developed the SDL/linux version of the game.
Please read the attached documents for credits and other information.

If you are unfamiliar with the game please read this great article:
http://rott.classicgaming.gamespy.com/hell/


WHAT'S NEW for 1.01
-------------------
- Updated for *current* SDK/Toolchain.
- Uses new SDL with TV support. Just hold the TRIANGLE button when you start the game from the XMB.
- New SDL also fixes the pitch problem with the sound effects.
- Uses SDL_mixer for playing the music again.
- Bundled with mini-instruments for much better music while still keeping the size reasonable.
- Changed a couple of the default key mappings for changing weapons and setting the gamma.


WHAT'S NEW for 1.00
-------------------
- Slim psp support.
- fixed a memory leak bug, crashing the game after 5-10 minutes of playing.
- fixed intro screens / cut scenes
- some performance optimizations to rendering and timidity routines.
- added a PSP screen-size selector.On "Screen Size" selector menu, pressing [Right Arrow] 
  while at max screen size value, toggles between "Original" (320x240), "4x3" and
 "Full Screen" modes.
- added Brightness control.On "Screen Size" selector menu, pressing [Left Arrow] while
  at min screen size value, toggles between different brightness settings.
- new psp game icon.


INSTALLATION
------------
This game requires "homebrew-friendly" custom psp firmware to run.

- Select between the shareware and full versions (shareware game files are included)
- Copy ROTT_Shareware or ROTT_Darkwar to ms:/PSP/GAME or ms:/PSP/GAMEXXX 
  (XXX is your custom firmware version number)
- To run the full version you need to copy the game files from the original game CD (Rise of the Triad: Dark War) in to   
  ROTT_Darkwar folder on your PSP.


TV SUPPORT
----------
When you launch the game from the PSP's XMB, press and hold the TRIANGLE button. This calls
up the SDL preferences. If you have a Phat PSP or don't have the TV cable on the Slim PSP,
you will only be asked if you wish to view the game as widescreen. Yes sets the display to
be 480x272, the full size of the LCD display. No sets the display to 364x272, or a 4:3
aspect ratio very similar to what the game originally used.

If you have a Slim PSP with a TV cable, you will be asked if you wish to use the TV. If you
choose no, you will then be asked if you wish to view the game on the LCD as widescreen, like
above. If you choose yes, you will be asked if you wish to output the video as interlaced (on
the component cable only - the composite cable is ALWAYS interlaced). You will be asked if the
TV the cable is hooked to is 16:9 (HDTV). Then you will be asked if you wish to view the game
as widescreen. Just try a few different settings to find what you like the best on your TV.

The preferences are saved so that the next time the game is run, it will use those settings
(unless you hold TRIANGLE again).


MUSIC SUPPORT
-------------
In order to save space and reduce loading times, this release is bundled with minimized midi 
instrument library.

Better instrument samples can be downloaded from http://www.libsdl.org/projects/mixer/timidity/timidity.tar.gz 
timidity.cfg & instruments directory from the archive must be copied to the ROTT_xxxxx game folder.

The bundled instruments are from: http://www.i.h.kyoto-u.ac.jp/~shom/timidity/


CONTROLS
--------
Due to ovious PSP limitations, some game functions are not mapped in the default key configuration.
If you don't like the control layout/functions - you can re-assign them in the controls menu.
-Use [TRIANGLE] to get out of text entry mode

D-Pad Up      = forward
D-Pad Down    = backward
D-Pad Left    = turn left
D-Pad Right   = turn right
Left Trigger  = strafe left
Right Trigger = strafe right
Cross         = fire weapon
Circle        = action
Triangle      =
Square        =
Analog Up     = look/fly up
Analog Down   = look/fly down
Analog Left   = toggle weapons
Analog Right  = change gamma setting (brightness)
Start         = run
Select        = menu/escape


GAME PLAY
---------
Refer to original documentation for details on game play.

Network/multiplayer modes are not supported in this release, but you should be able to use some 
multiplayer levels in "exploration" mode.

