#include "messagetojson.h"

int utility::MessageToJson::ParseMessageToJson(const google::protobuf::Message& oMessage, std::string* pValue, bool bCanLog) const{
	return ParseMessageToJson(oMessage, *pValue, bCanLog);
}

int utility::MessageToJson::ParseMessageToJson(const google::protobuf::Message* pMessage, std::string& sValue, bool bCanLog) const{
	return ParseMessageToJson(*pMessage, sValue, bCanLog);
}

int utility::MessageToJson::ParseMessageToJson(const google::protobuf::Message* pMessage, std::string* pValue, bool bCanLog) const{
	return ParseMessageToJson(*pMessage, *pValue, bCanLog);
}

int utility::MessageToJson::ParseMessageToJson(const google::protobuf::Message& oMessage, std::string& sValue, bool bCanLog) const{
	if (bCanLog) std::cout << "MSG: ParseMessageToJson begin." << std::endl;
	sValue += "{ ";
	const auto* pDescriptor = oMessage.GetDescriptor();
	const auto* pReflection = oMessage.GetReflection();
	int iFieldCount = pDescriptor->field_count(), iRet = 0;
	bool bHasPreOne = false;
	for (int i = 0; i < iFieldCount; i++) {
		const auto *pFieldDescriptor = pDescriptor->field(i);
		// 如果本字段是空的就直接跳过。
		if (!pFieldDescriptor->is_repeated() && !pReflection->HasField(oMessage, pFieldDescriptor) ||
			pFieldDescriptor->is_repeated() && pReflection->FieldSize(oMessage, pFieldDescriptor) == 0) {
			continue;
		}
		if (bHasPreOne) {
			sValue += ", ";
		} else {
			bHasPreOne = true;
		}
		sValue += "\"" + pFieldDescriptor->name() + "\": ";
		if (pFieldDescriptor->is_repeated()) {
			sValue += "[ ";
			int iSize = pReflection->FieldSize(oMessage, pFieldDescriptor); // repeated 字段的元素数量
			for (int j = 0; j < iSize; j++) {
				auto oContext = utility::MessageContext(const_cast<google::protobuf::Message*>(&oMessage), pFieldDescriptor, j, bCanLog);
				if ((iRet = GetRepeatedFieldOneJsonValue(oContext, sValue)) != 0) {
					printf("ERR: GetRepeatedFieldOneJsonValue failed. iRet %d\n", iRet);
					return 1;
				}
				if (j < iSize - 1) {
					sValue += ", ";
				}
			}
			sValue += " ]";
		} else {
			auto oContext = utility::MessageContext(const_cast<google::protobuf::Message*>(&oMessage), pFieldDescriptor, -1, bCanLog);
			if ((iRet = GetOneFieldJsonValue(oContext, sValue)) != 0) {
				printf("ERR: GetOneFieldJsonValue failed. iRet %d\n", iRet);
				return 2;
			}
		}
	}
	sValue += " }";
	return 0;
}

int utility::MessageToJson::GetOneFieldJsonValue(const MessageContext &oContext, std::string& sValue) const {
	const auto [pMessage, pReflection, pDescriptor, pFieldDescriptor, _, bCanLog] = oContext;
	if (bCanLog) std::cout << "MSG: GetOneFieldJsonValue begin." << std::endl;
	switch (pFieldDescriptor->type())
	{
	case google::protobuf::FieldDescriptor::TYPE_MESSAGE:
		ParseMessageToJson(pReflection->GetMessage(*pMessage, pFieldDescriptor), sValue, bCanLog);
		break;
	case google::protobuf::FieldDescriptor::TYPE_BYTES:
	case google::protobuf::FieldDescriptor::TYPE_STRING:
		sValue += "\"" + pReflection->GetString(*pMessage, pFieldDescriptor) + "\"";
		break;
	case google::protobuf::FieldDescriptor::TYPE_UINT32:
		sValue += std::to_string(pReflection->GetUInt32(*pMessage, pFieldDescriptor));
		break;
	case google::protobuf::FieldDescriptor::TYPE_ENUM: {
		const auto *pEnumValueDescriptor = pReflection->GetEnum(*pMessage, pFieldDescriptor);
		sValue += "\"" + pEnumValueDescriptor->name() + "\"";
		break;
	}
	default:
		printf("ERR: Wrong field type. %d\n", pFieldDescriptor->type());
		return 1;
	}
	return 0;
}

int utility::MessageToJson::GetRepeatedFieldOneJsonValue(const MessageContext &oContext, std::string& sValue) const {
	const auto [pMessage, pReflection, pDescriptor, pFieldDescriptor, index, bCanLog] = oContext;
	if (bCanLog) std::cout << "MSG: GetRepeatedFieldOneJsonValue begin." << std::endl;
	switch (pFieldDescriptor->type())
	{
	case google::protobuf::FieldDescriptor::TYPE_MESSAGE:
		ParseMessageToJson(pReflection->GetRepeatedMessage(*pMessage, pFieldDescriptor, index), sValue, bCanLog);
		break;
	case google::protobuf::FieldDescriptor::TYPE_BYTES:
	case google::protobuf::FieldDescriptor::TYPE_STRING:
		sValue += "\"" + pReflection->GetRepeatedString(*pMessage, pFieldDescriptor, index) + "\"";
		break;
	case google::protobuf::FieldDescriptor::TYPE_UINT32:
		sValue += std::to_string(pReflection->GetRepeatedUInt32(*pMessage, pFieldDescriptor, index));
		break;
	case google::protobuf::FieldDescriptor::TYPE_ENUM: {
		const auto *pEnumValueDescriptor = pReflection->GetRepeatedEnum(*pMessage, pFieldDescriptor, index);
		sValue += "\"" + pEnumValueDescriptor->name() + "\"";
		break;
	}
	default:
		printf("ERR: Wrong field type. %d\n", pFieldDescriptor->type());
		return 1;
	}
	return 0;
}