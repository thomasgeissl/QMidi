#include "mainwindow.h"

#include <QDebug>
#include <QComboBox>
#include <QFont>
#include <QHBoxLayout>

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      _midiIn(new QMidiIn(this)),
      _midiOut(new QMidiOut(this)),
      _inPortComboBox(new QComboBox(this)),
      _outPortComboBox(new QComboBox(this)),
      _inConsole(new QPlainTextEdit),
      _messageComposer(new MessageComposer(this))
{
    QWidget *mainWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(mainWidget);

    qDebug()<<"inputs"<<_midiIn->getPorts();
    qDebug()<<"outputs"<<_midiOut->getPorts();

    _inPortComboBox->addItems(_midiIn->getPorts());
    _outPortComboBox->addItems(_midiOut->getPorts());

    QLabel *inLabel = new QLabel("Midi In");
    QLabel *outLabel = new QLabel("Midi Out");

    QFont headingFont = inLabel->font();
    headingFont.setBold(true);
    headingFont.setPixelSize(18);
    inLabel->setFont(headingFont);
    outLabel->setFont(headingFont);

    mainLayout->addWidget(inLabel);
    mainLayout->addWidget(_inPortComboBox);
    QPushButton *inOpenPortButton = new QPushButton(tr("Open port"));
    QPushButton *inOpenVirtualPortButton = new QPushButton(tr("Open virtual port"));

    connect(inOpenPortButton, SIGNAL(clicked(bool)), this, SLOT(onInOpenPortButtonClicked(bool)));
    connect(inOpenVirtualPortButton, SIGNAL(clicked(bool)), this, SLOT(onInOpenVirtualPortButtonClicked(bool)));

    mainLayout->addWidget(inOpenPortButton);
    mainLayout->addWidget(inOpenVirtualPortButton);

    _inConsole->setDisabled(true);
    mainLayout->addWidget(_inConsole);

    mainLayout->addWidget(outLabel);
    mainLayout->addWidget(_outPortComboBox);
    QPushButton *outOpenPortButton = new QPushButton(tr("Open port"));
    connect(outOpenPortButton, SIGNAL(clicked(bool)), this, SLOT(onOutOpenPortButtonClicked(bool)));

    mainLayout->addWidget(outOpenPortButton);
    mainLayout->addWidget(_messageComposer);
    QLabel *sendLabel = new QLabel("Send message");
    QFont sendLabelFont = sendLabel->font();
    sendLabelFont.setBold(true);
    sendLabelFont.setPointSize(14);
    sendLabel->setFont(sendLabelFont);
    mainLayout->addWidget(sendLabel);

    QPushButton *sendMessageButton = new QPushButton("Send message");
    connect(sendMessageButton, SIGNAL(clicked(bool)), this, SLOT(onSendMessageButtonClicked(bool)));
    mainLayout->addWidget(sendMessageButton);



    mainWidget->setLayout(mainLayout);
    setCentralWidget(mainWidget);
}

MainWindow::~MainWindow()
{

}

void MainWindow::onMidiMessageReceive(QMidiMessage *message)
{
    _inConsole->appendPlainText("");

}

void MainWindow::onInOpenPortButtonClicked(bool value)
{
    Q_UNUSED(value);
    qDebug()<<"opening input"<<_inPortComboBox->currentText();
    _midiIn->openPort(_inPortComboBox->currentIndex());
}

void MainWindow::onInOpenVirtualPortButtonClicked(bool value)
{
    _midiIn->openVirtualPort("QMidiExample");
}

void MainWindow::onOutOpenPortButtonClicked(bool value)
{
    Q_UNUSED(value);
    qDebug()<<"opening output"<<_outPortComboBox->currentText();
    _midiOut->openPort(_outPortComboBox->currentIndex());
}

void MainWindow::onSendMessageButtonClicked(bool value)
{
    Q_UNUSED(value);
    _midiOut->sendMessage(_messageComposer->getMidiMessage());
}
