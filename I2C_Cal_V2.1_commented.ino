#include <M5Stack.h>                          // Load M5Stack library - only library that needs to be loaded

#define KEYBOARD_I2C_ADDR     0X08            // I2C address for Faces Keyboard
#define KEYBOARD_INT          5               // Interrupt line for Faces Keyboard
float Data1 = 0;                              // Store First number for calculation
float Data2 = 0;                              // Store Secound number for Calculation
char Fun;                                     // Store Function to do ( +, -, *, / )
int CalNum = 0;                               // Number being input, First or Secound
int SumFlag = 0;                              // Flag set after first Calculation 
float Sum;                                    // Store Calculation Result
String Datain;                                // String to store data from keyboard
uint8_t key_val;                              // Get each character from keyboard


void setup()                                  // Setup 
{
  M5.begin();                                 // Start M5Stack library 
  Wire.begin();                               // Start Wire library - does not have to be included
  M5.Lcd.setTextFont(4);                      // Set Text size for all text
  pinMode(KEYBOARD_INT, INPUT_PULLUP);        // Set Int. pin high
  CalNum = 1;                                 // Set as first number in
  Draw_Screen();                              // Draw boxs and line on screen
 }


void loop()                                   // Main Loop
{
  if(digitalRead(KEYBOARD_INT) == LOW)        // Wait Int. line to go low
   {
    Wire.requestFrom(KEYBOARD_I2C_ADDR, 1);   // Request 1 byte from keyboard
    
    while (Wire.available())                  // Loop while character available 
     { 
      uint8_t key_val = Wire.read();          // Read a byte as character
      if(key_val != 0)                        // If a Value was read then
       {    
        if(isDigit(key_val) || key_val == '.')  // If Char. is a Digit or point then
         {
          if( SumFlag == 1 )                    // If Sum Flag = 1 then
           {
            StoreData();                        // Store Data and clear variables
           }
          Datain += (char)key_val;              // Change Value to char. and add to Datain string
          IsNumber();                           // Call IsNumber (input is a number) function
         }
        if( key_val == 'A' || key_val == '+' || key_val == '-' || key_val == '*' || key_val == '/' || key_val == '=' ) // If Value in is a Function Key then
         {
          FunKey(key_val);                      // Call FunKey (input is a function key )
         }
      }
    }
  }   
}           
   

void FunKey( uint8_t key_in )                   // FunKey (Function Key) Function 
 {   
   switch (key_in)                              // Switch on the key_in value
    {
     case 'A':                                  // If key_in is and A then
      M5.Lcd.clear();                           // Clear the Screen
      Draw_Screen();                            // Draw boxs and line on screen
      Data1 = 0;                                // Set Data1 to Zero
      Data2 = 0;                                // Set Data2 to Zero
      Sum = 0;                                  // Set Sum to Zero
      Datain = "                    ";          // Clear Datain String
      CalNum = 1;                               // Set CalNum to one
      Fun = ' ';                                // Set Fun (Function) to Blank
     break;                                     // Exit switch

     case '=':                                  // If key_in is and equal then
      if( Fun == '+' )                          // If Fun (Function) is a Plus then
       {
        Sum = Data1 + Data2;                    // Sum (Total) equals Data1 Plus Data2
       }

      if( Fun == '-' )                          // If Fun (Function) is a Minus then
       {
        Sum = Data1 - Data2;                    // Sum (Total) equals Data1 Minus Data 2
       }

      if( Fun == '*' )                          // If Fun (Function) is a Multiply then
       {  
        Sum = Data1 * Data2;                    // Sum (Total) equals Data1 times Data2
       }

      if( Fun == '/' )                          // If Fun (Function) is a Divide then
       {
        Sum = Data1 / Data2;                    // Sum (Total) equals Data1 Divided by Data2
       }
 
      M5.Lcd.setCursor(105,190);                // Set Cursor location on screen
      M5.Lcd.print(Sum);                        // Print Sum (Total) of calculation
      SumFlag = 1;                              // Set SumFlag to one, indicates first set of calculations done
     break;                                     // Exit switch

     case '+':                                  // If Key_in is and Plus then
      Fun = '+';                                // Set Fun (Function) to plus
      CalNum += 1 ;                             // Set CalNum to CalNum plus one
      Datain = "                 ";             // Clear Datain string
      M5.Lcd.setCursor(20, 140);
      M5.Lcd.print("   ");                      // Print Blanks to screen, clear function box
      M5.Lcd.setCursor(20, 140);                // Set Cursor loaction on screen
      M5.Lcd.print(Fun);                        // Print Fun (Function) on screen
     break;                                     // Exit switch

     case '-':                                  // If key_in is a Minus then
      Fun = '-';                                // Set Fun (Function) to Minus
      CalNum += 1;                              // Set CalNum to CalNum plus one
      Datain = "                 ";             // Clear Datain string
      M5.Lcd.setCursor(20, 140);                // Set Cursor location on screen
      M5.Lcd.print("   ");                      // Print Blanks to screen, clear function box
      M5.Lcd.setCursor(20, 140);                // Set Cursor loaction on screen
      M5.Lcd.print(Fun);                        // Print Fun (Function) on screen   
     break;                                     // Exit switch

     case '*':                                  // If key_in is a Multiply then
      Fun = '*';                                // Set Fun (Function) to Multiply
      CalNum += 1;                              // Set CalNum to CalNum plus one 
      Datain = "                 ";             // Clear Datain string  
      M5.Lcd.setCursor(20, 140);                // Set Cursor location on screen
      M5.Lcd.print("   ");                      // Print Blanks to screen, clear function box 
      M5.Lcd.setCursor(20, 140);                // Set Cursor location on screen
      M5.Lcd.print(Fun);                        // Print Fun (Function) on screen   
     break;                                     // Exit switch

     case '/':                                  // If key_in is a Divide then
      Fun = '/';                                // Set Fun (Function) to Divide
      CalNum += 1;                              // Set CalNum to CalNum plus one  
      Datain = "                 ";             // Clear Datain string  
      M5.Lcd.setCursor(20, 140);                // Set Cursor location on screen
      M5.Lcd.print("   ");                      // Print Blanks to screen, clear function box
      M5.Lcd.setCursor(20, 140);                // Set Cursor location on screen
      M5.Lcd.print(Fun);                        // Print Fun (Function) on screen
     break;                                     // Exit switch

     default:                                   // default for switch
     break;                                     // Exit switch
   } 
 }
 

