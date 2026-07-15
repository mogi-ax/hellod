/*
  Copyright (C) 2026 mogi <xerakbetter@gmail.com>

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, see <https://www.gnu.org/licenses/>.
*/

#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_keycode.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_mutex.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_video.h>
#include <lua.h>
#include <lauxlib.h>
#include <renderer.h>
#include <stdlib.h>
SDL_Window* sdlWindow = NULL;
SDL_Renderer* sdlRenderer = NULL;



void Renderer_init(struct Renderer_InitInfo iinfo)
{
  SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO);
  if (iinfo.testrun)
  {
    sdlWindow=SDL_CreateWindow(
      "hellod", iinfo.width, iinfo.height, 0);
  }
  else {
    sdlWindow = SDL_CreateWindow("hellod",
       100, 100,SDL_WINDOW_BORDERLESS);
    }
  
  int modecount=0;
  SDL_DisplayMode** modes=SDL_GetFullscreenDisplayModes(
    iinfo.display, &modecount);
  SDL_DisplayMode* mode = modes[0];
  SDL_SetWindowFullscreenMode(sdlWindow, mode);
  SDL_SetWindowFullscreen(sdlWindow, true);
  
  if (sdlWindow==NULL) {
    SDL_Log("something got wrong %s",SDL_GetError());exit(1);
  }
  sdlRenderer=SDL_CreateRenderer(sdlWindow, NULL);
  if (sdlRenderer==NULL) {
    SDL_Log("something got wrong %s",SDL_GetError());exit(1);
  }
  
  SDL_SetWindowSurfaceVSync(sdlWindow, 1);
}
void Renderer_run()
{
  bool running = true;
  
  while (running)
  {
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
      if (event.type == SDL_EVENT_QUIT)
      {
        running = false;
      }
      if (event.type == SDL_EVENT_KEY_DOWN)
      {
        if (event.key.key == SDLK_ESCAPE)
        {
          running = false;
        }
      }
    }
    SDL_RenderClear(sdlRenderer);

    
    SDL_RenderPresent(sdlRenderer);
  }
}

void Renderer_quit()
{
  SDL_DestroyRenderer(sdlRenderer);
  SDL_DestroyWindow(sdlWindow);
  SDL_Quit();
}

 // lua api ----------------------------------------------------------------------------


