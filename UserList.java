package org.techtown.login;

import com.google.gson.annotations.SerializedName;

import java.util.ArrayList;
import java.util.List;


public class UserList
{
    private String userNum;
    private String password;
    private String phone;
    private String id;
    private String email;

    public String getUserNum ()
    {
        return userNum;
    }

    public void setUserNum (String userNum)
    {
        this.userNum = userNum;
    }

    public String getPassword ()
    {
        return password;
    }

    public void setPassword (String password)
    {
        this.password = password;
    }

    public String getPhone ()
    {
        return phone;
    }

    public void setPhone (String phone)
    {
        this.phone = phone;
    }

    public String getId ()
    {
        return id;
    }

    public void setId (String id)
    {
        this.id = id;
    }

    public String getEmail ()
    {
        return email;
    }

    public void setEmail (String email)
    {
        this.email = email;
    }

    /*@Override
    public String toString()
    {
        return "ClassUserList [userNum = "+userNum+", password = "+password+", phone = "+phone+", id = "+id+", email = "+email+"]";
    }*/
}
