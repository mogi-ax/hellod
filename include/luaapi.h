#pragma once
#define LUAAPI_TYPENAME_RENDERER_SURFACE "_renderer_surface"

void Luaapi_executeFile(char* script_path);
void Renderer_initLua();
void Luaapi_initLua();
void Luaapi_init();
void Luaapi_quit();
