
/* SP_proc.c */ 
#include        <rpc/rpc.h>     /* standard RPC include file */
#include        "C2S.h"
#include 	<stdio.h>
#include 	<stdlib.h>
#include	<string.h>
#include	<ctype.h>
#include	<stdbool.h>
#include "Skey.h"
#include "global.h"
#include "rsaref.h"
#include <md5.h>


unsigned char decryptedBlock[800];unsigned int decryptedBlockLen;
unsigned char iv[8];

bool SP_Validator(char tok[]) 
{
	int m,k;
	memset(iv, '\0', 8);
	R_DecryptPEMBlock(decryptedBlock, &decryptedBlockLen, tok+8,44,key,iv);
	if(memcmp(tok,decryptedBlock,8)==0)
	return true;
	else
	{
	printf("Wrong Client ID");
	return false;exit(1);
	}
}

ReplyBuilder(unsigned char d[],unsigned char t[],unsigned int le,char str2[],unsigned char kcs[],unsigned char iv[])
{
	R_EncryptPEMBlock(t,&le,str2,strlen(str2),kcs,iv);
	memcpy(d,decryptedBlock,8);
	memcpy(d+8,decryptedBlock+8,8);
	memcpy(d+16,t,le);
}  

enc_replyy* alpha_1(enc_request q)
{
	memset(iv, '\0', 8);
	printf("len %d \n",q.enc_len);int i;unsigned char decryptedBlock1[800];unsigned int decryptedBlockLen1;
	for (i=0; i<8; i++)
	printf("%c ", q.enc_message_array[i]);
	printf("\n\n");
	
	if(SP_Validator(q.enc_message_array))
	{printf("\nHI\n");
		static enc_replyy er;	static netreply r2; //52
		int i=0,k=0,m;unsigned char kcs[8];
		memcpy(kcs,decryptedBlock+16,8);
		for (k=0; k<7; k++)
		printf("%03d ", (int)kcs[k]);
		printf("\n\n");
		int len = strlen(q.enc_message_array+484)	;	
		R_DecryptPEMBlock(decryptedBlock1, &decryptedBlockLen1, q.enc_message_array+484,12,kcs,iv);
		printf("size of alpha string %d \n",decryptedBlockLen1);
		for (m=0; m<decryptedBlockLen1; m++)
		{printf("%c \n",decryptedBlock1[m]); }
		printf("\n\n"); 
		
		int j = decryptedBlockLen1;
		char str[j+1]; char str1[j+1];char str2[j];
		memset(str,'\0',j+1);
		memset(str1,'\0',j+1);
		memset(str2,'\0',j+1);
		memcpy(str,decryptedBlock1,j);
		printf("string length %d\n",strlen(str));
		printf("String Entered %s \n",str); 
		int ct=0,disp=0;
		while(ct<j)
		{
			if(str[ct] >= '!' && str[ct] <= '@')
			{//printf("\n");
				//str1[i]=str[i];
			}
			else
			{//printf("\n");
				str2[disp]=str[ct];disp++;}
			ct++;
		}
		
		printf("Alphabets Extracted: %s \n",str2);
		unsigned char temp_rep[100]; unsigned int t_r_l;
		//R_EncryptPEMBlock(temp_rep,&t_r_l,str2,strlen(str2),kcs,iv);
		//printf("preparing reply \n");
		//ReplyBuilder(r2.rep.a.msg,r2.rep.C1,r2.rep.S1,str2,q);
		ReplyBuilder(er.enc_message_array,temp_rep,t_r_l,str2,kcs,iv);
		
		er.enc_len=sizeof(er.enc_message_array);printf("the length of reply %d \n",er.enc_len);
		
		return(&er); 
	}	

}

enc_replyy* numeric_1(enc_request q)
{
	memset(iv, '\0', 8);
	printf("len %d \n",q.enc_len);int i;unsigned char decryptedBlock1[800];unsigned int decryptedBlockLen1;
	for (i=0; i<8; i++)
	printf("%c ", q.enc_message_array[i]);
	printf("\n\n");
	
	if(SP_Validator(q.enc_message_array))
	{printf("\nHI\n");
		static enc_replyy er;	static netreply r2; //52
		int i=0,k=0,m;unsigned char kcs[8];
		memcpy(kcs,decryptedBlock+16,8);
		for (k=0; k<7; k++)
		printf("%03d ", (int)kcs[k]);
		printf("\n\n");
		int len = strlen(q.enc_message_array+484)	;	
		R_DecryptPEMBlock(decryptedBlock1, &decryptedBlockLen1, q.enc_message_array+484,12,kcs,iv);
		printf("size of alpha string %d \n",decryptedBlockLen1);
		for (m=0; m<decryptedBlockLen1; m++)
		{printf("%c \n",decryptedBlock1[m]); }
		printf("\n\n"); 
		
		int j = decryptedBlockLen1;
		char str[j+1]; char str1[j+1];char str2[j];
		memset(str,'\0',j+1);
		memset(str1,'\0',j+1);
		memset(str2,'\0',j+1);
		memcpy(str,decryptedBlock1,j);
		printf("string length %d\n",strlen(str));
		printf("String Entered %s \n",str); 
		int ct=0,disp=0;
		while(ct<j)
		{
			if(str[ct] >= '!' && str[ct] <= '@')
			{printf("\n");
				str1[disp]=str[ct];disp++;
			}
			else
			{//printf("\n");
				//str2[disp]=str[ct];disp++;
			}
			ct++;
		}
		printf("NUMBERS Extracted: %s \n",str1);
		unsigned char temp_rep[100]; unsigned int t_r_l;
		//R_EncryptPEMBlock(temp_rep,&t_r_l,str1,strlen(str1),kcs,iv);
		printf("preparing reply \n");
		ReplyBuilder(er.enc_message_array,temp_rep,t_r_l,str1,kcs,iv);
		er.enc_len=sizeof(er.enc_message_array);printf("the length of reply %d \n",er.enc_len);
		return(&er); 
	}		
}

