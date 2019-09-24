#include <stdio.h>
#include <stdlib.h>


#define Color_ctor(O)   {}


struct Color
{
    char m_nop;
};

enum ColorEnum { RED, GREEN, DEFAULT };

static void Color_setColor(enum ColorEnum color){		
		static const char * pallette[] = { "\x1B[31m", "\x1B[32m", "\033[0m" };
		puts(pallette[color]);
}

struct Scaleable {
    void* (**__vptr)(void*);
};

void Scaleable_ctor(const struct Scaleable* const this);
void Scaleable_dtor(const struct Scaleable* const this);
void Scaleable_scale(struct Scaleable* const this, double);
void* (*Scaleable_vptr[])(void*)  =
{
    (void* (*)(void*))Scaleable_dtor,
    (void* (*)(void*))Scaleable_scale
};

void Scaleable_ctor(const struct Scaleable* const this)
{
    struct Scaleable* const self = (struct Scaleable* const)this;
    self->__vptr = Scaleable_vptr;
}

void Scaleable_dtor(const struct Scaleable* const this)
{
}

void Scaleable_scale(struct Scaleable* const this, double f)
{
    printf("Pure virtual method has been called\n");
    abort();
}


int Shape_NumOfShapes = 0;
void Shape_printInventory() 
{
    printf("Shape::printInventory - %d\n", Shape_NumOfShapes);
}

struct Shape
{
    struct Scaleable m_base;
    int              m_id;
};
void Shape_ctor(const struct Shape* const this);
void Shape_dtor(const struct Shape* const this);
void Shape_draw_void(const struct Shape* const this);
void Shape_draw_Color(const struct Shape* const this, enum ColorEnum c);
void Shape_scale(double f);
double Shape_area(const struct Shape* const this);


void* (*Shape_vptr[])(void*) = {
    (void* (*)(void*))Shape_dtor,
    (void* (*)(void*))Shape_scale,
    (void* (*)(void*))Shape_draw_void,
    (void* (*)(void*))Shape_draw_Color, 
    (void* (*)(void*))Shape_area
                                };

void Shape_ctor(const struct Shape* const this)
{
    Scaleable_ctor((struct Scaleable const* const)this);
    ((struct Scaleable* const)this)->__vptr = Shape_vptr;

    ((struct Shape* const)this)->m_id = ++Shape_NumOfShapes;
    printf("Shape::Shape() - %d\n",  this->m_id);
}

void Shape_cctor(const struct Shape* const this, const struct Shape* const other)
{
    Scaleable_ctor((struct Scaleable const* const)this);
    ((struct Scaleable* const)this)->__vptr = Shape_vptr;
    
    ((struct Shape* const)&this)->m_id = ++Shape_NumOfShapes;
	printf("Shape::Shape(Shape&) - %d from - %d\n", this->m_id, other->m_id);  
}

void Shape_dtor(const struct Shape* const this)
{
    Shape_draw_void(this);
    printf("Shape::Shape() - %d\n", ((struct Shape* const)this)->m_id);
    --Shape_NumOfShapes;

    ((struct Scaleable* const)this)->__vptr = Scaleable_vptr;
    Scaleable_dtor(((struct Scaleable* const)this));
}

void Shape_draw_void(const struct Shape* const this)
{
    printf("Shape::draw() - %d\n", this->m_id);
}

void Shape_draw_Color(const struct Shape* const this, enum ColorEnum c) 
{
    printf("Shape::draw(c) - %d\n", this->m_id);
    Color_setColor(c);

    ((struct Scaleable* const)this)->__vptr[2]((struct Shape* const)this);

    Color_setColor(DEFAULT); 
}

void Shape_scale(double f)
{ 
    printf("Shape::scale(%f)\n", f);
}

double Shape_area(const struct Shape* const this)
{
    return -1;
}

struct Circle
{
    struct Shape m_base;
    double       m_radius;
};

void Circle_ctor(const struct Circle* const this);
void Circle_dtor(const struct Circle* const this);
void Circle_ctor_double(const struct Circle* const this, double);
void Circle_cctor(const struct Circle* const this, const struct Circle* const other);
void Circle_draw(const struct Circle* const this);
void Circle_scale(struct Circle* const this, double f);
double Circle_area(const struct Circle* const this);

void* (*Circle_vptr[])(void*) = 
        {
            (void* (*)(void*))Circle_dtor,
            (void* (*)(void*))Circle_scale, 
            (void* (*)(void*))Circle_draw,
            (void* (*)(void*))Shape_draw_Color, 
            (void* (*)(void*))Circle_area
        };

void Circle_ctor(const struct Circle* const this) 
{
    struct Circle* const self = (struct Circle* const)this;
    Shape_ctor((struct Shape const* const)this);
    ((struct Scaleable* const)this)->__vptr = Circle_vptr;
    self->m_radius = 1; 
    printf("Circle::Circle() - %d, r:%f\n", self->m_base.m_id, self->m_radius); 
}

