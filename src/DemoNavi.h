#ifndef DEMONAVI_H
#define DEMONAVI_H

#include <QQmlApplicationEngine>
#include <QGuiApplication>

#include <QModuleManager.h>

class DemoNavi : public QGuiApplication
{
    Q_OBJECT
public:
    explicit                DemoNavi(int&, char **);
    virtual                 ~DemoNavi();

    bool                    Init();

public:
    QModuleManager*         GetQModuleManager();

private:
    bool                    initModules();

signals:


public slots:
    void                    getResponse( int resCode, int sender, QVariantMap resPacket );
};

#endif // DEMONAVI_H
