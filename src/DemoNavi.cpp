#include "DemoNavi.h"

#include <QQuickView>

#include <QLocale>
#include <QTranslator>

#include <ViewControlModule.h>

#include <CLogger.h>

namespace nsDemoNavi
{
    const char* TAG = "DemoNavi";
}

using namespace nsDemoNavi;

DemoNavi::DemoNavi(int &arg, char **argv)
    : QGuiApplication(arg, argv)
{

}

DemoNavi::~DemoNavi()
{
    QModuleManager* pManager = GetQModuleManager();
    pManager->stopIndependentModules();

    pManager->deregistModule( QModuleEnum::eMODULE::ViewControlModule );
}

QModuleManager* DemoNavi::GetQModuleManager()
{
    return QModuleManager::GetInstance();
}

bool DemoNavi::Init()
{
    bool isSuccess = false;

    do {
        if( initModules() == false ){
            LOGE( TAG, "Failed to init modules" );
            break;
        }

        isSuccess = true;

    } while(false);

    return isSuccess;
}

bool DemoNavi::initModules()
{
    QModuleManager* pManager = GetQModuleManager();
    ViewControlModule* pViewControlModule = reinterpret_cast<ViewControlModule*>(pManager->getModuleById((int)QModuleEnum::eMODULE::ViewControlModule));

    pManager->runIndependentModules();

    return true;
}

void DemoNavi::getResponse(int resCode, int sender, QVariantMap resPacket)
{
    switch( resCode )
    {
    case MDL_RES_NONE:
        break;
    default:
        break;
    }
}
