

#include <SDL3/SDL_stdinc.h>
#include <renderer.h>
#include <luaapi.h>
#include <lua.h>
#include <lauxlib.h>
#include <util.h>
lua_State* L;

void Luaapi_executeFile(char* script_path)
{
  if (luaL_dofile(L, script_path) == LUA_OK)
  {
    logi("successfully executed file %s",script_path);
  }
  else {
    logi("error while executing %s:\n%s",script_path,lua_tostring(L,-1));
    die(1);
  }
}

int _finalize_renderer_surface(lua_State* L)
{
  Renderer_Surface* rsurf =
    (Renderer_Surface*)luaL_checkudata(L, 1, LUAAPI_TYPENAME_RENDERER_SURFACE);
  logi("released renderer surface %x",rsurf);
  SDL_free(rsurf->surf);
  return 0;
}

int _create_renderer_surface(lua_State* L)
{
  int w=luaL_checkinteger(L,1),h=luaL_checkinteger(L, 2);
  Renderer_Surface* rsurf = 
   (Renderer_Surface*)lua_newuserdata(L, sizeof(Renderer_Surface));
  rsurf->surf=SDL_CreateSurface(w,h,SDL_PIXELFORMAT_ARGB8888);
  // ?? rsurf

  if(luaL_newmetatable(L,LUAAPI_TYPENAME_RENDERER_SURFACE)) // ?? rsurf table
  {
    lua_pushstring(L, "__gc"); // ?? rsurf table "__gc"
    lua_pushcfunction(L, _finalize_renderer_surface); // ?? rsurf table "__gc" cfunc
    lua_settable(L, -3); // ?? rsurf table
  }

  lua_setmetatable(L, -2); // ?? rsurf
  logi("created renderer surface %x with size %d,%d",rsurf,w,h);
  return 1;
}

void _register_renderer_surface()
{
  lua_pushcfunction(L, _create_renderer_surface);
  lua_setfield(L, -2, "create_surface");
}

void Renderer_initLua()
{
  lua_newtable(L);

  _register_renderer_surface();

  lua_setfield(L, -2, "rend");
}

void Luaapi_initLua()
{
  lua_newtable(L);

  Renderer_initLua();

  lua_setglobal(L,"hd");
}

void Luaapi_init()
{
  L = luaL_newstate();
  Luaapi_initLua();
}
void Luaapi_quit()
{
  lua_close(L);
}