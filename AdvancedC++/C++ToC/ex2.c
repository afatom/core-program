#include <stdio.h>
#include <stdlib.h>

typedef void(*GenericFunc)(void);

typedef enum Color_ColorEnum {
	_Color__RED, _Color__GREEN, _Color__DEFAULT
} Color_ColorEnum;

typedef struct Color Color;
 
typedef struct Scaleable Scaleable;
typedef struct Shape Shape;
typedef struct Circle Circle;
typedef struct Rectangle Rectangle;

void _Scaleable__VirtualDtor(Scaleable* const this);
void _Scaleable__VirtualScale(void);
void _Scaleable__ScaleableDfltCtor(Scaleable* const this);

void _Shape__VirtualDtor(Shape* const this);
void _Shape__VirtualScale(Shape* const this, double f);
void _Shape__VirtualDraw(const Shape* const this);
void _Shape__VirtualDrawWithColor(const Shape* const this,Color_ColorEnum c);
double _Shape__VirtualArea(const Shape* const this);
void _Shape__DfltCtor(Shape* const this);
void _Shape__CopyCtor(Shape* const this, const Shape* const other);


void _Circle__VirtualDtor(Circle* const this);
void _Circle__VirtualScale(Circle* const this, double f);
void _Circle__VirtualDraw(const Circle* const this);
void _Circle__VirtualDrawWithColor(const Circle* const this,Color_ColorEnum c);
double _Circle__VirtualArea(const Circle* const this);
double _Circle__VirtualRadius(const Circle* const this);

void _Circle__DfltCtor(Circle* const this);
void _Circle__CopyCtor(Circle* const this, const Circle* const other);
void _Circle__CtorFromDouble(Circle* const this, double r);




void _Rectangle__DfltCtor(Rectangle* const this);
void _Rectangle__CtorFromInt(Rectangle* const this, int a);
void _Rectangle__CtorFromTwoInts(Rectangle* const this, int a, int b);
void _Rectangle__CopyCtor(Rectangle* const this, const Rectangle* const other);
void _Rectangle__VirtualDtor(Rectangle* const this);
void _Rectangle__VirtualDraw(const Rectangle* const this);
void _Rectangle__VirtualDrawWithColor(const Rectangle* const this,Color_ColorEnum c);
void _Rectangle__VirtualScale(Rectangle* const this, double f);
double _Rectangle__VirtualArea(const Rectangle* const this);














GenericFunc ScaleableVirtTable[2] = {
									(GenericFunc)&_Scaleable__VirtualDtor, 
									(GenericFunc)&_Scaleable__VirtualScale
									};

GenericFunc ShapeVirtTable[5] = {
								(GenericFunc)& _Shape__VirtualDtor,
								(GenericFunc)& _Shape__VirtualScale,
								(GenericFunc)& _Shape__VirtualDraw,
								(GenericFunc)& _Shape__VirtualDrawWithColor,
								(GenericFunc)& _Shape__VirtualArea
								};

GenericFunc CircleVirtTable[6] = {
								(GenericFunc)&_Circle__VirtualDtor,
								(GenericFunc)&_Circle__VirtualScale ,
								(GenericFunc)&_Circle__VirtualDraw ,
								(GenericFunc)&_Shape__VirtualDrawWithColor,
								(GenericFunc)&_Circle__VirtualArea,
								(GenericFunc)&_Circle__VirtualRadius 
								};


GenericFunc RectangleVirtTable[5] = {
									(GenericFunc)& _Rectangle__VirtualDtor,
									(GenericFunc)& _Rectangle__VirtualScale,
									(GenericFunc)& _Rectangle__VirtualDraw,
									(GenericFunc)& _Rectangle__VirtualDrawWithColor,
									(GenericFunc)& _Rectangle__VirtualArea
									};

/**********************************************************************/





void _Color__SetColor(Color_ColorEnum _color)
{		
	static const char * pallete[] = { "\x1B[31m", "\x1B[32m", "\033[0m" };
	puts(pallete[_color]);
}
/***********************************************************************
class Scaleable {
public:
	virtual ~Scaleable() { }	
	virtual void scale(double) = 0;
};
***********************************************************************/

struct Scaleable{
	GenericFunc* ScaleableVirtPtr;
	};

void _Scaleable__VirtualDtor(Scaleable* const this){ }

void _Scaleable__VirtualScale(void)
{
	puts("This Function Should Not Called in any situation! Abort Program");
	abort();
}

void _Scaleable__ScaleableDfltCtor(Scaleable* const this)
{
	this->ScaleableVirtPtr = ScaleableVirtTable;
}


/**********************************************************************/
/** Class Shape **/
/**********************************************************************/

