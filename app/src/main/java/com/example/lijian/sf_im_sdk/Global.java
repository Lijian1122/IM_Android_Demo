package com.example.lijian.sf_im_sdk;

import android.app.Application;

public class Global extends Application {
    public IM_SDK m_IM_SDK;
    private static Global myGlobal;
    @Override
    public void onCreate() {
        super.onCreate();
        System.out.println("开始初始化");
        m_IM_SDK = new IM_SDK();
        m_IM_SDK.InitSDK(1, "668", "lijian", "22",
                "2", "192.168.1.206", "1344", 8084);
        System.out.println("初始化完成");
        myGlobal = this;
    }

    //private final static Global myGlobal = new Global();
    public static Global getInstance(){
      return myGlobal;
    }
    public IM_SDK getIm_SDK(){
        //m_IM_SDK.ConnectMsgServer();
        return m_IM_SDK;
    }

    public void setCallback(OnGetInterface callback){
        m_IM_SDK.setCalReCallBackListenner(callback);
    }
}
