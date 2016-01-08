#include "messagecomposer.h"

#include <QGridLayout>
#include <QLabel>
#include <QVBoxLayout>

MessageComposer::MessageComposer(QWidget *parent) : QWidget(parent),
    _statusComboBox(new QComboBox(this)),
    _channelComboBox(new QComboBox(this)),
    _pitchSpinBox(new QSpinBox(this)),
    _velocitySpinBox(new QSpinBox(this)),
    _controlSpinBox(new QSpinBox(this)),
    _valueSpinBox(new QSpinBox(this))
{

    _statuses << "Note off" << "Note on" << "Control change" << "Program change"
             << "Pitch bend" << "Aftertouch" << "Poly Aftertouch"
             << "Sysex" << "Time code" << "Song pos pointer" << "Song select"
             << "Sysex end" << "Time clock" << "Start"
             << "Continue" << "Stop" << "Active sensing" << "System reset";
    QGridLayout *mainLayout = new QGridLayout(this);

    QLabel *heading = new QLabel("Compose Message");
    QFont headingFont = heading->font();
    headingFont.setBold(true);
    headingFont.setPointSize(14);
    heading->setFont(headingFont);
    mainLayout->addWidget(heading,0,0);

    mainLayout->addWidget(new QLabel(tr("Channel")), 1,0);
    QStringList channels;
    for(int i = 1; i <= 16; i++)
    {
        channels << QString::number(i);
    }
    _channelComboBox->addItems(channels);
    mainLayout->addWidget(_channelComboBox,1,1,1,2);

    mainLayout->addWidget(new QLabel(tr("Status")),2,0);


    _statusComboBox->addItems(_statuses);

    connect(_statusComboBox, SIGNAL(currentTextChanged(QString)), this, SLOT(onStatusChange(QString)));
    mainLayout->addWidget(_statusComboBox, 2,1,1,2);

    mainLayout->addWidget(new QLabel(tr("Pitch")),3,0);
    mainLayout->addWidget(_pitchSpinBox, 3,1,1,2);

    mainLayout->addWidget(new QLabel(tr("Velocity")),4,0);
    mainLayout->addWidget(_velocitySpinBox, 4,1,1,2);

    mainLayout->addWidget(new QLabel(tr("Control")),5,0);
    mainLayout->addWidget(_controlSpinBox, 5,1,1,2);

    mainLayout->addWidget(new QLabel(tr("Value")),6,0);
    mainLayout->addWidget(_valueSpinBox, 6,1,1,2);


    mainLayout->setSpacing(0);
    mainLayout->setMargin(0);
    setLayout(mainLayout);


    onStatusChange(_statusComboBox->currentText());
}

QMidiMessage *MessageComposer::getMidiMessage()
{
    QMidiMessage *message = new QMidiMessage(this);
    return message;
}

void MessageComposer::onStatusChange(QString status)
{
    if(status == _statuses[0] || status == _statuses[1]) //note on or note off
    {
        _pitchSpinBox->setEnabled(true);
        _velocitySpinBox->setEnabled(true);
        _controlSpinBox->setEnabled(false);
        _valueSpinBox->setEnabled(false);

    }
    if(status == _statuses[2]) //control change
    {
        _pitchSpinBox->setEnabled(false);
        _velocitySpinBox->setEnabled(false);
        _controlSpinBox->setEnabled(true);
        _valueSpinBox->setEnabled(true);
    }
    if(status == _statuses[3] || status == _statuses[5]) //program change or aftertouch
    {
        _pitchSpinBox->setEnabled(false);
        _velocitySpinBox->setEnabled(false);
        _controlSpinBox->setEnabled(true);
        _valueSpinBox->setEnabled(true);
    }

    if(status == _statuses[4]) //bend
    {
        _pitchSpinBox->setEnabled(false);
        _velocitySpinBox->setEnabled(false);
        _controlSpinBox->setEnabled(false);
        _valueSpinBox->setEnabled(true);
        //TODO: value setMax
    }
    if(status == _statuses[6]) //poly aftertouch
    {
        _pitchSpinBox->setEnabled(true);
        _velocitySpinBox->setEnabled(false);
        _controlSpinBox->setEnabled(false);
        _valueSpinBox->setEnabled(true);
    }

}

