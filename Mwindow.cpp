#include "Mwindow.h"
#include "Gwindow.h"
#include "board.h"
#include <QPushButton>
#include <QLabel>
#include <QString>
#include <QApplication>
#include<vector>
#include <QRadioButton>
#include <QMessageBox>

#include "puzzle_heur.h"
#include "puzzle_solver.h"
#include "puzzle_move.h"

/**
construtor for main window. the game window is set as teh central 
widget. line edits where the user defines the puzzle arguments such as 
board size, number of tiles misplaced, and random seed. radio buttons
are made so the user can choose to use the manhattan or the out of place
heuristic to run the a star algorithm on. user input is chek so
it fits perimeters or an error message is displayed. mainwindow uses 
the Qmainwindow template to formate buttons and widgets 
*/
MainWindow::MainWindow()  {

	b_=NULL;
	heuristic = NULL;

	g= new GWindow;
	setCentralWidget(g->view);
	createToolbars();
	//left to right
	// adding user input lines to layout
	layout = new QFormLayout();
	
	sizeedit= new QLineEdit();
	startmoveedit = new QLineEdit();
	randomseededit = new QLineEdit();

	//creating window for outputting cheats
	cheatwindow = new QListWidget();
	// Error Bar
	g->error = new QLineEdit("No error");
	cheatwindow->setFixedHeight(100);
	cheatwindow->setFixedWidth(100);
	sizeedit->setFixedWidth(100);
	startmoveedit->setFixedWidth(100);
	randomseededit->setFixedWidth(100);
	layout->addRow("CHEATS: ", cheatwindow);
	layout->addRow( "Board Size:", sizeedit);
	layout->addRow( "Starting Moves:", startmoveedit);
	layout->addRow( "Random Seed Value:", randomseededit);
	layout->addRow(g->error);
	//add layout to new widget to dock that widget
	QWidget *wi = new QWidget;
	wi->setLayout( layout);
	qdw= new QDockWidget();
	qdw->setWidget(wi);


	//creating new layout for radio buttons
	layout2 = new QHBoxLayout;   
	manhattan_ = new QRadioButton("&manhattan",this);
	outofplace_ = new QRadioButton("&outofplace",this);
	//placing buttons in the layout  

	layout2->addWidget(  manhattan_);
	layout2->addWidget(  outofplace_);

	//adding it as a new dock widget
	QWidget *wi2 = new QWidget;
	wi2->setLayout( layout2);
	qdw2= new QDockWidget();
	qdw2->setWidget(wi2);

	//adding both dock widget to window and removing the delete function 
	addDockWidget(Qt::LeftDockWidgetArea, qdw);
	qdw->setFeatures(QDockWidget::NoDockWidgetFeatures);
	addDockWidget(Qt::BottomDockWidgetArea, qdw2);
	qdw2->setFeatures(QDockWidget::NoDockWidgetFeatures);


}

/** deconstructor*/
MainWindow::~MainWindow()
{

}

/** make toolbar that includes the 3 buttons as well as their connect 
functions to create an action if the buttons are pushed. toolbar
is added to the main puzzle window 
*/
void MainWindow::createToolbars()
{

	toolbar = addToolBar(tr("File"));
	quit = new QAction( "Exit", this);
	toolbar->addAction (quit); //action is added to the toolbar
	connect(quit, SIGNAL(triggered()), this, SLOT(quitFunction()));
	start = new QAction( "Start", this);
	toolbar->addAction (start);
	connect(start, SIGNAL(triggered()), this, SLOT(startFunction())); 
	astar = new QAction( "Perform A*", this);
	toolbar->addAction (astar);
	connect(astar, SIGNAL(triggered()), this, SLOT(astarFunction()));
}

/** function to connect the start action. when it's called all the user
inputs are taken from the line edits and made sure they fit perimeters.
a new board is created (from the board constructor) with the user 
provided arguments

*/
void MainWindow::startFunction(){


	int size, initMoves, seed;
	//takes the strings from the line edits and converts to ints
	size= sizeedit->text().toInt();
	initMoves= startmoveedit->text().toInt();
	seed= randomseededit->text().toInt();
	
	//if any of the arguments are improper, a error message displays
	//board is not created
	if(size!=9&&size!=16){
		g->error->setText("board must be 3x3 or 4x4");
		return;
	}
	if(initMoves<=1||initMoves>1000000){
		g->error->setText("initial moves must be greater than 1");
		return;
	}
	if(seed<=1||seed>1000000){
		g->error->setText("seed must be greater than 1");
		return;
	}
	//else board is made with the user defined arguments which are passed
	//to the board constructor
	b_= new Board(size, initMoves, seed);
	g->createboard(b_);

}
/** end app*/
void MainWindow::quitFunction(){

	QApplication::quit();
}
/** performs the a star functiondepending on which radio button is clicked
one has to be clicked or an error message displays. puzzle solver is called
of the heuristic of choice and the list size is returned.
we iterate thru the solution list and make a copy of it and output it
to the cheat window
*/
void MainWindow::astarFunction(){
	// if game isnt scambled
	if(b_ == NULL) {
		g->error->setText("start a game!");
		return;
	}
	//for manhattan heuristic
	if(manhattan_->isChecked()) {
		heuristic = new ManhattanHeuristic();
	}
	//for out of place heuristic
	else if (outofplace_->isChecked()) {
		heuristic = new OutOfPlaceHeuristic();
	}
	//if neither are selected
	else if (!manhattan_->isChecked()&&!outofplace_->isChecked()) {
		g->error->setText("No heuristic chosen!");
	}
	//once a star is pressed and goes thru
	if(outofplace_->isChecked()||manhattan_->isChecked()){
		//clears previous message
		cheatwindow->clear();
		g->error->clear();
		//creates an instance of puzzle solver on current board
		PuzzleSolver *cheat= new PuzzleSolver(*b_);
		//performs a star to get a list of best moves
		int moves = cheat->run(heuristic);
		//copies list into a linkedlist
		mylist<int>*sol= cheat->getlist();
		//outputs message
		cheatwindow->addItem ("Use this");
		cheatwindow->addItem ("sequence: ");
		//goes thru linkedlist and outputs each item in cheat box
		for(int i=0;i<moves; i++){
			cheatwindow->addItem(QString::number((*sol).at(i)));
		}


	}

}


