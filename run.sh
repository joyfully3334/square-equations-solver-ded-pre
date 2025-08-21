#!/bin/bash

# Format: run.sh file1 file2 ... fileN -a arg1 arg2 ... argN

file=""
flags="-D _DEBUG -ggdb3 -std=c++17 -O0 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation -fstack-protector -fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer -Wlarger-than=8192 -Wstack-usage=8192 -pie -fPIE -Werror=vla -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,leak,nonnull-attribute,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr"
RED='\033[0;31m'
GREEN='\033[0;32m'
GRAY='\033[0;37m'
NC='\033[0m'

echo -e "${GRAY}--COMPILE--   $(date +%T:%N | head -c 11)${NC}"

echo $(echo "$*" | awk -F'-a ' '{print $1}') "${flags}" | xargs g++ -o ./.tmp.out

if [[ $? != 0 ]]; then
  echo -e "${RED}--COMPERR--   $(date +%T:%N | head -c 11)${NC}"
  exit 1;
fi

echo -e "${GREEN}--STARTED--   $(date +%T:%N | head -c 11)${NC}"

if [[ "$*" =~ .*-a.+ ]]; then
  trap 'rm ./.tmp.out >/dev/null 2>&1; echo -e "\n${RED}--SIGKILL--   $(date +%T:%N | head -c 11)${NC}"; exit 1' SIGKILL SIGTERM SIGINT
  echo "$*" | rev | awk -F' a-' '{print $1}' | rev | xargs ./.tmp.out
else
  trap 'rm ./.tmp.out >/dev/null 2>&1; echo -e "\n${RED}--SIGKILL--   $(date +%T:%N | head -c 11)${NC}"; exit 1' SIGKILL SIGTERM SIGINT
  ./.tmp.out
fi

echo -e "\n${RED}--STOPPED--   $(date +%T:%N | head -c 11)${NC}"

rm ./.tmp.out >/dev/null 2>&1
