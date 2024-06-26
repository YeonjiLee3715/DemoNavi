#include "NaviHomeView.h"

#include <viewDefs.h>
#include <QViewEventHandler.h>
#include <QButtonEventHandler.h>

#include <cmnDefs.h>

NaviHomeView::NaviHomeView(QObject* objView, QObject *parent)
    : QBaseView(objView, parent)
{

}

NaviHomeView::~NaviHomeView()
{

}

void NaviHomeView::RegistControlEventHandlers()
{
    m_mapCtrHandlers.insert( (int)ControlEnum::OBJECT_VIEW, reinterpret_cast<QBaseEventHandler*>(new QViewEventHandler(this)));
    m_mapCtrHandlers.insert( (int)ControlEnum::OBJECT_BUTTON_CONTROL, reinterpret_cast<QBaseEventHandler*>(new QButtonEventHandler(this)));
}
