/***********************************************************************
 
 Copyright (c) 2008, 2009, 2010, Memo Akten, www.memo.tv
 *** The Mega Super Awesome Visuals Company ***
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of MSA Visuals nor the names of its contributors
 *       may be used to endorse or promote products derived from this software
 *       without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * ***********************************************************************/

/***************
 DEPENDENCIES:
 - NONE
 ***************/ 


------------------------------------------------------------------------
ofxCocoa
------------------------------------------------------------------------

A GLUT replacement add-on for openFrameworks 006+ to use native Cocoa OpenGL and windowing instead of GLUT. Can provide upto 200% better performance in certain situations (multiscreen + fullscreen)
Supports Fbos, shaders, FSAA, setting window stylemasks/decorations/transparency, programmatic windows, Interface Builder integration, fullscreen on single or more screens, NSTimer or CVDisplayLink callback.

Thanks to Anton (aka Vade http://vade.info/) for countless hours of Mac+OpenGL debates and of course the entire openFrameworks team (www.openframeworks.cc)




PROGRAMMATIC CREATION VS INTERFACE BUILDER
------------------------------------------------------------------------
See README.txt in 'nibs' folder for info on Programmatic creation of windows & views or via Interface builder 



INIT OPTIONS
------------------------------------------------------------------------
In main.mm, initalize the initSettings struct before the window and opengl view are created to set parameters like transparency, borders & window decorations, fullscreen antialiasing etc.



CVDISPLAYLINK VS NSTIMER
------------------------------------------------------------------------
MSA::ofxCocoa::setSyncToDisplayLink(bool b) to setup the loop timer using NSTimer (default) or the new CVDisplayLink which creates a separate thread callback just before the screen is about to refresh



FULLSCREEN
------------------------------------------------------------------------
Can go fullscreen to any screen using the [NSView enterFullScreen] method, or stretch window to cover any number of views. e.g.
using namespace MSA::ofxCocoa;
- goFullscreen(currentScreen());	// go fullscreen on whichever monitor the window is currently on using [NSView enterFullScreen]
- goFullscreen(screen(2));			// go fullscreen on screen #2 using [NSView enterFullScreen]
- goFullscreen(mainScreen());		// go fullscreen on primary screen using [NSView enterFullScreen]
- setWindowRect(rectForCurrentScreen()); // stretch window to cover currentScreen
- setWindowRect(rectForScreen(2));		// stretch window to cover screen #2
- setWindowRect(rectForAllScreens());	// stretch window to cover all screens


