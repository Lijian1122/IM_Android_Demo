//
// Created by Administrator on 2019/4/9.
//
#include "com_example_lijian_sf_im_sdk_IM_SDK.h"
#include <Android/log.h>
#include "IMBaseData.h"
#include "SF_IM_SDK.h"
#include <pthread.h>
#include "stddef.h"
#include <stdio.h>
#include <stdlib.h>

#define TAG "android_jni"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG ,__VA_ARGS__)

JavaVM *g_jvm = NULL;
jobject g_obj = NULL;
jlong result;
pthread_t im_p;
JNIEnv *g_env = NULL;
void *getCallback(void *p);
void GetIMCallbackData(IMCALLBACK_TYPE type, void* param);
jstring str2jstring(JNIEnv* env,const char* pat);


JNIEXPORT jint JNICALL
Java_com_example_lijian_sf_1im_1sdk_IM_1SDK_InitSDK(JNIEnv *env,jobject obj, jint type, jstring userID ,jstring userName,jstring groupID,
                                                    jstring userGroup,jstring serverIp,jstring userHeadPortrait,jint port)
{
         jint resCode = 0;

         env->GetJavaVM(&g_jvm);
         g_obj = env->NewGlobalRef(obj);
         g_env = env;
         result =(jlong)SF_IM_SDK::GetInstance();

         if(result == 0)
         {
            resCode = -1;
            return resCode;
         }
         const char* m_userID = env->GetStringUTFChars(userID, NULL);
         const char* m_userName = env->GetStringUTFChars(userName, NULL);
         const char* m_groupID = env->GetStringUTFChars(groupID, NULL);
         const char* m_userGroup = env->GetStringUTFChars(userGroup, NULL);
         const char* m_serverIp = env->GetStringUTFChars(serverIp, NULL);
         const char* m_userHeadPortrait = env->GetStringUTFChars(userHeadPortrait, NULL);

         int m_type = (int)type;
         int m_port = (int)port;

         resCode =  ((SF_IM_SDK*)result)->InitInstance((IMIDENTITY_TYPE)m_type,m_userID,m_userName, m_groupID,m_userGroup, m_serverIp,
         m_userHeadPortrait, m_port ,GetIMCallbackData);

         return resCode;
}

/*
 * Class:     com_example_lijian_sf_im_sdk_IM_SDK
 * Method:    ConnectMsgServer
 * Signature: (J)V
 */
JNIEXPORT void JNICALL
Java_com_example_lijian_sf_1im_1sdk_IM_1SDK_ConnectMsgServer(JNIEnv *env, jobject obj)
{
       LOGI("开始连服务1111");
      ((SF_IM_SDK*)result)->ConnectMsgServer();
       LOGI("开始连服务2222");
}

/*
 * Class:     com_example_lijian_sf_im_sdk_IM_SDK
 * Method:    SendMsg
 * Signature: (JLjava/lang/String;I)V
 */
JNIEXPORT void JNICALL
Java_com_example_lijian_sf_1im_1sdk_IM_1SDK_SendMsg(JNIEnv *env, jobject obj, jstring msgData, jint length)
{
     const char* m_msg = env->GetStringUTFChars(msgData, NULL);
     ((SF_IM_SDK*)result)->SendMsg(m_msg,(int)length);
}

/*
 * Class:     com_example_lijian_sf_im_sdk_IM_SDK
 * Method:    ForbidSendMsg
 * Signature: (JIILjava/lang/String;Ljava/lang/String;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL
Java_com_example_lijian_sf_1im_1sdk_IM_1SDK_ForbidSendMsg
  (JNIEnv *env, jobject obj, jint send_Type, jint forbidType, jstring userID, jstring userName, jstring time)
  {
           const char* m_userID = env->GetStringUTFChars(userID, NULL);
           const char* m_userName = env->GetStringUTFChars(userName, NULL);
           const char* m_time = env->GetStringUTFChars(time, NULL);
           ((SF_IM_SDK*)result)->ForbidSendMsg((int)send_Type ,(int)forbidType ,m_userID,m_userName,m_time);
  }

/*
 * Class:     com_example_lijian_sf_im_sdk_IM_SDK
 * Method:    DisonnServer
 * Signature: (J)V
 */
JNIEXPORT void JNICALL
Java_com_example_lijian_sf_1im_1sdk_IM_1SDK_DisConnServer(JNIEnv *env, jobject)
{
    // ((SF_IM_SDK*)result)->ExitInstance();
    ((SF_IM_SDK*)result)->CloseSocket();
}

