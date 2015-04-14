#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QListWidget>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QTimer>
#include <QTimeLine>
#include <QGraphicsItemAnimation>
#include <QPushButton>
#include <QToolBar>
#include<QAction>
#include <QDockWidget>
#include <QWidget>
#include <QLineEdit>
#include "puzzle_heur.h"
#include <QMenu>
#include <QLabel>
#include <QFormLayout>
#include <QMenuBar>
#include <QHBoxLayout>
#include "Gwindow.h"
#define WINDOW_MAX_X 250
#define WINDOW_MAX_Y 250

/**
mainwindow is where the puzzle game functions are all created and 
utilities noted. all the buttons and spaces are here. mainwindow
checks that user input arguemnts are correct and calls gamewindow to
create the board. it also runs puzzle solver when the star buttom is pushed
*/
class MainWindow : public QMainWindow {

	Q_OBJECT

	public:
		explicit MainWindow();
		~MainWindow();


	private:

		void createToolbars();

		GWindow *g;

		
		QToolBar *toolbar; //stores buttons
		QAction *start; //start button
		QAction *quit; //quit button
		QAction *astar; //perform a* algorithm
		QTimer *timer;
		QRadioButton *manhattan_;
		QRadioButton *outofplace_;
		//layouts attahed to puzzle window
		QFormLayout *layout;
		QHBoxLayout *layout2;
		QWidget *window;
		QListWidget *cheatwindow;
		QDockWidget *qdw;
		QDockWidget *qdw2;
		// user input arguments
		QLineEdit * randomseededit; 
		QLineEdit * startmoveedit;
		QLineEdit * sizeedit;

		Board * b_; //board that is being passed from the board initialization
		int counter;
		PuzzleHeuristic* heuristic;// calls the two heuristic functions 

	  	public slots:

		void startFunction(); //starts game
		void quitFunction(); //end app
		void astarFunction(); //performs a* algor



};

#endif // MAINWINDOW_H
