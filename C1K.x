/* C1K.x */ 

struct enc_reply{
int enc_len;
unsigned char enc_message_array[700];
};

struct token{ 
unsigned char C[8]; 
unsigned char S[8];
unsigned char keey[8] ;
}; 

struct ID{
unsigned char C[8]; 
unsigned char S[8];
};

struct reply{
unsigned char C[8]; 
unsigned char S[8];
unsigned char keey[8] ;
struct token t;
}; 

struct netReply{
int replylen;
struct reply R;
};

program C1K_PROG {
	version CS_VERS {
enc_reply RSKEY(ID) = 1;	
		} = 1; /* version number */
	} = 0x32222221;  /*program number should be large & unique */