void Circle_ctor_double(const struct Circle* const this, double r)
{
    struct Circle* const self = (struct Circle* const)this;
    Shape_ctor((struct Shape const* const)this);
    ((struct Scaleable* const)this)->__vptr = Circle_vptr;
    self->m_radius = r; 
    printf("Circle::Circle() - %d, r:%f\n", self->m_base.m_id, self->m_radius); 
}

void Circle_cctor(const struct Circle* const this, const struct Circle* const other) 
{
    struct Circle* const self = (struct Circle* const)this;
    Shape_cctor((struct Shape* const)this, (struct Shape* const)other);
    ((struct Scaleable* const)this)->__vptr = ((struct Scaleable* const)other)->__vptr;

    *self = *other; 
    printf("Circle::Circle() - %d, r:%f\n", ((struct Shape*)self)->m_id, self->m_radius);
}

void Circle_dtor(const struct Circle* const this)
{
    ((struct Scaleable* const)this)->__vptr = ((struct Scaleable* const)(&this->m_base))->__vptr;
    Shape_dtor((struct Shape const * const)this);
    printf("Circle::~Circle() - %d, r:%f\n", ((struct Shape const * const)this)->m_id, this->m_radius);
}

void Circle_draw(const struct Circle* const this) 
{ 
    printf("Circle::draw()  - %d, r:%f\n", ((struct Shape*)this)->m_id, this->m_radius);
}

void Circle_scale(struct Circle* const this, double f) 
{
    printf("Circle::scale(%f)\n", f);
    this->m_radius *= f;
}

double Circle_area(const struct Circle* const this)
{
    return this->m_radius * this->m_radius * 3.1415;	
}

double radius(const struct Circle* const this) 
{ 
    printf("Circle::draw()  - %d, r:%f\n", ((struct Shape*)this)->m_id, this->m_radius);
    return this->m_radius;
}



struct Rectangle
{
    struct Shape m_base;
    int       m_a;
    int       m_b;
};

void Rectangle_ctor(const struct Rectangle* const this);
void Rectangle_dtor(const struct Rectangle* const this);
void Rectangle_ctor_i(const struct Rectangle* const this, int);
void Rectangle_ctor_2i(const struct Rectangle* const this, int, int);
void Rectangle_cctor(const struct Rectangle* const this, const struct Rectangle* const other);
void Rectangle_draw(const struct Rectangle* const this);
void Rectangle_draw_Color(const struct Rectangle* const this, enum ColorEnum c);
void Rectangle_scale(struct Rectangle* const this, double f);
double Rectangle_area(const struct Rectangle* const this);


void* (*Rectangle_vptr[])(void*) = 
        {
            (void* (*)(void*))Rectangle_dtor,
            (void* (*)(void*))Rectangle_scale, 
            (void* (*)(void*))Rectangle_draw,
            (void* (*)(void*))Rectangle_draw_Color, 
            (void* (*)(void*))Rectangle_area
        };

void Rectangle_ctor(const struct Rectangle* const this) 
{ 
    Shape_ctor((struct Shape const* const)this);
    ((struct Scaleable* const)this)->__vptr = Rectangle_vptr;

    ((struct Rectangle* const)this)->m_a = 1;
    ((struct Rectangle* const)this)->m_b = 1;
    printf("Rectangle::Rectangle() - %d, [%d, %d]\n", ((struct Shape const * const)this)->m_id, this->m_a, this->m_b);
}

void Rectangle_ctor_i(const struct Rectangle* const this, int a) 
{ 
    Shape_ctor((struct Shape const* const)this);
    ((struct Scaleable* const)this)->__vptr = Rectangle_vptr;
    
    ((struct Rectangle* const)this)->m_a = a;
    ((struct Rectangle* const)this)->m_b = a;
    printf("Rectangle::Rectangle() - %d, [%d, %d]\n", ((struct Shape const * const)this)->m_id, this->m_a, this->m_b);
}

void Rectangle_ctor_2i(const struct Rectangle* const this, int a, int b) 
{ 
    Shape_ctor((struct Shape const* const)this);
    ((struct Scaleable* const)this)->__vptr = Rectangle_vptr;
    
    ((struct Rectangle* const)this)->m_a = a;
    ((struct Rectangle* const)this)->m_b = b;
    printf("Rectangle::Rectangle() - %d, [%d, %d]\n", ((struct Shape const * const)this)->m_id, this->m_a, this->m_b);
}

void Rectangle_cctor(const struct Rectangle* const this,const struct Rectangle* const other) 
{ 
    struct Rectangle* const self  = (struct Rectangle* const)this;
    Shape_cctor((struct Shape const* const)this, (struct Shape const* const)other);
    ((struct Scaleable* const)this)->__vptr = Rectangle_vptr;

    *self = *other;
    printf("Rectangle::Rectangle(Rectangle&) - %d, a:%d/%d\n", ((struct Shape*)this)->m_id, this->m_a, this->m_b);
}

void Rectangle_dtor(const struct Rectangle* const this) 
{ 
    ((struct Scaleable* const)this)->__vptr = ((struct Scaleable* const)(&this->m_base))->__vptr;
    Shape_dtor((struct Shape*)this);
    printf("Rectangle::~Rectangle() - %d, [%d, %d]\n", ((struct Shape*)this)->m_id, this->m_a, this->m_b);
}

