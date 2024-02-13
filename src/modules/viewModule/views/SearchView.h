#ifndef SEARCHVIEW_H
#define SEARCHVIEW_H

#include <QObject>
#include <QBaseView.h>

class SearchView final : public QBaseView
{
    Q_OBJECT
public:
    explicit SearchView(QObject* objView, QObject* parent = nullptr);
    virtual  ~SearchView();

protected:
    virtual void    RegistControlEventHandlers() override;

signals:

};

#endif // SEARCHVIEW_H
