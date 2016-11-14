#include "FLockEntryMsg.h"


const struct NetMessageOps FLockEntryMsg_Ops = {
   .serializePayload = FLockEntryMsg_serializePayload,
   .deserializePayload = _NetMessage_deserializeDummy,
   .processIncoming = NetMessage_processIncoming,
   .getSupportedHeaderFeatureFlagsMask = NetMessage_getSupportedHeaderFeatureFlagsMask,
};

void FLockEntryMsg_serializePayload(NetMessage* this, SerializeCtx* ctx)
{
   FLockEntryMsg* thisCast = (FLockEntryMsg*)this;

   // clientNumID
   NumNodeID_serialize(&thisCast->clientNumID, ctx);

   // clientFD
   Serialization_serializeInt64(ctx, thisCast->clientFD);

   // ownerPID
   Serialization_serializeInt(ctx, thisCast->ownerPID);

   // lockTypeFlags
   Serialization_serializeInt(ctx, thisCast->lockTypeFlags);

   // entryInfo
   EntryInfo_serialize(thisCast->entryInfoPtr, ctx);

   // fileHandleID
   Serialization_serializeStrAlign4(ctx, thisCast->fileHandleIDLen, thisCast->fileHandleID);

   // lockAckID
   Serialization_serializeStrAlign4(ctx, thisCast->lockAckIDLen, thisCast->lockAckID);
}
