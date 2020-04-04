# VirtualXBee
This class mimics the read functionality of the XBees you worked with in class.

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
**initDelay** is a time in milliseconds which allows you to set the initial delay time, and **tbm** is a time in milliseconds wich allows you to set the minimum waiting period between successive receives. Both of these are of the type *long*.

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
This will return, at random, one of the five communication codes from the other bot if data is available. If not, then a **-1** will be returned. Because this is random, you should take special care to have 5 unique values before you do your final calculation.

## Data Processing
The data will be initialized as a two bit hexadecimal number. The Least Significant Bit (the rightmost number) will have the relevant information, while the Most Significant Bit (the leftmost number) will have no information. You will be responsible for converting this into a format that your Arduino can process. It is recommended that you convert each of these codes from hexadecimal to binary - there are many resources online if you do not know how to do this. Once you have turned your code into binary, you can dissect it as such:
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
  byte INCOMING[4] = {0x01, 0x02,0x06, 0x0B};
  XBee xb(INCOMING, sizeof(INCOMING));
```
