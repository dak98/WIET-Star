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