JNIEXPORT void JNICALL
Java_com_example_lijian_sf_1im_1sdk_IM_1SDK_ExitSDK(JNIEnv *, jobject)
{
   ((SF_IM_SDK*)result)->CloseSocket();
   ((SF_IM_SDK*)result)->ExitInstance();
}

JNIEXPORT jint JNICALL
Java_com_example_lijian_sf_1im_1sdk_IM_1SDK_GetServerTime(JNIEnv *env, jobject)
{
        int ServerTime = ((SF_IM_SDK*)result)->GetSyncServerTime();
        return ServerTime;
}

/*JNIEXPORT void JNICALL
Java_com_example_lijian_sf_1im_1sdk_IM_1SDK_OnIMCallbackListener(JNIEnv *env, jobject thiz, jobject jcallback)
{
    env->GetJavaVM(&g_jvm);
    jobject  callback = env->NewGlobalRef(jcallback);
    //pthread_create(&im_p,NULL, getCallback,callback);
    return;
}*/

void GetIMCallbackData(IMCALLBACK_TYPE type, void* param)
{
      LOGI("IM callbackTpoe ; %d", (int)type);

      JNIEnv *env;
      //获取当前native线程是否有没有被附加到jvm环境中
      int getEnvStat = g_jvm->GetEnv((void **)&env ,JNI_VERSION_1_4);
      if (getEnvStat == JNI_EDETACHED)
      {
          //如果没有， 主动附加到jvm环境中，获取到env
          if (g_jvm->AttachCurrentThread(&env, NULL) != 0) {
                return;
         }
      }
      switch (type)
      {
           //登录结果回调
      	  case IMCALLBACK_TYPE::LOGIN:
      	  {
      	       IMLoginDataCallback *m_callback = (IMLoginDataCallback *)param;
               LOGI("IM callbackTyep ; %d", m_callback->result);

               jclass jSdkClass = env->GetObjectClass(g_obj);
               int resType = (int)m_callback->result;
               jmethodID javaCallback = env->GetMethodID(jSdkClass, "OnGetLoginState", "(I)V");

               env->CallVoidMethod(g_obj, javaCallback, resType);
      	       break;
           }
      	   //发消息回调
      	   case IMCALLBACK_TYPE::SENDMSG:
      	  {
      	     IMSendMsgCallback *m_callback = (IMSendMsgCallback *)param;
      	        LOGI("IM callbackTyep ; %d", m_callback->resCode);

                jclass jSdkClass = env->GetObjectClass(g_obj);
                int resType = (int)m_callback->resCode;

                jmethodID javaCallback = env->GetMethodID(jSdkClass, "onSendMsgData", "(ILjava/lang/String;)V");

                jstring	userID = str2jstring(env,(const char*)m_callback->userID);
                env->CallVoidMethod(g_obj, javaCallback, resType,userID);
      		    break;
      	  }
      		//群操作回调
      	  case IMCALLBACK_TYPE::GROUPOPERATE:
      	 {
      			 break;
      	  }
      	  //接收消息回调
      	  case IMCALLBACK_TYPE::RECVMSG:
      	 {
            IMMsgDataCallback *m_callback = (IMMsgDataCallback *)param;
            unsigned char* msgdata = m_callback->msgcontent;
            jstring  content =  str2jstring(env,(const char*)msgdata);

            jstring  content6 = env->NewStringUTF((const char*)msgdata);

            //str = jstringToWindows(env, (const char*)msgdata);
            //printf("The string in C code %s/n",str);
            //jstring tostring = WindowsTojstring(env,str);

            LOGI("IM callbackTyep666 ; %s", msgdata);

            jclass jSdkClass = env->GetObjectClass(g_obj);
            jmethodID javaCallback = env->GetMethodID(jSdkClass, "onGetMsgData", "(IILjava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");

            jstring	userID = str2jstring(env,(const char*)m_callback->userID);
            jstring	fromUsername = str2jstring(env,(const char*)m_callback->fromUsername);
            jstring fromUserHead = str2jstring(env,(const char*)m_callback->fromUserHead);
            jstring fromUerGroupID = str2jstring(env,(const char*)m_callback->fromUerGroupID);
            jstring fromGroup = str2jstring(env,(const char*)m_callback->fromGroup);
            jstring msgTime = str2jstring(env,(const char*)m_callback->msgTime);

            int  resCode = (int)m_callback->resCode;
            int  roleType = (int)m_callback->fromUserRole;

            env->CallVoidMethod(g_obj, javaCallback,resCode,roleType ,userID,fromUsername,fromUserHead,fromUerGroupID,fromGroup,msgTime,content);
      		break;
      	  }
          //禁言回调
          case IMCALLBACK_TYPE::DISABLESEND:
      	  {
               IMDisableSendMsg *m_disableSend = (IMDisableSendMsg *)param;

               jstring  name =  str2jstring(env,(const char*)m_disableSend->userName);
               jstring  userId =  str2jstring(env,(const char*)m_disableSend->userId);
               jstring  forbidtime =  str2jstring(env,(const char*)m_disableSend->forbidtime);

                jclass jSdkClass = env->GetObjectClass(g_obj);
                jmethodID javaCallback = env->GetMethodID(jSdkClass, "onGetDisableSend", "(IIILjava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");


               int sendType = (int)m_disableSend->sendType;
               int redCode = (int)m_disableSend->resCode;
               int forbidType = (int)m_disableSend->forbidType;

               env->CallVoidMethod(g_obj, javaCallback,sendType,redCode,forbidType ,userId,name,forbidtime);
      		   break;
      	   }

      	   //退出
      	   case IMCALLBACK_TYPE::EXIT:
      	        //g_jvm->DetachCurrentThread();
      	        break;
      	}

        //Detach主线程
      	if (g_jvm->DetachCurrentThread() != JNI_OK)
      	{
            LOGI("%s: DetachCurrentThread() failed", __FUNCTION__);
        }
}

