# VirtualXBee
This class mimics the read functionality of the XBees you worked with in class. A user-intialized array represents the sensing codes from the 4 other bots in your IDC team. From there, you can read from the array at a constant time interval to simulate reading from Software Serial and grabbing those values to your own Arduino.

## Initialization 
To create an XBee object, you should call the constructor in the following manner:
```arduino
byte INCOMING[4] = {0x00, 0x01, 0x02, 0x03};
XBee xb(INCOMING, sizeof(INCOMING));
```
This will create a set of placeholder data, and an XBee object called xb. For the rest of this tutorial, we will use **xb** as the name of our XBee object. By default, the XBee object will be created with an initial delay time of 2 seconds - nothing will be received during this time. Then, it will be able to receive a message every 1 second. To change this, you can call:
```arduino
byte INCOMING[4] = {0x00, 0x01, 0x02, 0x03};
XBee xb(INCOMING, sizeof(INCOMING), initDelay, tbm);
```
**initDelay** is a time in milliseconds which allows you to set the initial delay time, and **tbm** is a time in milliseconds wich allows you to set the minimum waiting period between successive receives. Both of these are of the type *long*. The delay times are meant to simulate each of the bots doing their IDC tasks before sending out the information they received. Since each bot moves at a different speed, and may not complete their task at the same time, this delay is included to be more representative of what may be happening in real life.

This should be called after the Xbee.h code, outside of any loops (i.e. a global variable).

## Methods
There are two methods that you will need to implement. The first is called with
```arduino
xb.available()
```
This will return an integer telling you if data is available, or in other words, if enough time has passed before your previous read. A **1** signifies that data is available, while a **0** will signify that data is not.

The second method is called with:
```arduino
xb.read()
```
This will return, in succession, one of the four communication codes from the other bot if data is available. If not, then a **-1** will be returned. Think about how you will store this information, taking special care to have 4 unique values before you do your final calculation. There is a random chance that data is lost and you are not able to receive all 4 values. This is done to emulate real life complications, and as such, you should have a timeout method to prevent an infinite loop of doing nothing.

## Data Processing
The data will be initialized as a two bit hexadecimal number. The Least Significant Bit (the rightmost number) will have the relevant information, while the Most Significant Bit (the leftmost number) will have no information. You will be responsible for converting this into a format that your Arduino can process. It is recommended that you convert each of these codes from hexadecimal to binary to get the information you need - there are many resources online if you do not know how to do this. Once you have turned your code into binary, you can dissect it as such:
```arduino
   0000     010              0
  |____|   |___|            |_|
   |       |                |
  Waste  (Continent)  (Object Distance)
```
The continent is a binary representation of that continent's integer, while the object distance represents whether or not an object is close. Refer to the IDC documentation for how specific things are represented. As an example, say you are simulating a round where you are on continent 5, and the other bots are telling you:
* Continent 1, Object Far
* Continent 2, Object Close
* Continent 4, Object Close
* Continent 6, Object Far

You should initialize the XBee as
```arduino
  byte INCOMING[4] = {0x02, 0x05, 0x09, 0x0B};
  XBee xb(INCOMING, sizeof(INCOMING));
```
When you read the data, it will return it to you in integer format, but again, the binary representation will be more telling of that that number represents. Think about some clever math operations you can use to get the info you need out of those integers.

## Authors
Trishul Naganelli

Grant Mak
