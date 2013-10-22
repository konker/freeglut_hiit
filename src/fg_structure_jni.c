/*
 * freeglut_structure_jni.c
 *
 * Windows and menus need tree structure
 *
 * Copyright (c) 1999-2000 Pawel W. Olszta. All Rights Reserved.
 * Written by Pawel W. Olszta, <olszta@sourceforge.net>
 * Creation date: Sat Dec 18 1999
 *
 * Modified by: Konrad Markus <konker@luxvelocitas.com>
 * Modified date: Tue Oct 22 2013
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * PAWEL W. OLSZTA BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <GL/freeglut.h>
#include "fg_internal.h"

/* -- PRIVATE FUNCTIONS ---------------------------------------------------- */

extern void fgPlatformCreateWindow ( SFG_Window *window );
extern void fghDefaultReshape(int width, int height);

static void fghClearCallBacks( SFG_Window *window )
{
    if( window )
    {
        int i;
        for( i = 0; i < TOTAL_CALLBACKS; ++i )
            window->CallBacks[ i ] = NULL;
    }
}

#if TARGET_HOST_ANDROID
    #include <android/native_window.h>
    #include <android/native_window_jni.h>

/*
 * This private function creates, opens and adds to the hierarchy
 * a freeglut window complete with OpenGL context and stuff...
 *
 * If parent is set to NULL, the window created will be a topmost one.
 */

SFG_Window* fgCreateWindowJni( SFG_Window* parent, ANativeWindow *jniwin, const char* title,
                            GLboolean positionUse, int x, int y,
                            GLboolean sizeUse, int w, int h,
                            GLboolean gameMode, GLboolean isMenu )
{
    /* Have the window object created */
    SFG_Window *window = (SFG_Window *)calloc( 1, sizeof(SFG_Window) );

    fgPlatformCreateWindow ( window );

    fghClearCallBacks( window );
    SET_WCB( *window, Reshape, fghDefaultReshape);

    /* Initialize the object properties */
    window->ID = ++fgStructure.WindowID;

    fgListInit( &window->Children );
    if( parent )
    {
        fgListAppend( &parent->Children, &window->Node );
        window->Parent = parent;
    }
    else
        fgListAppend( &fgStructure.Windows, &window->Node );

    /* Set the default mouse cursor */
    window->State.Cursor    = GLUT_CURSOR_INHERIT;

    /* Mark window as menu if a menu is to be created */
    window->IsMenu          = isMenu;

    /*
     * Open the window now. The fgOpenWindowJni() function is system
     * dependant, and resides in freeglut_window.c. Uses fgState.
     */
    fgOpenWindowJni( window, jniwin, title, positionUse, x, y, sizeUse, w, h, gameMode,
                  (GLboolean)(parent ? GL_TRUE : GL_FALSE) );

    return window;
}
#endif

