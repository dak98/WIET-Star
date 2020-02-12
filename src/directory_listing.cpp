/*
  Copyright 2020 Jakub Czajka

  This file is part of WietStar.

  WietStar is free software: you can redistribute it and/or modify it under the
  terms of the GNU General Public License as published by the Free Software
  Foundation, either version 3 of the License, or (at your option) any later
  version.

  WietStar is distributed in the hope that it will be useful, but WITHOUT ANY
  WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
  A PARTICULAR PURPOSE. See the GNU General Public License for more details.

  You should have received a copy of the GNU General Public License along with
  WietStar. If not, see <https://www.gnu.org/licenses/>.
*/

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
