#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <tm_reader.h>
#include <string.h>
#include "reader_main.h"



char server_buffer[65536];

void read_user_input(uint32_t rd_inp);
void startpush();
void senddata ( char *buffer, int length);

int main (void)
{
    int rc = 0;
    uint32_t rd_inp = 2;

    startpush();
    
    while(1) {
        read_user_input(rd_inp);
    }

    return rc;
}

void read_user_input(uint32_t rd_inp)
{
    uint32_t rd_input = rd_inp, cnt = 0; 
    char *serial_port= "tmr:///dev/ttyS1"; 
    struct reader_info_type rdr_info = {0};
    uint32_t readasync_argc = 4;
    char *readasync_argv[] = {"", "tmr:///dev/ttyS1", "--ant", "1"};
    struct rfid_tag_type rfid_tag[512] = {0};    

    //printf("1. read reader data\n");
    //printf("2. read tag data\n");


    //printf("Read user input\n");
    //scanf("%d", &rd_input);

    switch(rd_input)
    {
        case 1:
            printf("read reader data: %d\n", rd_input);
	    reader_main (serial_port, &rdr_info);
	    memcpy((void *)server_buffer,  (void *)&rdr_info, sizeof(rdr_info));
	    senddata ( server_buffer, 1024);
#if 0	    
	    printf("\n\n");
	    printf("/reader/version/hardware: %s\n", rdr_info.rdr_ver);
            printf("/reader/version/serial: %s\n", rdr_info.rdr_ser);
	    printf("/reader/version/model:  %s\n", rdr_info.rdr_mod);
	    printf("/reader/version/software: %s\n", rdr_info.rdr_sw_ver);
	    printf("/reader/uri:  %s\n", rdr_info.rdr_uri);
	    printf("/reader/version/productID: %d\n", rdr_info.rdr_prd_id);
	    printf("/reader/version/productGroupID: %d\n", rdr_info.rdr_prd_grp_id);
	    printf("/reader/version/productGroup: %s\n", rdr_info.rdr_prd_grp);
	    printf("/reader/description:  %s\n", rdr_info.rdr_dsc);
#endif
	    break;
        case 2:
            printf("read tag data: %d\n", rd_input);
	    readasync_main (readasync_argc, readasync_argv, &rfid_tag[0]);
	    memcpy((void *)server_buffer,  (void *)&rfid_tag, sizeof(rfid_tag));
	    senddata ( server_buffer, 1024);
#if 0	    
	    printf("\n\n");
	    for (cnt=0; cnt < 10; cnt++) {
	        printf("TAG-ID EPC: %s\n", rfid_tag[cnt].tag_id);
	    }
#endif
	    break;
        case 3:
            printf("Undefined: %d\n", rd_input);
	    break;
        default:
            printf("Invalid input: %d\n", rd_input);
	    break;
    }

}


