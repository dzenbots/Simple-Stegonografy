@echo off
gcc hide_text.c ./src/bmpHeader.c ./src/bitmapInfoHeader.c ./src/wingetopt.c ./src/stego_proccessor.c ./src/secrethider.c -o program.exe
