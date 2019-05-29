package com.example.lijian.sf_im_sdk;

import java.text.SimpleDateFormat;
import java.util.Date;

public class TimerUtils {
     TimerUtils(){};
    public static String getNormalTime(long value) {
        SimpleDateFormat format = new SimpleDateFormat("HH:mm:ss") ; //yyyy-MM-dd
        String time = format.format(new Date(value)) ;
        return time;
    }
}
