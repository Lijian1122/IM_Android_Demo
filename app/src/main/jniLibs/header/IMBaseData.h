#pragma once
#include <string>
#include <iostream>
#include <memory>
#include <tuple> 
#include <functional>
#include "GlobalDefine.h"

#define BIND_CALLBACK_1(func)   std::bind(&func, this, placeholders::_1)
#define BIND_CALLBACK_2(func)	std::bind(&func, this, placeholders::_1, placeholders::_2)

using namespace std;

enum
{
	MKO_STRING = 0,
	MKO_INT,
	MKO_SHARED_VOIDPTR,
	MKO_VOIDPTR,
};

enum IMCALLBACK_TYPE{
	LOGIN,
	GROUPOPERATE,
	SENDMSG,
	RECVMSG,
	DISABLESEND,
    SENDMSG_TOOFAST,
	SENDMSG_FAILED,
	EXIT
};


enum IMIDENTITY_TYPE{
	TEACHER = 1,
	STUDNET,
	ADMIN
};


enum IMSEND_TYPE{
	ABLE_SEND = 1,
	DISABLE_SEND
};

enum IMDISABLESEND_TYPE{
	DISABLESEND_SINGLE = 3,
	DISABLESEND_ALL
};

enum LOGIN_RESCODE
{

	LOGIN_ERROR = -1,
	LOGIN_SCUESS = 0,

	LOGIN_BREAKCONN = 1,
	LOGIN_RECONNECT_OK = 2,
	LOGIN_RECONNECT_ERROR = 3
};

enum GROUP_OPERATE
{
	GROUP_DELETE = 0,
	GROUP_ADD
};

typedef struct _IMUserParam{
	IMIDENTITY_TYPE userTye;
	std::string userID;
	std::string userName;
	std::string	userHeadPortrait;
	std::string groupID;
	std::string userGroup = ""; //������չ
	std::string  serverIp;
	UInt16 port = 8083;
}IMUserParam;


typedef struct _IMLoginDataCallback{
	Int8            result;
	UInt8			server_result;
	UInt8           mySelectedStatus;
	UInt32          serverTime = 0;
	unsigned char		csUserName[128];
	unsigned char		errInfo[128];
}IMLoginDataCallback;


typedef struct _IMGropDataCallback{
	GROUP_OPERATE      changeType;
	UInt32          resCode;
	std::string		userID;
	std::string	    groupID;
}IMGropDataCallback;

//typedef struct _IMMsgDataCallback{
//	IMCALLBACK_TYPE     msgType;
//	UInt32          resCode;
//	std::string		userID;
//	std::string		fromUsername;
//	std::string     fromUserHead;
//	IMIDENTITY_TYPE     fromUserRole;
//	std::string     fromUerGroupID;
//	std::string     fromGroup;
//	std::string     msgTime;
//	std::string     msgcontent;
//}IMMsgDataCallback;

//消息回调
typedef struct _IMMsgDataCallback{
	UInt32          resCode;
	unsigned char		userID[128];
	unsigned char		fromUsername[128];
	unsigned char       fromUserHead[128];
	IMIDENTITY_TYPE     fromUserRole;
	unsigned char     fromUerGroupID[128];
	unsigned char     fromGroup[128];
	unsigned char     msgTime[128];
	unsigned char     msgcontent[1024];
}IMMsgDataCallback;

typedef struct _IMSendMsgCallback{
	UInt32          resCode;
	unsigned char	userID[128];
}IMSendMsgCallback;

/*typedef struct _IMDisableSendMsg{
	IMSEND_TYPE sendType;
	UInt32  resCode = 0;
	IMDISABLESEND_TYPE  forbidType;
	std::string   userId = "";
	std::string   userName = "";
	std::string   forbidtime = "";
}IMDisableSendMsg;*/


//禁言结构体参数
typedef struct _IMDisableSendMsg{
	IMSEND_TYPE sendType;
	UInt32  resCode = 0;
	IMDISABLESEND_TYPE  forbidType;
	unsigned char  userId[128];
	unsigned char  userName[128];
	unsigned char  forbidtime[128];
}IMDisableSendMsg;


typedef void(*IM_CALLBACKFUNC)(IMCALLBACK_TYPE type, void* param);

typedef std::tuple<std::string, Int32, std::shared_ptr<void>, void*> MKO_TUPLE_PARAM;
typedef std::function<void(std::string, MKO_TUPLE_PARAM)> MKODelegate;
