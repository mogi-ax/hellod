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

#define LUAAPI_MASTER_NAMESPACE_NAME "hd"
#define LUAAPI_CATEGORY_RENDERER "rend"
#define LUAAPI_RENDERER_TYPENAME_SURFACE "renderer_surface"
#define LUAAPI_RENDERER_TYPENAME_TEXTURE "renderer_texture"
#define LUAAPI_RENDERER_FUNCNAME_CREATE_SURFACE "create_surface"
#define LUAAPI_RENDERER_FUNCNAME_CREATE_TEXTURE "create_texture"
#define LUAAPI_RENDERER_FUNCNAME_LOAD_SURFACE "load_surface"
#define LUAAPI_RENDERER_FUNCNAME_LOAD_TEXTURE "load_texture"


#include <lua.h>
extern lua_State* L;

void Luaapi_executeFile(char* script_path);
void Luaapi_initLua();
void Luaapi_init();
void Luaapi_quit();