int _Shape__NumOfShapes;

struct Shape{
	Scaleable m_scaleable;
	int m_id;
	}; 


/**************************************************
 * 
 * Shape() : m_id(++NumOfShapes) {
		std::printf("Shape::Shape() - %d\n", m_id); 
	}
	* 
 * ************************************************/

void _Shape__DfltCtor(Shape* const this)
{
	_Scaleable__ScaleableDfltCtor((Scaleable*)this);
	((Scaleable*)this)->ScaleableVirtPtr = ShapeVirtTable;
	this->m_id = ++_Shape__NumOfShapes;
	printf("Shape::Shape() - %d\n", this->m_id);  
}




/*Shape(const Shape& other) : m_id(++NumOfShapes) {
		std::printf("Shape::Shape(Shape&) - %d from - %d\n", m_id, other.m_id);
	}*/


void _Shape__CopyCtor(Shape* const this, const Shape* const other)
{
	_Scaleable__ScaleableDfltCtor((Scaleable*)this);
	((Scaleable*)this)->ScaleableVirtPtr = ShapeVirtTable;
	this->m_id = ++_Shape__NumOfShapes;
	printf("Shape::Shape(Shape&) - %d from - %d\n", this->m_id, other->m_id);
}

/**
 * ~Shape() {
		draw();
		--NumOfShapes; 
		std::printf("Shape::~Shape - %d\n", m_id);
	}*/




void _Shape__VirtualDtor(Shape* const this)
{
	_Shape__VirtualDraw(this);
	--_Shape__NumOfShapes;
	printf("Shape::~Shape - %d\n", this->m_id);
	/*virt ptr: pointing to base virt table*/
	((Scaleable*)this)->ScaleableVirtPtr = ScaleableVirtTable;
	_Scaleable__VirtualDtor((Scaleable*)this);
}


/***
 * 
	virtual void draw() const {
		std::printf("Shape::draw() - %d\n", m_id);		
	}
 * */

void _Shape__VirtualDraw(const Shape* const this)
{
	printf("Shape::draw() - %d\n", this->m_id);
}

/**
 * 	
	virtual void draw(Color::ColorEnum c) const {
		std::printf("Shape::draw(c) - %d\n", m_id);
		Color::setColor(c);
		draw();
		Color::setColor(Color::DEFAULT);
	}
 * */

void _Shape__VirtualDrawWithColor(const Shape* const this, Color_ColorEnum c)
{
	printf("Shape::draw(c) - %d\n", this->m_id);
	_Color__SetColor(c);
	_Shape__VirtualDraw(this);
	_Color__SetColor(_Color__DEFAULT);
}


/**
 * 	virtual void scale(double f = 1) { 
		std::printf("Shape::scale(%f)\n", f);
	}
 * */
void _Shape__VirtualScale(Shape* const this, double f)
{
	printf("Shape::scale(%f)\n", f);
}




/**
 * virtual double area() const { return -1; }
	

 * */

double _Shape__VirtualArea(const Shape* const this)
{
	return -1;
}


/**
 * static void printInventory() 
	{
		std::printf("Shape::printInventory - %d\n", NumOfShapes);
	}
	* 
 * */

void _Shape__PrintInventory() 
{
	printf("Shape::printInventory - %d\n", _Shape__NumOfShapes);
}






/**********************************************************************/
/** Class Circle **/
/**********************************************************************/

struct Circle{
	Shape m_shape;
	double m_radius;
	};

/**	~Circle() { 
		std::printf("Circle::~Circle() - %d, r:%f\n", m_id, m_radius); 
	}
 * */
void _Circle__VirtualDtor(Circle* const this)
{
	printf("Circle::~Circle() - %d, r:%f\n", ((Shape*)this)->m_id, this->m_radius);
	
	/*???????????*/
	((Scaleable*)((Shape*)this))->ScaleableVirtPtr = ShapeVirtTable;
	_Shape__VirtualDtor((Shape*)this);
}


/**Circle() : m_radius(1) { 
		std::printf("Circle::Circle() - %d, r:%f\n", m_id, m_radius); 
	}
 * **/

void _Circle__DfltCtor(Circle* const this)
{
	_Shape__DfltCtor((Shape*)this);
	((Scaleable*)this)->ScaleableVirtPtr = CircleVirtTable;
	this->m_radius = 1;
	printf("Circle::Circle() - %d, r:%f\n", ((Shape*)this)->m_id, this->m_radius);
}


/**
 * 	Circle(double r) : m_radius(r) { 
		std::printf("Circle::Circle(double) - %d, r:%f\n", m_id, m_radius); 
	}
 * **/
