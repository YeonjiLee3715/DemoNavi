#include "SearchView.h"

#include <viewDefs.h>
#include <QViewEventHandler.h>
#include <QButtonEventHandler.h>
#include <QTextEditEventHandler.h>

#include <cmnDefs.h>

SearchView::SearchView(QObject* objView, QObject *parent)
    : QBaseView(objView, parent)
{

}

SearchView::~SearchView()
{

}

void SearchView::RegistControlEventHandlers()
{
    m_mapCtrHandlers.insert( (int)ControlEnum::OBJECT_VIEW, reinterpret_cast<QBaseEventHandler*>(new QViewEventHandler(this)));
    m_mapCtrHandlers.insert( (int)ControlEnum::OBJECT_BUTTON_CONTROL, reinterpret_cast<QBaseEventHandler*>(new QButtonEventHandler(this)));
    m_mapCtrHandlers.insert( (int)ControlEnum::OBJECT_TEXTEDIT_CONTROL, reinterpret_cast<QBaseEventHandler*>(new QTextEditEventHandler(this)));
}
