package com.projects.omkar.plottercontrol;

import android.app.DownloadManager;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.net.http.RequestQueue;
import android.os.AsyncTask;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;


import com.android.volley.Request;
import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.android.volley.toolbox.StringRequest;
import com.android.volley.toolbox.Volley;
import com.apptakk.http_request.HttpRequest;
import com.apptakk.http_request.HttpRequestTask;
import com.apptakk.http_request.HttpResponse;

import org.apache.http.client.HttpClient;
import org.apache.http.client.ResponseHandler;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.impl.client.BasicResponseHandler;
import org.apache.http.impl.client.DefaultHttpClient;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {

    EditText _editText1,_ipAddress;
    String payload;
    Button sendRequest,_sendPhoto,ipOk;
    TextView dataSent;
    TextView about;
    Button ip;
    String IPADDRESS;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        about=(TextView)findViewById(R.id.textView_about) ;

        _editText1 = (EditText) findViewById(R.id.editText1);
        dataSent = (TextView) findViewById(R.id.sentData);
        sendRequest = (Button) findViewById(R.id.button_send);
        _sendPhoto = (Button)findViewById(R.id.button_SendPhoto);
        ip= (Button)findViewById(R.id.button_changeServerIP);
        _ipAddress = (EditText)findViewById(R.id.editText_ipAddress);
        ipOk=(Button)findViewById(R.id.button_IP_okay);


        final String[] text = {""};


        sendRequest.setOnClickListener(this);
        about.setOnClickListener(this);
        _sendPhoto.setOnClickListener(this);
        ip.setOnClickListener(this);
        ipOk.setOnClickListener(this);
    }

    @Override
    public void onClick(View view) {

        if (view == sendRequest) {
             payload = _editText1.getText().toString();
            //  dataSent.setText(payload);
            // Instantiate the RequestQueue.
            com.android.volley.RequestQueue queue = Volley.newRequestQueue(this);
            String url ="http://"+IPADDRESS+"/dbtrigger.php?gcodeOf="+payload;

            //  String uri = String.format("http://192.168.0.102/dbtrigger.php?gcodeOf=%1$s",
            // "omkar");
            // Request a string response from the provided URL.

            StringRequest stringRequest = new StringRequest(Request.Method.GET, url,
                    new Response.Listener<String>() {
                        @Override
                        public void onResponse(String response) {
                            // Display the first 500 characters of the response string.
                         //   dataSent.setText("Response is: "+ response.substring(0,500));
                            dataSent.setText("Data Sent to Plotter");
                        }
                    }, new Response.ErrorListener() {
                @Override
                public void onErrorResponse(VolleyError error) {
                   // dataSent.setText("That didn't work!");
                }
            });

// Add the request to the RequestQueue.
            queue.add(stringRequest);

            Toast.makeText(this, "Sending Data To Plot", Toast.LENGTH_SHORT).show();

        }


        if(view==about)
        {
            Intent helpIntent = new Intent(MainActivity.this,aboutActivity.class);
            startActivity(helpIntent);
        }
        if(view==_sendPhoto)
        {


            Intent sendPhotoIntent = new Intent(MainActivity.this,sendPhotoActivity.class);

            startActivity(sendPhotoIntent);
        }
        if(view== ip)
        {
            _ipAddress.setVisibility(View.VISIBLE);
            ipOk.setVisibility(View.VISIBLE);
        }
        if(view==ipOk)
        {
           IPADDRESS= _ipAddress.getText().toString();
            SharedPreferences sharedPreferences = getSharedPreferences("ip", Context.MODE_PRIVATE);
            SharedPreferences.Editor editor = sharedPreferences.edit();
            sharedPreferences.edit().clear().commit();
            editor.putString("ipaddress",IPADDRESS);
            editor.commit();

            _ipAddress.setText("");
            _ipAddress.setVisibility(View.INVISIBLE);
            ipOk.setVisibility(View.INVISIBLE);
        }
    }


    private class MyTask extends AsyncTask<Void, Void, Void>
    {
        @Override
        protected Void doInBackground(Void... params) {

            try
            {
                HttpClient Client = new DefaultHttpClient();
                // String URL = "/media/webservice/httpget.php?user="+loginValue+"&name="+fnameValue+"&email="+emailValue+"&pass="+passValue;
                String URL = "/192.168.43.4/dbtrigger.php?gcodeOf=omkar";
                String SetServerString = "";

                // Create Request to server and get response

                HttpGet httpget = new HttpGet(URL);
                ResponseHandler<String> responseHandler = new BasicResponseHandler();

                SetServerString = Client.execute(httpget, responseHandler);

                // Show response on activity
              //  dataSent.setText(SetServerString);

            }
            catch(Exception ex)
            {
                //dataSent.setText(ex.toString());
            }
            return null;

        }

        @Override
        protected void onPostExecute(Void result) {


        }

        @Override
        protected void onProgressUpdate(Void... values) {}
    }

    private void sendPayload() {


    }


}



