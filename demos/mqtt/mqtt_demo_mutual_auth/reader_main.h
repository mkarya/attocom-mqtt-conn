#ifndef _READER_MAIN_H
#define _READER_MAIN_H



struct reader_info_type {
    char  rdr_ver[64];
    char  rdr_ser[64];
    char  rdr_mod[64];
    char  rdr_sw_ver[64];
    char  rdr_uri[64];
    int   rdr_prd_id;
    int   rdr_prd_grp_id;
    char  rdr_prd_grp[64];
    char  rdr_dsc[64];
};

struct rfid_tag_type {
	char  tag_id[64];
};


int reader_main (char *, struct reader_info_type *rdr_info );
int readasync_main(int rd_argc, char *rd_argv[], struct rfid_tag_type *);





#endif /* _READER_MAIN_H */

