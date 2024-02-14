#include "QNetworkManager.h"

#include <QRandomGenerator>

#include "CLogger.h"

#include <unistd.h>

namespace nsQNetworkManager{
const char* TAG = "QNetworkManager";
}

using namespace nsQNetworkManager;

QNetworkManager::QNetworkManager( QObject* parent) :
    QObject(parent)
{
    initNetworkAccessManager();
}

QNetworkManager::~QNetworkManager()
{
    if( m_mngNetwork!= nullptr ){
        delete m_mngNetwork;
        m_mngNetwork = nullptr;
    }
}

int QNetworkManager::Get(int nSender, QNetworkRequest& netReq, bool &isSuccess, int msTimeout)
{
    isSuccess = false;

    if( netReq.url().isEmpty() || netReq.url().isValid() == false )
        return 0;

    netReq.setTransferTimeout( 10000 ); // 10 sec
    int messageId = SetMessageId( netReq );
    SetSender( nSender, netReq );
    LOGI( TAG, "messageId: %d, Sender: %d", messageId, nSender );

    QNetworkReply* netRes = m_mngNetwork->get(netReq);

    if( netRes->error() == QNetworkReply::NoError )
        isSuccess = true;

    return messageId;
}

int QNetworkManager::Post(int nSender, QNetworkRequest& netReq, const QByteArray& data, bool& isSuccess , int msTimeout)
{
    isSuccess = false;

    if( netReq.url().isEmpty() || netReq.url().isValid() == false )
        return 0;

    int messageId = SetMessageId( netReq );
    SetSender( nSender, netReq );
    LOGI( TAG, "messageId: %d, Sender: %d", messageId, nSender );

    QNetworkReply* netRes = m_mngNetwork->put(netReq, data);

    if( netRes->error() == QNetworkReply::NoError )
        isSuccess = true;

    return messageId;
}

QNetworkReply* QNetworkManager::PostWait( int nSender, QNetworkRequest& netReq, const QByteArray& data, bool& isSuccess, int msTimeout)
{
    isSuccess = false;

    if( netReq.url().isEmpty() || netReq.url().isValid() == false )
        return nullptr;

    netReq.setAttribute((QNetworkRequest::Attribute)NETWORK_ATTRIBUTE_MESSAGE_ID, QVariant((int)0));
    SetSender( nSender, netReq );
    LOGI( TAG, "messageId: 0, Sender: %d", nSender );

    QEventLoop loop;

    QNetworkReply* netRes = m_mngNetwork->put(netReq, data);

    connect(netRes, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
    disconnect(netRes, SIGNAL(finished()), &loop, SLOT(quit()));

    if( netRes->error() == QNetworkReply::NoError ) {
        isSuccess = true;
    }
    else {
        LOGI( TAG, "messageId: 0, nSender: %d Error(%d): %s"
             , nSender, (int)netRes->error(), netRes->errorString().toStdString().c_str() );
    }

    if( netRes->isFinished() == false )
        netRes->abort();

    return netRes;
}

QNetworkAccessManager* QNetworkManager::getNetworkAccessManager()
{
    return m_mngNetwork;
}

QNetworkReply* QNetworkManager::GetWait( int nSender, QNetworkRequest& netReq, bool& isSuccess, int msTimeout )
{
    isSuccess = false;

    if( netReq.url().isEmpty() || netReq.url().isValid() == false )
        return nullptr;

    netReq.setAttribute((QNetworkRequest::Attribute)NETWORK_ATTRIBUTE_MESSAGE_ID, QVariant((int)0));
    SetSender( nSender, netReq );
    LOGI( TAG, "messageId: 0, Sender: %d", nSender );

    QEventLoop loop;

    QNetworkReply* netRes = m_mngNetwork->get(netReq);

    connect(netRes, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
    disconnect(netRes, SIGNAL(finished()), &loop, SLOT(quit()));

    if( netRes->error() == QNetworkReply::NoError ) {
        isSuccess = true;
    }
    else {
        LOGE( TAG, "messageId: 0, nSender: %d Error(%d): %s"
             , nSender, (int)netRes->error(), netRes->errorString().toStdString().c_str() );
    }

    if( netRes->isFinished() == false )
        netRes->abort();

    return netRes;
}

void QNetworkManager::ReplyFinished(QNetworkReply* netRes)
{
    if( netRes == nullptr )
        return;

    int messageId = netRes->request().attribute( (QNetworkRequest::Attribute)NETWORK_ATTRIBUTE_MESSAGE_ID ).toInt();
    int nSender = netRes->request().attribute( (QNetworkRequest::Attribute)NETWORK_ATTRIBUTE_SENDER ).toInt();

    LOGI( TAG, "messageId: %d, nSender: %d Error(%d): %s"
            , messageId, nSender, (int)netRes->error(), netRes->errorString().toStdString().c_str() );

    netRes->deleteLater();
}

void QNetworkManager::ReplyError(QNetworkReply::NetworkError err)
{
    QNetworkReply* netRes = qobject_cast<QNetworkReply*>(sender());

    int messageId = 0;
    if( netRes != nullptr )
       messageId = netRes->request().attribute( (QNetworkRequest::Attribute)NETWORK_ATTRIBUTE_MESSAGE_ID ).toInt();

    LOGE( TAG, "messageId: %d, Error(%d): %s"
                , messageId, (int)err, netRes->errorString().toStdString().c_str() );
}

#ifndef QT_NO_SSL
void QNetworkManager::ReplySslErrors(const QList<QSslError>& lstSslErr)
{
    QNetworkReply* netRes = qobject_cast<QNetworkReply*>(sender());
    int messageId = 0;

    if( netRes != nullptr )
       messageId = netRes->request().attribute( (QNetworkRequest::Attribute)NETWORK_ATTRIBUTE_MESSAGE_ID ).toInt();

    QString strErr;
    for( QList<QSslError>::const_iterator it = lstSslErr.cbegin(); it != lstSslErr.cend(); ++it )
        strErr.append( QString( "\tError(%1): %2\n" ).arg( it->error() ).arg( it->errorString() ) );

    LOGE( TAG, "messageId: %d \n%s", messageId, strErr.toStdString().c_str() );
}
#endif

int QNetworkManager::CreateMessageId()
{
    return QRandomGenerator::global()->generate();
}

int QNetworkManager::SetMessageId(QNetworkRequest& netReq)
{
    int messageId = CreateMessageId();
    //응답 받은 후 처리를 위한 정보 저장
    netReq.setAttribute((QNetworkRequest::Attribute)NETWORK_ATTRIBUTE_MESSAGE_ID, QVariant(messageId));

    return messageId;
}

void QNetworkManager::SetSender(int nSender, QNetworkRequest& netReq)
{
    netReq.setAttribute((QNetworkRequest::Attribute)NETWORK_ATTRIBUTE_SENDER, QVariant(nSender));
}

bool QNetworkManager::initNetworkAccessManager()
{
    m_mngNetwork = new QNetworkAccessManager(this);

    return true;
}
