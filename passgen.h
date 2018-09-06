#pragma once

#include <QtWidgets/QMainWindow>
#include "bassmod.h"
#include "ui_passgen.h"
#include "gen.h"

class PassGen : public QMainWindow
{
	Q_OBJECT

public:
	PassGen(QWidget *parent = Q_NULLPTR);
	~PassGen();
private:
	Ui::PassGenClass ui;
	Gen *m_generator;
	void soundBassmod(); //initialize music using BASSMOD library
public slots:
	void slotMusic(bool); //pause or play music
};
