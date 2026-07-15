#include <stdarg.h>
#include <SDL3/SDL_log.h>
#include <stdlib.h>
#include <util.h>

void logi(const char *fmt, ...)
{
  va_list ap;

	va_start(ap, fmt);
  SDL_Log(fmt,ap);
	va_end(ap);
}
void die(int code)
{
  exit(code);
}