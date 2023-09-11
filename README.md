# 2d-and-3d-computer-graphics

## "Foundation Building and Central Building of XJTLU" - 2D Modeling Project

This project is to celebrate the 15th anniversary of XJTLU. I usually study in Foundation Building and Central Building, so I build these two buildings by code and created many interation options.

### Design of hierarchical mode

1.	Main scenario
1)	The background (void background())
+	The background will be darker when it is night, and the background will be lighter when it is morning.
2)	FB (void fb())
+	FB has a concave wall in the middle, some windows, as well as the lines between these windows. Each two windows are adjacent to each other.
3)	CB (void cb())
+	CB has a brace, cube, as well as the concave lines
4)	Trees (void tree1(); void tree2(); void tree3(); void tree4())
+	There are 4 trees in front of the building
5)	Bird (void bird())
+	The bird consists of head, eyes, body, wings, and a tail
+	The bird is flying automatically
6)	Clock (void drawClock())
+	The clock consists of the outline, a minute hand, and an hour hand.
7)	Balloon (void balloon1(); void balloon2(); void balloon3())
+	The balloon consists of lines and sphere
+	There are three balloons swinging automatically
8)	"Happy anniversary!" text (void printBitmapString(void* font, const char* s); int TextOut(float x, float y, const char* cstr); void greetingText())
+	This line follows the current time behind the “Happy anniversary” line.


2.	Interactive operations
1)	Menu
+	Show all the operations that is set in the keyboard
+	This menu has sub-menus to categorize different operations
2)	Switch building between FB and CB
+	Users can choose which building to show in the screen
3)	Heighten the bird
+	Users can heighten the bird while it is flying
4)	Enlarge or shrink the balloon
5)	Set, quicken or slow down the clock
+	Users can set customized clock, quicken or slow down the clock rotation speed
6)	Change the viewport (zoom in/out, move)
+	Users can zoom in to see closely

### Instruction section

1.	Menu operation
+	I create a menu, so that mouse and keyboard can control the display altogether.
+	When we click the right button, we can show the menu and click what we want to operate.
glutCreateMenu is to create the menu structure.
glutAddMenuEntry is to add the option.

For example,
balloonOp = glutCreateMenu(menu);
glutAddMenuEntry("larger", 'm');

we create a new menu balloonOp, and a new button in balloonOp menu. When we click this “larger” button, actually we click on ‘m’ button, which is already set how it will perform in the keyboardInput().

2.	Switch building between FB and CB
+	When we press ‘b’ button/‘Change building’ in the menu, the building will be changed.
+	This is easy to perform by just changing the variable ‘building’ to switch.
Building==0: FB 
Building==1: CB
   

3.	Heighten the bird
+	When we click the left mouse, the bird will fly higher.
+	Variable ‘birdy’, which indicates the y position of the bird, is larger once we press the left mouse.
     

4.	Enlarge or shrink the balloon
+	When we click the ‘n’, the balloon will be smaller
When we click the ‘m’, the balloon will be larger
+	Variable ‘bp’, which indicates the scale of balloon, is larger once we press ‘m’, or smaller once we press ’n’.

    

5.	Set, quicken or slow down the clock
+	When we choose the ‘clock operations’ in the menu, the clock will be changed correspondingly.
+	Variable ‘clock’ can set the current o’clock.
+	We can use ‘k’ ‘l’ button or ‘quicker’ ‘slower’ in the menu to change the clock rotation speed
6-18 is daytime, while 18-24-6 is nighttime.
+	Variable ‘cp’, which indicates the rotation angle of clock, is quicker once we press ‘k’, or slower once we press ’l’.

6.	Change the viewport (zoom in/out, move)
We can use ‘w’ ’a’ ’s’ ’d’  ‘-’ ’+’ button or zoom in/out in the menu to operate the viewport

7.	Simplified methods (glArc, glCircle, glLines, glRect, glTri)
I create a series of method, including glArc, glCircle, glLines, glRect, glTri, in substitute of long code of creating these components every time.


### Display of Result

<img width="243" alt="image" src="https://github.com/sophiefeifeifeiya/2d-and-3d-computer-graphics/assets/75290925/80f335a5-9c55-4ba5-9c04-adbbd1f3dc18">

<img width="245" alt="image" src="https://github.com/sophiefeifeifeiya/2d-and-3d-computer-graphics/assets/75290925/6d0554dc-5265-4366-a641-b758a29b5f55">


## "Minimalist Home" - 3D Modeling Project

### Design of hierarchical mode

![WeChat94b985ba5552b08a8c9fe17f9d253592](https://github.com/sophiefeifeifeiya/2d-and-3d-computer-graphics/assets/75290925/3be73683-6e3b-4725-8a1e-fb142bd79a03)


### Instruction section

![WeChat1f313f408ead920cde925b0dd3b31947](https://github.com/sophiefeifeifeiya/2d-and-3d-computer-graphics/assets/75290925/b09bedf6-282f-480b-bd04-ab0024c917dd)

### Display of Result

![menu](https://github.com/sophiefeifeifeiya/2d-and-3d-computer-graphics/assets/75290925/c2988ff9-6906-4cd5-ac22-75672081e296)
