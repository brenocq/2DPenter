#include <Arduino.h>
#include "penterSoftware.h"
#include <string>
#include <WiFi.h>
using namespace std;
#define SIZE 40

// Replace with your network credentials
const char* ssid     = "BrenoCQ";
const char* password = "penter2d";

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

float moveDistance = 1;

float pot(float x, int k);
float mod(float k);
float f(string s, float x);
int num(string s, int l, int r);
void graph(bool a[SIZE][SIZE], string s, float prop);
void cross(bool a[SIZE][SIZE]);
void seta(bool a[SIZE][SIZE]);
void chama (bool a[SIZE][SIZE]);
void desenha(float x, float y);

PenterSoftware penter;
void setup() {
  Serial.begin(115200);
  penter.begin();

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

void loop() {
  WiFiClient client = server.available();   // Listen for incoming clients
  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    string currentLine = "";                // make a string to hofloat incoming data from the client
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
            if (header.indexOf("GET /home") >= 0) {
              Serial.println("Ypositive");
              penter.moveHome();
            } else if (header.indexOf("GET /Ypositive") >= 0) {
              Serial.println("Ypositive");
              penter.moveAxes(0,moveDistance);
            } else if (header.indexOf("GET /Ynegative") >= 0) {
              Serial.println("Ynegative");
              penter.moveAxes(0,-moveDistance);
            } else if (header.indexOf("GET /Xpositive") >= 0) {
              Serial.println("Xpositive");
              penter.moveAxes(moveDistance,0);
            } else if (header.indexOf("GET /Xnegative") >= 0) {
              Serial.println("Xnegative");
              penter.moveAxes(-moveDistance,0);
            } else if (header.indexOf("GET /Point") >= 0) {
              penter.penPoint();
            } else if (header.indexOf("GET /001") >= 0) {
              moveDistance = 0.1;
            } else if (header.indexOf("GET /010") >= 0) {
              moveDistance = 1;
            } else if (header.indexOf("GET /100") >= 0) {
              moveDistance = 10;
            } else if (header.indexOf("GET /Plot") >= 0) {
              string function="";
              int indexIni = header.indexOf("GET /Plot")+9;
              int indexEnd = header.indexOf(" HTTP");
              for (size_t i = indexIni; i < indexEnd; i++) {
                function+=header[i];
              }
              //Serial.print("FUNCTION:");Serial.println(function);
              //function = "xe2-1";
              // Move penter to home
              penter.moveHome();
              bool matrix[SIZE][SIZE];
              for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                  matrix[i][j] = 0;
                }
              }
              float zoom=2;
              zoom=(SIZE/2)/zoom;
              seta (matrix);
              graph(matrix, function, zoom);
              for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                  Serial.print(matrix[i][j]);Serial.print(" ");
                }
                Serial.println();
              }
              chama(matrix);
              //cross(matrix);
              //graph(matrix, str, zoom);
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
            client.println("    /* Clear floats after the columns */");
            client.println("    .row:after {");
            client.println("      content: \"\";");
            client.println("      display: table;");
            client.println("      clear: both;");
            client.println("    }");
            client.println("");
            client.println("  </style>");
            client.println("  <!-- Script JavaScript -->");
            client.println("");
            client.println("  <script>");
            client.println("");
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
            client.println("          <h3>Home</h3>");
            client.println("            <a href=\"/home\"><img src=\"http://www.newdesignfile.com/postpic/2010/03/home-icon-white_338306.png\" height=\"150\" /></a>");
            client.println("          <center>");
            client.print("             <h3>Move axes( ");client.print(moveDistance);client.println("mm )</h3>");
            client.println("             <h5>Click the center to make a point on the paper</h5>");
            client.println("             <img src=\"https://image.flaticon.com/icons/svg/60/60931.svg\" alt = \"arrows\" usemap = \"#arrowMap\" height=\"200\">");
            client.println("           </center>");
            client.println("           <map name = \"arrowMap\">");
            client.println("             <area shape = \"rect\" coords = \"50,0,150,60\" alt = \"up arrow\"");
            client.println("               href = \"/Ypositive\" target = \"_blank\" />");
            client.println("             <area shape = \"rect\" coords = \"50,140,150,200\" alt = \"down arrow\"");
            client.println("                href = \"/Ynegative\" target = \"_blank\" />");
            client.println("             <area shape = \"rect\" coords = \"140,50,200,150\" alt = \"right arrow\"");
            client.println("               href = \"/Xpositive\" target = \"_blank\" />");
            client.println("             <area shape = \"rect\" coords = \"0,50,60,150\" alt = \"left arrow\"");
            client.println("               href = \"/Xnegative\" target = \"_blank\" />");
            client.println("             <area shape = \"rect\" coords = \"60,60,140,140\" alt = \"central\"");
            client.println("               href = \"/Point\" target = \"_blank\" />");
            client.println("           </map>");
            client.println("           <input type=\"button\" value=\"0.1mm\" onclick=\"window.location.href = \'/001\';\"/>");
            client.println("           <input type=\"button\" value=\"1mm\"   onclick=\"window.location.href = \'/010\';\"/>");
            client.println("           <input type=\"button\" value=\"10mm\"   onclick=\"window.location.href = \'/100\';\"/>");
            client.println("      </div>");
            client.println("    </div>");
            client.println("");
            client.println("    <br /><br />");
            client.println("");
            client.println("    <div class=\"plotFunc\">");
            client.println("      <h2>PLOT YOUR FUNCTION</h2>");
            client.println("      <h3>Exemple: xe3-2xe2+1</h3>");
            client.println("      <div>");
            client.println("         <input type = \"text\" id = \"inputText\"></input>");
            client.println("         <button onClick=\"javascript: window.open(\'/Plot\' + document.getElementById(\'inputText\').value);\" id = \"sendButton\">PLOT!</button>");
            client.println("      </div>");
            client.println("    </div>");
            client.println("");
            client.println("  </div>");
            client.println("</body>");
            client.println("</html>");
            client.println();

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
}

