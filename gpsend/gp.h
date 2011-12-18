#ifndef GWO_H_
#define GWO_H_

typedef struct ismgraw {
        char   sms_seq[20];       /*����Ϣ���к�      */
        char   cdr_type[2];       /*����Ϣ��������    */
        char   user_type[1];      /*�û�����          */
        char   user_dn[11];      /*�����û�����      */
        char   sp_code[12];        /*sp����            */
        char   third_dn[11];      /*����������        */
        char   serv_code[21];      /*�������          */
        char   oper_code[10];     /*ҵ�����          */
        char   chrg_type[2];      /*�û��Ʒ����      */
        char   info_fee[6];       /*��Ϣ��            */
        char   month_fee[6];      /*���·�            */
        char   send_sts[7];       /*����Ϣ����״̬    */
        char   priority[1];       /*����Ϣ�������ȼ�  */
        char   info_len[3];       /*��Ϣ����          */
        char   chrg_prov[4];      /*�Ʒ��û��������ʡ*/
        char   ismg_code[6];      /*���ش���          */
        char   forw_ismg[6];      /*ǰת���ش���      */
        char   smsc_code[11];     /*����Ϣ���Ĵ���    */
        char   apply_t[14];       /*����ʱ��          */
        char   finish_t[14];      /*�������ʱ��      */
        char   cr[1];
}ismgraw_t;

int gp_fmt(char *o, char *i);

#endif /*GWO_H_*/

