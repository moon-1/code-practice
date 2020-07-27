package myapplication.httpurlconnection;

import java.util.List;

import retrofit2.Call;
import retrofit2.http.Body;
import retrofit2.http.GET;
import retrofit2.http.POST;
import retrofit2.http.Query;

public interface JsonPlaceHolderApi {
    @POST("posts")
    Call<Post> createPost(@Body Post post);
}


