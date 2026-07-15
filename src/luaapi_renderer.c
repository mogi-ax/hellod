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
#include <SDL3/SDL_error.h>
#include <luaapi_renderer.h>

#include <SDL3/SDL_render.h>
#include <SDL3/SDL_stdinc.h>
#include <renderer.h>
#include <luaapi.h>
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <stdio.h>
#include <util.h>

// Renderer_Surface ------------------------------------------------------------------------------
int _index_renderer_surface(lua_State* L)
{
  const char* key = luaL_checklstring(L, -1, NULL);
  Renderer_Surface* rsurf =
    (Renderer_Surface*)luaL_checkudata(L, -2, LUAAPI_RENDERER_TYPENAME_SURFACE);
  if (strcmp("w",key) == 0) {
    lua_pushinteger(L, rsurf->w);
  }
  else if (key[0] == 'h') {
    lua_pushinteger(L, rsurf->h);
  }
  else {
    crit("wrong property name %s for render surface",key);
  }
  return 1;
}

int _finalize_renderer_surface(lua_State* L)
{
  Renderer_Surface* rsurf =
    (Renderer_Surface*)luaL_checkudata(L, -1, LUAAPI_RENDERER_TYPENAME_SURFACE);
  //logi("released renderer surface %p",rsurf);
  Renderer_freeSurface(rsurf);
  return 0;
}

int _create_renderer_surface(lua_State* L)
{
  int w=luaL_checkinteger(L,-1),h=luaL_checkinteger(L, -2);
  
  Renderer_Surface* rsurf = 
   (Renderer_Surface*)lua_newuserdatauv(
    L, sizeof(Renderer_Surface),0);
  if (!Renderer_createSurface(rsurf, w, h))
  {
    crit("internal error: %s",SDL_GetError());
  }
  // ?? rsurf

  if(luaL_newmetatable(L,LUAAPI_RENDERER_TYPENAME_SURFACE)) // ?? rsurf table
  {
    lua_pushstring(L, "__gc"); // ?? rsurf table "__gc"
    lua_pushcfunction(L, _finalize_renderer_surface); // ?? rsurf table "__gc" cfunc
    lua_settable(L, -3); // ?? rsurf table
    lua_pushstring(L, "__index"); // ?? rsurf table "__gc"
    lua_pushcfunction(L, _index_renderer_surface); // ?? rsurf table "__gc" cfunc
    lua_settable(L, -3); // ?? rsurf table
  }
  lua_setmetatable(L, -2); // ?? rsurf
  
  return 1;
}
int _load_renderer_surface(lua_State* L)
{
  const char* path = luaL_checklstring(L, -1, NULL);
  Renderer_Surface* rsurf = 
   (Renderer_Surface*)lua_newuserdatauv(
    L, sizeof(Renderer_Surface),0);
  if (!Renderer_loadImageAsSurface(rsurf,path))
  {
    crit("internal error: %s",SDL_GetError());
  }
  // ?? rsurf

  if(luaL_newmetatable(L,LUAAPI_RENDERER_TYPENAME_SURFACE)) // ?? rsurf table
  {
    lua_pushstring(L, "__gc"); // ?? rsurf table "__gc"
    lua_pushcfunction(L, _finalize_renderer_surface); // ?? rsurf table "__gc" cfunc
    lua_settable(L, -3); // ?? rsurf table
    lua_pushstring(L, "__index"); // ?? rsurf table "__gc"
    lua_pushcfunction(L, _index_renderer_surface); // ?? rsurf table "__gc" cfunc
    lua_settable(L, -3); // ?? rsurf table
  }
  lua_setmetatable(L, -2); // ?? rsurf
  
  return 1;
  
}

