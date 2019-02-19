
#include "../include/bmpHeader.h"

//check if header of file is BMP file header
Status checkBMPFileHeader(pBMPHeader BmpHeader)
{
    if (BmpHeader->bfType != BMP_HEADER_MAGIC && BmpHeader->bfReserved != BMP_HEADER_NULL)
    {
        ERR(STATUS_NOT_BMP_HEADER);
    }
    return STATUS_SUCCESS;
}

//getting BMP file header
Status getBMPHeader(char* filename, pBMPHeader BmpHeader)
{
    //check arguments
    if (filename == NULL || BmpHeader == NULL)
    {
        ERR(STATUS_INVALID_PARAMETERS);
    }
    //try to open file for reading
    FILE* fin = fopen(filename, "rb");
    if (fin == NULL)
    {
        ERR(STATUS_FILE_NOT_ALLOWED);
    }
    //read header of BMP file
    fread(BmpHeader, 1, sizeof(BMPHeader), fin);
    fclose(fin);
    return STATUS_SUCCESS;
}


