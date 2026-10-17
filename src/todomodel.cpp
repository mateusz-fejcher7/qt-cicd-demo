#include "todomodel.h"

TodoModel::TodoModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

int TodoModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return static_cast<int>(m_items.size());
}

QVariant TodoModel::data(const QModelIndex &index, int role) const
{
    if (!checkIndex(index, CheckIndexOption::IndexIsValid | CheckIndexOption::ParentIsInvalid))
        return {};

    const Item &item = m_items.at(index.row());
    switch (role) {
    case TitleRole:
        return item.title;
    case DoneRole:
        return item.done;
    default:
        return {};
    }
}

QHash<int, QByteArray> TodoModel::roleNames() const
{
    return {
        { TitleRole, "title" },
        { DoneRole, "done" },
    };
}

bool TodoModel::add(const QString &title)
{
    const QString trimmed = title.trimmed();
    if (trimmed.isEmpty())
        return false;

    const int row = rowCount();
    beginInsertRows(QModelIndex(), row, row);
    m_items.append({ trimmed, false });
    endInsertRows();
    return true;
}

void TodoModel::remove(int row)
{
    if (row < 0 || row >= rowCount())
        return;

    beginRemoveRows(QModelIndex(), row, row);
    m_items.removeAt(row);
    endRemoveRows();
}

void TodoModel::toggle(int row)
{
    if (row < 0 || row >= rowCount())
        return;

    m_items[row].done = !m_items[row].done;
    const QModelIndex idx = index(row);
    emit dataChanged(idx, idx, { DoneRole });
}
