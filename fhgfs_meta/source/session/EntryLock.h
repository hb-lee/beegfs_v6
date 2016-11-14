#ifndef ENTRYLOCK_H_
#define ENTRYLOCK_H_

#include "EntryLockStore.h"

template<typename LockDataT>
class UniqueEntryLockBase
{
   public:
      ~UniqueEntryLockBase()
      {
         if (lockData)
            entryLockStore->unlock(lockData);
      }

      UniqueEntryLockBase(const UniqueEntryLockBase&) = delete;
      UniqueEntryLockBase& operator=(const UniqueEntryLockBase&) = delete;

      UniqueEntryLockBase(UniqueEntryLockBase&& src)
         : entryLockStore(NULL), lockData(NULL)
      {
         swap(src);
      }

      UniqueEntryLockBase& operator=(UniqueEntryLockBase&& src)
      {
         UniqueEntryLockBase(std::move(src)).swap(*this);
         return *this;
      }

      void swap(UniqueEntryLockBase& other)
      {
         std::swap(entryLockStore, other.entryLockStore);
         std::swap(lockData, other.lockData);
      }

   protected:
      typedef UniqueEntryLockBase BaseType;

      template<typename... ArgsT>
      UniqueEntryLockBase(EntryLockStore* entryLockStore, const ArgsT&... args)
         : entryLockStore(entryLockStore)
      {
         lockData = entryLockStore->lock(args...);
      }

      UniqueEntryLockBase()
         : entryLockStore(NULL), lockData(NULL)
      {
      }

   private:
      EntryLockStore* entryLockStore;
      LockDataT* lockData;
};

template<typename LockDataT>
inline void swap(UniqueEntryLockBase<LockDataT>& a, UniqueEntryLockBase<LockDataT>& b)
{
   a.swap(b);
}



class FileIDLock : UniqueEntryLockBase<FileIDLockData>
{
   public:
      FileIDLock() = default;

      FileIDLock(const FileIDLock&) = delete;
      FileIDLock& operator=(const FileIDLock&) = delete;

      FileIDLock(FileIDLock&& src) : BaseType(std::move(src)) {}
      FileIDLock& operator=(FileIDLock&& src)
      {
         BaseType::operator=(std::move(src));
         return *this;
      }

      FileIDLock(EntryLockStore* entryLockStore, const std::string& fileID)
         : UniqueEntryLockBase<FileIDLockData>(entryLockStore, fileID)
      {
      }
};

class DirIDLock : UniqueEntryLockBase<DirIDLockData>
{
   public:
      DirIDLock() = default;

      DirIDLock(const DirIDLock&) = delete;
      DirIDLock& operator=(const DirIDLock&) = delete;

      DirIDLock(DirIDLock&& src) : BaseType(std::move(src)) {}
      DirIDLock& operator=(DirIDLock&& src)
      {
         BaseType::operator=(std::move(src));
         return *this;
      }

      DirIDLock(EntryLockStore* entryLockStore, const std::string& dirID, const bool writeLock)
         : UniqueEntryLockBase<DirIDLockData>(entryLockStore, dirID, writeLock)
      {
      }
};

class ParentNameLock : UniqueEntryLockBase<ParentNameLockData>
{
   public:
      ParentNameLock() = default;

      ParentNameLock(const ParentNameLock&) = delete;
      ParentNameLock& operator=(const ParentNameLock&) = delete;

      ParentNameLock(ParentNameLock&& src) : BaseType(std::move(src)) {}
      ParentNameLock& operator=(ParentNameLock&& src)
      {
         BaseType::operator=(std::move(src));
         return *this;
      }

      ParentNameLock(EntryLockStore* entryLockStore, const std::string& parentID,
            const std::string& name)
         : UniqueEntryLockBase<ParentNameLockData>(entryLockStore, parentID, name)
      {
      }
};

#endif /* ENTRYLOCK_H_ */
