package org.techtown.login;

import retrofit2.Call;
import retrofit2.http.GET;

public interface RetrofitAPI {
    @GET("/userList")
    Call<String> getUserList();
}