#ifndef VIEWDEFS_H
#define VIEWDEFS_H

#include <QObject>
#include <QMetaType>
#include <QMetaEnum>

#include <baseComponentsDefs.h>

// Qml object names
#define _idVwNaviHome                   "_idVwNaviHome"
#define _idVwSearch                     "_idVwSearch"

#define _idBtnSearch                    "_idBtnSearch"

// End Qml object names

class CustomControlEnum: public ControlEnum
{
    Q_OBJECT
    QML_ELEMENT

public:
    typedef enum eViewId
    {
        ID_VW_NAVI_HOME = 500,
        ID_VW_SEARCH
    }eViewId;

    typedef enum eBtnControlId
    {
        ID_BTN_WN_CLOSE = 10000,
        ID_BTN_ADD,
        ID_BTN_DELETE,
        ID_BTN_SEARCH
    }eBtnControlId;

    typedef enum eEdtControlId
    {
        ID_EDT_SEARCH = 11000,
    }eEdtControlId;

    typedef enum eLstControlId
    {
        ID_LST_SEARCH_RESULT = 12000,
    }eLstControlId;

    CustomControlEnum( QObject* parent = nullptr ): ControlEnum( parent ) {}

    Q_ENUM( eViewId )
    Q_ENUM( eBtnControlId )
    Q_ENUM( eLstControlId )
    Q_ENUM( eEdtControlId )
};

Q_DECLARE_METATYPE( CustomControlEnum::eViewId )
Q_DECLARE_METATYPE( CustomControlEnum::eBtnControlId )
Q_DECLARE_METATYPE( CustomControlEnum::eLstControlId )
Q_DECLARE_METATYPE( CustomControlEnum::eEdtControlId )

#endif // VIEWDEFS_H
