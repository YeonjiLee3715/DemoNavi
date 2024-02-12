#ifndef NAVIHOMEVIEW_H
#define NAVIHOMEVIEW_H

#include <QObject>
#include <QBaseView.h>

class NaviHomeView final : public QBaseView
{
    Q_OBJECT
public:
    explicit NaviHomeView(QObject* objView, QObject* parent = nullptr);
    virtual  ~NaviHomeView();

protected:
    virtual void    RegistControlEventHandlers() override;

signals:

};

#endif // NAVIHOMEVIEW_H
