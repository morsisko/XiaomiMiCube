#include <CubeFinder.h>
#include <Cube.h>
#include <U8g2lib.h>

bool isSolving = false;
bool wasSolved = true;
unsigned long lastMove = 0;
unsigned long solvingStarted = 0;
unsigned long solvingEnded = 0;

//Change to your own display and wiring u8g2(U8G2_R0, /* clock=*/ 33, /* data=*/ 32, /* cs=*/ 26, /* dc=*/ 25)
U8G2_ST7565_ERC12864_ALT_F_4W_SW_SPI u8g2(U8G2_R0, 33, 32, 26, 25);

void onSolved(Cube* cube)
{
  Serial.println("Solved");

  wasSolved = true;
  if (isSolving)
  {
    isSolving = false;
    solvingEnded = millis();

    Serial.println((solvingEnded - solvingStarted) / 1000.f);
  }
}

void onMoved(Cube* cube, uint8_t moveCode)
{
  unsigned long currentTime = millis();

  if (wasSolved)
    wasSolved = false;

  else if (!isSolving && currentTime - lastMove > 10000)
  {
    Serial.println("Solving started");
    solvingStarted = millis();
    isSolving = true;
  }

  lastMove = currentTime;
}

CubeFinder finder;
Cube cube;
void setup() {
  BLEDevice::init("");
  Serial.begin(115200);
  Serial.println("Setup...");
  Serial.setDebugOutput(true);
  cube.setOnSolve(onSolved);
  cube.setOnMove(onMoved);
  u8g2.begin();
  u8g2.setContrast(20);

}

void loop() {
  if (finder.isCubeFound())
  {
    u8g2.clearBuffer();          // clear the internal memory
    u8g2.setFont(u8g2_font_logisoso32_tn); // choose a suitable font
    u8g2.setCursor(0, 40);

    unsigned long diff = 0;
    if (isSolving && solvingStarted)
      diff = millis() - solvingStarted;
      
    else if (!isSolving && solvingStarted && solvingEnded)
      diff = solvingEnded - solvingStarted;

    else
      diff = 0;
      
    u8g2.print(diff / 1000.f, 3);
    u8g2.sendBuffer();          // transfer internal memory to the display
    delay(100);
    return;
  }
  
  Serial.println("Scanning...");
  
  finder.scan(5);

  if (finder.isCubeFound())
  {
    Serial.println(finder.getCubeDevice().toString().c_str());
    cube.connect(finder.getCubeDevice());
    cube.requestAllProperties();
  }

  else
  {
    Serial.println("Couldn't find the device");
  }
  

  delay(5000);
    
}
