#ifndef GWO_H_
#define GWO_H_

typedef struct ismgraw {
        char   sms_seq[20];       /*短消息序列号      */
        char   cdr_type[2];       /*短消息话单类型    */
        char   user_type[1];      /*用户类型          */
        char   user_dn[11];      /*个人用户号码      */
        char   sp_code[12];        /*sp代码            */
        char   third_dn[11];      /*第三方号码        */
        char   serv_code[21];      /*服务号码          */
        char   oper_code[10];     /*业务代码          */
        char   chrg_type[2];      /*用户计费类别      */
        char   info_fee[6];       /*信息费            */
        char   month_fee[6];      /*包月费            */
        char   send_sts[7];       /*短消息发送状态    */
        char   priority[1];       /*短消息发送优先级  */
        char   info_len[3];       /*信息长度          */
        char   chrg_prov[4];      /*计费用户号码归属省*/
        char   ismg_code[6];      /*网关代码          */
        char   forw_ismg[6];      /*前转网关代码      */
        char   smsc_code[11];     /*短消息中心代码    */
        char   apply_t[14];       /*申请时间          */
        char   finish_t[14];      /*处理结束时间      */
        char   cr[1];
}ismgraw_t;

int gp_fmt(char *o, char *i);

#endif /*GWO_H_*/

