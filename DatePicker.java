package com.practicecode.datepickerdialog_201812312;

import androidx.appcompat.app.AppCompatActivity;

import android.app.DatePickerDialog;
import android.app.Dialog;
import android.app.TimePickerDialog;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.DatePicker;
import android.widget.EditText;
import android.widget.TimePicker;
import android.widget.Toast;

import java.util.Calendar;

public class MainActivity extends AppCompatActivity {
    Button btnSelectDate,btnSelectTime,btnSelectMember;
    DatePickerDialog datePickerDialog;
    TimePickerDialog timePickerDialog;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        btnSelectDate=(Button)findViewById(R.id.button1);
        btnSelectTime=(Button)findViewById(R.id.button2);
        btnSelectMember=(Button)findViewById(R.id.button3);
    }
    public void onClick(View v){
        if(v == btnSelectDate){//날짜선택
            final Calendar c = Calendar.getInstance(); //현재 시간 얻음
            int mYear = c.get(Calendar.YEAR);
            int mMonth = c.get(Calendar.MONTH);
            int mDay = c.get(Calendar.DAY_OF_MONTH);

            DatePickerDialog datePickerDialog = new DatePickerDialog(this,
                    new DatePickerDialog.OnDateSetListener() {
                        @Override
                        public void onDateSet(DatePicker view, int year ,int monthOfYear, int dayOfMonth) {
                            btnSelectDate.setText(dayOfMonth + "/" + (monthOfYear + 1) + "/" + year); //선택한 날짜로 버튼의 텍스트 변경

                        }
                    },mYear,mMonth,mDay);
            datePickerDialog.show();
        }
        if(v == btnSelectTime){//시간선택
            final Calendar c = Calendar.getInstance();
            int mHour = c.get(Calendar.HOUR_OF_DAY);
            int mMinute = c.get(Calendar.MINUTE);

            TimePickerDialog timePickerDialog = new TimePickerDialog(this,
                    new TimePickerDialog.OnTimeSetListener() {
                        @Override
                        public void onTimeSet(TimePicker view, int hourOfDay, int minute) {
                            btnSelectTime.setText(hourOfDay + ":" + minute);
                        }
                    },mHour,mMinute,false);
                timePickerDialog.show();
        }
        if(v == btnSelectMember){//인원수 선택
            final Dialog memberDialog = new Dialog(this);//dialog 생성
            memberDialog.setContentView(R.layout.custom_dialog);//custom_dialog layout불러오기

            Button ok = (Button) memberDialog.findViewById(R.id.ok); //ok button
            Button cancel = (Button) memberDialog.findViewById(R.id.cancel);// cancel button
            final EditText member = (EditText) memberDialog.findViewById(R.id.memberNum);// number of people
            ok.setOnClickListener(new View.OnClickListener(){//ok 버튼이 눌렸을 경우
                @Override
                public void onClick(View v){
                    String num = member.getText().toString();
                    if(num.length() > 0){
                        btnSelectMember.setText("인원수: "+num);//버튼 text 변경
                        memberDialog.dismiss();
                    }
                    else{//number of people 입력되지 않았을 경우
                        Toast.makeText(getApplicationContext(),"인원수를 입력하시오",
                                Toast.LENGTH_LONG).show();
                    }
                }
            });
            cancel.setOnClickListener(new View.OnClickListener(){//cancel 버튼이 눌렸을 경우
                @Override
                public void onClick(View v){
                    memberDialog.dismiss();//dialog 사라지게함
                }
            });
            memberDialog.show();
        }
    }

}