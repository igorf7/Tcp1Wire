#include "tcpclient.h"

#include <QDataStream>
#include <QDateTime>
#include <QThread>

/**
 * @brief Class constructor
 * @param parent
 */
TcpClient::TcpClient(QObject *parent) : QObject(parent)
{
    tcpSocket = new QTcpSocket(this);
    tcpSocket->setSocketOption(QAbstractSocket::LowDelayOption,
                               QVariant::fromValue(1));

    connect(tcpSocket, SIGNAL(connected()), SLOT(slotConnected()));
    connect(tcpSocket, SIGNAL(disconnected()), SLOT(slotDisconnected()));
    connect(tcpSocket, SIGNAL(readyRead()), SLOT(slotReadyRead()));
    //connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
    //        this, SLOT(slotError(QAbstractSocket::SocketError)));
}

/**
 * @brief Class dectructor
 */
TcpClient::~TcpClient()
{
    qDebug() <<"By-by from" <<this;

    if (tcpSocket->isOpen()) {
        tcpSocket->close();
    }
    emit quitTcpClient();
}

/**
 * @brief MyTcpClient::onClientStart
 */
void TcpClient::onClientStart()
{

}

/**
 * @brief MyTcpClient::slotReadyRead
 */
void TcpClient::slotReadyRead()
{
    QByteArray data;

    for (;;) {
        data += tcpSocket->readAll();
        if (tcpSocket->bytesAvailable() < 1) {
            break;
        }
    }
    if (!data.isEmpty()) {
        emit showResponse((QByteArray&)data);
    }
}

/**
 * @brief MyTcpClient::slotError
 * @param err
 */
void TcpClient::slotError(QAbstractSocket::SocketError err)
{
    QString strError =
        "Error: " + (err == QAbstractSocket::HostNotFoundError ?
                     "The host was not found." :
                     err == QAbstractSocket::RemoteHostClosedError ?
                     "The remote host is closed." :
                     err == QAbstractSocket::ConnectionRefusedError ?
                     "The connection was refused." :
                     QString(tcpSocket->errorString())
                    );
    QByteArray errMsg;
    errMsg.append(strError.toUtf8());
    emit showError(errMsg);
}

/**
 * @brief MyTcpClient::slotConnected
 */
void TcpClient::slotConnected()
{
    emit confirmTcpConnection(true);
}

/**
 * @brief MyTcpClient::slotDisconnected
 */
void TcpClient::slotDisconnected()
{
    emit confirmTcpConnection(false);
}

/**
 * @brief MyTcpClient::onSetTcpConnection
 * @param hostName
 * @param port
 */
void TcpClient::onSetTcpConnection(const QString &hostName, quint16 port)
{
    tcpSocket->connectToHost(hostName, port);
}

/**
 * @brief MyTcpClient::onSetTcpDisconnection
 */
void TcpClient::onSetTcpDisconnection()
{
    tcpSocket->close();
}

/**
 * @brief MyTcpClient::onSendToServer
 * @param msg
 */
void TcpClient::onSendToServer(const QByteArray &msg)
{
    tcpSocket->write(msg);
    tcpSocket->flush();
}
