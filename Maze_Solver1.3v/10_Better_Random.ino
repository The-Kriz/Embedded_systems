/*
   (X:0,Y:0)          (X:24,Y:0)                    +
   ----------------------            -- <- X-> ++   +
   |_                |  |                           Y
   |                    |                           |
   |                    |     ^                     |
   |                    |     | 0 North
   |                    |
   |                    |     -> 1 East
   |x|                | |
   ----------------------
   (X:0,Y:24)       (X:24,Y:24)

  North: 0
  East: 1
  South: 2
  West: 3
  
*/
////////////////////////////////////////////////////////////////////////////////////////////////////////
// MAZE VARIABLES
const int MAZE_WIDTH = 25;
const int MAZE_HEIGHT = 25;
int maze[MAZE_WIDTH][MAZE_HEIGHT] = {0};   // Define the maze and initialize all cells to unvisited (0)
//int current_x = 0;                                                        // CELLS ON Left:24/RIGHT:0
int current_y = 24;
////////////////////////////////////////////////////////////////////////////////////////////////////////
bool isCellVisited(int x, int y)                        // Function to check if a cell has been visited
{
  return maze[x][y] == 1;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
void markCellAsVisited(int x, int y)                               // Function to mark a cell as visited
{
  maze[x][y] = 1;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
void updateCurrentXY(int turn, int orientation)                                           // maze update
{
  if (turn == 0) // Turn left
  {
    switch (orientation)
    {
      case 0:
        current_y--;
        break;
      case 1:
        current_x--;
        break;
      case 2:
        current_y++;
        break;
      case 3:
        current_x++;
        break;
    }
  }
  else if (turn == 1)
  {
    switch (orientation)
    {
      case 0:
        current_y++;
        break;
      case 1:
        current_x++;
        break;
      case 2:
        current_y--;
        break;
      case 3:
        current_x--;
        break;
    }
  }

  else
  {
    switch (orientation)
    {
      case 0:
        current_y--;
        break;
      case 1:
        current_x++;
        break;
      case 2:
        current_y++;
        break;
      case 3:
        current_x--;
        break;
    }
  }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
void Make_Better_Decision()
{
  int Wall_On_Left = Left_Wall();
  int Wall_On_Center = Center_Wall();
  int Wall_On_Right = Right_Wall();
  
  // Print wall information using Serial
  Serial.print("Wall on Left: ");
  Serial.println(Wall_On_Left);
  Serial.print("Wall on Center: ");
  Serial.println(Wall_On_Center);
  Serial.print("Wall on Right: ");
  Serial.println(Wall_On_Right);

  // Print wall information using Bluetooth
  bt.print("Wall on Left: ");
  bt.println(Wall_On_Left);
  bt.print("Wall on Center: ");
  bt.println(Wall_On_Center);
  bt.print("Wall on Right: ");
  bt.println(Wall_On_Right);

  // Initialize random seed
  int n = rand() % 2;
  
  if (Wall_On_Left && Wall_On_Center && Wall_On_Right)
  {
    Serial.println("U-Turn");
    bt.println("U-Turn");
    MPU_Move_Forward(U_Turn_Check_ForwardTargetDistance, U_Turn_Check_ForwardTargetDistance);
    if (Left_Wall() and Center_Wall() and Right_Wall())
    {
      U_Turn();
      markCellAsVisited(current_x, current_y);
    }
  }
  else if (Wall_On_Left && Wall_On_Right)
  {
    Serial.println("Move Forward");
    bt.println("Move Forward");
    Move_Forward();
    updateCurrentXY( 3, current_orientation);
    markCellAsVisited(current_x, current_y);
  }
  else if (Wall_On_Left && Wall_On_Center)
  {
    Serial.println("Turn Right");
    bt.println("Turn Right");
    Turn_Right();
    updateCurrentXY( 1, current_orientation);
    markCellAsVisited(current_x, current_y);
  }
  else if (Wall_On_Right && Wall_On_Center)
  {
    Serial.println("Turn Left");
    bt.println("Turn Left");
    Turn_Left();
    updateCurrentXY( 0, current_orientation);
    markCellAsVisited(current_x, current_y);

  }
  else if (Wall_On_Left)
  {
    Serial.println("Random Decision - Right or Forward");
    bt.println("Random Decision - Right or Forward");
    if (n == 0)
    {
      Serial.println("Move Forward");
      bt.println("Move Forward");
      Move_Forward();
      updateCurrentXY( 3, current_orientation);
      markCellAsVisited(current_x, current_y);
    }
    else
    {
      Serial.println("Turn Right");
      bt.println("Turn Right");
      Turn_Right();
      updateCurrentXY( 1, current_orientation);
      markCellAsVisited(current_x, current_y);

    }
  }
  else if (Wall_On_Right)
  {
    Serial.println("Random Decision - Left or Forward");
    bt.println("Random Decision - Left or Forward");
    if (n == 0)
    {
      Serial.println("Move Forward");
      bt.println("Move Forward");
      MPU_Move_Forward();
      updateCurrentXY( 3, current_orientation);
      markCellAsVisited(current_x, current_y);
    }
    else
    {
      Serial.println("Turn Left");
      bt.println("Turn Left");
      Turn_Left();
      updateCurrentXY( 0, current_orientation);
      markCellAsVisited(current_x, current_y);

    }
  }
  else if (Wall_On_Center)
  {
    Serial.println("Random Decision - Left or Right");
    bt.println("Random Decision - Left or Right");
    if (n == 0)
    {
      Serial.println("Turn Right");
      bt.println("Turn Right");
      Turn_Right();
      updateCurrentXY( 1, current_orientation);
      markCellAsVisited(current_x, current_y);

    }
    else
    {
      Serial.println("Turn Left");
      bt.println("Turn Left");
      Turn_Left();
      updateCurrentXY( 0, current_orientation);
      markCellAsVisited(current_x, current_y);

    }
  }
  else
  {
    Serial.println("No Wall");
    bt.println("No Wall");
    if (n == 0)
    {
      Turn_Right();
      updateCurrentXY( 1, current_orientation);
      markCellAsVisited(current_x, current_y);
    }
    else
    {
      Turn_Left();
      updateCurrentXY( 0, current_orientation);
      markCellAsVisited(current_x, current_y);
    }
  }
}
