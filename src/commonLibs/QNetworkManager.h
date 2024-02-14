#ifndef QNETWORKMANAGER_H
#define QNETWORKMANAGER_H

#include <QObject>

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

#define NETWORK_RESPONS_SIGNAL( RECEIVER ) \
    void SendResponsTo##RECEIVER( int messageId, QNetworkReply* netRes );

#define NETWORK_EMIT_RESPONS_SIGNAL( RECEIVER , MESSAGEID, NETRES) \
    emit SendResponsTo##RECEIVER( MESSAGEID, NETRES );

#define NETWORK_RESPONS_SLOT    \
    void ReceiveNetworkRespons( int messageId, QNetworkReply* netRes );

#define NETWORK_DEF_RESPONS_SLOT( RECEIVER )    \
    void RECEIVER::ReceiveNetworkRespons( int messageId, QNetworkReply* netRes )

#define NETWORK_CONNECT_SIGNAL( P_NETWORKMANAGER, RECEIVER, P_RECEIVER ) \
    connect(P_NETWORKMANAGER, SIGNAL(SendResponsTo##RECEIVER(int, QNetworkReply*)),P_RECEIVER, SLOT(ReceiveNetworkRespons(int, QNetworkReply*)), Qt::QueuedConnection);

class QNetworkManager : public QObject
{
    Q_OBJECT

public:
    typedef enum eNetworkRequestType{
        NETWORK_REQUEST_GET,    //QNetworkRequest::User
        NETWORK_REQUEST_PUT
    }NetworkRequestType;

    typedef enum eNetworkAttribute{
        NETWORK_ATTRIBUTE_MESSAGE_ID = 20000,   //QNetworkRequest::User
        NETWORK_ATTRIBUTE_SENDER,
        NETWORK_ATTRIBUTE_COMMAND,
        NETWORK_ATTRIBUTE_FILE_NAME,
        NETWORK_ATTRIBUTE_FILE_TYPE
    }NetworkAttribute;

    typedef enum eRequestSender{
        SENDER_UNKNOWN = 0,
    }RequestSender;

public:
    explicit QNetworkManager( QObject* parent = 0);
    ~QNetworkManager();

     // default timeout: 30 sec. see QNetworkRequest::TransferTimeoutConstant::DefaultTransferTimeoutConstant
    int Get(int nSender, QNetworkRequest& netReq, bool& isSuccess, int msTimeout = 30000 );
    QNetworkReply* GetWait(int nSender, QNetworkRequest& netReq, bool& isSuccess, int msTimeout = 30000 );

    int Post(int nSender, QNetworkRequest& netReq, const QByteArray& pData , bool &isSuccess, int msTimeout = 30000 );
    QNetworkReply* PostWait(int nSender, QNetworkRequest& netReq, const QByteArray& pData, bool& isSuccess, int msTimeout = 30000 );

protected:
    QNetworkAccessManager* getNetworkAccessManager();

    void SetSender(int nSender, QNetworkRequest& netReq );

    bool initNetworkAccessManager();
public slots:
    void ReplyFinished(QNetworkReply* netRes);
    void ReplyError( QNetworkReply::NetworkError err );
#ifndef QT_NO_SSL
    void ReplySslErrors(const QList<QSslError> &lstSslErr );
#endif

private:
    int CreateMessageId();
    int SetMessageId( QNetworkRequest& netReq );

private:
    QNetworkAccessManager*  m_mngNetwork;
};

Q_DECLARE_METATYPE(QNetworkManager::NetworkRequestType)
Q_DECLARE_METATYPE(QNetworkManager::NetworkAttribute)
Q_DECLARE_METATYPE(QNetworkManager::RequestSender)

#endif // QNETWORKMANAGER_H
