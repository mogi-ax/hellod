SCRIPT_PATH="$(readlink -f $(dirname $0))"

if test -z "$CC"; then
  CC=gcc
fi
if test -z "$PYTHON"; then
  PYTHON=python
fi
if test -z "$PROGRAM_LANG"; then
  PROGRAM_LANG=en
fi
if test -z "$IGNORE_MISSING"; then
  IGNORE_MISSING=0
fi
pkg-config sdl3
if test $? -ne 0; then
  if test "$IGNORE_MISSING" -ne 1; then
    echo "cannot find sdl3 in pkg-config. install with your package manager or something else"
    exit 1
  fi
fi
pkg-config pam
if test $? -ne 0; then
  if test "$IGNORE_MISSING" -ne 1; then
    echo "cannot find pam in pkg-config. install with your package manager or something else"
    exit 1
  fi
fi
pkg-config lua
if test $? -ne 0; then
  if test "$IGNORE_MISSING" -ne 1; then
    echo "cannot find lua in pkg-config. install with your package manager or something else"
    exit 1
  fi
fi
CFLAGS="--std=gnu23 $(pkg-config sdl3 --cflags) $(pkg-config pam --cflags) $(pkg-config lua --cflags) -lc $C_FLAGS"
LDFLAGS="$(pkg-config sdl3 --libs) $(pkg-config pam --libs) $(pkg-config lua --libs)  $LD_FLAGS"

SRC_LIST=$(find "$SCRIPT_PATH/src" -maxdepth 1 -type f -not -path '*/\.*')

INCLUDE_FOLDER="$SCRIPT_PATH/include"

$PYTHON "$SCRIPT_PATH/scripts/gen_locale.py" --lang="$PROGRAM_LANG"

BUILD_FOLDER="$SCRIPT_PATH/build"
mkdir $BUILD_FOLDER 2> /dev/null

FLAGS="-I$INCLUDE_FOLDER $CFLAGS $LDFLAGS -o $BUILD_FOLDER/hellod"
echo "$FLAGS" | sed "s/ /\n/g" > $SCRIPT_PATH/compile_flags.txt
$CC $FLAGS $SRC_LIST

