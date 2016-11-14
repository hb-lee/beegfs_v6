#ifndef SETATTRRESPMSG_H_
#define SETATTRRESPMSG_H_

#include <common/net/message/SimpleIntMsg.h>


struct SetAttrRespMsg;
typedef struct SetAttrRespMsg SetAttrRespMsg;

static inline void SetAttrRespMsg_init(SetAttrRespMsg* this);
static inline void SetAttrRespMsg_initFromValue(SetAttrRespMsg* this, int value);

// getters & setters
static inline int SetAttrRespMsg_getValue(SetAttrRespMsg* this);

struct SetAttrRespMsg
{
   SimpleIntMsg simpleIntMsg;
};


void SetAttrRespMsg_init(SetAttrRespMsg* this)
{
   SimpleIntMsg_init( (SimpleIntMsg*)this, NETMSGTYPE_SetAttrResp);
}
   
void SetAttrRespMsg_initFromValue(SetAttrRespMsg* this, int value)
{
   SimpleIntMsg_initFromValue( (SimpleIntMsg*)this, NETMSGTYPE_SetAttrResp, value);
}

int SetAttrRespMsg_getValue(SetAttrRespMsg* this)
{
   return SimpleIntMsg_getValue( (SimpleIntMsg*)this);
}

#endif /*SETATTRRESPMSG_H_*/
