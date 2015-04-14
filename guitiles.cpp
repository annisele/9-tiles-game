#include "guitiles.h"
#include <sstream>
#include "Gwindow.h"

/** constructor
@param count, the number of the guitile
@param nx, x position where the tile needs to move
@param ny, y position where the tile needs to move
@param width
@param height
@param state of the gwindow
*/

GUItiles::GUItiles( int count, double nx, double ny, double w, double h, GWindow *parent  ) :
	QGraphicsRectItem(nx, ny, w, h) {

		x = nx;
		y = ny;
		width = w;
		height = h;
		parent_=parent;

		tile=this;

		//tansforms int count into the string text number of tile
		std::ostringstream o;
		o << count;
		num=count;
		//displays text
		text= new QGraphicsSimpleTextItem(o.str().c_str(), this);
		text->setPos(x+20,y+20);
		//set timer and connects it to move function
		timer.setInterval(4);
		connect(&timer, SIGNAL(timeout()), this, SLOT(animate()));

	}


/** gets target x position*/
int GUItiles::getX() {
	return x;
}
/** gets target y position*/
int GUItiles::getY() {
	return y;
}
/** sets target x position
@param target x*/
void GUItiles::setX(int nx) {
	x = nx;
}
/** sets target y position
@param target y*/
void GUItiles::setY(int ny) {
	y = ny;
}
/**move function
@param target x
@param target y
*/
void GUItiles:: moveto(int XX, int YY){

	QPointF p( XX, YY );
	QRectF r( rect() );
	//moves tile
	r.moveTo(p);
	setRect( r );
	//moves number
	text->setPos(XX + 20, YY + 20);
}
/** start timer, sets interval to 4*/
void GUItiles::starttimer() {
	timer.start(4);
}
/** slide tile function, where the tile is moved from original position 
target x and y position for the duration of the timer. once
the tile is moved to the black space, the timer is stopped.

*/
void GUItiles::animate() {

	int x_ = QGraphicsRectItem::rect().left();
	int y_ = QGraphicsRectItem::rect().top();
	//if current x pos is less, increase x
	if(x > x_) {
		x_++;
	}
	//if current x pos is more, decrease x
	else if(x < x_) {
		x_--;
	}
	//if current y pos is less, increase y
	if(y > y_) {
		y_++;
	}
	//if current y pos is more, decrease y
	else if(y < y_) {
		y_--;
	}
	moveto(x_, y_);
	//moved
	if(x_ == x && y_ == y) {
		timer.stop();
		return;
	}
}
/** return the number of the tile*/
int GUItiles::getnum() const 
{ return num; }

/** function to signal when tile is pressed*/
void GUItiles::mousePressEvent (QGraphicsSceneMouseEvent* e)
{
	emit clicked(num, tile);
}


