#ifndef GUItiles_H
#define GUItiles_H
#include<QTimer>
#include<QObject>
#include <QGraphicsRectItem>

/**
  This class maintains the location, size, and speed of a QGraphicsRectItem.
  It is easier to do the arithmetic with this data, and then update the position
  separately, then to extract coordinates from the QRectF that is contained within
  the QGraphicsRectItem
 */
class GWindow;
class GUItiles : public QObject, public QGraphicsRectItem 
{
	Q_OBJECT
		signals:
		void clicked(int num, GUItiles* tile);
	public:

	GUItiles( int ,double nx, double ny, double w, double h, GWindow *parent);
	void setX( int x );// sets the x position to move to
	void setY( int y );// sets the y position to move to
	int getnum()const;// gets tile number

	int getX(); //x target position
	int getY(); //y tartget position
	void mousePressEvent (QGraphicsSceneMouseEvent* e);
	void  moveto(int XX, int YY); //move function
	private:
	GWindow *parent_; 
	QTimer timer; 
	int num; //tile key in vector
	GUItiles *tile; //instance of tile 
	int x; 
	int y;
	int width; 
	int height;
	QGraphicsSimpleTextItem *text; //number of board tile

	public slots:
		void animate(); //sliding tile function 
		void starttimer(); //start timer

};

#endif // GUItiles_H
