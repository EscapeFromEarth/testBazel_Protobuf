#include <iostream>
#include "utility/fillmessage.h"
#include "utility/messagetojson.h"
#include "proto/test.pb.h"

const bool bCanLog = false;

int main() {
	std::cout << "hello world!" << std::endl;
	std::cout << "------------------------------------" << std::endl;
	Test::Group oGroup;
	int iRet = 0;
	if ((iRet = utility::FillMessage::GetSingleton()->FillOneMessage(&oGroup, bCanLog)) != 0) {
		printf("ERR: FillOneMessage failed. iRet %d\n", iRet);
		return 1;
	}
	std::cout << "------------------------------------" << std::endl;
	std::string sJsonValue;
	if ((iRet = utility::MessageToJson::GetSingleton()->ParseMessageToJson(oGroup, sJsonValue, bCanLog)) != 0) {
		printf("ERR: ParseMessageToJson failed. iRet %d\n", iRet);
		return 2;
	}
	std::cout << sJsonValue << std::endl;
	std::cout << "------------------------------------" << std::endl;
	std::cout << oGroup.DebugString() << std::endl;
	
	return 0;
}