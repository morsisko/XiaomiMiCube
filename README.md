# XiaomiMiCube
A library that allows you to connect ESP32 with Xiaomi Rubiks Cube over BLE

# Demo
[![Video](http://img.youtube.com/vi/8LSAVdsl4qg/0.jpg)](http://www.youtube.com/watch?v=8LSAVdsl4qg)

Source code of this demo: [Click](examples/lcd_timer/lcd_timer.ino)
# Connecting
Before using this library, make sure you use the newest version of BLE library.

Firstly you need to make your cube discoverable, to do so turn any of its faces. Your cube should make a beep.

To find your device you may use `CubeFinder`

```cpp
BLEDevice::init("");
Cube cube;
CubeFinder finder;
finder.scan(5); // Scan BLE devices for 5 seconds
if (finder.isCubeFound()) {
  cube.connect(finder.getCubeDevice());
}
```

# Callbacks
You may bind callbacks to your `Cube`, so your function will be executed on each move or whenever the cube is solved.

```cpp
void onSolved(Cube* cube)
{
  //events on cube solved...
}

void onMoved(Cube* cube, uint8_t moveCode)
{
  //events on moved...
}

cube.setOnSolve(onSolved);
cube.setOnMove(onMoved);
```

# Requesting data
You may request data such as battery voltage, total moves that you have ever made on your cube, current firmware version and cube unique id. Example of getting moves count:

```cpp
cube.requestTotalMoves();
delay(1000); // wait for the BLE reply
uint32_t moves = cube.getTotalMoves();
```

# Cube state
You can also check whenever cube is in particular state. To do so you need to generate the cube state (for example in the onMove callback, but you can do it everywhere).

```cpp
const CubeState& state = cube.getState();
if (state.get(32) == CubeState::Color::Green) {
  // check whether the middle block on the green face is green, should be always true
}
```

Ids of particular blocks:
![Blocks](https://github.com/morsisko/XiaomiMiCube/blob/master/positions.png?raw=true)
