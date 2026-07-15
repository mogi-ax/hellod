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




#pragma once
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>

#define RENDERER_MAXIMUM_OBJECT 2048

typedef struct Renderer_InitInfo
{
  bool testrun;
  int width;
  int height;
  SDL_DisplayID display;
} Renderer_InitInfo;
typedef struct Renderer_Texture {
  SDL_Texture* tex;
} Renderer_Texture;

typedef struct Renderer_Surface {
  SDL_Surface* surf;
} Renderer_Surface;

enum Renderer_Kind {
  RENDERER_OBJECT_KIND_TEXTUREDISPLAY,
  RENDERER_OBJECT_KIND_SURFACEDISPLAY,
  RENDERER_OBJECT_KIND_BUTTON,
  RENDERER_OBJECT_KIND_INPUTFIELD,
};
typedef struct Renderer_Object {
  int offset_x,offset_y;
  float rel_x,rel_y;
  enum Renderer_Kind kind;
  union {
    struct Renderer_Texture* tex;
    struct Renderer_Surface* surf;
  };
  struct Renderer_Object* parent;
} Renderer_Object;



void Renderer_init(struct Renderer_InitInfo iinfo);
void Renderer_run();
void Renderer_quit();