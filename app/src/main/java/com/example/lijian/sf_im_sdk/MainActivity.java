package com.example.lijian.sf_im_sdk;

import android.content.Context;
import android.os.Message;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.Button;
import android.widget.EditText;
import android.view.View;
import android.widget.ListAdapter;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import android.os.Handler;

public class MainActivity extends AppCompatActivity implements  OnUpdateUiInterface {

    //IM_SDK m_IM_SDK = new IM_SDK();
    //OncallBackListener m_listener =  new OncallBackListener();
    TextView loginStateView;
    List<MsgContent> list = new ArrayList<>();
    MsgItemAdapter itemAdapter;

    MsgContent MsgItem = new MsgContent();
    TimerUtils timerUtils = new TimerUtils();

    private Handler mHandlerUI = new Handler(){
        public void handleMessage(Message  msg) {
            Bundle dataBundle = msg.getData();
            if (dataBundle == null)
                return;
            int Type = dataBundle.getInt("type");

            switch (Type){
                case 0:
                    int state = dataBundle.getInt("state");
                    switch (state){
                        case -1: {
                            loginStateView.setText("直播互动              连互动服务失败");
                            break;
                        }
                        case 0:{
                            loginStateView.setText("直播互动              已连上互动服务");
                            break;
                        }
                        case 1:{
                            loginStateView.setText("直播互动              检测到断开互动服务，正在重连");
                            break;
                        }
                        case 2:{
                            loginStateView.setText("直播互动              已重连到互动服务");
                            break;
                        }
                        case 3:{
                            loginStateView.setText("直播互动              网络异常，重连到互动服务失败");
                            break;
                        }
                    }
                    break;
                case 3:
                    MsgContent m_Item = new MsgContent();
                    m_Item.setName(dataBundle.getString("name"));
                    m_Item.setMsgtime(dataBundle.getString("msgTime"));
                    m_Item.setMsgData(dataBundle.getString("msgData"));
                    list.add(m_Item);
                    itemAdapter.notifyDataSetChanged();
                    break;
            }
            //msg.recycle();
        }
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        loginStateView = findViewById(R.id.sample_text);

        itemAdapter = new MsgItemAdapter(MainActivity.this ,R.layout.item , list);
        ListView listView = (ListView) findViewById(R.id.listview);
        listView.setAdapter(itemAdapter);
        //Global.getInstance().getIm_SDK().setCalReCallBackListenner(new OnGetInterface()
        Global.getInstance().setCallback(new OnGetInterface(){
            @Override
            public void AddItem(MsgContent item) {
                UpdateUIInterface(item);
            }
            public void GetLoginStaete(int state){
                UpdateLoginInterface(state);
            }
       });
        loginStateView.setText("直播互动              正在连互动服务");

        Global.getInstance().getIm_SDK().ConnectMsgServer();

        System.out.println("开始连接服务");
        System.out.println("连接服务完成");

        //发送消息
        Button  sendBtn = findViewById(R.id.bt1);
        sendBtn.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                EditText m_edit = findViewById(R.id.et);

                String msgData = m_edit.getText().toString();

                if(!msgData.isEmpty())
                {
                    Global.getInstance().getIm_SDK().SendMsg(msgData,msgData.length());
                    m_edit.setText("");

                    int serverTime =Global.getInstance().getIm_SDK().GetServerTime();
                    String timeStr =Long.toString(serverTime);

                    MsgContent item = new MsgContent("lijian " ,timeStr,msgData);

                    System.out.println("serverTime  6666:"+ serverTime);

                    list.add(item);
                    itemAdapter.notifyDataSetChanged();
                }else
                {
                    Toast.makeText(MainActivity.this, "发送消息不允许为空!", Toast.LENGTH_LONG).show();
                }
                }
        });

        //禁言
        Button  forbBtn = findViewById(R.id.bt2);
        forbBtn.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {

                //System.out.println("开始连接服务");
               // Global.getInstance().getIm_SDK().ConnectMsgServer();
               // System.out.println("连接服务完成");
                // m_IM_SDK.ForbidSendMsg(1, 4, "02", "02", "600");
                    //m_IM_SDK.ForbidSendMsg(2, 4, "02", "02", "600");
            }
        });

        //断开服务
        Button  disconnBtn = findViewById(R.id.bt3);
        disconnBtn.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {

                Global.getInstance().getIm_SDK().DisConnServer();
                finish();
            }
        });
    }
    public void UpdateUIInterface(MsgContent msgContent){
        Message msg = new Message();

        //Message.obtain(mHandlerUI, 1, msgContent).sendToTarget();

        Bundle dataBundle = new Bundle();
        dataBundle.putInt("type",3);
        dataBundle.putString("name",msgContent.getName());
        dataBundle.putString("msgTime",msgContent.getMsgtime());
        dataBundle.putString("msgData",msgContent.getMsgData());
        msg.setData(dataBundle);
        mHandlerUI.sendMessage(msg);
        return;
    }

    public void UpdateLoginInterface(int state){
        Message msg = new Message();
        Bundle dataBundle = new Bundle();
        dataBundle.putInt("type",0);
        dataBundle.putInt("state",state);
        msg.setData(dataBundle);
        mHandlerUI.sendMessage(msg);
        return;
    }
    private void initList() {
        for (int i = 0; i < 100; i++) {
            MsgContent item = new MsgContent("lijian " ,"413441341343434","北京三海教育科技有限公司666");
            list.add(item);
        }
    }
}