#include "DeleteDirEntriesMsgEx.h"

#include <program/Program.h>
#include <common/fsck/FsckDirEntry.h>
#include <toolkit/BuddyCommTk.h>

bool DeleteDirEntriesMsgEx::processIncoming(ResponseContext& ctx)
{
   LOG_DEBUG("DeleteDirEntriesMsg incoming", 4,
      "Received a DeleteDirEntriesMsg from: " + ctx.peerName() );
   LogContext log("DeleteDirEntriesMsgEx");

   MetaStore* metaStore = Program::getApp()->getMetaStore();
   EntryLockStore* entryLockStore = Program::getApp()->getMirroredSessions()->getEntryLockStore();

   FsckDirEntryList& entries = getEntries();
   FsckDirEntryList failedEntries;

   for ( FsckDirEntryListIter iter = entries.begin(); iter != entries.end(); iter++ )
   {
      const std::string& parentID = iter->getParentDirID();
      const std::string& entryName = iter->getName();
      FsckDirEntryType dirEntryType = iter->getEntryType();

      DirIDLock dirLock;
      ParentNameLock dentryLock;

      if (iter->getIsBuddyMirrored())
      {
         dirLock = {entryLockStore, parentID, true};
         dentryLock = {entryLockStore, parentID, entryName};
      }

      DirInode* parentDirInode = metaStore->referenceDir(parentID, iter->getIsBuddyMirrored(),
            true);

      if (!parentDirInode)
      {
         log.log(3,"Failed to delete directory entry; ParentID: " + parentID + "; EntryName: " +
            entryName + " - ParentID does not exist");
         failedEntries.push_back(*iter);
         continue;
      }

      FhgfsOpsErr unlinkRes;

      if (FsckDirEntryType_ISDIR(dirEntryType))
         unlinkRes = parentDirInode->removeDir(entryName, NULL);
      else
         unlinkRes = parentDirInode->unlinkDirEntry(entryName, NULL,
            DirEntry_UNLINK_ID_AND_FILENAME);

      metaStore->releaseDir(parentID);

      if (unlinkRes != FhgfsOpsErr_SUCCESS )
      {
         log.logErr("Failed to delete directory entry; ParentID: " + parentID + "; EntryName: " +
            entryName + "; Err: " + FhgfsOpsErrTk::toErrString(unlinkRes));
          failedEntries.push_back(*iter);
      }
      else if (iter->getIsBuddyMirrored())
         BuddyCommTk::setBuddyNeedsResyncState(true);
   }

   ctx.sendResponse(DeleteDirEntriesRespMsg(&failedEntries) );

   return true;
}
