#include "Gwindow.h"
#include "Mwindow.h"
#include "guitiles.h"
#include <QPushButton>
#include <QApplication>
#include<vector>
#include<iostream>
#include<vector>
#include<cmath>

/** 
in the graphics window constructor I create a new scene that holds the 
gameboard tiles and add that to the graphics view. the board is set to null
and a blank finished board initially shows up.


*/
GWindow::GWindow()  {

	scene = new QGraphicsScene();
	view = new QGraphicsView( scene );
	//QLineEdit *error = new QLineEdit("  ");

	b_=NULL;

	Board *blank = new Board(9,0,342);
	createboard(blank);
	view->setFixedSize( 270, 270 );
	view->setWindowTitle( "Puzzle");
	view->show();



}

/** a new playable board is then created passing in a b_ item 
from the board class. all the tiles a Qrectitems whose dimensions
are set based on the size of the board and the dimensions of the
game window. all the tile items are added to the vector of guitiles
with their respective location and text number.


*/
void GWindow::createboard(Board *b){

	//sets up board

	if(b_!=NULL)//in case board isnt null, deletes everything in board
	{
		for (int i=0; i<b_->getSize();i++)
		{
			delete tiles[i];
		}
		tiles.clear();
		delete b_;
	}
	b_=b;
	di = static_cast<int>(sqrt(b_->getSize()));

	int *temptiles= b_->getTiles();

	for(int i=0; i<b_->getSize(); i++){
		// new tile at right location
		item = new GUItiles(temptiles[i],(i%di)*(240/di), (i/di)*(240/di), 240/di, 240/di, this);
		// add tile to vector of guitiles 
		tiles.push_back (item);
		if(temptiles[i]!=0)
		{       //if tile isnt black, show the tile on the gameboard
			scene->addItem(tiles[i]);
			//set color
			item->setBrush (QColor(204,238,255,150));
			//connect function as a button, if clicked, calls move function
			connect(tiles[i], SIGNAL(clicked(int ,GUItiles*)), this, SLOT(movetile(int,GUItiles*)));
		}
	}
}
/** deconstructor*/
GWindow::~GWindow()
{


}
/** how tiles are moved- first we move the board tiles in the board array
that corresponds with the text num of the guitile pressed.
the position of the tile that is moved in the board tile array is then
set to be the "empty" guitile. the tile item that is pressed is moved to 
the empty slot.  
*/
void GWindow::movetile(int num, GUItiles *tile){
	if(b_->solved()) return;// if game solved, board becomes static

	di = static_cast<int>(sqrt(b_->getSize()));

	b_->move(num);
	int empty=0;
	if((b_->key)==1)//if board move is no allowed 
	//key is 0 if move is not performed on the board num in the board class
	// the tile isnt adjacent to a blank space
	{
		error->setText("invalid, try another move yo");

	}
	if((b_->key)==0){
	// key is 0 if move is possible
		int keyx, keyy;
		int *temptiles= b_->getTiles();
		// find black space
		for (int i=0; i<b_->getSize();i++){
			if (temptiles[i]==num){
				empty=i;
				break;
			}
		}
		
		// figure out the move to position based on location of blank space
		keyx = empty % di;
		keyy = empty / di; 

		// set that as x and y
		tile->setX(keyx*(240/di));
		tile->setY(keyy*(240/di));
		//start timer which calls animate and moves tiles
		tile->starttimer();

		//if solved, end board functions
		if(b_->solved()) {
			error->setText(" WHOO FINISHED !");
			return;
		}
	}
}