void _register_renderer_surface()
{
  lua_pushcfunction(L, _create_renderer_surface);
  lua_setfield(L, -2, LUAAPI_RENDERER_FUNCNAME_CREATE_SURFACE);
  lua_pushcfunction(L, _load_renderer_surface);
  lua_setfield(L, -2, LUAAPI_RENDERER_FUNCNAME_LOAD_SURFACE);
}
// Renderer_Texture ------------------------------------------------------------------------------
int _index_renderer_texture(lua_State* L)
{
  const char* key = luaL_checklstring(L, -1, NULL);
  Renderer_Texture* rsurf =
    (Renderer_Texture*)luaL_checkudata(L, -2, LUAAPI_RENDERER_TYPENAME_TEXTURE);
  if (key[0] == 'w') {
    lua_pushinteger(L, rsurf->w);
  }
  else if (key[0] == 'h') {
    lua_pushinteger(L, rsurf->h);
  }
  else {
    crit("wrong property name %s for render texture",key);
  }
  return 1;
}

int _finalize_renderer_texture(lua_State* L)
{
  Renderer_Texture* rsurf =
    (Renderer_Texture*)luaL_checkudata(L, -1, LUAAPI_RENDERER_TYPENAME_TEXTURE);
  //logi("released renderer texture %p",rsurf->tex);
  Renderer_freeTexture(rsurf);
  return 0;
}

int _create_renderer_texture(lua_State* L)
{
  int w=luaL_checkinteger(L,-1),h=luaL_checkinteger(L, -2);
  Renderer_Texture* rsurf = 
   (Renderer_Texture*)lua_newuserdatauv(
    L, sizeof(Renderer_Texture),0);
  if (!Renderer_createTexture(rsurf, w, h))
  {
    crit("internal error: %s",SDL_GetError());
  }
  // ?? rsurf

  if(luaL_newmetatable(L,LUAAPI_RENDERER_TYPENAME_TEXTURE)) // ?? rsurf table
  {
    lua_pushstring(L, "__gc"); // ?? rsurf table "__gc"
    lua_pushcfunction(L, _finalize_renderer_texture); // ?? rsurf table "__gc" cfunc
    lua_settable(L, -3); // ?? rsurf table
    lua_pushstring(L, "__index"); // ?? rsurf table "__gc"
    lua_pushcfunction(L, _index_renderer_texture); // ?? rsurf table "__gc" cfunc
    lua_settable(L, -3); // ?? rsurf table
  }
  lua_setmetatable(L, -2); // ?? rsurf

  return 1;
}
int _load_renderer_texture(lua_State* L)
{
  const char* path = luaL_checklstring(L, -1, NULL);
  Renderer_Texture* rsurf = 
   (Renderer_Texture*)lua_newuserdatauv(
    L, sizeof(Renderer_Texture),0);
  if (!Renderer_loadImageAsTexture(rsurf,path))
  {
    crit("internal error: %s",SDL_GetError());
  }
  // ?? rsurf

  if(luaL_newmetatable(L,LUAAPI_RENDERER_TYPENAME_TEXTURE)) // ?? rsurf table
  {
    lua_pushstring(L, "__gc"); // ?? rsurf table "__gc"
    lua_pushcfunction(L, _finalize_renderer_texture); // ?? rsurf table "__gc" cfunc
    lua_settable(L, -3); // ?? rsurf table
    lua_pushstring(L, "__index"); // ?? rsurf table "__gc"
    lua_pushcfunction(L, _index_renderer_texture); // ?? rsurf table "__gc" cfunc
    lua_settable(L, -3); // ?? rsurf table
  }
  lua_setmetatable(L, -2); // ?? rsurf
  
  return 1;
  
}
void _register_renderer_texture()
{
  lua_pushcfunction(L, _create_renderer_texture);
  lua_setfield(L, -2, LUAAPI_RENDERER_FUNCNAME_CREATE_TEXTURE);
  lua_pushcfunction(L, _load_renderer_texture);
  lua_setfield(L, -2, LUAAPI_RENDERER_FUNCNAME_LOAD_TEXTURE);
}



void Renderer_initLua()
{
  lua_newtable(L);

  _register_renderer_surface();
  _register_renderer_texture();

  lua_setfield(L, -2, "rend");
}