void StoreData( void )                          // Store Data function
{
 Data1 = Sum;                                   // Store Sum in Data1
 Data2 = 0;                                     // Set Data2 to zero
 SumFlag = 0;                                   // Set SumFlag to zero
 Datain = "                    ";               // Clear Datain string  
 M5.Lcd.setCursor(20, 140);                     // Set Cursor location on screen
 M5.Lcd.print(Fun);                             // Print Fun (Function) on screen
 M5.Lcd.setCursor(70, 100);                     // Set Cursor location on screen
 M5.Lcd.print("                    ");          // Clear Data1 print area
 M5.Lcd.setCursor(70, 140);                     // Set Cursor location on screen
 M5.Lcd.print("                    ");          // Clear Data2 print area
 M5.Lcd.setCursor(70, 100);                     // Set Cursor location on screen
 M5.Lcd.print(Data1);                           // Print Data1 on screen
 M5.Lcd.setCursor(105,190);                     // Set Cursor location on screen
 M5.Lcd.print("                    ");          // Clear Sum print area
}


void IsNumber( void )                           // IsNummber (Is a Number) function
 {
  if( CalNum == 1 )                             // If CalNum (Calculation Number) equals one then
   {
    Data1 = Datain.toFloat();                   // Datal equal Datain converted to a Float number
    M5.Lcd.setCursor(70,100);                   // Set Cursor location on screen
    M5.Lcd.print(Data1);                        // Print Data1 on screen
   } 
         
  if( CalNum >= 2 )                             // If CalNum (Calculation Number) equals two then
   {
    Data2 = Datain.toFloat();                   // Data2 equal Datain converted to a Float number
    M5.Lcd.setCursor(70, 140);                  // Set Cursor location on screen
    M5.Lcd.print(Data2);                        // Print Data1 on screen
   }
 }


 /* X and Y equals upper left corner, W equals with, H equals hight of Box, color set to white */
 void DrawBox( int LocX, int LocY, int W, int H )  // DrawBox (Draw a Box) function
  {
   M5.Lcd.drawLine( LocX, LocY, LocX + W, LocY, TFT_WHITE);          // Draw line at X, Y, X+W, Y, set color to white
   M5.Lcd.drawLine( LocX, LocY + H, LocX + W, LocY + H, TFT_WHITE);  // Draw line at X, Y+H, X+W, Y+H, set color to white
   M5.Lcd.drawLine( LocX, LocY, LocX, LocY + H, TFT_WHITE);          // Draw line at X, Y, X, Y+H, set color to white
   M5.Lcd.drawLine( LocX + W, LocY, LocX + W, LocY + H, TFT_WHITE);  // Draw line at X+W, Y, X+W Y+H, set color to white
  }


 void Draw_Screen( void )                          // Draw Screen function
  {
   M5.Lcd.clear();                                 // Cear the screen
   M5.Lcd.drawLine( 1, 180, 320, 180, TFT_WHITE);  // Draw a line across screen
   M5.Lcd.setCursor( 15,20 );                      // Set Cursor location on screen
   M5.Lcd.print( "FRACTION CALCULATOR" );          // Print FRACTION CALCULATOR on screen
   DrawBox( 50, 95, 250, 32 );                     // Call DrawBox function
   DrawBox( 10, 135, 30, 32 );                     // Call DrawBox function
   DrawBox( 50, 135, 250, 32 );                    // Call DrawBox function
   M5.Lcd.setCursor(10,190);                       // Set Cursor location on screen
   M5.Lcd.print("SUM  =");
  }
