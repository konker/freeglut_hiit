/*
 * freeglut_window_jni.c
 *
 * Window management methods.
 *
 * Copyright (c) 1999-2000 Pawel W. Olszta. All Rights Reserved.
 * Written by Pawel W. Olszta, <olszta@sourceforge.net>
 * Creation date: Fri Dec 3 1999
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

#define FREEGLUT_BUILDING_LIB
#include <GL/freeglut.h>
#include "fg_internal.h"
#include "fg_gl2.h"


/* Native window support for Android. Requires ndk >= r5 */
#if TARGET_HOST_ANDROID
    #include <android/native_window.h>
    #include <android/native_window_jni.h>

extern void fgPlatformOpenWindowJni( SFG_Window* window, ANativeWindow *jniwin, const char* title,
                                  GLboolean positionUse, int x, int y,
                                  GLboolean sizeUse, int w, int h,
                                  GLboolean gameMode, GLboolean isSubWindow );

/*
 * Creates a new top-level freeglut window
 */
int FGAPIENTRY glutCreateWindowJni( const char* title, ANativeWindow *jniwin )
{
    /* XXX GLUT does not exit; it simply calls "glutInit" quietly if the
     * XXX application has not already done so.  The "freeglut" community
     * XXX decided not to go this route (freeglut-developer e-mail from
     * XXX Steve Baker, 12/16/04, 4:22 PM CST, "Re: [Freeglut-developer]
     * XXX Desired 'freeglut' behaviour when there is no current window"
     */
    /*
    FREEGLUT_EXIT_IF_NOT_INITIALISED ( "glutCreateWindowJni" );
    */
    return fgCreateWindowJni( NULL, jniwin, title, fgState.Position.Use,
                           fgState.Position.X, fgState.Position.Y,
                           fgState.Size.Use, fgState.Size.X, fgState.Size.Y,
                           GL_FALSE, GL_FALSE )->ID;
}

/*
 * Opens a window. Requires a SFG_Window object created and attached
 * to the freeglut structure. OpenGL context is created here.
 */
void fgOpenWindowJni( SFG_Window* window, ANativeWindow *jniwin, const char* title,
                   GLboolean positionUse, int x, int y,
                   GLboolean sizeUse, int w, int h,
                   GLboolean gameMode, GLboolean isSubWindow )
{
    fgPlatformOpenWindowJni( window, jniwin, title,
                          positionUse, x, y,
                          sizeUse, w, h,
                          gameMode, isSubWindow );

    fgSetWindow( window );

    window->Window.DoubleBuffered =
        ( fgState.DisplayMode & GLUT_DOUBLE ) ? 1 : 0;

#ifndef EGL_VERSION_1_0  /* No glDrawBuffer/glReadBuffer in GLES */
    if ( ! window->Window.DoubleBuffered )
    {
        glDrawBuffer ( GL_FRONT );
        glReadBuffer ( GL_FRONT );
    }
#endif
    window->Window.attribute_v_coord = -1;
    window->Window.attribute_v_normal = -1;
    window->Window.attribute_v_texture = -1;

    fgInitGL2();

    window->State.WorkMask |= GLUT_INIT_WORK;
}
#endif

