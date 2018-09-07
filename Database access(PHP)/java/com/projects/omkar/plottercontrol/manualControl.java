package com.projects.omkar.plottercontrol;

import android.content.Context;
import android.content.SharedPreferences;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import com.android.volley.Request;
import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.android.volley.toolbox.StringRequest;
import com.android.volley.toolbox.Volley;


public class manualControl extends AppCompatActivity implements View.OnClickListener {

    private Button up,down,left,right,reset;
    private static final String DEFAULT = "192.168.43.4";
    private String IP;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_manual_control);

        up = (Button)findViewById(R.id.button1);
        down = (Button)findViewById(R.id.button2);
        left = (Button)findViewById(R.id.button3);
        right = (Button)findViewById(R.id.button4);
        reset = (Button)findViewById(R.id.button5);


        up.setOnClickListener(this);

    }

    @Override
    public void onClick(View view) {
        if(view == up)
        {
            String payload="^.ngc";
            SharedPreferences sharedPreferences = getSharedPreferences("ip", Context.MODE_PRIVATE);
            IP= sharedPreferences.getString("ipaddress",DEFAULT);

            // Instantiate the RequestQueue.
            com.android.volley.RequestQueue queue = Volley.newRequestQueue(this);
            String url ="http://"+ IP +"/dbtrigger.php?gcodeOf="+payload;
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

        if(view == down)
        {
            String payload="+.ngc";
            SharedPreferences sharedPreferences = getSharedPreferences("ip", Context.MODE_PRIVATE);
            IP= sharedPreferences.getString("ipaddress",DEFAULT);

            // Instantiate the RequestQueue.
            com.android.volley.RequestQueue queue = Volley.newRequestQueue(this);
            String url ="http://"+ IP +"/dbtrigger.php?gcodeOf="+payload;
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
        if(view == left)
        {
            String payload="<.ngc";
            SharedPreferences sharedPreferences = getSharedPreferences("ip", Context.MODE_PRIVATE);
            IP= sharedPreferences.getString("ipaddress",DEFAULT);

            // Instantiate the RequestQueue.
            com.android.volley.RequestQueue queue = Volley.newRequestQueue(this);
            String url ="http://"+ IP +"/dbtrigger.php?gcodeOf="+payload;
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
        if(view == right)
        {
            String payload=">.ngc";
            SharedPreferences sharedPreferences = getSharedPreferences("ip", Context.MODE_PRIVATE);
            IP= sharedPreferences.getString("ipaddress",DEFAULT);

            // Instantiate the RequestQueue.
            com.android.volley.RequestQueue queue = Volley.newRequestQueue(this);
            String url ="http://"+ IP +"/dbtrigger.php?gcodeOf="+payload;
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
        if(view == reset)
        {
            String payload="-.ngc";
            SharedPreferences sharedPreferences = getSharedPreferences("ip", Context.MODE_PRIVATE);
            IP= sharedPreferences.getString("ipaddress",DEFAULT);

            // Instantiate the RequestQueue.
            com.android.volley.RequestQueue queue = Volley.newRequestQueue(this);
            String url ="http://"+ IP +"/dbtrigger.php?gcodeOf="+payload;
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
