

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gp.h>




void mkfmt(char *fmt , size_t l)
{
        sprintf(fmt, "%%-%d.%ds", l,l);
}


typedef struct gp_send {
        char rec_type [2];
        char	sms_seq[20];
        char	cdr_type[2];
        char	user_type[1];
        char	charge_dn[15];
        char	ec_code[18];
        char	si_code[12];
        char	third_dn[15];
        char	serv_code[21];
        char	oper_code[10];
        char	send_sts[4];
        char	priority[1];
        char	info_len[3];
        char	ismg_code[6];
        char	forw_ismg[6];
        char	smsc_code[11];
        char	apply_t[14];
        char	finish_t[14];
        char	reserved[20];
        char	cr[1];
        char  lf[1];

}gp_send_t;


static gp_send_t   os;
static ismgraw_t  in;
int gp_fmt(char *o, char *i)
{

        char fb[64];
        char fmt[16];
        char tb[64];


        memset(o, 0, sizeof(os));

        memcpy(o + offsetof(gp_send ,rec_type), "20", sizeof(os.rec_type));


        memcpy(o + offsetof(gp_send ,sms_seq), i + offsetof(ismgraw_t, sms_seq), sizeof(os.sms_seq));
        memcpy(o + offsetof(gp_send ,cdr_type), i + offsetof(ismgraw_t, cdr_type), sizeof(os.cdr_type));
        memcpy(o + offsetof(gp_send ,user_type), i + offsetof(ismgraw_t, user_type), sizeof(os.user_type));

        mkfmt(fmt, sizeof(os.charge_dn));
        memset(fb, 0 , sizeof(fb));
        memcpy(fb, i + offsetof(ismgraw_t, user_dn), sizeof(in.user_dn));
        sprintf(tb, fmt,fb );
        memcpy(o + offsetof(gp_send ,charge_dn), tb, sizeof(os.charge_dn));


        mkfmt(fmt, sizeof(os.ec_code) + sizeof(os.si_code));
        sprintf(fb,fmt, "");
        memcpy(o + offsetof(gp_send ,ec_code), fb, sizeof(os.ec_code) + sizeof(os.si_code));

        mkfmt(fmt, sizeof(os.third_dn));
        memset(fb, 0 , sizeof(fb));
        memcpy(fb, i + offsetof(ismgraw_t, third_dn), sizeof(in.third_dn));
        sprintf(tb, fmt,fb );
        memcpy(o + offsetof(gp_send ,third_dn), tb, sizeof(os.third_dn));

        memcpy(o + offsetof(gp_send ,serv_code), i + offsetof(ismgraw_t, serv_code),
               sizeof(os.serv_code) + sizeof(os.oper_code));

        mkfmt(fmt, sizeof(os.send_sts));
        sprintf(fb,fmt, "0");
        memcpy(o + offsetof(gp_send ,send_sts), fb,  sizeof(os.send_sts));
        memcpy(o + offsetof(gp_send ,priority), i + offsetof(ismgraw_t, priority),
               sizeof(os.priority) );
        
        memcpy(fb, i + offsetof(ismgraw_t, info_len),
               sizeof(in.info_len) );
        
        sprintf(tb, "%03d", atoi(fb));
        memcpy(o + offsetof(gp_send, info_len), tb, sizeof(os.info_len));

        memcpy(o + offsetof(gp_send ,ismg_code), i + offsetof(ismgraw_t, ismg_code),
               sizeof(os.ismg_code)
               + sizeof(os.forw_ismg)
               + sizeof(os.smsc_code)
               + sizeof(os.apply_t)
               + sizeof(os.finish_t)
              );

        memset(o + offsetof(gp_send ,reserved), ' ', sizeof(os.reserved));
        memcpy(o + offsetof(gp_send ,cr) ,"\r", sizeof(os.cr));
        memcpy(o + offsetof(gp_send ,lf) ,"\n", sizeof(os.lf));

        o[offsetof(gp_send ,lf) + 1] = 0;


        return 0;

}


