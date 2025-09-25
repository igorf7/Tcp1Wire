#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>
#include <QTcpSocket>

class TcpClient : public QObject
{
    Q_OBJECT
public:
    TcpClient(QObject *parent = nullptr);

    ~TcpClient();

signals:
    void showResponse(const QByteArray &response);
    void showError(const QByteArray &err_msg);
    void confirmTcpConnection(bool isConnected);
    void quitTcpClient();

private:
    QTcpSocket* tcpSocket;

private slots:
    void slotReadyRead();
    void slotError(QAbstractSocket::SocketError);
    void slotConnected();
    void slotDisconnected();

public slots:
    void onClientStart();
    void onSetTcpConnection(const QString &hostName, quint16 port);
    void onSetTcpDisconnection();
    void onSendToServer(const QByteArray &msg);
};

#endif // TCPCLIENT_H
