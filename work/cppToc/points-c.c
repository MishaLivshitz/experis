#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define PHASE (2)

#define Point2D_GetX(THIS)	(THIS)->m_x
#define Point2D_GetY(THIS)	(THIS)->m_y
#define Point2D_dtor(p)	{}
/***** Phase 1 *****{{ */
#if PHASE >= 1

struct Point2D
{
    double m_x;
    double m_y;
};

void Point2Dv(struct Point2D * const this)
{
    this->m_x=0;
    this->m_y=0;
}

void Point2Ddd(struct Point2D * const this, double _x, double _y)
{
    this->m_x = _x;
    this->m_y = _y;
}

void Point2D_cctor(struct Point2D * const this, const struct Point2D * const _other)
{
    *this = *_other;
}

double Point2D_Distance(const struct Point2D * const this, const struct Point2D* const _other)
{
	double dx = this->m_x - _other->m_x;
	double dy = this->m_y - _other->m_y;
	return sqrt(dx * dx + dy * dy);
}

struct Point2D * const Point2D_assInc(struct Point2D * const this, const struct Point2D* const _other)
{
	this->m_x += _other->m_x;
	this->m_y += _other->m_y;
	
	return this;
}

struct Point2D * const Point2D_assMul(struct Point2D * const this, double _factor)
{
	this->m_x *= _factor;
	this->m_y *= _factor;
	
	return this;
}


void pointless()
{
	struct Point2D p0;
	struct Point2D p1;
	struct Point2D dxy;

    Point2Dv(&p0);
    Point2Ddd(&p1,0,10);


	printf("distance p0 --> p1 == %f\n", Point2D_Distance(&p0, &p1));

	Point2Ddd(&dxy, +4, -7);
	Point2D_assInc(&p1,&dxy);
	printf("%f, %f\n", Point2D_GetX(&p1), Point2D_GetY(&p1));
	printf("now distance p0 --> p1 == %f\n", Point2D_Distance(&p0,&p1));

	Point2D_dtor(dxy);
	Point2D_dtor(p1);
	Point2D_dtor(p0);
}
#endif

#if PHASE >= 2

struct NamedPoint2D{
	struct Point2D m_base;
	const char* m_name;
};

#define NamedPoint2D_dtor(p) Point2D_dtor(p->m_base)

void NamedPoint2D_default_val(struct NamedPoint2D * const this)
{
	Point2Dv(&this->m_base);
	this->m_name = "origin";
}

void NamedPoint2D_char_p(struct NamedPoint2D * const this, const char* _name)
{
	Point2Dv(&this->m_base);
	this->m_name = _name;
}

void NamedPoint2D_dd_default(struct NamedPoint2D * const this, double _x, double _y)
{
	Point2Ddd(&this->m_base,_x,_y);
	this->m_name = "anonymous Point";
}

void NamedPoint2D_dd_char_p(struct NamedPoint2D * const this, double _x, double _y, const char *_name)
{
	Point2Ddd(&this->m_base,_x,_y);
	this->m_name = _name;
}

void NamedPoint2D_point_cctor_default_name(struct NamedPoint2D * const this,const struct Point2D* const point)
{
	Point2D_cctor(&this->m_base, point);
	this->m_name = "anonymous Point";
}

void NamedPoint2D_point_cctor_name(struct NamedPoint2D * const this,const struct Point2D* const point, const char *_name)
{
	Point2D_cctor(&this->m_base, point);
	this->m_name = _name;
}

const char *NamedPoint2D_GetName(const struct NamedPoint2D * const this)
{
	return this->m_name;
}

void dog()
{
	struct NamedPoint2D home;
	struct Point2D point;
	struct NamedPoint2D dog;
	
	
	NamedPoint2D_dd_char_p(&home,5,7, "home");
	Point2D_cctor(&point, (struct Point2D*)&home);
	NamedPoint2D_point_cctor_default_name(&dog, &point);

	Point2D_assMul((struct Point2D*)&dog,2);
	printf("Distance from %s to %s is %f\n", NamedPoint2D_GetName(&home), NamedPoint2D_GetName(&dog), Point2D_Distance((struct Point2D*)&home, (struct Point2D*)&dog));
	
	NamedPoint2D_dtor(dog);
	Point2D_dtor(point);
	NamedPoint2D_dtor(home);
}


#endif

int main()
{
#if PHASE >= 1
	pointless();
#endif

#if PHASE >= 2
	dog();
	/*area();*/
#endif

	return 0;
}

