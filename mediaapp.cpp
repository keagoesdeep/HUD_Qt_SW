#include "mediaapp.h"
#include "player.h"

#include <QBoxLayout>
#include <QFileDialog>
#include <QToolButton>
#include <QMouseEvent>

MediaApp::MediaApp(QWidget *parent)
    : QWidget(parent)
{
    //create the player
    m_player = new Player(this);
    connect(m_player, SIGNAL(positionChanged()), this, SLOT(onPositionChanged()));
    connect(m_player, SIGNAL(stateChanged()), this, SLOT(onStateChanged()));

    //this timer (re-)hides the controls after a few seconds when we are in fullscreen mode
    m_fullScreenTimer.setSingleShot(true);
    connect(&m_fullScreenTimer, SIGNAL(timeout()), this, SLOT(hideControls()));

    //create the UI
    QVBoxLayout *appLayout = new QVBoxLayout;
    appLayout->setContentsMargins(0, 0, 0, 0);
    createUI(appLayout);
    setLayout(appLayout);

    onStateChanged(); //set the controls to their default state

    setWindowTitle(tr("Ground station"));
    resize(400, 400);
}

MediaApp::~MediaApp()
{
    delete m_player;
}

void MediaApp::toggleFullScreen()
{
    if (isFullScreen()) {
        setMouseTracking(false);
        m_player->setMouseTracking(false);
        m_fullScreenTimer.stop();
        showControls();
        showNormal();
    } else {
        setMouseTracking(true);
        m_player->setMouseTracking(true);
        hideControls();
        showFullScreen();
    }
}

void MediaApp::onStateChanged()
{
    QGst::State newState = m_player->state();
    m_playButton->setEnabled(newState != QGst::StatePlaying);
    m_pauseButton->setEnabled(newState == QGst::StatePlaying);

    //if we are in Null state, call onPositionChanged() to restore
    //the position of the slider and the text on the label
    if (newState == QGst::StateNull) {
        onPositionChanged();
    }
}

/* Called when the positionChanged() is received from the player */
void MediaApp::onPositionChanged()
{
    QTime length(0,0);
    QTime curpos(0,0);

    if (m_player->state() != QGst::StateReady &&
        m_player->state() != QGst::StateNull)
    {
        length = m_player->length();
        curpos = m_player->position();
    }
    // changed the position of slider that showed movie time
    // currently does nothing, to be deleted in the future
}

/* Called when the user changes the slider's position */
void MediaApp::setPosition(int value)
{
    uint length = -m_player->length().msecsTo(QTime(0,0));
    if (length != 0 && value > 0) {
        QTime pos(0,0);
        pos = pos.addMSecs(length * (value / 1000.0));
        m_player->setPosition(pos);
    }
}

void MediaApp::showControls(bool show)
{
    m_playButton->setVisible(show);
    m_pauseButton->setVisible(show);
    m_fullScreenButton->setVisible(show);
}

void MediaApp::mouseMoveEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    if (isFullScreen()) {
        showControls();
        m_fullScreenTimer.start(3000); //re-hide controls after 3s
    }
}

QToolButton *MediaApp::initButton(QStyle::StandardPixmap icon, const QString & tip,
                                  QObject *dstobj, const char *slot_method, QLayout *layout)
{
    QToolButton *button = new QToolButton;
    button->setIcon(style()->standardIcon(icon));
    button->setIconSize(QSize(36, 36));
    button->setToolTip(tip);
    connect(button, SIGNAL(clicked()), dstobj, slot_method);
    layout->addWidget(button);

    return button;
}

void MediaApp::createUI(QBoxLayout *appLayout)
{
    appLayout->addWidget(m_player);

    QHBoxLayout *btnLayout = new QHBoxLayout;
    btnLayout->addStretch();


    m_playButton = initButton(QStyle::SP_MediaPlay, tr("Play"),
                              m_player, SLOT(play()), btnLayout);

    m_pauseButton = initButton(QStyle::SP_MediaPause, tr("Pause"),
                               m_player, SLOT(pause()), btnLayout);

    m_fullScreenButton = initButton(QStyle::SP_TitleBarMaxButton, tr("Fullscreen"),
                                    this, SLOT(toggleFullScreen()), btnLayout);
    btnLayout->addStretch();

    appLayout->addLayout(btnLayout);
}

#include "moc_mediaapp.cpp"
