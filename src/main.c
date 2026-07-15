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


#include "luaapi.h"
#include <SDL3/SDL_init.h>
#include <stdlib.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_video.h>
#include <string.h>
#include <main.h>
#include <renderer.h>



bool flag_testrun = false;
char* flag_config_path = DEFAULT_CONFIG_LOCATION;
int flag_testrun_width = -1;
int flag_testrun_height = -1;

void check_flags(int argc,char** argv);
void set_envvar();
bool is_kmsdrm_supported();
bool contains_on_front(const char* check,const char* target);

int main(int argc,char** argv)
{
  check_flags(argc,argv);
  if (!flag_testrun)
  {
    set_envvar();
  }
  if (!flag_testrun && !is_kmsdrm_supported())
  {
    SDL_Log(ERRMSG_KMSDRM_NOT_SUPPORTED);
  }
  if (flag_testrun)
  {
    SDL_Log("test run");
  }
  else {
    SDL_Log("not test run");
  }
  SDL_Log("config path: %s",flag_config_path);
  SDL_Init(SDL_INIT_VIDEO);
  struct Renderer_InitInfo iinfo;
  iinfo.width=flag_testrun_width;
  iinfo.height=flag_testrun_height;
  iinfo.testrun=flag_testrun;
  iinfo.display=SDL_GetPrimaryDisplay();
  Renderer_init(iinfo);
  Luaapi_init();
  Luaapi_executeFile(flag_config_path);
  Renderer_run();
  Luaapi_quit();
  Renderer_quit();
  return 0;
}

void check_flags(int argc,char** argv)
{
  char* err_target;
  static const char* testrun_checker="testrun";
  static const char* config_path_checker="config-path";
  static const char* width_checker="testrun-width";
  static const char* height_checker="testrun-height";
  static const char* help_checker="help";
  
  for (int i = 1;i < argc;i++)
  {
    int is_kv = 0;
    int k_len = 0;
    char* curr_arg = argv[i];
    err_target=curr_arg;
    int hcnt = 0;
    for (int j = 0;curr_arg[j] && j < 2;j++)
    {
      if (curr_arg[j] == '-')
      {
        hcnt++;
      }
    }
    if (hcnt != 2)
    {
      err_target=curr_arg;
      goto unknown_argument;
    }
    
    for (int j = 2;curr_arg[j];j++)
    {
      k_len++;
      if (curr_arg[j] == '=') {
        k_len--;
        is_kv = j;
        break;
      }
    }
    //SDL_Log("%d %zu",k_len,strlen(test_config_checker));
    if(contains_on_front(help_checker,curr_arg+2))
    {
      if(k_len==strlen(help_checker) && is_kv == 0)
      {
        SDL_Log(ERRMSG_HELP);
        exit(0);
        continue;
      }
      else {
        goto incorrect_usage;
      }
    }
    else if(contains_on_front(testrun_checker,curr_arg+2))
    {
      if(k_len==strlen(testrun_checker) && is_kv == 0)
      {
        flag_testrun = true;
        continue;
      }
      else {
        goto incorrect_usage;
      }
    }
    else if(contains_on_front(config_path_checker,curr_arg+2))
    {
      if(k_len==strlen(config_path_checker) && is_kv != 0)
      {
        flag_config_path = curr_arg+is_kv+1;
        continue;
      }
      else {
        if(k_len!=strlen(config_path_checker))
          goto unknown_argument;
        goto incorrect_usage;
      }
    }
    else if(contains_on_front(width_checker,curr_arg+2))
    {
      if(k_len==strlen(width_checker) && is_kv != 0)
      {
        
        flag_testrun_width=atoi(curr_arg+is_kv+1);
        continue;
      }
      else {
        if(k_len!=strlen(width_checker))
          goto unknown_argument;
        goto incorrect_usage;
      }
    }
    else if(contains_on_front(height_checker,curr_arg+2))
    {
      if(k_len==strlen(height_checker) && is_kv != 0)
      {
        
        flag_testrun_height=atoi(curr_arg+is_kv+1);
        continue;
      }
      else {
        if(k_len!=strlen(height_checker))
          goto unknown_argument;
        goto incorrect_usage;
      }
    }
    else {
      goto unknown_argument;
    }
    
  }
  return;
  unknown_argument:
  SDL_Log(ERRMSG_UNKNOWN_ARGUMENT,err_target);
  exit(1);
  incorrect_usage:
  SDL_Log(ERRMSG_INCORRECT_USAGE,err_target);
  exit(1);
}

bool is_kmsdrm_supported()
{
  bool kmsfound = false;
  for (int i = 0;i < 100;i++)
  {
    bool search = true;
    static const char* kms_string = "kmsdrm";
    const char* str = SDL_GetVideoDriver(i);
    if (str == NULL)
    {
      break;
    }
    for(int j = 0;str[j];j++)
    {
      if (str[j] != kms_string[j])
      {
        search = false;
      }
    }
    if (search)
    {
      kmsfound = true;
      break;
    }
  }
  return kmsfound;
}
void set_envvar()
{
  setenv("SDL_VIDEO_DRIVER", "kmsdrm", 1);
  setenv("SDL_AUDIO_DRIVER", "alsa", 1);
}

bool contains_on_front(const char* check,const char* target)
{
  for (int i = 0; check[i]&&target[i];i++) {
    if (check[i] != target[i])
    {
      return false;
    }
  }
  return true;
}