void _Circle__CtorFromDouble(Circle* const this, double r)
{
	_Shape__DfltCtor((Shape*)this);
	((Scaleable*)this)->ScaleableVirtPtr = CircleVirtTable;
	this->m_radius = r;
	printf("Circle::Circle(double) - %d, r:%f\n", ((Shape*)this)->m_id, this->m_radius);

}


/**
 * Circle(const Circle& other)
	: Shape(other), m_radius(other.m_radius) { 
		std::printf("Circle::Circle(Circle&) - %d, r:%f\n", m_id, m_radius);
	}
 * **/
void _Circle__CopyCtor(Circle* const this, const Circle* const other)
{
	_Shape__CopyCtor((Shape*)this, (const Shape* const)other);
	((Scaleable*)this)->ScaleableVirtPtr = CircleVirtTable;
	this->m_radius = other->m_radius;
	printf("Circle::Circle(Circle&) - %d, r:%f\n", ((Shape*)this)->m_id, this->m_radius);
}


/*void draw() const { 
		std::printf("Circle::draw()  - %d, r:%f\n", m_id, m_radius);
	}*/

void _Circle__VirtualDraw(const Circle* const this)
{
	printf("Circle::draw()  - %d, r:%f\n", ((Shape*)this)->m_id, this->m_radius);
}


void _Circle__VirtualDrawWithColor(const Circle* const this,Color_ColorEnum c)
{
	((void(*)(const Shape* const ,Color_ColorEnum))CircleVirtTable[3])((Shape*)this,c); 
}

/*void scale(double f = 2) {
		std::printf("Circle::scale(%f)\n", f);
		m_radius *= f;
	}*/

void _Circle__VirtualScale(Circle* const this, double f)
{
	printf("Circle::scale(%f)\n", f);
	this->m_radius *= f;
}


/*double area() const {
		return m_radius * m_radius * 3.1415;	
	}*/

double _Circle__VirtualArea(const Circle* const this)
{
	return this->m_radius * this->m_radius * 3.1415;
}

/*double radius() const { 
		std::printf("Circle::draw()  - %d, r:%f\n", m_id, m_radius);
		return m_radius;
	}*/

double _Circle__VirtualRadius(const Circle* const this)
{
	printf("Circle::draw()  - %d, r:%f\n", ((Shape*)this)->m_id, this->m_radius);
	return this->m_radius; 
}



/**********************************************************************/
/** Class Rectangle **/
/**********************************************************************/

struct Rectangle{
	Shape m_shape;
	int m_a; 
	int m_b;
	};


/*Rectangle() : m_a(1), m_b(1) { 
		std::printf("Rectangle::Rectangle() - %d, [%d, %d]\n", m_id, m_a, m_b);
	}*/



void _Rectangle__DfltCtor(Rectangle* const this)
{	
	_Shape__DfltCtor((Shape*)this);
	((Scaleable*)this)->ScaleableVirtPtr = RectangleVirtTable;
	this->m_a = this->m_b = 1;
	printf("Rectangle::Rectangle() - %d, [%d, %d]\n", ((Shape*)this)->m_id, this->m_a, this->m_b);
} 

/*	Rectangle(int a) : m_a(a), m_b(a) { 
		std::printf("Rectangle::Rectangle(int) - %d, [%d, %d]\n", m_id, m_a, m_b);
	}*/
	
void _Rectangle__CtorFromInt(Rectangle* const this, int a)
{
	_Shape__DfltCtor((Shape*)this);
	((Scaleable*)this)->ScaleableVirtPtr = RectangleVirtTable;
	this->m_a = this->m_b = a;
	printf("Rectangle::Rectangle(int) - %d, [%d, %d]\n", ((Shape*)this)->m_id, this->m_a, this->m_b);
}

/*	Rectangle(int a, int b) : m_a(a), m_b(b) { 
		std::printf("Rectangle::Rectangle(int, int) - %d, [%d, %d]\n", m_id, m_a, m_b);
	}*/

void _Rectangle__CtorFromTwoInts(Rectangle* const this, int a, int b)
{
	_Shape__DfltCtor((Shape*)this);
	((Scaleable*)this)->ScaleableVirtPtr = RectangleVirtTable;
	this->m_a = a;
	this->m_b = b;
	printf("Rectangle::Rectangle(int, int) - %d, [%d, %d]\n", ((Shape*)this)->m_id, this->m_a, this->m_b);
}


/*	Rectangle(const Rectangle &other ) : m_a(other.m_a), m_b(other.m_b), Shape(other) 
	* { 
		std::printf("Rectangle::Rectangle(Rectangle&) - %d, a:%d/%d\n", m_id, m_a, m_b);
	}*/

