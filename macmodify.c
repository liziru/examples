#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

#define BUFF_SIZE 1024
#define VALUE_SIZE 40
#define USER_PI "pi"
#define GROUP_PI "pi"
#define IPFILE "./eth0"
#define CGI_ERROR_FAIL 1
#define CGI_SUCESS 0

int  ModifyIP(const char *ipaddr)
{
    char readbuf[BUFF_SIZE] = {};
    char *str =NULL;
    FILE *fp=fopen(IPFILE,"r");
    if(NULL==fp){
        return CGI_ERROR_FAIL;
    }
    int ret = fread(readbuf,1,BUFF_SIZE,fp);
    if(NULL == (str=strstr(readbuf,"hwaddress ")))
    {
        return CGI_ERROR_FAIL;
    }

    fclose(fp);
    if((fp=fopen(IPFILE,"w"))==NULL)
    {
        return CGI_ERROR_FAIL;
    }

    char gateway[ VALUE_SIZE]={"192.168.1.1"};
    char broadcast[VALUE_SIZE]={"192.168.1.255"};
    char *ptr = strrchr(ipaddr,'.');
    gateway[8]=*(ptr-1);
    broadcast[8]=*(ptr-1);

    //fprintf(stdout,"auto eth0\niface eth0 inet static\naddress %s\nnetmask 255.255.255.0\ngateway %s\nbroadcast %s\ndns-nameserver %s\n%s",ipaddr,gateway,broadcast,gateway,str);    
    fprintf(fp,"auto eth0\niface eth0 inet static\naddress %s\nnetmask 255.255.255.0\ngateway %s\nbroadcast %s\ndns-nameserver %s\n%s",ipaddr,gateway,broadcast,gateway,str);    

    if(NULL != fp)
    {
        fclose(fp);
        fp = NULL;
    }

    return 0;
}

int  ModifyMAC(const char *macaddr)
{
    char readbuf[BUFF_SIZE] = {};
    char *str =NULL;
    FILE *fp=fopen(IPFILE,"r");
    if(NULL==fp){
        return CGI_ERROR_FAIL;
    }
    int ret = fread(readbuf,1,BUFF_SIZE,fp);
    if(NULL == (str=strstr(readbuf,"hwaddress ")))
    {
        return CGI_ERROR_FAIL;
    }

//	   fprintf(stdout,"1 %s\n",readbuf);    
    memset(str+10,0,sizeof(readbuf)-(str+8-readbuf));
//  	 fprintf(stdout,"2 %s\n",readbuf);    
    strncpy(str+10,macaddr,strlen(macaddr));
//   	fprintf(stdout,"3 %s\n",readbuf);    
    fclose(fp);
    if((fp=fopen(IPFILE,"w"))==NULL)
    {
        return CGI_ERROR_FAIL;
    }
    //fprintf(stdout,"auto eth0\niface eth0 inet static\naddress %s\nnetmask 255.255.255.0\ngateway %s\nbroadcast %s\ndns-nameserver %s\n%s",ipaddr,gateway,broadcast,gateway,str);    
    fprintf(fp,"%s\n",readbuf);    
    fprintf(stdout,"%s\n",readbuf);    

    if(NULL != fp)
    {
        fclose(fp);
        fp = NULL;
    }

    return CGI_SUCESS;
}


int main(int argc, char const *argv[])
{
#if 0
    int ret = ModifyIP("192.168.1.105");
    if(ret != 0 )
        printf("error.\n");
#endif
	
    int ret = ModifyMAC("00:00:d4:85:f3:00");
    if(ret != 0 )
        printf("error.\n");

    return 0;
}
