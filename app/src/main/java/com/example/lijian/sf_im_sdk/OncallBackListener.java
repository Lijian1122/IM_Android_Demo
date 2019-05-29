package com.example.lijian.sf_im_sdk;


public class OncallBackListener implements callBackListener {
    public void onGetCallbackData(int total, int already)
    {
        System.out.println("total:"+total);
        System.out.println("already:"+already);
    }

    public void onGetStr(String username)
    {
        System.out.println("My name is:"+username);
    }

    public void onGetLong(long name , long ID)
    {
        System.out.println("total6666:"+ name);
        System.out.println("already666:"+ID);
    }
}
