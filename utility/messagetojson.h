#pragma once

#include "google/protobuf/message.h"
#include "singleton.h"
#include "messagecontext.h"
#include <string>

namespace utility
{

class MessageToJson {
	Singleton(MessageToJson);	

public:
	int ParseMessageToJson(const google::protobuf::Message& oMessage, std::string& sValue, bool bCanLog) const;
	int ParseMessageToJson(const google::protobuf::Message& oMessage, std::string* pValue, bool bCanLog) const;
	int ParseMessageToJson(const google::protobuf::Message* pMessage, std::string& sValue, bool bCanLog) const;
	int ParseMessageToJson(const google::protobuf::Message* pMessage, std::string* pValue, bool bCanLog) const;
private:
	int GetOneFieldJsonValue(const MessageContext &oContext, std::string& sValue) const;
	int GetRepeatedFieldOneJsonValue(const MessageContext &oContext, std::string& sValue) const;
};

}

