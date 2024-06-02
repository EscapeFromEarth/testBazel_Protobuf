#pragma once

#include "google/protobuf/message.h"

namespace utility
{

class MessageContext {
public:
	MessageContext(google::protobuf::Message *pMessage, const google::protobuf::FieldDescriptor *pFieldDescriptor,
		int index, bool bCanLog = false) : pMessage(pMessage), pReflection(pMessage->GetReflection()),
		pDescriptor(pMessage->GetDescriptor()), pFieldDescriptor(pFieldDescriptor), index(index), bCanLog(bCanLog) {}
	google::protobuf::Message *pMessage;
	const google::protobuf::Reflection *pReflection;
	const google::protobuf::Descriptor *pDescriptor;
	const google::protobuf::FieldDescriptor *pFieldDescriptor;
	int index;
	bool bCanLog;
};

}
