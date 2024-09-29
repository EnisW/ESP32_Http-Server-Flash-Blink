#include <Arduino.h>
#include "functions.h"

#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <uri/UriBraces.h>



WebServer server(80);


const int LED1 = 4;



void sendHtml() {
  String response = R"(
    <!DOCTYPE HTML>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>ESP32 Plus Operation Flash Led Blink</title>
    <style>
        body {
            background-color: #1e159c;
            font-family: Arial, sans-serif;
            display: flex;
            justify-content: center;
            align-items: center;
            height: 100vh;
            margin: 0;
        }

        .container {
            border: 5px solid #ffffff;
            border-radius: 25px;
            background-color: #7c7c7c;
            box-shadow: 0px 8px 15px rgba(0, 0, 0, 0.1);
            display: flex;
            justify-content: center;
            align-items: center;
            flex-direction: column;
            height: 60vh;
            width: 50vh;
        }

        form {
            display: flex;
            flex-direction: column;
            justify-content: center;
            align-items: center;
            width: 100%;
        }

        .submitButton {
            background-color: green;
            color: white;
            font-size: 1.5em;
            margin-top: 30px;
            padding: 10px 20px;
            border: none;
            border-radius: 15px;
            cursor: pointer;
        }

        .submitButton:hover {
            background-color: darkgreen;
        }

        .textField {
            font-size: 1.2em;
            margin: 10px 0;
            padding: 10px;
            border: 2px solid #ccc;
            border-radius: 5px;
            width: 80%;
        }

        h2 {
            font-size: 2em;
            color: #d0ff00;
            margin-bottom: 20px;
        }

        label, select {
            font-size: 1.2em;
            margin-top: 10px;
            display: inline-block;
        }

        select {
            font-weight: bold;
            padding: 10px;
            border: 2px solid #ccc;
            border-radius: 5px;
            width: 50%;
            font-size: 1.2em;
            margin-left: 10px;
        }
    </style>
</head>
<body>
    <div class="container">
        <h2>FLASH LED BLINK</h2>  
        <form action="/submit" method="POST">
            <input type="text" name="number1" class="textField" placeholder="Number 1">
            <label style="color: #d3166e;" for="comboBox"><b>Select Calculation Type</b></label>
            <select id="comboBox" name="comboBox">
                <option value="+">+</option>
                <option value="-">-</option>
                <option value="/">÷</option>
                <option value="x">x</option>
            </select>
            <input style="margin-top: 40px;" type="text" name="number2" class="textField" placeholder="Number 2">
            <input type="submit" value="BLINK FLASH !" class="submitButton">
        </form>
    </div>
</body>
</html>

  )";

  server.send(200, "text/html", response);
}


void connectWifi() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.println("Connecting to WiFi " + (String)WIFI_SSID) + "\n";

  while(WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("WiFi Successfully Connected !");

  Serial.println("Connection IP Address ---->  " + WiFi.localIP().toString());

  server.on("/", sendHtml);
  server.on("/submit", HTTP_POST, []() {
    int result = getNumbersAndCalculate();

    for(int i =0; i < result; i++) {
      digitalWrite(LED1, HIGH);
      delay(500);
      digitalWrite(LED1, LOW);
      delay(1500);
    }
    
    sendHtml();
  });

  server.begin();
  Serial.println("HTTP server started");

}

int getNumbersAndCalculate() {
    String number1String = "";
    String number2String = "";
    String operation = "";

    if(server.hasArg("number1") && server.hasArg("number2") && server.hasArg("comboBox")) {
      number1String = server.arg("number1");
      
      number2String = server.arg("number2");

      operation = server.arg("comboBox");
      
      
    }

    

    int number1Int = number1String.toInt();
    int number2Int = number2String.toInt();

    char charOperation = operation[0];
    Serial.println("String : " + operation + " Char : " + charOperation);

    int result = 0;

    switch(charOperation) {
      case '+' :
      result = number1Int + number2Int;
      break;

      case '-' :
      result = number1Int - number2Int;
      break;

      case '/' :
      result = number1Int / number2Int;
      break;

      case 'x' :
      result = number1Int * number2Int;
      break;

    }
    Serial.println("Result = " + result);
    return result;

  }

void setup(void) {
  Serial.begin(115200);

  pinMode(LED1, OUTPUT);

  connectWifi();
}

void loop(void) {
  server.handleClient();
  delay(2);
}
