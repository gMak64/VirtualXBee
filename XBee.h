class XBee {
  private:
    byte* incomingValues; // Byte array of all possible incoming values
    int incomingValuesLength; // Length of above byte array
    long nextRead; // Time at which the next character will become available
    long timeBetweenMessages; // Time between incoming pieces of data
    int index; // Used to index into the array of data

    void setNextRead() {
      nextRead = millis() + timeBetweenMessages;
    }

    void initialize(byte* s, int sl, long initDelay, long tbm) {
      incomingValues = s;
      incomingValuesLength = sl;
      timeBetweenMessages = tbm;
      index = -1;
      nextRead = millis() + initDelay; // delay first message
    }

  public:
    XBee(byte* s, int sl, long initDelay, long tbm)
    {
      initialize(s, sl, initDelay, tbm);
    }

    XBee(byte* s, int sl)
    {
      initialize (s, sl, 2 * 1000, 1000);
    }

    int available () {
      if (millis() > nextRead) {
        return 1;
      }
      else {
        return 0;
      }
    }

    int read () {
      if (available() > 0 && index < 3) {
        int noSend = random(10);
        if (noSend == 7) {
         incomingValues[3] = incomingValues[0];
        }
        setNextRead();
        index++;
        return incomingValues[index];
      } else {
        return -1;
      }
    }
};


/*

  XBee Simulation Class:

  This class mimics the read functionality of the XBees you
  worked with in class. Initialize the XBee as below:

  ``
  byte INCOMING[4] = {0x00, 0x01, 0x02, 0x03};
  XBee xb(INCOMING, sizeof(INCOMING));
  ``

  INCOMING is a byte array representing all the values the
  XBee could receive during simulation. When a valid read is
  called, one of the bytes is selected, converted to an integer,
  and returned to the caller.

  The xb will not receive any messages for 2 seconds of
  simulation time and then will receive a message every second
  If you would like to change this, initialize the XBee as below

  ``
  byte INCOMING[4] = {0x00, 0x01, 0x02, 0x03};
  XBee xb(INCOMING, sizeof(INCOMING), initDelay, timeBetweenMessages);
  ``

  where
  initDelay - type long:
  how long the xb will wait until it receives its first message

  timeBetweenMessages - type long:
  the time between incoming messages

  --------------------------------------------------------------
  Methods:
  The below methods mirror two of the
  Arduino Software Serial library methods.

  ``
  xb.available()
  ``

  This method returns an integer telling you how many bytes
  are currently available to be read. It will return a 1 if 
  data is avaialable, and 0 if not.

  ``
  xb.read()
  ``

  This method returns the data received by the XBee.
  If no data has been received, this method returns -1.

  No other software serial library methods are implemented
  ---------------------------------------------------------------
  Created 2 April 2020
  By Trishul Nagenalli
  Modified 3 April 2020
  By Grant Mak
*/ 

void setup()
{
  randomSeed(analogRead(0));
}

void loop()
{
}

