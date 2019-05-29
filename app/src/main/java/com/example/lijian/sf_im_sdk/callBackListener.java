package com.example.lijian.sf_im_sdk;

import android.widget.TextView;

public interface callBackListener {

    public void onGetCallbackData(int total, int already);

    public void onGetStr(String username);

    public void onGetLong(long name , long ID);
}
