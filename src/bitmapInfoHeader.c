
#include "../include/bitmapInfoHeader.h"

Status getBitmapInfoHeader(char* filename, pBitmapInfoHeader bih)
{
    if (filename == NULL || bih == NULL)
    {
        ERR(STATUS_INVALID_PARAMETERS);
    }
    FILE* file = fopen(filename, "rb");
    fseek(file, 14, SEEK_SET);
    fread(bih, 1, sizeof(BitmapInfoHeader), file);
    fclose(file);
    return STATUS_SUCCESS;
}

Status checkBitmapInfoHeader(pBitmapInfoHeader bih)
{
    if (bih->biBitCount != BIT_COUNT)
    {
        ERR(STATUS_UNSUPPORTED_FILE);
    }
    return STATUS_SUCCESS;
}