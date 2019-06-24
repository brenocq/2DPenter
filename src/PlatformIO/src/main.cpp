#include <Arduino.h>
#include "penterSoftware.h"

PenterSoftware penter;
const int motorStep[3] = {22,3,19};
const int motorDir[3] = {23,1,21};
void setup() {
  Serial.begin(115200);
  penter.begin();
}

void loop() {
  penter.moveAxes(0, -10);
  delay(1000);
  penter.moveAxes(0, -10);
  delay(1000);
  /*penter.penPoint();
  penter.moveAxes(1, 1);
  penter.penPoint();
  penter.moveAxes(1, 1);
  penter.penPoint();
  penter.moveAxes(4, 0);
  delay(1000);*/
}


/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com
*********/

/*// Load Wi-Fi library
#include <WiFi.h>

// Replace with your network credentials
const char* ssid     = "BrenoCQ";
const char* password = "penter2d";

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state
String output26State = "off";
String output27State = "off";

// Assign output variables to GPIO pins
const int output2 = 2;

void setup() {
  Serial.begin(115200);
  // Initialize the output variables as outputs
  pinMode(output2, OUTPUT);
  // Set outputs to LOW
  digitalWrite(output2, LOW);

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop(){
  WiFiClient client = server.available();   // Listen for incoming clients
  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            // turns the GPIOs on and off
            if (header.indexOf("GET /26/on") >= 0) {
              Serial.println("GPIO 26 on");
              output26State = "on";
              digitalWrite(output2, HIGH);
            } else if (header.indexOf("GET /26/off") >= 0) {
              Serial.println("GPIO 26 off");
              output26State = "off";
              digitalWrite(output2, LOW);
            } else if (header.indexOf("GET /27/on") >= 0) {
              Serial.println("GPIO 27 on");
              output27State = "on";
              digitalWrite(output2, HIGH);
            } else if (header.indexOf("GET /27/off") >= 0) {
              Serial.println("GPIO 27 off");
              output27State = "off";
              digitalWrite(output2, LOW);
            }
            client.println("<!DOCTYPE html>");
            client.println("<html lang=\"en\">");
            client.println("<head>");
            client.println("  <!-- Style CSS -->");
            client.println("  <style>");
            client.println("    h1{");
            client.println("      font-size: 30pt;");
            client.println("      color: white;");
            client.println("      text-shadow: 0px 0px 20px white;");
            client.println("      text-align: center;");
            client.println("    }");
            client.println("    h2{");
            client.println("      color: white;");
            client.println("      text-align: center;");
            client.println("      text-shadow: 0px 0px 5px white;");
            client.println("    }");
            client.println("    body{");
            client.println("      background-image: url(http://wallpoper.com/images/00/31/33/51/black-background_00313351.jpg);");
            client.println("      color: white;");
            client.println("      font-family: Courier;");
            client.println("    }");
            client.println("    .plotFunc, .move{");
            client.println("      background-color: rgba(255,255,255,.1);");
            client.println("      text-align: center;");
            client.println("      padding-top: 10px;");
            client.println("      padding-bottom: 10px;");
            client.println("      margin: 0px 0px 0px 0px;");
            client.println("      border: 0px;");
            client.println("    }");
            client.println("    .column {");
            client.println("      float: left;");
            client.println("      width: 50%%;");
            client.println("    }");
            client.println("");
            client.println("    /* Clear floats after the columns ");
            client.println("    .row:after {");
            client.println("      content: \"\";");
            client.println("      display: table;");
            client.println("      clear: both;");
            client.println("    }");
            client.println("");
            client.println("  </style>");
            client.println("  <!-- Script JavaScript -->");
            client.println("  <script>");
            client.println("  function showDiv() {");
            client.println("    if(document.getElementById(\'welcomeDiv\').style.display == \"none\"){");
            client.println("      document.getElementById(\'welcomeDiv\').style.display = \"block\";");
            client.println("    }else{");
            client.println("      document.getElementById(\'welcomeDiv\').style.display = \"none\";");
            client.println("    }");
            client.println("");
            client.println("  }");
            client.println("  </script>");
            client.println("</head>");
            client.println("<body>");
            client.println("");
            client.println("  <header>");
            client.println("    <title> 2D Pentel </title>");
            client.println("    <code>");
            client.println("    <h1>2D <b>PEN</b>TER</h1>");
            client.println("    <h2><code>The best way to plot your function!</code></h2>");
            client.println("    </code>");
            client.println("  </header>");
            client.println("");
            client.println("  <div class=\"interface\">");
            client.println("");
            client.println("    <div class=\"move\">");
            client.println("      <h2>MOVE</h2>");
            client.println("      <div class=\"row\">");
            client.println("        <div class=\"column\">");
            client.println("          <center><a href=\"/home\"><button class=\"button\">Home</button></a></center>");
            client.println("        </div>");
            client.println("        <div class=\"column\">");
            client.println("          <div id=\"welcomeDiv\"  style=\"display:none;\" class=\"answer_list\" > BATATA</div>");
            client.println("          <input type=\"button\" name=\"answer\" value=\"Show Div\" onclick=\"showDiv()\" />");
            client.println("        </div>");
            client.println("      </div>");
            client.println("    </div>");
            client.println("");
            client.println("    <br /><br />");
            client.println("");
            client.println("    <div class=\"plotFunc\">");
            client.println("      <h2>PLOT YOUR FUNCTION</h2>");
            client.println("      <h3>Exemple: 2x^3+x^2+5</h3>");
            client.println("    </div>");
            client.println("");
            client.println("  </div>");
            client.println("</body>");
            client.println("</html>");
            client.println();*/

            /*// Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}</style></head>");

            // Web Page Heading
            client.println("<body><h1>ESP32 Web Server</h1>");

            client.println("<p><a href=\"/home\"><button class=\"button\">Home</button></a></p>");
            client.println("<div id=\"welcomeDiv\"  style=\"display:none;\" class=\"answer_list\" > WELCOME</div>");
            client.println("<input type\=\"button\" name=\"answer\" value=\"Show Div\" onclick=\"showDiv()\" />");
            client.println("<script>");
            client.println("function showDiv() {");
           client.println("document.getElementById('welcomeDiv').style.display = \"block\";}");
            client.println("</script>");

            // Display current state, and ON/OFF buttons for GPIO 26
            client.println("<p>GPIO 26 - State " + output26State + "</p>");
            // If the output26State is off, it displays the ON button
            if (output26State=="off") {
              client.println("<p><a href=\"/26/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/26/off\"><button class=\"button button2\">OFF</button></a></p>");
            }

            // Display current state, and ON/OFF buttons for GPIO 27
            client.println("<p>GPIO 27 - State " + output27State + "</p>");
            // If the output27State is off, it displays the ON button
            if (output27State=="off") {
              client.println("<p><a href=\"/27/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/27/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            client.println("</body></html>");

            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}*/
