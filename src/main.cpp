// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "app_environment.h"
#include "import_qml_components_plugins.h"
#include "import_qml_plugins.h"

#include "DemoNavi.h"

Q_IMPORT_QML_PLUGIN(com_custom_basecomponentsPlugin)

int main(int argc, char *argv[])
{
    set_qt_environment();

    DemoNavi app(argc, argv);

    if( app.Init() == false ){
        return -1;
    }

    return app.exec();
}
