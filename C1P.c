/* client.c */
#include        <stdio.h>
#include        <rpc/rpc.h> 
#include        "C1K.h"
#include		"C2S.h"
#include	<stdlib.h>
#include	<string.h>
#include	<md5.h>
#include "global.h"
#include "rsaref.h"
#include "Ckey.h"


main(argc, argv)
int     argc;
char    *argv[];
{
	CLIENT          *cl;            /* RPC handle */
	char            *server;
	char			*server1;
	
	struct enc_reply *skey; 
	struct reply convert_rp;
	struct ID arg4;
	server = argv[4];
	server1 = argv[3];
	char *cid,*sid;
	cid = argv[1];
	sid = argv[2];
	/********************************************/
	if ( (cl = clnt_create(server, C1K_PROG, CS_VERS, "udp")) == NULL) {
		clnt_pcreateerror(server);
		exit(2);}
	/***********************************************/
	memset(arg4.C,'\0',8);
	memset(arg4.S,'\0',8);
	memcpy (arg4.S, sid, 7);
	memcpy (arg4.C, cid, 7);
	int i,k,j,l;
	unsigned char decryptedBlock[600];unsigned char iv[8]; memset(iv, '\0', 8); 
	unsigned int decryptedBlockLen;unsigned char decryptedBlock1[100];unsigned int decryptedBlockLen1;
	unsigned int plainLen;
	unsigned char plaintext[500];
	if ( (skey = rskey_1(arg4,cl)) == NULL) {
		clnt_perror(cl, "call failed");
		exit(3);}
	/* for (i=0; i<strlen( skey->enc_message_array); i++)
	printf("%03d ", (int)skey->enc_message_array[i]);
	printf("\n\n"); */
	R_DecryptPEMBlock(decryptedBlock, &decryptedBlockLen, skey->enc_message_array,skey->enc_len,key,iv);
	printf("%d",decryptedBlockLen);
	for (i=0; i<16; i++)
	printf("%c ", decryptedBlock[i]);
	printf("\n\n");
	for (k=0; k<7; k++)
	{printf("%03d ", (int)decryptedBlock[16+k]);}
	printf("\n\n");
	memcpy(plaintext, decryptedBlock, 8);
	memcpy(plaintext+8, decryptedBlock+8,8);
	memcpy(plaintext+16, decryptedBlock+16, 8);
	memcpy(plaintext+24, decryptedBlock+24, decryptedBlockLen-24);
	printf("Entering Complexity");
	
	memcpy(convert_rp.C,plaintext,8);
	memcpy(convert_rp.S,plaintext+8,8);
	memcpy(convert_rp.keey,plaintext+16,8);
	printf ("\nCid: %s Sid: %s\n",convert_rp.C,convert_rp.S);
	for (l=0; l<7; l++)
	{printf("%03d ", (int)convert_rp.keey[l]);}
	printf("\n\n");
	printf("C id: %.*s \t", 8, plaintext);	
	printf("S id: %.*s", 8, plaintext+8);	

	/********************************************/
	if ( (cl = clnt_create(server1, C2S_PROG, C2S_VERS, "udp")) == NULL) {
		clnt_pcreateerror(server1);
		exit(2);}
	/***********************************************/
	struct enc_replyy *sk_a;
	struct enc_replyy *sk_n;
	struct REQ arg2;
	struct REQ arg3;
	struct enc_request requ;
	struct enc_request reqst;
	unsigned char encryptedBlock[100]; unsigned int encryptedBlockLen;
	/**********************************************/
	/***********************************************/
	int ch;int b=0;unsigned int decryptedBlockLen2;unsigned char decryptedBlock2[100];int x=0;int len=0;
	printf("Enter the Desired Service 1.Alpha 2.Numeric \n");
	scanf("%d",&ch);
	
	
	/**********************************************/
	switch(ch)
	{
	case 1:
		memset(arg2.C1,'\0',8);
		memset(arg2.a.msg,'\0',100);
		memset(arg2.t1.C1,'\0',8);
		memset(arg2.t1.S1,'\0',8);
		memcpy (arg2.t1.S1, sid, 6);
		memcpy(arg2.t1.C1,cid, 6);
		memcpy(arg2.C1, cid, 6);
		memcpy(arg2.t1.key1,convert_rp.keey, 7);
		printf("Enter the string for alpha function \n");
		scanf(" %[^\n]s",&arg2.a.msg);
		
		R_EncryptPEMBlock(encryptedBlock,&encryptedBlockLen,arg2.a.msg,strlen(arg2.a.msg),convert_rp.keey,iv);
		memcpy(requ.enc_message_array, plaintext, 8);
		memcpy(requ.enc_message_array+8,decryptedBlock+24, decryptedBlockLen-24);
		len =  decryptedBlockLen - 16;printf("Length of the encrypted message %d \n",decryptedBlockLen);
		memcpy(requ.enc_message_array+len,encryptedBlock, encryptedBlockLen);
		printf("Length of the encrypted message %d \n",encryptedBlockLen);

		requ.enc_len = sizeof(requ.enc_message_array);
		printf("Length of the encrypted message %d \n",requ.enc_len);
		
		if ( (sk_a = alpha_1(requ, cl)) == NULL) {
			clnt_perror(cl, "call failed");
			exit(3);
		}
		
		for(b=0;b<16;b++)
		printf("%c",sk_a->enc_message_array[b]);
		R_DecryptPEMBlock(decryptedBlock2, &decryptedBlockLen2, sk_a->enc_message_array+16,12,convert_rp.keey,iv);
		printf("\n\n");
		for(x=0;x<decryptedBlockLen2;x++)
		printf("%c",decryptedBlock2[x]);
		printf("\n\n");
		break;	
		/*********************************************/
	case 2: memset(arg3.C1,'\0',8);
		memset(arg3.a.msg,'\0',100);
		memset(arg3.t1.C1,'\0',8);
		memset(arg3.t1.S1,'\0',8);
		memcpy (arg3.t1.S1, sid, 7);
		memcpy(arg3.t1.C1,cid, 7);
		memcpy(arg3.C1, cid, 7);
		memcpy(arg3.t1.key1,convert_rp.keey, 7);
		printf("Enter the string for numeric function \n");
		scanf(" %[^\n]s",&arg3.a.msg);
		
		R_EncryptPEMBlock(encryptedBlock,&encryptedBlockLen,arg3.a.msg,strlen(arg3.a.msg),convert_rp.keey,iv);
		
		memcpy(reqst.enc_message_array, plaintext, 8);
		memcpy(reqst.enc_message_array+8,decryptedBlock+24, decryptedBlockLen-24);
		 len =  decryptedBlockLen - 16;printf("Length of the encrypted message %d \n",decryptedBlockLen);
		memcpy(reqst.enc_message_array+len,encryptedBlock, encryptedBlockLen);
		printf("Length of the encrypted message %d \n",encryptedBlockLen);

		reqst.enc_len = sizeof(reqst.enc_message_array);
		printf("Length of the encrypted message %d \n",reqst.enc_len);
		
		if ( (sk_n = numeric_1(reqst, cl)) == NULL) {
			clnt_perror(cl, "call failed");
			exit(3);
		}
		
		for(b=0;b<16;b++)
		printf("%c",sk_n->enc_message_array[b]);
		R_DecryptPEMBlock(decryptedBlock2, &decryptedBlockLen2, sk_n->enc_message_array+16,12,convert_rp.keey,iv);
		printf("\n\n");
		for(x=0;x<decryptedBlockLen2;x++)
		printf("%c",decryptedBlock2[x]);
		printf("\n\n");
		break;
	}	/*********************************************/
	clnt_destroy(cl);               /* done with the handle */
	exit(0);
} 