void Rectangle_draw(const struct Rectangle* const this)
{
  	printf("Rectangle::draw()  - %d, [%d, %d]\n", ((struct Shape*)this)->m_id, this->m_a, this->m_b);
}

void Rectangle_draw_Color(const struct Rectangle* const this, enum ColorEnum c)
{
    printf("Rectangle::draw(%d)  - %d, [%d, %d]\n", c, ((struct Shape*)this)->m_id, this->m_a, this->m_b);
}

void Rectangle_scale(struct Rectangle* const this, double f)
{
    printf("Rectangle::scale(%f)\n", f);
    this->m_a *= f;
    this->m_b *= f;
}

double Rectangle_area(const struct Rectangle* const this)
{
    return this->m_a * this->m_b; 
}


void draw(struct Shape* const obj) { 

	static struct Circle unit;
    static int flag = 0;

	puts("-----draw(Shape&)-----");
	((void (*)(struct Scaleable* const, double))(((struct Scaleable*)obj)->__vptr[1]))((struct Scaleable* const)obj, 1);
	((void (*)(struct Shape* const))(((struct Scaleable*)obj)->__vptr[2]))((struct Shape* const)obj);
    
    if(!flag)
    {
        Circle_ctor_double(&unit,4);
        flag = 1;
    }
	
	puts("-----draw(Shape&)-----");
}

void report(const struct Shape* const s) 
{
	puts("-----report-----");
	((void (*)(struct Shape* const))(((struct Scaleable*)s)->__vptr[2]))((struct Shape* const)s);
	Shape_printInventory();
	puts("-----report-----");
}


double diffWhenDoubled(struct Shape* const shape){
	double a0 = ((double (*)(struct Shape* const))(((struct Scaleable*)shape)->__vptr[4]))((struct Shape* const)shape);
    double a1;

    ((void (*)(struct Scaleable* const, double))(((struct Scaleable*)shape)->__vptr[1]))((struct Scaleable* const)shape, 2);
    a1 = ((double (*)(struct Shape* const))(((struct Scaleable*)shape)->__vptr[4]))((struct Shape* const)shape);
	return a1 - a0;
}

void doPointerArray(){
    struct Circle* c = (struct Circle*)malloc(sizeof(struct Circle));
    struct Rectangle* r = (struct Rectangle*)malloc(sizeof(struct Rectangle));
    struct Circle* c1 = (struct Circle*)malloc(sizeof(struct Circle));
	struct Shape *array[3];
	puts("-----doPointerArray-----");
    

    Circle_ctor(c);
    Rectangle_ctor_i(r,3);
    Circle_ctor_double(c1,4);

    array[0] = (struct Shape* const)c;
    array[1] = (struct Shape* const)r;
    array[2] = (struct Shape* const)c1;

    {
        int i;
        for(i = 0; i < 3; ++i)
        { 
            ((void (*)(struct Scaleable* const, double))(((struct Scaleable*)array[i])->__vptr[1]))((struct Scaleable* const)array[i], 1);
            ((void (*)(struct Shape* const))(((struct Scaleable*)array[i])->__vptr[2]))((struct Shape* const)array[i]);
        }
    
	    printf("area: %f\n", diffWhenDoubled((struct Shape*)&*array[2]));
    
        for(i = 0; i < 3; ++i) { 
            ((void (*)(struct Shape* const))(((struct Scaleable*)array[i])->__vptr[0]))((struct Shape* const)array[i]);
            free(array[i]); 
            array[i] = NULL; 
        }
    }

	puts("-----doPointerArray-----");
}


int main(int argc, char **argv, char **envp)
{	
    struct Circle c;
	struct Rectangle s;
    Circle_ctor(&c);
    Rectangle_ctor_i(&s, 4);	
	printf("---------------Start----------------\n");

	printf("0.-------------------------------\n");	
	draw((struct Shape*)&c);

	printf("+..............\n");		
	draw((struct Shape*)&c);

	printf("+..............\n");		
    draw((struct Shape*)&s);

	printf("+..............\n");		
	report((struct Shape*)&c);

	printf("1.-------------------------------\n");	
	
    doPointerArray();

	/*std::printf("2.-------------------------------\n");

    doObjArray();

	std::printf("3.-------------------------------\n");

    Shape::printInventory();
    Circle c2 = c;
    c2.printInventory();

	std::printf("4.-------------------------------\n");
   
    Circle olympics[5];
	std::printf("olympic diff %f\n", diffWhenDoubled(olympics[1]));

	std::printf("5.-------------------------------\n");

    Rectangle *fourRectangles = new Rectangle[4];
    dispose(fourRectangles);

	std::printf("6.-------------------------------\n");
	EmptyBag eb;
	std::printf("Empty things are: %zu %zu %zu", sizeof(Empty), sizeof(EmptyEmpty), sizeof(EmptyBag) );
	
	std::printf("7.-------------------------------\n");
	disappear();	

	std::printf("---------------END----------------\n");
 */
    return 0;
}