package com.example.lijian.sf_im_sdk;

public class MsgContent {

    private String name;
    private String msgtime;
    private String msgData;

    public MsgContent(){
    }

    public MsgContent(String name, String msgtime ,String msgData) {
        this.name = name;
        this.msgtime = msgtime;
        this.msgData = msgData;

    }
    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getMsgtime() {
        return msgtime;
    }

    public void setMsgtime(String msgtime) {
        this.msgtime = msgtime;
    }

    public String getMsgData() {
        return msgData;
    }

    public void setMsgData(String msgData) {
        this.msgData = msgData;
    }
}
