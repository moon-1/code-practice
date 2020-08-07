package org.techtown.login;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.TextView;

import com.google.gson.Gson;

import retrofit2.Call;
import retrofit2.Callback;
import retrofit2.Response;

import retrofit2.Retrofit;
import retrofit2.converter.gson.GsonConverterFactory;

public class LoginActivity extends AppCompatActivity {

    private TextView textViewResult;
    private Gson mGson;
    private Retrofit mRetrofit;
    private RetrofitAPI mRetrofitAPI;
    private Call<String> mCallUserList;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.test);
        textViewResult = findViewById(R.id.text_view_result);
        setRetrofitInit();
        callUserList();

    }

    private void setRetrofitInit() {
        mRetrofit = new Retrofit.Builder()
                .baseUrl("http://192.168.1.165:12339/test?Hello")
                 .addConverterFactory(GsonConverterFactory.create())
                .build();

        mRetrofitAPI = mRetrofit.create(RetrofitAPI.class);
    }

    private void callUserList() {

        mCallUserList = mRetrofitAPI.getUserList();
        mCallUserList.enqueue(mRetrofitCallback);

    }

    private Callback<String> mRetrofitCallback = new Callback<String>() {

        @Override
        public void onResponse(Call<String> call, Response<String> response) {
            String result = response.body();
            UserList userList = (UserList) mGson.fromJson(result,UserList.class);

            for (userList: result) {
                String content = "";
                content += "Num: " + userList.getUserNum() + "\n";
                content += "User ID: " + userList.getId() + "\n";
                content += "PASSOWRD: " + userList.getPassword()+ "\n";
                content += "Email: " + userList.getEmail() + "\n";
                content += "Phone" + userList.getPhone() + "\n";

            textViewResult.append(content);
        }

        @Override
        public void onFailure(Call<String> call, Throwable t) {
            t.printStackTrace();
        }
    }


}