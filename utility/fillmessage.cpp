#include <iostream>
#include <string>
#include "fillmessage.h"

int utility::FillMessage::FillOneMessage(google::protobuf::Message& oMessage, bool bCanLog) const {
	return FillOneMessage(&oMessage, bCanLog);
}

int utility::FillMessage::FillOneMessage(google::protobuf::Message* pMessage, bool bCanLog) const {
	if (bCanLog) std::cout << "MSG: FillOneMessage begin." << std::endl;
	const auto* pDescriptor = pMessage->GetDescriptor();
	std::cout << pDescriptor->name() << std::endl;
	int iFieldCount = pDescriptor->field_count(), iRet = 0;
	for (int i = 0; i < iFieldCount; i++) {
		const auto* pFieldDescriptor = pDescriptor->field(i);
		std::string sFieldName = pFieldDescriptor->name();
		if (pFieldDescriptor->is_repeated()) {
			std::cout << "num of " << sFieldName << "(s): ";
			int iRepeatedNum = 0;
			std::cin >> iRepeatedNum;
			for (int j = 0; j < iRepeatedNum; j++) {
				auto oContext = utility::MessageContext(pMessage, pFieldDescriptor, j, bCanLog);
				if ((iRet = AddFieldValue(oContext)) != 0) {
					printf("ERR: AddFieldValue failed. iRet %d\n", iRet);
					return 1;
				}
			}
		} else {
			auto oContext = utility::MessageContext(pMessage, pFieldDescriptor, -1, bCanLog);
			if ((iRet = SetFieldValue(oContext)) != 0) {
				printf("ERR: SetFieldValue failed. iRet %d\n", iRet);
				return 2;
			}
		}
	}
	return 0;
}

int utility::FillMessage::SetFieldValue(utility::MessageContext& oContext) const {
	auto &[pMessage, pReflection, pDescriptor, pFieldDescriptor, _, bCanLog] = oContext;
	if (bCanLog) std::cout << "MSG: SetFieldValue, Type " << pFieldDescriptor->type() << std::endl;
	if (pFieldDescriptor->type() == google::protobuf::FieldDescriptor::TYPE_MESSAGE) {
		FillOneMessage(pReflection->MutableMessage(pMessage, pFieldDescriptor), bCanLog);
		return 0;
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
	case google::protobuf::FieldDescriptor::TYPE_UINT32:
		pReflection->SetUInt32(pMessage, pFieldDescriptor, static_cast<uint32_t>(std::stoll(sValue)));
		break;
	case google::protobuf::FieldDescriptor::TYPE_ENUM: { // 有创建变量就要加大括号
		// 注意一个是 Enum，一个是 EnumValue
		const auto* pEnumDescriptor = pFieldDescriptor->enum_type();
		pFieldDescriptor->message_type();
		const auto* pEnumValueDescriptor = pEnumDescriptor->FindValueByName(sValue);
		if (pEnumValueDescriptor == nullptr) {
			printf("ERR: Wrong enum value. enum %s, value %s\n", pFieldDescriptor->name().c_str(), sValue.c_str());
			return 1;
		} else {
			pReflection->SetEnum(pMessage, pFieldDescriptor, pEnumValueDescriptor);
		}
		break;
	}
	default:
		std::cout << "ERR: Wrong field type." << std::endl;
		return 2;
	}
	return 0;
}

int utility::FillMessage::AddFieldValue(utility::MessageContext& oContext) const {
	auto &[pMessage, pReflection, pDescriptor, pFieldDescriptor, index, bCanLog] = oContext;
	if (bCanLog) std::cout << "MSG: AddFieldValue, Type " << pFieldDescriptor->type() << std::endl;
	if (pFieldDescriptor->type() == google::protobuf::FieldDescriptor::TYPE_MESSAGE) {
		FillOneMessage(pReflection->AddMessage(pMessage, pFieldDescriptor), bCanLog);
		return 0;
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
	case google::protobuf::FieldDescriptor::TYPE_UINT32:
		pReflection->AddUInt32(pMessage, pFieldDescriptor, static_cast<uint32_t>(std::stoll(sValue)));
		break;
	case google::protobuf::FieldDescriptor::TYPE_ENUM: {
		// 注意一个是 Enum，一个是 EnumValue
		const auto* pEnumDescriptor = pFieldDescriptor->enum_type();
		pFieldDescriptor->message_type();
		const auto* pEnumValueDescriptor = pEnumDescriptor->FindValueByName(sValue);
		if (pEnumValueDescriptor == nullptr) {
			printf("ERR: Wrong enum value. enum %s, value %s\n", pFieldDescriptor->name().c_str(), sValue.c_str());
			return 1;
		} else {
			pReflection->AddEnum(pMessage, pFieldDescriptor, pEnumValueDescriptor);
		}
		break;
	}
	default:
		std::cout << "ERR: Wrong field type." << std::endl;
		return 2;
	}
	return 0;
}
