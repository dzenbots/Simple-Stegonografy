
#include "../include/stego_proccessor.h"
#include "../include/secrethider.h"

static void showHeaderInfo(pBMPHeader bmpHeader)
{
    printf("BMP HEADER:\n");
    printf("\tBMP magic:      0x%X\n", bmpHeader->bfType);
    printf("\tBMP file size:  0x%X\n", bmpHeader->bfSize);
    printf("\tBitmap offset:  0x%X\n\n", bmpHeader->bfOffBits);
}

static void showBitmapInfo(pBitmapInfoHeader bih)
{
    printf("BITMAP HEADER\n");
    printf("\tWidth:      %d pixels\n", bih->biWidth);
    printf("\tHeight:     %d pixels\n", bih->biHeight);
    printf("\tBit Count:  %d\n", bih->biBitCount);
    printf("\tImage Size: 0x%X pixels\n\n", bih->biSizeImage);
    printf("\tCapacity:   0x%X bytes\n\n", PIXELS_TO_BYTES(bih->biSizeImage));
}

static void showSecretBufferInfo(uint32 bufferSize)
{
    printf("Secret buffer size: 0x%X\n", bufferSize);
}

static Status extract_info(FILE* bmpinputFile, FILE* outputFile, uint32 secretSize, uint32 sizeImage)
{

    return STATUS_SUCCESS;
}

Status stego_proccess(char* bmpFileName, char *targetFileName, char* outFileName, uint32 mode)
{
    Status status;
    switch (mode)
    {
        case MODE_PACK:
        {
            if (bmpFileName == NULL || targetFileName == NULL || outFileName == NULL)
            {
                ERR(STATUS_INVALID_PARAMETERS);
            }
            pBMPHeader bmpHeader = (pBMPHeader)calloc(1, sizeof(BMPHeader));
            if (bmpHeader == NULL)
            {
                ERR(STATUS_MEMORY_ACCESS_ABORT);
            }
            if ((status = getBMPHeader(bmpFileName, bmpHeader)) != STATUS_SUCCESS)
            {
                free(bmpHeader);
                return status;
            }
            if ((status = checkBMPFileHeader(bmpHeader)) != STATUS_SUCCESS)
            {
                free(bmpHeader);
                return status;
            }
            showHeaderInfo(bmpHeader);
            pBitmapInfoHeader bih = (pBitmapInfoHeader)calloc(1, sizeof(BitmapInfoHeader));
            if (bih == NULL)
            {
                free(bmpHeader);
                ERR(STATUS_MEMORY_ACCESS_ABORT);
            }
            if ((status = getBitmapInfoHeader(bmpFileName, bih)) != STATUS_SUCCESS)
            {
                free(bmpHeader);
                free(bih);
                return status;
            }
            if ((status = checkBitmapInfoHeader(bih)) != STATUS_SUCCESS)
            {
                free(bmpHeader);
                free(bih);
                return status;
            }
            showBitmapInfo(bih);
            FILE* secretfin = fopen(targetFileName, "rb");
            if (secretfin == NULL)
            {
                free(bmpHeader);
                free(bih);
                ERR(STATUS_FILE_NOT_ALLOWED);
            }
            fseek(secretfin, 0, SEEK_END);
            uint32 secretSize = ftell(secretfin);
            if (secretSize + sizeof(uint32) > PIXELS_TO_BYTES(bih->biSizeImage))
            {
                fclose(secretfin);
                free(bih);
                free(bmpHeader);
                ERR(STATUS_UNSUPPORTED_FILE);
            }
            showSecretBufferInfo(secretSize);
            byte* secretBuffer = (byte*)calloc(secretSize, sizeof(byte));
            if (secretBuffer == NULL)
            {
                fclose(secretfin);
                free(bmpHeader);
                free(bih);
                ERR(STATUS_MEMORY_ACCESS_ABORT);
            }
            fseek(secretfin, 0, SEEK_SET);
            fread(secretBuffer, secretSize, sizeof(byte), secretfin);
            fclose(secretfin);
            FILE* bmpinputFile = fopen(bmpFileName, "rb");
            if (bmpinputFile == NULL)
            {
                free(bmpHeader);
                free(bih);
                free(secretBuffer);
                ERR(STATUS_FILE_NOT_ALLOWED);
            }
            FILE* bmpoutputFile = fopen(outFileName, "wb");
            if (bmpoutputFile == NULL)
            {
                free(bmpHeader);
                free(bih);
                free(secretBuffer);
                fclose(bmpinputFile);
                ERR(STATUS_FILE_NOT_ALLOWED);
            }
            fwrite(bmpHeader, 1, sizeof(BMPHeader), bmpoutputFile);
            fwrite(bih, 1, sizeof(BitmapInfoHeader), bmpoutputFile);
            fseek(bmpinputFile, bmpHeader->bfOffBits, SEEK_SET);

            status = hideInfo(bmpinputFile, bmpoutputFile, secretBuffer, secretSize, bih->biSizeImage);

            free(bmpHeader);
            free(bih);
            free(secretBuffer);
                
            fclose(bmpoutputFile);
            fclose(bmpinputFile);
            break;
        }

        case MODE_UNPACK:
        {
            if (bmpFileName == NULL || outFileName == NULL)
            {
                ERR(STATUS_INVALID_PARAMETERS);
            }
            FILE *fin = fopen(bmpFileName, "rb");
            if (fin == NULL)
            {
                ERR(STATUS_FILE_NOT_ALLOWED);
            }
            FILE *fout = fopen(outFileName, "wb");
            if (fout == NULL)
            {
                ERR(STATUS_FILE_NOT_ALLOWED);
            }
            fseek(fin, sizeof(BMPHeader) + sizeof(BitmapInfoHeader), SEEK_SET);

            extractInfo(fin, fout);

            fclose(fin);
            fclose(fout);
            status = STATUS_SUCCESS;
            break;
        }
        default:
        {
            ERR(STATUS_INVALID_PARAMETERS);
        }
    }
    return status;
}
