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
#include <stdarg.h>
#include <SDL3/SDL_log.h>
#include <stdlib.h>
#include <util.h>

void logi(const char *fmt, ...)
{
  va_list ap;

	va_start(ap, fmt);
  SDL_LogMessageV(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO,fmt,ap);
	va_end(ap);
}
void die(int code)
{
  exit(code);
}
void crit(const char *fmt,...)
{
  va_list ap;

	va_start(ap, fmt);
  SDL_LogMessageV(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR,fmt,ap);
	va_end(ap);
  exit(1);
}