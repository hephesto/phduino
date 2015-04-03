// floatToString.h
//
// Tim Hirzel
// tim@growdown.com
// March 2008
// float to string
// 
// If you don't save this as a .h, you will want to remove the default arguments 
//     uncomment this first line, and swap it for the next.  I don't think keyword arguments compile in .pde files

//char * floatToString(char * outstr, float value, int places, int minwidth=, bool rightjustify) {
char * floatToString(char * outstr, float value, int places, int minwidth=0, bool rightjustify=false) {
    // this is used to write a float value to string, outstr.  oustr is also the return value.
    int digit;
    float tens = 0.1;
    int tenscount = 0;
    int i;
    float tempfloat = value;
    int c = 0;
    int charcount = 1;
    int extra = 0;
    // make sure we round properly. this could use pow from <math.h>, but doesn't seem worth the import
    // if this rounding step isn't here, the value  54.321 prints as 54.3209

    // calculate rounding term d:   0.5/pow(10,places)  
    float d = 0.5;
    if (value < 0)
        d *= -1.0;
    // divide by ten for each decimal place
    for (i = 0; i < places; i++)
        d/= 10.0;    
    // this small addition, combined with truncation will round our values properly 
    tempfloat +=  d;

    // first get value tens to be the large power of ten less than value    
    if (value < 0)
        tempfloat *= -1.0;
    while ((tens * 10.0) <= tempfloat) {
        tens *= 10.0;
        tenscount += 1;
    }

    if (tenscount > 0)
        charcount += tenscount;
    else
        charcount += 1;

    if (value < 0)
        charcount += 1;
    charcount += 1 + places;

    minwidth += 1; // both count the null final character
    if (minwidth > charcount){        
        extra = minwidth - charcount;
        charcount = minwidth;
    }

    if (extra > 0 and rightjustify) {
        for (int i = 0; i< extra; i++) {
            outstr[c++] = ' ';
        }
    }

    // write out the negative if needed
    if (value < 0)
        outstr[c++] = '-';

    if (tenscount == 0) 
        outstr[c++] = '0';

    for (i=0; i< tenscount; i++) {
        digit = (int) (tempfloat/tens);
        itoa(digit, &outstr[c++], 10);
        tempfloat = tempfloat - ((float)digit * tens);
        tens /= 10.0;
    }

    // if no places after decimal, stop now and return

    // otherwise, write the point and continue on
    if (places > 0)
    outstr[c++] = '.';


    // now write out each decimal place by shifting digits one by one into the ones place and writing the truncated value
    for (i = 0; i < places; i++) {
        tempfloat *= 10.0; 
        digit = (int) tempfloat;
        itoa(digit, &outstr[c++], 10);
        // once written, subtract off that digit
        tempfloat = tempfloat - (float) digit; 
    }
    if (extra > 0 and not rightjustify) {
        for (int i = 0; i< extra; i++) {
            outstr[c++] = ' ';
        }
    }


    outstr[c++] = '\0';
    return outstr;
}


/*  EXAMPLE APPLICATION
 #include "floatToString.h"  //set to whatever is the location of floatToStrig

 void setup() {

 Serial.begin(9600);

 char buffer[25]; // just give it plenty to write out any values you want to test
 // ==========================================
 // now run a series on the floatToString function

 // looking at the precision of the float

 Serial.println("floatToString(buffer, 1000000.321 , 5);");
 Serial.println(floatToString(buffer, 1000000.321, 5)); 
 Serial.println();
 Serial.println("floatToString(buffer, 100000.321 , 5);");
 Serial.println(floatToString(buffer, 100000.321, 5)); 
 Serial.println();
 Serial.println("floatToString(buffer, 10000.321 , 5);");
 Serial.println(floatToString(buffer, 10000.321, 5)); 
 Serial.println();  
 Serial.println("floatToString(buffer, 1000.321 , 5);");
 Serial.println(floatToString(buffer, 1000.321, 5)); 
 Serial.println();
 Serial.println("floatToString(buffer, 100.321 , 5);");
 Serial.println(floatToString(buffer, 100.321, 5)); 
 Serial.println();

 // ==========================================
 // looking at effect of changing precision
 Serial.println("floatToString(buffer, 100000.321 , 6);");
 Serial.println(floatToString(buffer, 100000.321, 6));
 Serial.println();
 Serial.println("floatToString(buffer, 100000.321 , 7);");
 Serial.println(floatToString(buffer, 100000.321, 7));
 Serial.println();
 Serial.println("floatToString(buffer, 100000.321 , 8);");
 Serial.println(floatToString(buffer, 100000.321, 8));
 Serial.println();
 Serial.println("floatToString(buffer, 100000.321 , 9);");
 Serial.println(floatToString(buffer, 100000.321, 9));
 Serial.println();


 // ==========================================

 // check negatives and rounding, and some edge cases
 Serial.println("floatToString(buffer, -5004.321 , 5);");
 Serial.println(floatToString(buffer, -5004.321 , 5)); 
 Serial.println();

 Serial.println("floatToString(buffer, 99.999 , 3); ");
 Serial.println(floatToString(buffer, 99.999 , 3)); 
 Serial.println();

 Serial.println("floatToString(buffer, 100, 1);");
 Serial.println(floatToString(buffer, 100, 1)); 
 Serial.println();

 Serial.println("floatToString(buffer, -100.999 , 1);");
 Serial.println(floatToString(buffer, -100.999 , 1)); 
 Serial.println();

 Serial.println("floatToString(buffer, -54.321 , 0);");
 Serial.println(floatToString(buffer, -54.321 , 0)); 
 Serial.println();

 Serial.println("floatToString(buffer, 0.321 , 5);");
 Serial.println(floatToString(buffer, 0.321 , 5));    
 Serial.println();

 Serial.println("floatToString(buffer, -1.0001 , 5);");
 Serial.println(floatToString(buffer, -1.0001 , 5));   
 Serial.println();

 Serial.println("floatToString(buffer, -0.000001 , 5);");
 Serial.println(floatToString(buffer, -0.000001 , 5)); 
 Serial.println();

 Serial.println("floatToString(buffer, 0.000001 , 5);");
 Serial.println(floatToString(buffer, 0.000001 , 5)); 
 Serial.println();

 Serial.println("floatToString(buffer, -0.00001 , 5);");
 Serial.println(floatToString(buffer, -0.00001 , 5)); 
 Serial.println();

 Serial.println("floatToString(buffer, 0.000099 , 5);");
 Serial.println(floatToString(buffer, 0.000099 , 5)); 
 Serial.println();

 // alternative technique that depends on <stdio.h>
 //Serial.println("Serial.println(dtostrf(-1.0001, 2, 5, s));");
 //char s[32];
 // Serial.println(dtostrf(-1.0001, 2, 5, s)));

 delay(1000);
 Serial.println();

 }

 void loop() {
 }
*/

