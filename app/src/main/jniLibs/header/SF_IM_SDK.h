/*****************************************************
******************************************************/
#include "IMBaseData.h"
#include <string>

using namespace std;

class SF_IM_SDK
{
public:

	~SF_IM_SDK();

	/*
	*/
	static SF_IM_SDK* GetInstance();

	/*
	*/
	int InitInstance(void *UserInfo, IM_CALLBACKFUNC callback);

    int InitInstance(IMIDENTITY_TYPE userTye,
		             const char* userID,
		             const char* userName,
		             const char* groupID,
		             const char* userGroup,
		             const char* serverIp,
		             const char* userHeadPortrait,
		             UInt32 port,IM_CALLBACKFUNC callback);
	/*
	*/
	int ConnectMsgServer();

	/*
	*/
	int SendMsg(const char *msgdata ,int size);

	/*
	*/
	int DeleteGroup(const char *groupId);

	/*
	*/
	int ForbidSendMsg(IMDisableSendMsg *disableSendMsg);

	int ForbidSendMsg(int send_Type , int forbidType ,const char* userID, const char*  userNname, const char* time);

	/*
	*/
	int GetSyncServerTime();

	/*
	*/
	void CloseSocket();

	/*
	*/
	int ExitInstance();

	static void GetIMData(IMCALLBACK_TYPE type, void* param);

private:
	SF_IM_SDK();
	
	void InitLog();

	void MKOForTcpClientModuleCallBack(const std::string& keyId, MKO_TUPLE_PARAM mkoParam);

	void MKOForLoginModuleCallBack(const std::string& keyId, MKO_TUPLE_PARAM mkoParam);

	void MKOForSessionModuleCallback(const std::string& keyId, MKO_TUPLE_PARAM mkoParam);

public:

      const char* strstr;
private:

    bool firstConnFlag;

	bool sendMsgFlag;

	static SF_IM_SDK* theApp;

	IMUserParam *m_userInfo;

	IM_CALLBACKFUNC m_IMcallback;

	IMLoginDataCallback *m_logincallback;

	IMSendMsgCallback *m_sendMsgcallback;
};

