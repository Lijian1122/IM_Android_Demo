package com.example.lijian.sf_im_sdk;

import android.widget.ListView;
import android.widget.TextView;
import java.io.UnsupportedEncodingException;
import java.util.ArrayList;
import java.util.List;
import android.os.Handler;

public class IM_SDK {

    static {
        System.loadLibrary("SF_IM_SDK");
        //System.loadLibrary("Android_IM_SDK");
    }

    public IM_SDK(){

        m_callback = new OnGetInterface() {
            @Override
            public void AddItem(MsgContent item) {
            }

            @Override
            public void GetLoginStaete(int state) {
            }
            };
     }

    public void setCalReCallBackListenner(OnGetInterface callback){
      this.m_callback = callback;
    }

    //登录状态回调LOGIN_RESCODE rescode
    public void OnGetLoginState(int rescode){
        System.out.println("登录状态回调： " + rescode);
        this.m_callback.GetLoginStaete(rescode);
        return;
    }

    //接收消息
    public void onGetMsgData(int resCode,int fromUserRole,String userID,String	fromUsernam,String fromUserHead,String  fromUerGroupID,String  fromGroup,String   msgTime,String   msgcontent)
    {
        System.out.println("消息内容： " + msgcontent + "名字： " + userID + "时间 " + msgTime );
        MsgContent item = new MsgContent(fromUsernam,msgTime,msgcontent);
        m_callback.AddItem(item);
    }

    //发消息回调
    public void onSendMsgData(int resCode,String userID)
    {
        System.out.println("消息内容： " + resCode + "名字： " + userID);
        return;
    }

    //接收禁言消息
    public void onGetDisableSend(int sendType, int resCode ,int forbidType, String userId, String username, String time){

        System.out.println("禁言66： " + username + "时间 " + time +  "禁言类型:" +  sendType );
    }

    OnGetInterface m_callback;

    public native int InitSDK(int type, String userID ,String userName, String groupID,
                                String userGroup,String serverIp,String userHeadPortrait,int port);

    public native void ConnectMsgServer();

    public native void SendMsg(String msgdata ,int size);

    public native void ForbidSendMsg(int send_Type , int forbidType ,String userID, String userNname, String time);

    public native void DisConnServer();

    public native int GetServerTime();

    public native void ExitSDK();

    //public native void OnIMCallbackListener(OncallBackListener listener);
}
