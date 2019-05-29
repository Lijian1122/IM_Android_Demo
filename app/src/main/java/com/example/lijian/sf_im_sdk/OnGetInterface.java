package com.example.lijian.sf_im_sdk;
import android.widget.ListView;
import android.widget.TextView;

import java.util.List;

public interface OnGetInterface {

    //public TextView getText();

    //public List<MsgContent>  getDataList();

    //public  MsgItemAdapter getAdapter();

    public void AddItem(MsgContent item);

    public void GetLoginStaete(int state);
    //public ListView getListView();
}
