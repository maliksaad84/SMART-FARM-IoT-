#include <Console.h> 
#include <Process.h>
#include <SPI.h>
#include <RH_RF95.h>

RH_RF95 rf95;

char DeviceID[20]="\0"; //Storage DeviceID or Device identifier
char temp[20]="\0";           //Storage tempgtitude
char hum[20]="\0";           //Storage humitude
char raw[20]="\0";           //Storage rawitude

String thingSpeakAPI = "api.thingspeak.com";
String talkBackAPIKey = "M51DHW4YLWRQD27D";
const int checkTalkBackInterval = 10 * 1000;    // Time interval in milliseconds to check TalkBack (number of seconds * 1000 = interval)
String null_data = "NULL"; // null data for post command

int gateway_id = 0;
int address = 0;
long lastConnectionTime = 0;
String talkBackID = "37016";

void getTimeStamp();     //LG01 will call the Linux "date" command and get the time stamp
void receivepacket();    //Processing receive message and store it in the appropriate array
//void run_send_gps_data();//LG01 will call the Linux "send_gps_data.sh" command and write the GPS data in GPSWOX.com

String myWriteAPIString = "7ODSRFPVGH4S1U5W";
String dataString = "";
String dataString1 = "";
String s = "";
String y = "";
String y1 = "";
void uploadData(); // Upload Data to ThingSpeak.

void setup() { 
  Bridge.begin(115200);  
  Console.begin();
  while (!Console);
  
   if (!rf95.init()) {// Defaults after init are 434.0MHz, 13dBm, Bw = 125 kHz, Cr = 4/5, Sf = 128chips/symbol, CRC on
    Console.println("Starting LoRa failed!");
    while (1);
  }
  /* Set frequency is 868MHz,SF is 7,SB is 125KHz,CR is 4/5 and Tx power is 20dBm */
  rf95.setFrequency(868);
  rf95.setSpreadingFactor(7);
  rf95.setSignalBandwidth(125E3);
  rf95.setCodingRate4(5);
  rf95.setTxPower(20,false);
  
  Console.println("Ready to receive!");
}
void loop(){
 receivepacket();

                    int hh = hum;
             //     Console.print("Hi i am Maths " );  Console.println(hh);
               //     int hl = newData[1];
                    int th = temp;
               //     int tl = newData[3];

 ///////////////////////////////////////////////////
 dataString ="field1=";
                    dataString += hum;
                 //   dataString +=".";
                  //  dataString += tl;
                    dataString +="&field2=";
                    dataString += temp;
                 //   dataString +=".";
                //    dataString += hl;
 dataString1 ="field3=";
                    dataString1 += hum;
                 //   dataString1 +=".";
                  //  dataString1 += tl;
                    dataString1 +="&field4=";
                    dataString1 += temp;
                 //   dataString1 +=".";
                //    dataString1 += hl;
                                       
                    uploadData(); // 
                    dataString="";
                    dataString1="";
                    
    checkTalkBack();//Check if there is talkback command
    delay(checkTalkBackInterval); 
 
}

void getTimeStamp() {
  Process time;
  // date is a command line utility to get the date and the time 
  // in different formats depending on the additional parameter 
  time.begin("date");
  time.addParameter("+%D-%T");  // parameters: D for the complete date mm/dd/yy
                                //             T for the time hh:mm:ss    
  time.run();  // run the command

  // read the output of the command
  while(time.available()>0) {
    char c = time.read();
    Console.print(c);
  }
}



//Receiver LoRa packets and forward it 
void receivepacket() {
   if (rf95.available())
  {
    // received a packet
    Console.print("Get new data: ");

    int i = 0,j=0,code[4];
    int m1=0,m2=0,m3=0,m4=0;   
    uint8_t buf[50];
    char message[50]="\0";
    uint8_t len = sizeof(buf);
    if (rf95.recv(buf, &len)){
      strcpy(message,(char *)buf);
      while(i<50)
      {
      if(message[i]==',')
      {
        code[j]=i;
        j++;
        }
        i++;
      }
    }
    for(int k=0;k<code[0];k++)
    {
      temp[m1]=message[k];//get tempgtitude
      m1++;
    }
     for(int k=code[0]+1;k<code[1];k++)
    {
      hum[m2]=message[k];//get humitude
      m2++;
    }
     for(int k=code[1]+1;k<code[2];k++)
    {
      raw[m3]=message[k];//get rawitude
      m3++;
    }
    for(int k=code[2]+1;k<code[3];k++)
    {
      DeviceID[m4]=message[k];//get  DeviceID
      m4++;
    }
  //  run_send_gps_data();
    Console.print((char*)buf);
    Console.print("  with RSSI: ");
    Console.print(rf95.lastRssi(), DEC);
    Console.print("  ");getTimeStamp();
    Console.print("the tempgtitude is " );Console.println(temp);
    Console.print("the humitude is ");Console.println(hum);
    Console.print("the rawitude is ");Console.println(raw);
    Console.print("the DeviceID is ");Console.println(DeviceID);
    s = DeviceID;
    y="a8727";
    y1="malik";
     Console.print("the Dev is ");Console.println(s);
    
    
   
  }
}

