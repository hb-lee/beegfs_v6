#ifndef FSCKSETEVENTLOGGINGRESPMSG_H
#define FSCKSETEVENTLOGGINGRESPMSG_H

#include <common/net/message/NetMessage.h>
#include <common/toolkit/ListTk.h>
#include <common/toolkit/serialization/Serialization.h>

class FsckSetEventLoggingRespMsg: public NetMessageSerdes<FsckSetEventLoggingRespMsg>
{
   public:
      FsckSetEventLoggingRespMsg(bool result, bool loggingEnabled, bool missedEvents) :
         BaseType(NETMSGTYPE_FsckSetEventLoggingResp),
         result(result),
         loggingEnabled(loggingEnabled),
         missedEvents(missedEvents)
      { }

      FsckSetEventLoggingRespMsg() : BaseType(NETMSGTYPE_FsckSetEventLoggingResp)
      { }

   private:
      bool result;
      bool loggingEnabled;
      bool missedEvents;

   public:
      bool getResult() const { return result; }
      bool getLoggingEnabled() const { return loggingEnabled; }
      unsigned getMissedEvents() const { return this->missedEvents; }

      // inliner
      virtual TestingEqualsRes testingEquals(NetMessage* msg)
      {
         FsckSetEventLoggingRespMsg* msgIn = (FsckSetEventLoggingRespMsg*) msg;

         if (this->result != msgIn->getResult())
            return TestingEqualsRes_FALSE;

         if (this->loggingEnabled != msgIn->getLoggingEnabled())
            return TestingEqualsRes_FALSE;

         if (this->missedEvents != msgIn->getMissedEvents())
            return TestingEqualsRes_FALSE;

         return TestingEqualsRes_TRUE;
      }

      template<typename This, typename Ctx>
      static void serialize(This obj, Ctx& ctx)
      {
         ctx
            % obj->result
            % obj->loggingEnabled
            % obj->missedEvents;
      }
};

#endif /*FSCKSETEVENTLOGGINGRESPMSG_H*/
