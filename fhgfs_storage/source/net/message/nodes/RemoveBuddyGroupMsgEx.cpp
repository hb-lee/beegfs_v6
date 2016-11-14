#include "RemoveBuddyGroupMsgEx.h"

#include <common/net/message/nodes/RemoveBuddyGroupRespMsg.h>
#include <net/message/storage/listing/ListChunkDirIncrementalMsgEx.h>
#include <program/Program.h>

static FhgfsOpsErr checkChunkDirRemovable(const int dirFD)
{
   DIR* dir = fdopendir(dirFD);
   std::unique_ptr<DIR, StorageTk::CloseDirDeleter> _dir(dir);

   struct dirent buffer;
   struct dirent* result;

   while (readdir_r(dir, &buffer, &result) == 0)
   {
      if (!result)
         return FhgfsOpsErr_SUCCESS;

      if (strcmp(result->d_name, ".") == 0 || strcmp(result->d_name, "..") == 0)
         continue;

      struct stat statData;

      const int statRes = ::fstatat(dirfd(dir), result->d_name, &statData, AT_SYMLINK_NOFOLLOW);
      if (statRes != 0)
      {
         LOG(ERR, "Could not stat something in chunk directory.");
         return FhgfsOpsErr_INTERNAL;
      }

      if (!S_ISDIR(statData.st_mode))
         return FhgfsOpsErr_NOTEMPTY;

      const int subdir = ::openat(dirfd(dir), result->d_name, O_RDONLY);
      if (subdir < 0)
      {
         LOG(ERR, "Could not open directory in chunk path.");
         return FhgfsOpsErr_INTERNAL;
      }

      const FhgfsOpsErr checkRes = checkChunkDirRemovable(subdir);
      if (checkRes != FhgfsOpsErr_SUCCESS)
         return checkRes;
   }

   return FhgfsOpsErr_INTERNAL;
}

bool RemoveBuddyGroupMsgEx::processIncoming(ResponseContext& ctx)
{
   App* app = Program::getApp();

   LOG_DBG(DEBUG, "Received RemoveBuddyGroupMsg.", ctx.peerName());

   if (type != NODETYPE_Storage)
   {
      ctx.sendResponse(RemoveBuddyGroupRespMsg(FhgfsOpsErr_INTERNAL));
      return true;
   }

   uint16_t targetID = app->getMirrorBuddyGroupMapper()->getPrimaryTargetID(groupID);
   if (app->getTargetMapper()->getNodeID(targetID) != app->getLocalNode().getNumID())
      targetID = app->getMirrorBuddyGroupMapper()->getSecondaryTargetID(groupID);
   if (app->getTargetMapper()->getNodeID(targetID) != app->getLocalNode().getNumID())
   {
      LOG(ERR, "Group is not mapped on this target.", groupID);
      ctx.sendResponse(RemoveBuddyGroupRespMsg(FhgfsOpsErr_INTERNAL));
      return true;
   }

   const int dirFD = openat(Program::getApp()->getTargetFD(targetID, true), ".", O_RDONLY);
   if (dirFD < 0)
   {
      LOG(ERR, "Could not open directory file descriptor.", groupID);
      ctx.sendResponse(RemoveBuddyGroupRespMsg(FhgfsOpsErr_INTERNAL));
      return true;
   }

   const FhgfsOpsErr checkRes = checkChunkDirRemovable(dirFD);

   if (checkRes != FhgfsOpsErr_SUCCESS)
   {
      ctx.sendResponse(RemoveBuddyGroupRespMsg(checkRes));
      return true;
   }

   if (!checkOnly)
   {
      auto* const bgm = Program::getApp()->getMirrorBuddyGroupMapper();
      const NumNodeID localID = Program::getApp()->getLocalNode().getNumID();

      if (!bgm->unmapMirrorBuddyGroup(groupID, localID))
      {
         ctx.sendResponse(RemoveBuddyGroupRespMsg(FhgfsOpsErr_INTERNAL));
         return true;
      }
   }

   ctx.sendResponse(RemoveBuddyGroupRespMsg(FhgfsOpsErr_SUCCESS));
   return true;
}
