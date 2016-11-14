#ifndef REMOVEBUDDYGROUPMSG_H_
#define REMOVEBUDDYGROUPMSG_H_

#include <common/Common.h>
#include <common/net/message/AcknowledgeableMsg.h>
#include <common/nodes/Node.h>

class RemoveBuddyGroupMsg : public NetMessageSerdes<RemoveBuddyGroupMsg>
{
   public:
      RemoveBuddyGroupMsg(NodeType type, uint16_t groupID, bool checkOnly):
         BaseType(NETMSGTYPE_RemoveBuddyGroup), type(type), groupID(groupID), checkOnly(checkOnly)
      {
      }

      template<typename This, typename Ctx>
      static void serialize(This obj, Ctx& ctx)
      {
         ctx
            % serdes::as<int32_t>(obj->type)
            % obj->groupID
            % obj->checkOnly;
      }

   protected:
      RemoveBuddyGroupMsg() : BaseType(NETMSGTYPE_RemoveNode)
      {
      }

   protected:
      NodeType type;
      uint16_t groupID;
      bool checkOnly;
};

#endif