jstring str2jstring(JNIEnv* env,const char* pat)
{
    //定义java String类 strClass
    jclass strClass = (env)->FindClass("java/lang/String");
    //获取String(byte[],String)的构造器,用于将本地byte[]数组转换为一个新String
    jmethodID ctorID = (env)->GetMethodID(strClass, "<init>", "([BLjava/lang/String;)V");
    //建立byte数组
    jbyteArray bytes = (env)->NewByteArray(strlen(pat));
    //将char* 转换为byte数组
    (env)->SetByteArrayRegion(bytes, 0, strlen(pat), (jbyte*)pat);
    // 设置String, 保存语言类型,用于byte数组转换至String时的参数
    jstring encoding = (env)->NewStringUTF("utf-8");  //GB2312
    //将byte数组转换为java String,并输出
    return (jstring)(env)->NewObject(strClass, ctorID, bytes, encoding);
}

void *getCallback(void *p)
{
   JNIEnv *env;
   jboolean  mNeedDetach;

   if(p == NULL)
        return p;
    //获取当前native线程是否有没有被附加到jvm环境中
    int getEnvStat = g_jvm->GetEnv((void **)&env ,JNI_VERSION_1_4);
    if (getEnvStat == JNI_EDETACHED) {
    //如果没有， 主动附加到jvm环境中，获取到env
    if (g_jvm->AttachCurrentThread(&env, NULL) != 0) {
          return p;
    }
    mNeedDetach = JNI_TRUE;
     }
    //强转回来
    jobject jcallback = (jobject)p;
    //通过强转后的jcallback 获取到要回调的类
    jclass javaClass = env->GetObjectClass(jcallback);
    if (javaClass == 0)
    {
          //LOG("Unable to find class");
           g_jvm->DetachCurrentThread();
           return p;
     }
      //获取要回调的方法ID
     //jmethodID javaCallbackId = env->GetMethodID(javaClass,"onGetCallbackData","(II)V");
     //jmethodID javaCallbackId= env->GetMethodID(javaClass,"onGetStr","(Ljava/lang/String;)V");
      jmethodID javaCallbackId= env->GetMethodID(javaClass,"onGetLong","(JJ)V");

    if (javaCallbackId == NULL)
    {
               //LOGD("Unable to find method:onProgressCallBack");
            return p;
     }
      //执行回调

     //jstring param = env->NewStringUTF("C中调用Java的String参数方法");
     jlong parm1 = 666666;
     jlong parm2 = 888888;
     env->CallVoidMethod(jcallback, javaCallbackId,parm1,parm2);
     //env->CallVoidMethod(jcallback, javaCallbackIdS,"12345678");

      //释放当前线程
    if(mNeedDetach) {
        g_jvm->DetachCurrentThread();
    }
    //释放你的全局引用的接口，生命周期自己把控
    //env->DeleteGlobalRef(jcallback);
    //env = NULL;
    return p;
}

