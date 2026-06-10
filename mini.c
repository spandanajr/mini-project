#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ROWS 30
#define COLS 70
#define MAX_SHAPES 100

#define LINE 1
#define RECTANGLE 2
#define TRIANGLE 3
#define CIRCLE 4

char canvas[ROWS][COLS];

typedef struct
{
    int id;
    int type;
    int active;

    int x1, y1;
    int x2, y2;
    int x3, y3;

    int width;
    int height;
    int radius;

} Shape;

Shape shapes[MAX_SHAPES];

int shapeCount = 0;
int nextID = 1;

/* ---------------- Canvas Functions ---------------- */

void clearCanvas()
{
    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLS; j++)
        {
            canvas[i][j] = '_';
        }
    }
}

void displayCanvas()
{
    printf("\n");

    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLS; j++)
        {
            printf("%c ", canvas[i][j]);
        }
        printf("\n");
    }
}

void setPixel(int x, int y, char ch)
{
    if(x >= 0 && x < ROWS && y >= 0 && y < COLS)
    {
        canvas[x][y] = ch;
    }
}

/* ---------------- Drawing Algorithms ---------------- */

void drawLineAlgo(int x1, int y1, int x2, int y2)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);

    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;

    int err = dx - dy;

    while(1)
    {
        setPixel(x1, y1, '*');

        if(x1 == x2 && y1 == y2)
            break;

        int e2 = 2 * err;

        if(e2 > -dy)
        {
            err -= dy;
            x1 += sx;
        }

        if(e2 < dx)
        {
            err += dx;
            y1 += sy;
        }
    }
}

void drawRectangleAlgo(int x, int y, int width, int height)
{
    for(int i = y; i < y + width; i++)
    {
        setPixel(x, i, '*');
        setPixel(x + height - 1, i, '*');
    }

    for(int i = x; i < x + height; i++)
    {
        setPixel(i, y, '*');
        setPixel(i, y + width - 1, '*');
    }
}

void drawTriangleAlgo(int x1,int y1,int x2,int y2,int x3,int y3)
{
    drawLineAlgo(x1,y1,x2,y2);
    drawLineAlgo(x2,y2,x3,y3);
    drawLineAlgo(x3,y3,x1,y1);
}

void drawCircleAlgo(int xc,int yc,int r)
{
    int x = 0;
    int y = r;
    int d = 3 - 2 * r;

    while(y >= x)
    {
        setPixel(xc+x,yc+y,'*');
        setPixel(xc-x,yc+y,'*');
        setPixel(xc+x,yc-y,'*');
        setPixel(xc-x,yc-y,'*');

        setPixel(xc+y,yc+x,'*');
        setPixel(xc-y,yc+x,'*');
        setPixel(xc+y,yc-x,'*');
        setPixel(xc-y,yc-x,'*');

        x++;

        if(d > 0)
        {
            y--;
            d += 4*(x-y)+10;
        }
        else
        {
            d += 4*x+6;
        }
    }
}

/* ---------------- Rendering ---------------- */

void renderScene()
{
    clearCanvas();

    for(int i = 0; i < shapeCount; i++)
    {
        if(!shapes[i].active)
            continue;

        switch(shapes[i].type)
        {
            case LINE:
                drawLineAlgo(
                    shapes[i].x1,
                    shapes[i].y1,
                    shapes[i].x2,
                    shapes[i].y2
                );
                break;

            case RECTANGLE:
                drawRectangleAlgo(
                    shapes[i].x1,
                    shapes[i].y1,
                    shapes[i].width,
                    shapes[i].height
                );
                break;

            case TRIANGLE:
                drawTriangleAlgo(
                    shapes[i].x1,
                    shapes[i].y1,
                    shapes[i].x2,
                    shapes[i].y2,
                    shapes[i].x3,
                    shapes[i].y3
                );
                break;

            case CIRCLE:
                drawCircleAlgo(
                    shapes[i].x1,
                    shapes[i].y1,
                    shapes[i].radius
                );
                break;
        }
    }
}

/* ---------------- Add Functions ---------------- */

void addLine()
{
    Shape s;

    s.id = nextID++;
    s.type = LINE;
    s.active = 1;

    printf("Enter x1 y1 x2 y2: ");
    scanf("%d%d%d%d",&s.x1,&s.y1,&s.x2,&s.y2);

    shapes[shapeCount++] = s;

    printf("Line Added. ID = %d\n",s.id);
}

void addRectangle()
{
    Shape s;

    s.id = nextID++;
    s.type = RECTANGLE;
    s.active = 1;

    printf("Enter x y width height: ");
    scanf("%d%d%d%d",
          &s.x1,
          &s.y1,
          &s.width,
          &s.height);

    shapes[shapeCount++] = s;

    printf("Rectangle Added. ID = %d\n",s.id);
}