void _Rectangle__CopyCtor(Rectangle* const this, const Rectangle* const other)
{
	_Shape__CopyCtor((Shape*)this, (const Shape* const)other);
	((Scaleable*)this)->ScaleableVirtPtr = RectangleVirtTable;
	this->m_a = other->m_a;
	this->m_b = other->m_b;
	printf("Rectangle::Rectangle(Rectangle&) - %d, a:%d/%d\n", ((Shape*)this)->m_id, this->m_a, this->m_b);	
}


/*	~Rectangle() { 
		std::printf("Rectangle::~Rectangle() - %d, [%d, %d]\n", m_id, m_a, m_b);
	}*/

void _Rectangle__VirtualDtor(Rectangle* const this)
{
	printf("Rectangle::~Rectangle() - %d, [%d, %d]\n", ((Shape*)this)->m_id, this->m_a, this->m_b);	
	
	((Scaleable*)(Shape*)this)->ScaleableVirtPtr = ShapeVirtTable;
	_Shape__VirtualDtor((Shape*)this);
}


/*	void draw() const { 
		std::printf("Rectangle::draw()  - %d, [%d, %d]\n", m_id, m_a, m_b);
	}*/

void _Rectangle__VirtualDraw(const Rectangle* const this)
{
	printf("Rectangle::draw()  - %d, [%d, %d]\n", ((Shape*)this)->m_id, this->m_a, this->m_b);	
}

/*   void draw(Color::ColorEnum c) const {
		std::printf("Rectangle::draw(%d)  - %d, [%d, %d]\n", c, m_id, m_a, m_b);
	}*/

void _Rectangle__VirtualDrawWithColor(const Rectangle* const this,Color_ColorEnum c)
{
	printf("Rectangle::draw(%d)  - %d, [%d, %d]\n", c,((Shape*)this)->m_id, this->m_a, this->m_b);	
}

/*	void scale(double f = 4){
		std::printf("Rectangle::scale(%f)\n", f);
		m_a *= f;
		m_b *= f;
	}*/

void _Rectangle__VirtualScale(Rectangle* const this, double f)
{
	printf("Rectangle::scale(%f)\n", f);
	this->m_a *= (int)f;
	this->m_b *= (int)f;
}


/*	double area() const {
		return m_a * m_b;
	}*/
	
double _Rectangle__VirtualArea(const Rectangle* const this)
{
	return this->m_a * this->m_b;
}




void report(const Shape* const this) {
	puts("-----report-----");
	_Shape__VirtualDraw(this);
	_Shape__PrintInventory(); 
	puts("-----report-----");
}


/*inline void draw(Shape& obj) { 
	std::puts("-----draw(Shape&)-----");
	obj.scale();
	obj.draw();
	
	static Circle unit(4);
	
	std::puts("-----draw(Shape&)-----");
}*/

int Circle_Ctor_Activation_Flag = 0;
Circle unit;

void draw_shape(Shape* const obj)
{
	puts("-----draw(Shape&)-----");
	_Shape__VirtualScale(obj,1);
	_Shape__VirtualDraw(obj);
	
	if(Circle_Ctor_Activation_Flag == 0){
		_Circle__CtorFromDouble(&unit, 4);
	}
	puts("-----draw(Shape&)-----");
}


/*void draw(Circle c) { 
	std::puts("-----draw(Circle)-----");

    if(c.area() > 3.14){
	    static Circle unit(1);
		unit.draw();
	    unit.scale(3);
    }
    
	c.draw(); 
	std::puts("-----draw(Circle)-----");
}*/

void draw_circle(Circle* const circ)
{
	puts("-----draw(Circle)-----");
	//in this function no need for passing via circle vtable
	//because in this function compiler knows that c is circle (by val)
	
	
	//call c dtor
	
}


/*void doObjArray(){
	Shape objects[] = {
	    Circle(),
	    Rectangle(4),
	    Circle(9)
	};

    for(int i = 0; i < 3; ++i) 
		objects[i].draw();
}*/


/*
 * dflt shape ctor 
 * copy shape ctor 
 * 
 * 
 * */


/**********************************************************************/	
int main()
{
	//call circle dflt ctor 
	
	
	
	
	
	Color_ColorEnum x = _Color__DEFAULT;
	Shape myshape1;
	Shape myshape2;
	
	
	_Color__SetColor(x);
	
	
	_Shape__DfltCtor(&myshape1);
	
	report(&myshape1);
	
	_Shape__DfltCtor(&myshape2);
	
	report(&myshape2);
	
	
	draw_shape(&myshape1);
	
	//dtors
	if(Circle_Ctor_Activation_Flag != 0)
	{
		
	}
	
	return 0;
}
