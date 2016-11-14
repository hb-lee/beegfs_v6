#include <common/toolkit/tree/MirrorBuddyGroupMap.h>
#include <common/toolkit/tree/MirrorBuddyGroupMapIter.h>

MirrorBuddyGroupMapIter MirrorBuddyGroupMap_find(MirrorBuddyGroupMap* this,
   const uint16_t searchKey)
{
   RBTreeElem* treeElem = _PointerRBTree_findElem(
      (RBTree*)this, (const void*)(const size_t)searchKey);

   MirrorBuddyGroupMapIter iter;
   MirrorBuddyGroupMapIter_init(&iter, this, treeElem);

   return iter;
}

MirrorBuddyGroupMapIter MirrorBuddyGroupMap_begin(MirrorBuddyGroupMap* this)
{
   RBTreeElem* treeElem = container_of(rb_first(&this->rbTree.treeroot), RBTreeElem, treenode);

   MirrorBuddyGroupMapIter iter;
   MirrorBuddyGroupMapIter_init(&iter, this, treeElem);

   return iter;
}
