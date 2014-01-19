import processing.net.*;//network library

String input = "{1,2;3,4}";
int dataX = 2;//define constant
int dataY = 2;
int[][] data = new int[dataX][dataY];
int spacer;

void setup() 
{
  size(800, 600);
  spacer = 20;
  stroke(0);
  background(255);
}

void draw()
{
  
  /*
  for (int y = 0; y <= dataX; y++)
  {
    for (int x = 0; x <= dataY; x++)
    {
    }
  }
  */
  if (input.charAt(0) == '{')
  {
    for (int y = 0; y <= dataY; y++)
    {
      for (int x = 1; x <= dataX; x++)
      {
        int start = x;
        int end = start;
        while (boolean loop = true)
        {
          if (input.charAt(end) != ',') end++;
          else if (input.charAt(end) != ';') end++;
          else loop = false;
        }
        
      }
    }
  }
}

