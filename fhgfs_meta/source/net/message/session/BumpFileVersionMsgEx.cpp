#include "BumpFileVersionMsgEx.h"

#include <program/Program.h>

bool BumpFileVersionMsgEx::processIncoming(ResponseContext& ctx)
{
   LOG_DBG(DEBUG, "Received a BumpFileVersionMsg.", ctx.peerName());
   LOG_DBG(DEBUG, "", getEntryInfo().getEntryID(), getEntryInfo().getIsBuddyMirrored(),
         hasFlag(NetMessageHeader::Flag_BuddyMirrorSecond));

   return BaseType::processIncoming(ctx);
}

FileIDLock BumpFileVersionMsgEx::lock(EntryLockStore& store)
{
   return {&store, getEntryInfo().getEntryID()};
}

std::unique_ptr<MirroredMessageResponseState> BumpFileVersionMsgEx::executeLocally(
   ResponseContext& ctx, bool isSecondary)
{
   auto inode = Program::getApp()->getMetaStore()->referenceFile(&getEntryInfo());
   if (!inode)
      return boost::make_unique<ResponseState>(FhgfsOpsErr_INTERNAL);

   if (!inode->incrementFileVersion(&getEntryInfo()))
      return boost::make_unique<ResponseState>(FhgfsOpsErr_SAVEERROR);

   return boost::make_unique<ResponseState>(FhgfsOpsErr_SUCCESS);
}

bool BumpFileVersionMsgEx::forwardToSecondary(ResponseContext& ctx)
{
   return sendToSecondary(ctx, *this, NETMSGTYPE_BumpFileVersionResp) == FhgfsOpsErr_SUCCESS;
}
