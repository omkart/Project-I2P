package com.projects.omkar.plottercontrol;

import android.content.Context;
import android.content.SharedPreferences;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.TextView;

import com.android.volley.Request;
import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.android.volley.toolbox.StringRequest;
import com.android.volley.toolbox.Volley;

public class sendPhotoActivity extends AppCompatActivity implements View.OnClickListener {

    ImageButton smiley,chrome,veslogo,snapchat,facebook,amazon;
    private static final String DEFAULT = "192.168.43.4";
    private String IP;
    TextView payloadStatus;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_send_photo);

        smiley=(ImageButton)findViewById(R.id.button_smiley) ;
        chrome=(ImageButton)findViewById(R.id.button_chrome) ;

        veslogo=(ImageButton)findViewById(R.id.button_veslogo) ;
        snapchat=(ImageButton)findViewById(R.id.button_snapchat) ;

        facebook=(ImageButton)findViewById(R.id.button_facebook) ;
        amazon=(ImageButton)findViewById(R.id.button_amazon) ;

        payloadStatus = (TextView) findViewById(R.id.payload_status);

        smiley.setOnClickListener(this);
        chrome.setOnClickListener(this);
        veslogo.setOnClickListener(this);
        snapchat.setOnClickListener(this);
        amazon.setOnClickListener(this);
        facebook.setOnClickListener(this);
    }

    @Override
    public void onClick(View view) {
        if (view== smiley)
        {

            String payload="smiley.ngc";

            SharedPreferences sharedPreferences = getSharedPreferences("ip", Context.MODE_PRIVATE);
            IP= sharedPreferences.getString("ipaddress",DEFAULT);

            // Instantiate the RequestQueue.
            com.android.volley.RequestQueue queue = Volley.newRequestQueue(this);
            String url ="http://"+ IP +"/dbtrigger.php?gcodeOfImage="+payload;

            //  String uri = String.format("http://192.168.0.102/dbtrigger.php?gcodeOf=%1$s",
            // "omkar");
            // Request a string response from the provided URL.

            StringRequest stringRequest = new StringRequest(Request.Method.GET, url,
                    new Response.Listener<String>() {
                        @Override
                        public void onResponse(String response) {
                            // Display the first 500 characters of the response string.
                            //   dataSent.setText("Response is: "+ response.substring(0,500));

                        }
                    }, new Response.ErrorListener() {
                @Override
                public void onErrorResponse(VolleyError error) {
                    // dataSent.setText("That didn't work!");
                }
            });

// Add the request to the RequestQueue.
            queue.add(stringRequest);
        }
        if(view==veslogo)
        {

                String payload="veslogo.ngc";
            SharedPreferences sharedPreferences = getSharedPreferences("ip", Context.MODE_PRIVATE);
            IP= sharedPreferences.getString("ipaddress",DEFAULT);

            // Instantiate the RequestQueue.
            com.android.volley.RequestQueue queue = Volley.newRequestQueue(this);
            String url ="http://"+ IP +"/dbtrigger.php?gcodeOfImage="+payload;

                //  String uri = String.format("http://192.168.0.102/dbtrigger.php?gcodeOf=%1$s",
                // "omkar");
                // Request a string response from the provided URL.

                StringRequest stringRequest = new StringRequest(Request.Method.GET, url,
                        new Response.Listener<String>() {
                            @Override
                            public void onResponse(String response) {
                                // Display the first 500 characters of the response string.
                                //   dataSent.setText("Response is: "+ response.substring(0,500));

                            }
                        }, new Response.ErrorListener() {
                    @Override
                    public void onErrorResponse(VolleyError error) {
                        // dataSent.setText("That didn't work!");
                    }
                });

// Add the request to the RequestQueue.
                queue.add(stringRequest);

        }
        if(view==chrome)
        {

            String payload="chrome.ngc";
            SharedPreferences sharedPreferences = getSharedPreferences("ip", Context.MODE_PRIVATE);
            IP= sharedPreferences.getString("ipaddress",DEFAULT);

            // Instantiate the RequestQueue.
            com.android.volley.RequestQueue queue = Volley.newRequestQueue(this);
            String url ="http://"+ IP +"/dbtrigger.php?gcodeOfImage="+payload;

            //  String uri = String.format("http://192.168.0.102/dbtrigger.php?gcodeOf=%1$s",
            // "omkar");
            // Request a string response from the provided URL.

            StringRequest stringRequest = new StringRequest(Request.Method.GET, url,
                    new Response.Listener<String>() {
                        @Override
                        public void onResponse(String response) {
                            // Display the first 500 characters of the response string.
                            //   dataSent.setText("Response is: "+ response.substring(0,500));

                        }
                    }, new Response.ErrorListener() {
                @Override
                public void onErrorResponse(VolleyError error) {
                    // dataSent.setText("That didn't work!");
                }
            });

// Add the request to the RequestQueue.
            queue.add(stringRequest);

        }

        if(view==facebook)
        {

            String payload="facebook.ngc";
            SharedPreferences sharedPreferences = getSharedPreferences("ip", Context.MODE_PRIVATE);
            IP= sharedPreferences.getString("ipaddress",DEFAULT);

            // Instantiate the RequestQueue.
            com.android.volley.RequestQueue queue = Volley.newRequestQueue(this);
            String url ="http://"+ IP +"/dbtrigger.php?gcodeOfImage="+payload;

            //  String uri = String.format("http://192.168.0.102/dbtrigger.php?gcodeOf=%1$s",
            // "omkar");
            // Request a string response from the provided URL.

            StringRequest stringRequest = new StringRequest(Request.Method.GET, url,
                    new Response.Listener<String>() {
                        @Override
                        public void onResponse(String response) {
                            // Display the first 500 characters of the response string.
                            //   dataSent.setText("Response is: "+ response.substring(0,500));

                        }
                    }, new Response.ErrorListener() {
                @Override
                public void onErrorResponse(VolleyError error) {
                    // dataSent.setText("That didn't work!");
                }
            });

// Add the request to the RequestQueue.
            queue.add(stringRequest);

        }

        if(view==amazon)
        {

            String payload="amazon.ngc";
            SharedPreferences sharedPreferences = getSharedPreferences("ip", Context.MODE_PRIVATE);
            IP= sharedPreferences.getString("ipaddress",DEFAULT);

            // Instantiate the RequestQueue.
            com.android.volley.RequestQueue queue = Volley.newRequestQueue(this);
            String url ="http://"+ IP +"/dbtrigger.php?gcodeOfImage="+payload;
            //  String uri = String.format("http://192.168.0.102/dbtrigger.php?gcodeOf=%1$s",
            // "omkar");
            // Request a string response from the provided URL.

            StringRequest stringRequest = new StringRequest(Request.Method.GET, url,
                    new Response.Listener<String>() {
                        @Override
                        public void onResponse(String response) {
                            // Display the first 500 characters of the response string.
                            //   dataSent.setText("Response is: "+ response.substring(0,500));

                        }
                    }, new Response.ErrorListener() {
                @Override
                public void onErrorResponse(VolleyError error) {
                    // dataSent.setText("That didn't work!");
                }
            });

// Add the request to the RequestQueue.
            queue.add(stringRequest);

        }

        if(view==snapchat)
        {

            String payload="snapchat.ngc";
            SharedPreferences sharedPreferences = getSharedPreferences("ip", Context.MODE_PRIVATE);
            IP= sharedPreferences.getString("ipaddress",DEFAULT);

            // Instantiate the RequestQueue.
            com.android.volley.RequestQueue queue = Volley.newRequestQueue(this);
            String url ="http://"+ IP +"/dbtrigger.php?gcodeOfImage="+payload;
            //  String uri = String.format("http://192.168.0.102/dbtrigger.php?gcodeOf=%1$s",
            // "omkar");
            // Request a string response from the provided URL.

            StringRequest stringRequest = new StringRequest(Request.Method.GET, url,
                    new Response.Listener<String>() {
                        @Override
                        public void onResponse(String response) {
                            // Display the first 500 characters of the response string.
                            //   dataSent.setText("Response is: "+ response.substring(0,500));

                        }
                    }, new Response.ErrorListener() {
                @Override
                public void onErrorResponse(VolleyError error) {
                    // dataSent.setText("That didn't work!");
                }
            });

// Add the request to the RequestQueue.
            queue.add(stringRequest);

        }

    }
}
