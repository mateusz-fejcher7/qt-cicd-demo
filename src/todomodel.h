#pragma once

#include <QAbstractListModel>
#include <QList>
#include <QString>
#include <QtQml/qqmlregistration.h>

class TodoModel : public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT

public:
    enum Roles {
        TitleRole = Qt::UserRole + 1,
        DoneRole
    };
    Q_ENUM(Roles)

    explicit TodoModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE bool add(const QString &title);
    Q_INVOKABLE void remove(int row);
    Q_INVOKABLE void toggle(int row);

private:
    struct Item {
        QString title;
        bool done = false;
    };

    QList<Item> m_items;
};
