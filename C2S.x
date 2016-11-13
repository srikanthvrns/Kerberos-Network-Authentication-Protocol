/* C1K.x */

struct enc_request{
int enc_len;
unsigned char enc_message_array[800];
};

struct enc_replyy{
int enc_len;
unsigned char enc_message_array[800];
};

struct tokenn{ 
	unsigned char C1[8]; 
	unsigned char S1[8];
	unsigned key1[8] ;
}; 

struct arg{
	unsigned char msg[100];
};
 
struct Reply{
	unsigned char C1[8]; 
	unsigned char S1[8];
	struct arg a;
}; 

struct REQ{
	unsigned char C1[8]; 
	struct arg a;
	struct tokenn t1;
}; 

struct netreply{
int replen;
struct Reply rep;
};

program C2S_PROG {
	version C2S_VERS {	
		enc_replyy ALPHA(enc_request) = 1;
		enc_replyy NUMERIC(enc_request)= 2;
	} = 1; /* version number */
} = 0x35555555;  /*program number should be large & unique */

