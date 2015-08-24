#include "utils.h"

namespace mdview {

QString pathAppend(const QString &path1, const QString &path2)
{
    return QDir::cleanPath(path1 + QDir::separator() + path2);
}

}  // namespace mdview
