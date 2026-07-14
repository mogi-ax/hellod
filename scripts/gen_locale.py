

import sys,os.path as path
lang='en'
for i in sys.argv:
  if i.startswith('--lang='):
    lang=i[7:]
script_dir = path.split(path.split(__file__)[0])[0]
lang_dir = path.join(script_dir,"lang")
lang_filename=f"lang_{lang}.txt"
langfile=open(path.join(lang_dir,lang_filename),'r')
langheader=""
for line in langfile.readlines():
  a=line.split(' ')
  macroname=a[0]
  a.pop(0)
  macrovalue=' '.join(a).strip('\n')
  langheader+=f"#ifndef {macroname}\n"
  langheader+=f"#define {macroname} {macrovalue}\n"
  langheader+="#endif\n"
langfile.close()

headerdir=path.join(script_dir,"include")
macrofile=open(path.join(headerdir,'lang.h'),'w')
macrofile.write(langheader)
macrofile.close()