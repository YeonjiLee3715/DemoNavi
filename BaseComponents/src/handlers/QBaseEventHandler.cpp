#include "QBaseEventHandler.h"

namespace nsQBaseEventHandler
{
    const char* TAG = "QBaseEventHandler";
}

using namespace nsQBaseEventHandler;

QBaseEventHandler::QBaseEventHandler(QObject *parent)
    : QObject(parent)
{

}

QBaseEventHandler::~QBaseEventHandler()
{
    disconnect( this, nullptr, nullptr, nullptr );
}
