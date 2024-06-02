#pragma once

#include "google/protobuf/message.h"
#include "singleton.h"
#include "messagecontext.h"

namespace utility {

class FillMessage {
	Singleton(FillMessage);

public:
	int FillOneMessage(google::protobuf::Message& oMessage, bool bCanLog) const;
	int FillOneMessage(google::protobuf::Message* pMessage, bool bCanLog) const;
private:
	int SetFieldValue(MessageContext& oContext) const;
	int AddFieldValue(MessageContext& oContext) const;
};


}