void uploadData() {//Upload Data to ThingSpeak
  // form the string for the API header parameter:
if (y.equals(s))
//if (DeviceID == s)
{
  
Console.print("Going to send the data ");

  // form the string for the URL parameter, be careful about the required "
  String upload_url = "https://api.thingspeak.com/update?api_key=";
  upload_url += myWriteAPIString;
  upload_url += "&";
  upload_url += dataString;

  Console.println("Call Linux Command to Send Data");
  Process p;    // Create a process and call it "p", this process will execute a Linux curl command
  p.begin("curl");
  p.addParameter("-k");
  p.addParameter(upload_url);
  p.run();    // Run the process and wait for its termination

  Console.print("Feedback from Linux: ");
  // If there's output from Linux,
  // send it out the Console:
  while (p.available()>0) 
  {
    char c = p.read();
    Console.write(c);
  }
  Console.println("");
  Console.println("Call Finished");
  Console.println("####################################");
  Console.println("");
}

if (y1.equals(s))
//if (DeviceID == s)
{
  
Console.print("Going to send the data ");

  // form the string for the URL parameter, be careful about the required "
  String upload_url = "https://api.thingspeak.com/update?api_key=";
  upload_url += myWriteAPIString;
  upload_url += "&";
  upload_url += dataString1;

  Console.println("Call Linux Command to Send Data");
  Process p;    // Create a process and call it "p", this process will execute a Linux curl command
  p.begin("curl");
  p.addParameter("-k");
  p.addParameter(upload_url);
  p.run();    // Run the process and wait for its termination

  Console.print("Feedback from Linux: ");
  // If there's output from Linux,
  // send it out the Console:
  while (p.available()>0) 
  {
    char c = p.read();
    Console.write(c);
  }
  Console.println("");
  Console.println("Call Finished");
  Console.println("####################################");
  Console.println("");
}
}

void checkTalkBack()//Check if there is talkback command
{
    char talkBackCommand[200] = {0};
    Console.println("Checking Talkback from Server");
    int count=0;
    String talkBackURL =  "https://" + thingSpeakAPI + "/talkbacks/" + talkBackID + "/commands/execute.json?api_key=" + talkBackAPIKey;
    Process p;
    p.begin("curl");
    p.addParameter("-k");
    p.addParameter(talkBackURL);
    p.run();    // Run the process and wait for its termination    

    Console.print("Get Result:");
    while (p.available()>0)
    {
        talkBackCommand[count] = p.read();//
        Console.write(talkBackCommand[count]);
        count++;
    }
    Console.println("");
    Console.print("Command Length: ");
    Console.println(count);

    if (count > 2)
    {
        unsigned char data[50] = {0} ;//The data to be sent to LoRa Node 
        int quota_count = 0;
        int start_pos = 0;
        int stop_pos = 0;
        boolean payload_bit = false;
        for (int i=0;i < count ; i++)
        {
          if ( talkBackCommand[i] == 34 ) 
          {
            if( i > 1) 
            {
              if ( talkBackCommand[i-1] == 92) quota_count--; // ignore the quota if it is after \.
            }
            quota_count++; // discover quota ";
           
          }
          if ( quota_count == 5 && start_pos == 0  ) start_pos = i;
          if ( quota_count == 6 && stop_pos == 0 ) 
          {
            stop_pos = i-1;
             Console.println("MAALIK");
            Console.println(stop_pos);
            //break;
          }
        }

        Console.println("_____________________________________" );
        Console.print("Get Command String: " );
        int j=0;
        for (int i=start_pos+48; i<= 91; i++)
        {
          data[j]=talkBackCommand[i];
          Console.write(data[j]);
          j++;
        }
        Console.println("" );
        
        rf95.send(data, j+1); //Send data to LoRa Node.
        rf95.waitPacketSent();  //wait for sending
        Console.flush(); 
    }
    else
    {
        Console.println("No new command from server");
    }
    delay(1000);
    Console.println("");
}
