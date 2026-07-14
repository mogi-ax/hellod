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
#include <SDL3/SDL_video.h>
struct Renderer_InitInfo
{
  bool testrun;
  int width;
  int height;
  SDL_DisplayID display;
};

void Renderer_init(struct Renderer_InitInfo iinfo);