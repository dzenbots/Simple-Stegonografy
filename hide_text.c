
#include "./include/wingetopt.h"
#include "./include/stego_proccessor.h"

void print_help();

int main(int argc, char** argv)
{
    uint32 bitsOffset, fSize;
    uint32 c;
    char *bmpFileName = NULL, *targetFileName = NULL, *outFileName = NULL;
    byte mode;

    while ((c = getopt(argc, argv, "i:t:o:puh")) != -1)
    {
        switch(c)
        {
            case 'i':
            {
                bmpFileName = optarg;
                break;
            }

            case 't':
            {
                targetFileName = optarg;
                break;
            }

            case 'o':
            {
                outFileName = optarg;
                break;
            }

            case 'p':
            {
                mode = MODE_PACK;
                break;
            }

            case 'u':
            {
                mode = MODE_UNPACK;
                break;
            }

            case 'h':
            
            default:
            {
                print_help();
                return STATUS_SUCCESS;
            }
        }
    }

    if (mode == 0)
    {
        printf("Program mode is not specified\n");
        ERR(STATUS_INVALID_PARAMETERS);
    } 
    else return stego_proccess(bmpFileName, targetFileName, outFileName, mode);
}

void print_help()
{
    printf("\n*********************************\n");
    printf("** Simple Steganografy program **\n");
    printf("*********************************\n\n");
    printf("-i <filename> -> input bmp file name\n");
    printf("-t <filename> -> name of file which should be pack into picture\n");
    printf("-o <filename> -> output file name (*.bmp)\n\n");
    printf("-h            -> show this manual info\n");
    printf("-p            -> pack information\n");
    printf("-u            -> unpack information\n\n");
    printf("Example:\n\n");
    printf("> program_name.exe -i test.bmp -t secret.txt -o test-out.bmp -p\n\n");
    printf("> program_name.exe -i test-out.bmp -o secret.txt -u\n\n");
}