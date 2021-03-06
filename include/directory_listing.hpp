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

#ifndef DIRECTORY_LISTING_HPP
#define DIRECTORY_LISTING_HPP

#include <QListWidget>

namespace wiet_star
{

class directory_listing : public QListWidget
{
    Q_OBJECT

public:
    directory_listing(QString const& path, QString const& filter, QWidget *parent = nullptr);
    directory_listing(QString const& path, QWidget *parent = nullptr);

    QString get_dir_path() const { return path; }
    void set_dir_path(QString const& dir) { path = dir; }

    bool is_item_highlighted() const { return currentItem() != nullptr; }

    // Returns the name of the song currently highlighted if there is such one.
    std::optional<QString> get_current_item() const;

public slots:
    void refresh();

private:
    QString path;
    QString filter;
};

} // wiet_star

#endif // DIRECTORY_LISTING_HPP
