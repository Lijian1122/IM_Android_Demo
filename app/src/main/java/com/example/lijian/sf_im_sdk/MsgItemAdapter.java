package com.example.lijian.sf_im_sdk;

import android.content.Context;
import android.support.annotation.NonNull;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.TextView;
import java.util.List;
import java.text.SimpleDateFormat;
import java.util.Date;


public class MsgItemAdapter extends  ArrayAdapter<MsgContent> {

    private int layoutId;

    TimerUtils timerUtils = new TimerUtils();

    public MsgItemAdapter(Context context, int layoutId, List<MsgContent> list) {
        super(context, layoutId, list);
        this.layoutId = layoutId;
    }

    @NonNull
    @Override
    public View getView(int position, View convertView, ViewGroup parent) {
        MsgContent item = getItem(position);
        View view = LayoutInflater.from(getContext()).inflate(layoutId, parent, false);

        TextView textView1 = (TextView) view.findViewById(R.id.item_text1);
        TextView textView2 = (TextView) view.findViewById(R.id.item_text2);
        TextView textView3 = (TextView) view.findViewById(R.id.item_text3);

        textView1.setText(item.getName()+":");

       long time = Long.parseLong(item.getMsgtime());
       String timeStrampStr = timerUtils.getNormalTime(time * 1000);
       textView2.setText(timeStrampStr);
       textView3.setText(item.getMsgData());
       return view;
    }
}
