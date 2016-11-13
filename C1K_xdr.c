/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "C1K.h"

bool_t
xdr_enc_reply(xdrs, objp)
	register XDR *xdrs;
	enc_reply *objp;
{

#if defined(_LP64) || defined(_KERNEL)
	register int *buf;
#else
	register long *buf;
#endif

	int i;
	if (!xdr_int(xdrs, &objp->enc_len))
		return (FALSE);
	if (!xdr_vector(xdrs, (char *)objp->enc_message_array, 700,
		sizeof (u_char), (xdrproc_t) xdr_u_char))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_token(xdrs, objp)
	register XDR *xdrs;
	token *objp;
{

#if defined(_LP64) || defined(_KERNEL)
	register int *buf;
#else
	register long *buf;
#endif

	int i;
	if (!xdr_vector(xdrs, (char *)objp->C, 8,
		sizeof (u_char), (xdrproc_t) xdr_u_char))
		return (FALSE);
	if (!xdr_vector(xdrs, (char *)objp->S, 8,
		sizeof (u_char), (xdrproc_t) xdr_u_char))
		return (FALSE);
	if (!xdr_vector(xdrs, (char *)objp->keey, 8,
		sizeof (u_char), (xdrproc_t) xdr_u_char))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_ID(xdrs, objp)
	register XDR *xdrs;
	ID *objp;
{

#if defined(_LP64) || defined(_KERNEL)
	register int *buf;
#else
	register long *buf;
#endif

	int i;
	if (!xdr_vector(xdrs, (char *)objp->C, 8,
		sizeof (u_char), (xdrproc_t) xdr_u_char))
		return (FALSE);
	if (!xdr_vector(xdrs, (char *)objp->S, 8,
		sizeof (u_char), (xdrproc_t) xdr_u_char))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_reply(xdrs, objp)
	register XDR *xdrs;
	reply *objp;
{

#if defined(_LP64) || defined(_KERNEL)
	register int *buf;
#else
	register long *buf;
#endif

	int i;
	if (!xdr_vector(xdrs, (char *)objp->C, 8,
		sizeof (u_char), (xdrproc_t) xdr_u_char))
		return (FALSE);
	if (!xdr_vector(xdrs, (char *)objp->S, 8,
		sizeof (u_char), (xdrproc_t) xdr_u_char))
		return (FALSE);
	if (!xdr_vector(xdrs, (char *)objp->keey, 8,
		sizeof (u_char), (xdrproc_t) xdr_u_char))
		return (FALSE);
	if (!xdr_token(xdrs, &objp->t))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_netReply(xdrs, objp)
	register XDR *xdrs;
	netReply *objp;
{

#if defined(_LP64) || defined(_KERNEL)
	register int *buf;
#else
	register long *buf;
#endif

	if (!xdr_int(xdrs, &objp->replylen))
		return (FALSE);
	if (!xdr_reply(xdrs, &objp->R))
		return (FALSE);
	return (TRUE);
}
