/* Name: Jia-Shu(Joseph) Chen  ID: 11204321
   CIS22B Assignment 8 MW
   Compiler GNU GCC Compiler on Codeblocks*/
#include <iostream>
#include <iomanip>
#include <cctype>
#include <cstring>
#include <string>
#include <cstdlib>
#include <fstream>

using namespace std;
class Quadrilateral
{
protected:
    string type;
    int firstside;
    int secondside;
public:
    virtual ~Quadrilateral(){}
    virtual int area() = 0;
    virtual int perimeter() = 0;
    virtual int getfirstside() = 0;
    virtual int getsecondside() = 0;
    virtual string gettype() = 0;
};
ostream& operator<<(ostream&, Quadrilateral*);
Quadrilateral* createQuadrilateralFromString(string);

class Rectangle : public Quadrilateral
{
public:
    Rectangle(string, int, int);
    ~Rectangle(){}
    int getfirstside() {return firstside;}
    int getsecondside() {return secondside;}
    string gettype() {return type;}
    int area();
    int perimeter();

};

class Square : public Rectangle
{
public:
    Square(string, int);
    ~Square() {}
    string gettype() {return type;}
};

class Parallelogram : public Quadrilateral
{
protected:
    int height;
public:
    Parallelogram(string, int, int, int);
    ~Parallelogram() {}
    int getfirstside() {return firstside;}
    int getsecondside() {return secondside;}
    int area();
    int perimeter();
    string gettype() {return type;}
};

class Rhombus : public Parallelogram
{
public:
    ~Rhombus() {}
    Rhombus(string, int, int);
    string gettype() {return type;}
};

int main()
{
    const string filename = "Assignment8datafile.txt";   // use your filename here
    ifstream fin(filename.c_str());
    if (!fin)
    {
        cerr << "Unable to open " << filename << endl;
        exit(1);
    }
    string buffer;
    Quadrilateral* ptrQuad;
    while (getline(fin,buffer))
    {
        // Process only valid input
        if (buffer.size() > 1)
        {
            ptrQuad = createQuadrilateralFromString(buffer);
            cout << ptrQuad << endl;
            delete ptrQuad;
        }
    }
    fin.close();
}

Rhombus::Rhombus(string t, int side, int h) : Parallelogram(t, side, side, h)
{

}

Parallelogram::Parallelogram(string t, int one, int two, int h)
{
    type = t;
    firstside = one;
    secondside = two;
    height = h;
}

Square::Square(string t, int s) : Rectangle(t, s, s)
{

}

Rectangle::Rectangle(string t, int s, int stwo)
{
    type = t;
    firstside = s;
    secondside = stwo;
}

ostream& operator<<(ostream&out, Quadrilateral *quad)
{
    if(quad->gettype() == "rectangle")
    {
        out << "Rectangle:  sides " << quad->getfirstside() << " and " << quad->getsecondside() << " area= " << quad->area() << " perimeter= " << quad->perimeter();
        return out;
    }
    if(quad->gettype() == "square")
    {
        out << "Square: side " << quad->getfirstside() << " area= " << quad->area() << " perimeter= " << quad->perimeter();
        return out;
    }
    if(quad->gettype() == "parallelogram")
    {
        out << "Parallelogram: sides " << quad->getfirstside() << " and " << quad->getsecondside() << " area= " << quad->area() << " perimeter= " << quad->perimeter();
        return out;
    }
    if(quad->gettype() == "rhombus")
    {
        out << "Rhombus: side " << quad->getfirstside() << " area= " << quad->area() << " perimeter= " << quad->perimeter();
        return out;
    }
    return out;
}

int Rectangle::area()
{
    int areavalue;
    return areavalue = firstside*secondside;
}

int Rectangle::perimeter()
{
    int perimetervalue;
    return perimetervalue = (2*firstside)+(2*secondside);
}

int Parallelogram::area()
{
    int areavalue;
    return areavalue = firstside * height;
}

int Parallelogram::perimeter()
{
    int perimetervalue;
    return perimetervalue = (2*firstside) + (2*secondside);
}

Quadrilateral* createQuadrilateralFromString(string buffer)
{
    string tempbuffer;
    string temptype;
    string temptempsideone;
    string temptempsidetwo;
    string temptempheight;
    int tempsideone;
    int tempsidetwo;
    int tempheight;
    temptype = buffer.substr(0,9);
    if(temptype == "rectangle")
    {
        if(buffer.length() == 13)
        {
            temptempsideone = buffer.at(10);
            temptempsidetwo = buffer.at(12);
            tempsideone = temptempsideone[0] - '0';
            tempsidetwo = temptempsidetwo[0] - '0';
            return new Rectangle(temptype, tempsideone, tempsidetwo);
        }
        else if(buffer.length() == 14)
        {
            tempbuffer = buffer.substr(10,13);
            tempsideone = 10*(tempbuffer[0] - '0') + (tempbuffer[1] - '0');
            tempsidetwo = tempbuffer[3] - '0';
            return new Rectangle(temptype, tempsideone, tempsidetwo);
        }
        else if(buffer.length() == 15)
        {
            tempbuffer = buffer.substr(10,14);
            tempsideone = 10*(tempbuffer[0] - '0') + (tempbuffer[1] - '0');
            tempsidetwo = 10*(tempbuffer[3] - '0') + (tempbuffer[4] - '0');
            return new Rectangle(temptype, tempsideone, tempsidetwo);
        }
    }
    temptype = buffer.substr(0,6);
    if(temptype == "square")
    {
        tempbuffer = buffer.at(7);
        tempsideone = tempbuffer[0] - '0';
        return new Square(temptype, tempsideone);
    }
    temptype = buffer.substr(0,13);
    if(temptype == "parallelogram")
    {
        temptempsideone = buffer.at(14);
        temptempsidetwo = buffer.at(16);
        temptempheight = buffer.at(18);
        tempsideone = temptempsideone[0] - '0';
        tempsidetwo = temptempsidetwo[0] - '0';
        tempheight = temptempheight[0] - '0';
        return new Parallelogram(temptype, tempsideone, tempsidetwo, tempheight);
    }
    temptype = buffer.substr(0,7);
    if(temptype == "rhombus")
    {
        if(buffer.length() == 11)
        {
            tempbuffer = buffer.at(8);
            tempsideone = tempbuffer[0] - '0';
            temptempheight = buffer.at(10);
            tempheight = temptempheight[0] - '0';
            return new Rhombus(temptype, tempsideone, tempheight);
        }
        if(buffer.length() == 12)
        {
            tempbuffer = buffer.substr(8,11);
            tempsideone = 10*(tempbuffer[0]-'0') + (tempbuffer[1]-'0');
            tempheight = tempbuffer[3]-'0';
            return new Rhombus(temptype, tempsideone, tempheight);
        }
    }
    return 0;
}


