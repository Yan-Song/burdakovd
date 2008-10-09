/***************************************************************************
 *   Copyright (C) 2008 by Burdakov Daniel   *
 *   kreved@kreved.org   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/


#include <QtGui>
#include "worms.h"

worms::worms()
{
      createActions();
      createMenus();
      createToolBars();
      createStatusBar();
      settings = new QSettings("kreved.org", "worms");
      scene = new QGraphicsScene;
      
      scene->addEllipse(QRectF(-100.0, -100.0, 100.0, 100.0));
      scene->setBackgroundBrush(Qt::blue);
      this->
 // a gradient background
 QRadialGradient gradient(0, 0, 10);
 gradient.setSpread(QGradient::RepeatSpread);
 scene->setBackgroundBrush(gradient);
      
      QGraphicsView view(scene);
      view.show();
      readSettings();
}

void worms::about()
{
      QMessageBox::about(this, tr("About Application"),
            QString("This program was built ")+__DATE__+" "+__TIME__);
}

void worms::createActions()
{
      exitAct = new QAction(tr("E&xit"), this);
      exitAct->setShortcut(tr("Ctrl+Q"));
      exitAct->setStatusTip(tr("Exit the application"));
      connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

      aboutAct = new QAction(tr("&About"), this);
      aboutAct->setStatusTip(tr("Show the application's About box"));
      connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));
}

void worms::createMenus()
{
      fileMenu = menuBar()->addMenu(tr("&File"));
      fileMenu->addSeparator();
      fileMenu->addAction(exitAct);
      
      helpMenu = menuBar()->addMenu(tr("&Help"));
      helpMenu->addAction(aboutAct);
}

void worms::createToolBars()
{
//       editToolBar = addToolBar(tr("Edit"));
//       editToolBar->addAction(cutAct);
//       editToolBar->addAction(copyAct);
//       editToolBar->addAction(pasteAct);
}

void worms::createStatusBar()
{
      statusBar()->showMessage(tr("Ready"));
}

void worms::readSettings()
{
      QPoint pos = settings->value("pos", QPoint(200, 200)).toPoint();
      QSize size = settings->value("size", QSize(400, 400)).toSize();
      resize(size);
      move(pos);
}

void worms::writeSettings()
{
      settings->setValue("pos", pos());
      settings->setValue("size", size());
}

worms::~worms()
{

}

