/*
 * fg_window_android_jni.c
 *
 * Window management methods for Android
 *
 * Copyright (c) 1999-2000 Pawel W. Olszta. All Rights Reserved.
 * Written by Pawel W. Olszta, <olszta@sourceforge.net>
 * Copied for Platform code by Evan Felix <karcaw at gmail.com>
 * Copyright (C) 2012  Sylvain Beucler
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
#include "egl/fg_window_egl.h"
#include <android/native_app_glue/android_native_app_glue.h>


/*
 * Opens a window given a jni surface pointer. Requires a SFG_Window object created and attached
 * to the freeglut structure. OpenGL context is created here.
 */
void fgPlatformOpenWindowJni( SFG_Window* window, ANativeWindow *jniwin, const char* title,
                           GLboolean positionUse, int x, int y,
                           GLboolean sizeUse, int w, int h,
                           GLboolean gameMode, GLboolean isSubWindow )
{
  /* TODO: only one full-screen window possible? */
  if (fgDisplay.pDisplay.single_native_window != NULL) {
    fgWarning("You can't have more than one window on Android");
    return;
  }

  window->Window.Handle = jniwin;
  window->State.WorkMask |= GLUT_INIT_WORK;

  /* Create context */
  fghChooseConfig(&window->Window.pContext.egl.Config);
  window->Window.Context = fghCreateNewContextEGL(window);

  EGLDisplay display = fgDisplay.pDisplay.egl.Display;

  /* EGL_NATIVE_VISUAL_ID is an attribute of the EGLConfig that is
   * guaranteed to be accepted by ANativeWindow_setBuffersGeometry().
   * As soon as we picked a EGLConfig, we can safely reconfigure the
   * ANativeWindow buffers to match, using EGL_NATIVE_VISUAL_ID. */
  EGLint vid;
  eglGetConfigAttrib(display, window->Window.pContext.egl.Config,
		     EGL_NATIVE_VISUAL_ID, &vid);
  ANativeWindow_setBuffersGeometry(window->Window.Handle, 0, 0, vid);

  fghPlatformOpenWindowEGL(window);

  window->State.Visible = GL_TRUE;
}

