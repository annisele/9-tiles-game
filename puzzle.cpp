#include <QApplication>
#include <QGraphicsView>
#include <QMainWindow>
#include "Mwindow.h"
#include "Gwindow.h"
#include <iostream>
#include <cstdlib>
#include <deque>
#include "board.h"
#include "puzzle_heur.h"
#include "puzzle_solver.h"
#include "puzzle_move.h"
using namespace std;

/** @mainpage CSCI102 qt Puzzle -pa4
@section purpose Overview
simple puzzle game created using qt
@section requirements Requirements
how to call: ./puzzle_yiwen

*/

/**
main function which call the application which runs the 8 tile game.
*/

int main(int argc, char *argv[])
{

	QApplication a(argc, argv);
	MainWindow w;
	w.show();

	return a.exec();
}
