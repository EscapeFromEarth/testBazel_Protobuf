#include <iostream>
#include <string>
#include "proto/test.pb.h"

// 为了简化操作，允许的(protobuf)类型有 bytes、string、uint32、enum。

const bool bCanLog = 0;

void FillOneMessage(google::protobuf::Message* pMessage);

void SetFieldValue(const google::protobuf::Reflection* pReflection, google::protobuf::Message* pMessage, const google::protobuf::FieldDescriptor* pFieldDescriptor) {
	if (bCanLog) std::cout << "MSG: SetFieldValue, Type " << pFieldDescriptor->type() << std::endl;
	if (pFieldDescriptor->type() == google::protobuf::FieldDescriptor::TYPE_MESSAGE) {
		FillOneMessage(pReflection->AddMessage(pMessage, pFieldDescriptor));
		return;
	}
	std::string sValue;
	std::cout << pFieldDescriptor->name() << ": ";
	std::cin >> sValue;
	switch (pFieldDescriptor->type())
	{
	case google::protobuf::FieldDescriptor::TYPE_STRING:
	case google::protobuf::FieldDescriptor::TYPE_BYTES:
		pReflection->SetString(pMessage, pFieldDescriptor, sValue);
		break;
	case google::protobuf::FieldDescriptor::TYPE_FIXED32:
		pReflection->SetUInt32(pMessage, pFieldDescriptor, static_cast<uint32_t>(std::stoll(sValue)));
		break;
	case google::protobuf::FieldDescriptor::TYPE_ENUM: { // 有创建变量就要加大括号
		// 注意一个是 Enum，一个是 EnumValue
		const auto* pEnumDescriptor = pFieldDescriptor->enum_type();
		pFieldDescriptor->message_type();
		const auto* pEnumValueDescriptor = pEnumDescriptor->FindValueByName(sValue);
		if (pEnumValueDescriptor == nullptr) {
			printf("ERR: Wrong enum value. enum %s, value %s", pFieldDescriptor->name().c_str(), sValue.c_str());
			exit(0);
		} else {
			pReflection->SetEnum(pMessage, pFieldDescriptor, pEnumValueDescriptor);
		}
		break;
	}
	default:
		std::cout << "ERR: Wrong field type." << std::endl;
		exit(0);
	}
}

void AddFieldValue(const google::protobuf::Reflection* pReflection, google::protobuf::Message* pMessage, const google::protobuf::FieldDescriptor* pFieldDescriptor) {
	if (bCanLog) std::cout << "MSG: AddFieldValue, Type " << pFieldDescriptor->type() << std::endl;
	if (pFieldDescriptor->type() == google::protobuf::FieldDescriptor::TYPE_MESSAGE) {
		FillOneMessage(pReflection->AddMessage(pMessage, pFieldDescriptor));
		return;
	}
	std::string sValue;
	std::cout << pFieldDescriptor->name() << ": ";
	std::cin >> sValue;
	switch (pFieldDescriptor->type())
	{
	case google::protobuf::FieldDescriptor::TYPE_STRING:
	case google::protobuf::FieldDescriptor::TYPE_BYTES:
		pReflection->AddString(pMessage, pFieldDescriptor, sValue);
		break;
	case google::protobuf::FieldDescriptor::TYPE_FIXED32:
		pReflection->AddUInt32(pMessage, pFieldDescriptor, static_cast<uint32_t>(std::stoll(sValue)));
		break;
	case google::protobuf::FieldDescriptor::TYPE_ENUM: {
		// 注意一个是 Enum，一个是 EnumValue
		const auto* pEnumDescriptor = pFieldDescriptor->enum_type();
		pFieldDescriptor->message_type();
		const auto* pEnumValueDescriptor = pEnumDescriptor->FindValueByName(sValue);
		if (pEnumValueDescriptor == nullptr) {
			printf("ERR: Wrong enum value. enum %s, value %s", pFieldDescriptor->name().c_str(), sValue.c_str());
			exit(0);
		} else {
			pReflection->AddEnum(pMessage, pFieldDescriptor, pEnumValueDescriptor);
		}
		break;
	}
	default:
		std::cout << "ERR: Wrong field type." << std::endl;
		exit(0);
	}
}

void FillOneMessage(google::protobuf::Message* pMessage) {
	const auto* pReflection = pMessage->GetReflection();
	const auto* pDescriptor = pMessage->GetDescriptor();
	if (bCanLog) std::cout << "MSG: FillOneMessage" << std::endl;
	std::cout << pDescriptor->name() << std::endl;
	int iFieldCount = pDescriptor->field_count();
	for (int i = 0; i < iFieldCount; i++) {
		const auto* pFieldDescriptor = pDescriptor->field(i);
		std::string sFieldName = pFieldDescriptor->name();
		if (pFieldDescriptor->is_repeated()) {
			std::cout << "num of " << sFieldName << "(s): ";
			int iRepeatedNum = 0;
			std::cin >> iRepeatedNum;
			for (int i = 0; i < iRepeatedNum; i++) {
				AddFieldValue(pReflection, pMessage, pFieldDescriptor);
			}
		} else {
			SetFieldValue(pReflection, pMessage, pFieldDescriptor);
		}
	}
}


int main() {
	std::cout << "hello world!" << std::endl;
	Test::Group oGroup;
	FillOneMessage(&oGroup);
	std::cout << oGroup.DebugString() << std::endl;
	
	return 0;
}