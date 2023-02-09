@echo off

set cli=
set cli=%cli% -Werror -Werror=unknown-pragmas -Werror=vla
set cli=%cli% -Wall -Wextra -Wpedantic -Weverything
set cli=%cli% -Wno-c++98-compat -Wno-declaration-after-statement -Wno-used-but-marked-unused -Wno-missing-field-initializers
set cli=%cli% -Wno-unused-macros -Wno-nonportable-system-include-path -Wno-gnu-zero-variadic-macro-arguments

set cli=%cli% -fsanitize=undefined -fsanitize-trap=undefined -fno-sanitize-recover=undefined
set cli=%cli% -fsanitize=integer -fsanitize-trap=integer -fno-sanitize-recover=integer
set cli=%cli% -fsanitize=bounds -fsanitize-trap=bounds -fno-sanitize-recover=bounds
set cli=%cli% -fsanitize=float-divide-by-zero -fsanitize-trap=float-divide-by-zero -fno-sanitize-recover=float-divide-by-zero
set cli=%cli% -fsanitize=float-cast-overflow -fsanitize-trap=float-cast-overflow -fno-sanitize-recover=float-cast-overflow

clang %cli% *.cpp plugins/*.cpp -o main.exe