void addTriangle()
{
    Shape s;

    s.id = nextID++;
    s.type = TRIANGLE;
    s.active = 1;

    printf("Enter x1 y1 x2 y2 x3 y3: ");

    scanf("%d%d%d%d%d%d",
          &s.x1,&s.y1,
          &s.x2,&s.y2,
          &s.x3,&s.y3);

    shapes[shapeCount++] = s;

    printf("Triangle Added. ID = %d\n",s.id);
}

void addCircle()
{
    Shape s;

    s.id = nextID++;
    s.type = CIRCLE;
    s.active = 1;

    printf("Enter centerX centerY radius: ");
    scanf("%d%d%d",
          &s.x1,
          &s.y1,
          &s.radius);

    shapes[shapeCount++] = s;

    printf("Circle Added. ID = %d\n",s.id);
}

/* ---------------- List Shapes ---------------- */

void listShapes()
{
    printf("\n----- OBJECT LIST -----\n");

    for(int i = 0; i < shapeCount; i++)
    {
        if(shapes[i].active)
        {
            printf("ID: %d  ",shapes[i].id);

            switch(shapes[i].type)
            {
                case LINE:
                    printf("LINE\n");
                    break;

                case RECTANGLE:
                    printf("RECTANGLE\n");
                    break;

                case TRIANGLE:
                    printf("TRIANGLE\n");
                    break;

                case CIRCLE:
                    printf("CIRCLE\n");
                    break;
            }
        }
    }
}

/* ---------------- Delete Shape ---------------- */

void deleteShape()
{
    int id;

    printf("Enter Shape ID: ");
    scanf("%d",&id);

    for(int i = 0; i < shapeCount; i++)
    {
        if(shapes[i].id == id && shapes[i].active)
        {
            shapes[i].active = 0;

            printf("Deleted Successfully.\n");
            return;
        }
    }

    printf("Shape Not Found.\n");
}

/* ---------------- Modify Shape ---------------- */

void modifyShape()
{
    int id;

    printf("Enter Shape ID: ");
    scanf("%d",&id);

    for(int i = 0; i < shapeCount; i++)
    {
        if(shapes[i].id == id && shapes[i].active)
        {
            switch(shapes[i].type)
            {
                case LINE:
                    printf("New x1 y1 x2 y2: ");
                    scanf("%d%d%d%d",
                          &shapes[i].x1,
                          &shapes[i].y1,
                          &shapes[i].x2,
                          &shapes[i].y2);
                    break;

                case RECTANGLE:
                    printf("New x y width height: ");
                    scanf("%d%d%d%d",
                          &shapes[i].x1,
                          &shapes[i].y1,
                          &shapes[i].width,
                          &shapes[i].height);
                    break;

                case TRIANGLE:
                    printf("New x1 y1 x2 y2 x3 y3: ");
                    scanf("%d%d%d%d%d%d",
                          &shapes[i].x1,
                          &shapes[i].y1,
                          &shapes[i].x2,
                          &shapes[i].y2,
                          &shapes[i].x3,
                          &shapes[i].y3);
                    break;

                case CIRCLE:
                    printf("New centerX centerY radius: ");
                    scanf("%d%d%d",
                          &shapes[i].x1,
                          &shapes[i].y1,
                          &shapes[i].radius);
                    break;
            }

            printf("Shape Updated.\n");
            return;
        }
    }

    printf("Shape Not Found.\n");
}

/* ---------------- Main ---------------- */

int main()
{
    int choice;

    clearCanvas();

    while(1)
    {
        renderScene();

        printf("\n====== 2D GRAPHICS EDITOR ======\n");
        printf("1. Add Line\n");
        printf("2. Add Rectangle\n");
        printf("3. Add Triangle\n");
        printf("4. Add Circle\n");
        printf("5. Delete Shape\n");
        printf("6. Modify Shape\n");
        printf("7. List Shapes\n");
        printf("8. Display Canvas\n");
        printf("9. Exit\n");

        printf("Enter Choice: ");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:
                addLine();
                break;

            case 2:
                addRectangle();
                break;

            case 3:
                addTriangle();
                break;

            case 4:
                addCircle();
                break;

            case 5:
                deleteShape();
                break;

            case 6:
                modifyShape();
                break;

            case 7:
                listShapes();
                break;

            case 8:
                renderScene();
                displayCanvas();
                break;

            case 9:
                printf("Thank You!\n");
                return 0;

            default:
                printf("Invalid Choice!\n");
        }
    }

    return 0;
}
