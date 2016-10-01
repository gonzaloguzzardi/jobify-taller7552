package com.fiuba.tallerii.jobify;

import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentActivity;
import android.support.v4.app.FragmentManager;

/**
 * A login screen that offers login via email/password.
 */
public class LoginActivity extends FragmentActivity
{
    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_login);

        //Fragment code
        FragmentManager fm = getSupportFragmentManager();
        Fragment fragment = fm.findFragmentById(R.id.fragment_login_container);
        if (fragment == null)
        {
            fragment = new LoginFragment();
            fm.beginTransaction().add(R.id.fragment_login_container, fragment).commit();
        }
    }

}

