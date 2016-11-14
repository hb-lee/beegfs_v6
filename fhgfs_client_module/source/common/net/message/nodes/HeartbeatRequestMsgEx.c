#include <common/nodes/Node.h>
#include <components/DatagramListener.h>
#include <common/toolkit/SocketTk.h>
#include <app/App.h>
#include "HeartbeatMsgEx.h"
#include "HeartbeatRequestMsgEx.h"


const struct NetMessageOps HeartbeatRequestMsgEx_Ops = {
   .serializePayload = SimpleMsg_serializePayload,
   .deserializePayload = SimpleMsg_deserializePayload,
   .processIncoming = __HeartbeatRequestMsgEx_processIncoming,
   .getSupportedHeaderFeatureFlagsMask = NetMessage_getSupportedHeaderFeatureFlagsMask,
};

bool __HeartbeatRequestMsgEx_processIncoming(NetMessage* this, struct App* app,
   fhgfs_sockaddr_in* fromAddr, struct Socket* sock, char* respBuf, size_t bufLen)
{
   Logger* log = App_getLogger(app);
   const char* logContext = "HeartbeatRequest incoming";

   Config* cfg = App_getConfig(app);
   Node* localNode = App_getLocalNode(app);
   const char* localNodeID = Node_getID(localNode);
   NicAddressList* nicList = Node_getNicList(localNode);
   const BitStore* nodeFeatureFlags = Node_getNodeFeatures(localNode);

   HeartbeatMsgEx hbMsg;
   unsigned respLen;
   bool serializeRes;
   ssize_t sendRes;


   HeartbeatMsgEx_initFromNodeData(&hbMsg, localNodeID, (NumNodeID){0}, NODETYPE_Client, nicList,
      nodeFeatureFlags);
   HeartbeatMsgEx_setPorts(&hbMsg, Config_getConnClientPortUDP(cfg), 0);
   HeartbeatMsgEx_setFhgfsVersion(&hbMsg, BEEGFS_VERSION_CODE);
   
   respLen = NetMessage_getMsgLength( (NetMessage*)&hbMsg);
   serializeRes = NetMessage_serialize( (NetMessage*)&hbMsg, respBuf, bufLen);
   if(unlikely(!serializeRes) )
   {
      Logger_logErrFormatted(log, logContext, "Unable to serialize response");
      goto err_uninit;
   }
   
   if(fromAddr)
   { // datagram => sync via dgramLis send method
      DatagramListener* dgramLis = App_getDatagramListener(app);
      sendRes = DatagramListener_sendto(dgramLis, respBuf, respLen, 0, fromAddr);
   }
   else
      sendRes = Socket_sendto(sock, respBuf, respLen, 0, NULL);

   if(unlikely(sendRes <= 0) )
      Logger_logErrFormatted(log, logContext, "Send error. ErrCode: %lld", (long long)sendRes);

err_uninit:
   return true;
}


