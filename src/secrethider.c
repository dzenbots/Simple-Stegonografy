
#include "../include/secrethider.h"

uint32 getbit(byte value, byte bit)
{
    return (value >> bit) & 1;
}

void set1toByte(byte *value, byte offset)
{
    *value |= (1 << offset);
}

void set0toByte(byte* value, byte offset)
{
    *value &= ~(1 << offset);
}

Status hideInfo(FILE* bmpinputFile, FILE* bmpoutputFile, byte* secretBuffer, uint32 secretSize, uint32 sizeImage)
{
    uint32 i, j;
    byte bitvalue;
    pBMPColor color = (pBMPColor)calloc(1, sizeof(BMPColor));
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 8; j++)
        {
            bitvalue = getbit((byte)(secretSize >> (i * 8)), j);
            fread(color, 1, sizeof(BMPColor), bmpinputFile);
            if (bitvalue == 1)
            {
                set1toByte(&(color->B), 0);
            }
            else 
            {
                set0toByte(&(color->B), 0);
            }
            fwrite(color, 1, sizeof(BMPColor), bmpoutputFile);
        }
    }
    for (i = 0; i < secretSize; i++)
    {
        for (j = 0; j < 8; j++)
        {
            bitvalue = getbit(secretBuffer[i], j);
            fread(color, 1, sizeof(BMPColor), bmpinputFile);
            if (bitvalue == 1)
            {
                set1toByte(&(color->B), 0);
            }
            else 
            {
                set0toByte(&(color->B), 0);
            }
            fwrite(color, 1, sizeof(BMPColor), bmpoutputFile);
        }
    }
    while (!feof(bmpinputFile))
    {
        fread(color, 1, sizeof(BMPColor), bmpinputFile);
        fwrite(color, 1, sizeof(BMPColor), bmpoutputFile);
    }
    free(color);
    return STATUS_SUCCESS;
}

Status extractInfo(FILE* bmpinputFile, FILE* outputfile)
{
    uint32 secretSize = 0;
    byte bitvalue;
    pBMPColor color = (pBMPColor)calloc(1, sizeof(BMPColor));
    uint32 i, j;
    byte secretByte;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 8; j++)
        {
            fread(color, 1, sizeof(BMPColor), bmpinputFile);
            bitvalue = getbit(color->B, 0);
            if (bitvalue == 1)
            {
                set1toByte((byte*)(&secretSize) + i, j);
            }
            else
            {
                set0toByte((byte*)(&secretSize) + i, j);
            }
        }
    }
    printf("%d\n", secretSize);
    for (i = 0; i < secretSize; i++)
    {
        secretByte = 0;
        for (j = 0; j < 8; j++)
        {
            fread(color, 1, sizeof(BMPColor), bmpinputFile);
            bitvalue = getbit(color->B, 0);
            if (bitvalue == 1)
            {
                set1toByte(&secretByte, j);
            }
            else
            {
                set0toByte(&secretByte, j);
            }
        }
        fwrite(&secretByte, 1, sizeof(byte), outputfile);
    }
    free(color);
    return STATUS_SUCCESS;
}