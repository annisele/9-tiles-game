#ifndef GWindow_H
#define GWindow_H

#include <QMainWindow>
#include <QMenuBar>
#include <QAction>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QTimer>
#include <QTimeLine>
#include <QGraphicsItemAnimation>
#include <QPushButton>
#include <QRadioButton>
#include<QLineEdit>
#include "guitiles.h"
#include "board.h"
#include <QPushButton>
#include <QApplication>
#include <QHBoxLayout>
#include <QWidget>
#define WINDOW_MAX_X 250
#define WINDOW_MAX_Y 250

/** 
This is the graphics window that inherits from graphicsview. 
it is the layout for the game. it is the central widget of qmainwindow.
all the functions for the creation and movement of the tile for gameplay
are implemented here. a vector of pointers to the guitile tiles
is a class data member that can be used and manipulated. 

*/
class GWindow : public QGraphicsView {
	Q_OBJECT


	public:
		explicit GWindow();
		~GWindow();
		QGraphicsView *view; //game window
		QLineEdit *error ; // error box
		QGraphicsScene *scene; //where is game widget is placed
		void createboard(Board *b); //making a new gameboard that passes in the instance of Board
		int di;



	private:

		GUItiles *item; //instance of guitile
		Board *b_; //pointer to the board being played
		std::vector<GUItiles*> tiles; //vector of tiles, visual data structure of the board tiles
		QTimer *timer; // timer for animating tiles

		public slots:
			void movetile(int num, GUItiles *tile); //move function




};

#endif // MAINWINDOW_H
