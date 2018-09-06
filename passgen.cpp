#include "passgen.h"
#include "gen.h"
#include <QString>
#include "bassmod.h"


void PassGen::slotMusic(bool on)
{
	if (on)
	{
		ui.pushButtonMusic->setText("Music:\nON");
		BASSMOD_MusicPlay();
	}
	else
	{
		ui.pushButtonMusic->setText("Music:\nOFF");
		BASSMOD_MusicPause();
	}

}

PassGen::PassGen(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	soundBassmod();
	m_generator = new Gen(
		ui.comboBoxPassLength->currentIndex() + 1,
		ui.checkBoxSymbols->isChecked(),
		ui.checkBoxNumbers->isChecked(),
		ui.checkBoxLowercase->isChecked(),
		ui.checkBoxUppercase->isChecked(),
		ui.checkBoxSimilar->isChecked(),
		ui.checkBoxAmbigous->isChecked()
	);
	connect(ui.comboBoxPassLength, SIGNAL(currentIndexChanged(int)), m_generator, SLOT(slotSetLength(int)));
	connect(ui.checkBoxSymbols, SIGNAL(stateChanged(int)), m_generator, SLOT(slotSetSymbols(int)));
	connect(ui.checkBoxNumbers, SIGNAL(stateChanged(int)), m_generator, SLOT(slotSetNumbers(int)));
	connect(ui.checkBoxLowercase, SIGNAL(stateChanged(int)), m_generator, SLOT(slotSetLowercase(int)));
	connect(ui.checkBoxUppercase, SIGNAL(stateChanged(int)), m_generator, SLOT(slotSetUppercase(int)));
	connect(ui.checkBoxSimilar, SIGNAL(stateChanged(int)), m_generator, SLOT(slotSetSimilar(int)));
	connect(ui.checkBoxAmbigous, SIGNAL(stateChanged(int)), m_generator, SLOT(slotSetAmbigous(int)));
	connect(ui.pushButtonGenerate, SIGNAL(pressed()), m_generator, SLOT(slotGeneratePassword()));
	connect(m_generator, SIGNAL(signalPassword(QString)), ui.lineEditPassOut, SLOT(setText(QString)));
	connect(ui.pushButtonCopy, SIGNAL(pressed()), ui.lineEditPassOut, SLOT(selectAll()));
	connect(ui.pushButtonCopy, SIGNAL(pressed()), ui.lineEditPassOut, SLOT(copy()));
	connect(ui.pushButtonMusic, SIGNAL(toggled(bool)), this, SLOT(slotMusic(bool)));
}

PassGen::~PassGen()
{
	BASSMOD_Free();
}

void PassGen::soundBassmod()
{
	if (!BASSMOD_Init(-1, 44100, 0)) //initialize device
	{
		BASSMOD_Init(-2, 44100, 0); //in case of failure initialize device without sound
	}
	BASSMOD_MusicLoad(false, "sound\\DYNAMITE.xm", 0, 0, BASS_MUSIC_LOOP);
	BASSMOD_MusicPlay();
}