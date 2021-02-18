#include <CubeFinder.h>
#include <Cube.h>

CubeFinder finder;
Cube cube;

void onSolved(Cube* cube)
{
  Serial.println("Solved");
  const CubeState& state = cube->getState();

  if (state.get(32) == CubeState::GREEN)
    Serial.println("Block with number 32 is green!");
}

void onMoved(Cube* cube, uint8_t moveCode)
{
  Serial.print("Move: ");
  Serial.println(Cube::moveToString((Cube::MoveCode)moveCode));
}

void setup() {
  BLEDevice::init("");
  Serial.begin(115200);
  Serial.println("Init...");
  cube.setOnSolve(onSolved);
  cube.setOnMove(onMoved);
}

void loop() {
  if (!cube.isConnected())
  {  
    Serial.println("Scanning...");
    finder.scan(5);

    if (finder.isCubeFound())
    {
      Serial.println("Cube has been found!");
      cube.connect(finder.getCubeDevice());
      cube.requestAllProperties();
    }
  }

  delay(1000);
}
