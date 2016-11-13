#include        <rpc/rpc.h>     /* standard RPC include file */
#include        "C1K.h" 
#include 	<stdio.h>
#include 	<stdlib.h>
#include	<stdbool.h>
#include <string.h>
#include "global.h"
#include "rsaref.h"
#include <md5.h>

FILE *myfp ;
unsigned char key[8]="g3e8f2h2";//random chosen
unsigned char secret_c[10],secret_s[10];

bool KP_Validator(char cid[],char sid[])
{ 
	char buf[20],buf1[20];
	memset(buf,'\0',20);
	memset(buf1,'\0',20);
	fgets(buf,17,myfp);
	fgets(buf1,17,myfp);
	
	if(memcmp(buf,cid,sizeof(cid))==0)
	{if(memcmp(buf1,sid,sizeof(sid))==0)
		{	
			memset(secret_c,'\0',10);
			memset(secret_s,'\0',10);
			memcpy(secret_c,buf+8,8);
			memcpy(secret_s,buf1+8,8);
			printf("HI");return true;
		}
	}
	else
	{return false;exit(1);}
}

randkey(unsigned char key1[])
{int i;
	FILE *dt, *popen();
	char text[128], randText[128];
	dt = popen("date; ps -e", "r");
	fread(text, 128, 1, dt);
	md5_calc(randText, text, 128);
	memcpy(key, randText, 7);
	memcpy(key1, key, 7);

	for (i=0; i<7; i++)
	printf("%03d ", (int)key1[i]);
	printf("\n\n");
	pclose(dt);
}

tokenbuilder(char c[], char s[], char ky2[],ID id,char ky3[])
{
	memcpy(c,id.C,7);
	memcpy(s,id.S,7);
	memcpy(ky2,ky3,7);
}

replybuilder(char c[], char s[],ID id)
{
	memcpy(c, id.C, 7);
	memcpy(s, id.S, 7);
}

enc_reply* rskey_1(ID id)
{
	int j ,i,k;static enc_reply ereply;enc_reply etoken;
	static reply rp;unsigned char iv[8]; memset(iv, '\0', 8);unsigned char encryptedBlock[200];
	unsigned int encryptedBlockLen;unsigned char encryptedBlock1[500];unsigned int plainLen;
	unsigned char plaintext[100]; unsigned int encryptedBlockLen1;
	//printf("enc_msg : "); 
	//for(i=0;i<sizeof(id);i++)
	//{printf("%c",requ.enc_message_array[i]);}
	//printf("enc_msg:%s\n",requ.enc_message_array);
	//strncpy(id.C,requ.enc_message_array,8);
	//strncpy(id.S,requ.enc_message_array+8,8);
	//memcpy((unsigned char*) &id, requ.enc_message_array,requ.enc_len);
	printf("\n C:%s\n",id.C);
	printf("S:%s\n",id.S);
	myfp= fopen("DB.key","r");
	if(KP_Validator(id.C,id.S))
	{
		memset(rp.keey,'\0',8);
		memset(rp.t.keey,'\0',8);

		randkey(rp.keey);
		tokenbuilder(rp.t.C,rp.t.S,rp.t.keey,id,rp.keey);
		replybuilder(rp.C,rp.S,id);

		printf("\n CLient ID in token: %s \n Server ID: %s \n Client ID: %s \n",rp.t.C,rp.t.S,rp.C);
		

		plainLen = sizeof(rp.t);printf("%d",plainLen);
		memcpy(plaintext, rp.t.C, sizeof(rp.t.C));
		memcpy(plaintext+8, rp.t.S, sizeof(rp.t.S));
		memcpy(plaintext+16, rp.t.keey, sizeof(rp.t.keey));
		for(i=0;i<plainLen-8;i++)
		{printf("%c",plaintext[i]);}
		
		for (k=0; k<7; k++)
		{printf("%03d ", (int)rp.keey[k]); }
		printf("\n\n");
		
		//printf("\n\n seg: %s \n\n",plaintext);		
		R_EncryptPEMBlock(encryptedBlock,&encryptedBlockLen,plaintext,plainLen,secret_s,iv);
		/* for (i=0; i<encryptedBlockLen; i++)
		printf("%03d ", (int)encryptedBlock[i]);
		printf("\n\n"); */
		//printf("\n\nserversmsg: %s \n\n",encryptedBlock);
		memcpy(encryptedBlock1,rp.C,sizeof(rp.C));
		memcpy(encryptedBlock1+8,rp.S,sizeof(rp.S));
		memcpy(encryptedBlock1+16,rp.keey,sizeof(rp.keey));
		memcpy(encryptedBlock1+24,encryptedBlock,encryptedBlockLen);
		encryptedBlockLen1=sizeof(encryptedBlock1); 
		printf("\n\n");
		printf("Encrypted block count %d \n",encryptedBlockLen1);
		/* for(i=0;i<16;i++)
		{printf("%c",encryptedBlock1[i]);}printf("\n"); */
		//printf("\n\nserversmsg: %s \n\n",encryptedBlock1);
		//		memcpy(ereply.enc_message_array, (unsigned char*) &rp, sizeof(rp));	
		R_EncryptPEMBlock(ereply.enc_message_array,&ereply.enc_len,encryptedBlock1,encryptedBlockLen1,secret_c,iv);
		printf("%d",strlen(ereply.enc_message_array)); printf("%d",ereply.enc_len);
		/* for (i=0; i<strlen(ereply.enc_message_array); i++)
		printf("%03d ", (int)ereply.enc_message_array[i]);
		printf("\n\n"); */
		return(&ereply); 
	}
	fclose(myfp);
}
