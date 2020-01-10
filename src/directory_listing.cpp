#include <directory_listing.hpp>

#include <QDebug>
#include <QDir>

namespace wiet_star
{

directory_listing::directory_listing(QString const& path, QString const& filter, QWidget *parent)
    : QListWidget{parent},
      path{path},
      filter{filter}
{
    refresh();
}

directory_listing::directory_listing(QString const& path, QWidget *parent)
    : directory_listing{path, QString(), parent} {}

std::optional<QString> directory_listing::get_current_item() const
{
    if (QListWidgetItem* i = currentItem(); is_item_highlighted())
        return i->text();
    return {};
}

// If directory does not exist, does nothing.
void directory_listing::refresh()
{
    QDir dir{path, filter};
    if (!dir.exists())
        qDebug() << "Directory" << path << "does not exist!";
    else
    {
        clear();

        foreach(QFileInfo item, dir.entryList())
            addItem(item.completeBaseName());
    }
}

} // wiet_star
