#ifndef QMODULEENUM_H
#define QMODULEENUM_H

#define MODULE_ViewControlModule        "ViewControlModule"

#define MDL_NAME( CLASS ) \
    QString( MODULE_##CLASS )

#define MDL_ID( CLASS ) \
    static_cast<int>( QModuleEnum::eMODULE::CLASS )

#include <QObject>
#include <QMetaEnum>
#include <QString>

#define PARAM_ERROR_CODE                "errorCode"
#define PARAM_ERROR_MESSAGE             "errorMessage"
#define PARAM_RESULT_CODE               "resultCode"

typedef QHash< QString, QVariant > MODULE_PARAM;

typedef enum eModuleRequestCode{
    MDL_REQ_NONE = 0,
    MDL_REQ_REFRESH_TREE_MODEL
}ModuleRequestCode;

typedef enum eModuleResponseCode{
    MDL_RES_NONE = 0,
    MDL_RES_REFRESH_TREE_MODEL
}ModuleResponseCode;

typedef enum eModuleErrorCode{
    MDL_ERROR_NONE = 0
}ModuleErrorCode;

typedef enum eModuleResultCode{
    MDL_RESULT_FAILED,
    MDL_RESULT_SUCCESSED
}ModuleResultCode;

class QModuleEnum : public QObject
{
    Q_OBJECT
public:
    typedef enum eMODULE{
        UNKNOWN = 0,
        DemoNavi = 1,
        ViewControlModule,

        ALL = 10000
    } eMODULE;

    QModuleEnum( QObject* parent );
    virtual ~QModuleEnum();
    Q_ENUM(eMODULE)

public:
    static bool isMainManager(QModuleEnum::eMODULE eModule)
    {
        return ( eModule == DemoNavi );
    }

    static QString getStringFromEnum( eMODULE eModule )
    {
         return QString( QMetaEnum::fromType<QModuleEnum::eMODULE>().valueToKey(static_cast<int>(eModule)) );
    }

    static int getIndexFromString( const QString& strName )
    {
        return QMetaEnum::fromType<QModuleEnum::eMODULE>().keysToValue( strName.toStdString().c_str() );
    }
};

#endif // QMODULEENUM_H
