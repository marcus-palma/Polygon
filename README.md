A small C++ CLI application with a simple interpreter and dynamic file loading to enable easy creation and usage of geometric shape area calculations.

Polygon CLI flow:
  1. Polygon prompts the user with a list of found Polygon shape files in ".\Shapes\".
  2. User selects a shape by pressing key 1 to 9.
  3. Based on the Polygon shape file content, Polygon prompts the user with a question containing explanation of syntax of data to input in order to calculate the area of the shape.
  4. User inputs the data.
  5. Based on the Polygon shape file content, Polygon performs given arithmetic operations with the given user input data to calculate the geometrical area.

Polygon shape files expected location:
  In a directory named "Shapes" in same directory as the "Polygon" program (.\Shapes\)

Polygon shape files expected name:
  Starting with "Polygon_", followed by any text ending with ".txt" (Polygon_*.txt)

Polygon shape files content expected keywords and syntax:
  Three lines of text separated with a "Line Feed" (LF) character are expected as following (3):
    1. Name: <text>: Indicates a line containing the name of the geometric shape, where <text> is the name.
    2. Question: <text>: Indicates a line containing the user prompt with description of the expected syntax of user input, where <text> is the user prompt.
    3. Area: <area-script>: Indicates a line containing the Area script, where <area-script> is the Area script.

Area script keywords and their syntax:
  • parameter: A parameter for user input, which expects an integer value.
  • multiply <parameter | int32>: An operator that multiplies the current result with the following parameter or integer value.
  • divide <parameter | int32>: An operator that divides the current result with the following parameter or integer value.
  • power <parameter | int32>: An operator that sets the current result to the power of the following parameter or integer value.


Examples of Polygon shape files (4):

1. Polygon_Circle.txt:
Name: Circle
Question: Please enter the length of the radius of the circle.
Area: parameter power 2 multiply 3

2. Polygon_Rectangle.txt:
Name: Rectangle
Question: Please enter the width and length of the rectangle, separated by space.
Area: parameter multiply parameter

3. Polygon_Square.txt:
Name: Square
Question: Please enter the length of the sides of the square.
Area: parameter power 2

4. Polygon_Triangle.txt:
Name: Triangle
Question: Please enter the width and length of the triangle, separated by space.
Area: parameter multiply parameter divide 2