float mod(float k){
	if (k<0) k*=-1;
	return k;
}

float pot(float x, int k){
	if (k==0) return 1;
	else return pot(x, k-1)*x;
}

int num(string s, int l, int r){
	int a = 0, i;
	for (i=l; i<r; i++){
		a*=10;
		a+=s[i]-'0';
	}
	return a;
}

float f(string s, float x){
	float sum = 0;
	int a[100], i, l, r, m, coef, expoent, flag = 0;
	string aux;
	for (i=0; i<100; i++) a[i]=0;
	if (s[0]!='+' && s[0]!='-') {
		aux="+"+s;
		s=aux;
	}
	l=r=0;
	while(s[l]!='\0'){
		flag = 0;

		if (s[l+1]=='x') {
			coef = 1;
			m = l+1; //m indica a posição do x

		}
		else {
			for (i=l+1; i<=s.size(); i++){
				if (s[i]=='x'){
					coef = num(s, l+1, i); //função num retorna o numero contido entre a substring s[l+1, i]
					m = i;
					break;
				}
				if (s[i]=='\0' || s[i]=='+' || s[i]=='-'){
					if (s[l]=='+') a[0] += num(s, l+1, i);
					else a[0] -= num(s, l+1, i);
					flag = 1;
					r = i;
					l = r;
					break;
				}
			}
		}

		if (flag) continue;

		if (s[m+1]!='e') {
			expoent = 1;
			r = m+1;
		}
		else {
			for (i=m+2; i<=s.size(); i++){
				if (s[i]=='+' || s[i]=='-' || s[i]=='\0'){
					expoent = num(s, m+2, i);
					r = i;
					break;
				}
			}
		}
		if (s[l]=='+') a[expoent] += coef;
		else a[expoent] -= coef;
		l = r;
	}

	for (i=0; i<100; i++) sum += a[i]*pot(x, i);
	return sum;
}

void graph(bool a[SIZE][SIZE], string s, float prop){
	float x;
	float y;
	for (x=-(SIZE/2); x<SIZE/2; x++){
		y = prop*f(s, x/prop);
    Serial.print("f(");Serial.print(x);Serial.print("):");Serial.println(y);
		if (mod(y)<SIZE/2) a[SIZE/2-(int)y][(int)x+SIZE/2]=0;
	}
	return;
}

void cross(bool a[SIZE][SIZE]){
	int i;
	for (i=0; i<SIZE; i++){
		a[SIZE/2][i]=0;
		a[i][SIZE/2]=0;
	}
}

void seta(bool a[SIZE][SIZE]){
	int i, j;
	for (i=0; i<SIZE; i++) for (j=0; j<SIZE; j++) a[i][j]=1;
}

void chama (bool a[SIZE][SIZE]){
	int i, j;
	for (i=0; i<SIZE; i++) desenha((float)i, SIZE/2);
	for (i=0; i<SIZE; i++) desenha(SIZE/2, (float)i);
	for (j=0; j<SIZE; j++){
		for (i=0; i<SIZE; i++){
			if (a[i][j]==0 && i != SIZE/2 && j != SIZE/2) desenha((float)i, (float)j);
		}
	}
}

void desenha(float x, float y){
	penter.point(x,y);
}
