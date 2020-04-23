#ifndef H_EXTENSIONS_CUTEHMI_DATAACQUISITION_0_INCLUDE_CUTEHMI_DATAACQUISITION_INTERNAL_TAGCACHE_HPP
#define H_EXTENSIONS_CUTEHMI_DATAACQUISITION_0_INCLUDE_CUTEHMI_DATAACQUISITION_INTERNAL_TAGCACHE_HPP

#include "common.hpp"
#include "TableObject.hpp"

#include <QReadWriteLock>

namespace cutehmi {
namespace dataacquisition {
namespace internal {

class CUTEHMI_DATAACQUISITION_PRIVATE TagCache:
	public TableObject
{
	public:
		explicit TagCache(Schema * schema, QObject * parent = nullptr);

		int getId(const QString & name, QSqlDatabase & db);

	protected:
		void insert(const QString & name, QSqlDatabase & db);

		void update(QSqlDatabase & db);

	private:
		typedef QHash<QString, int> TagIdContainter;

		struct Members
		{
			Schema * schema;
			TagIdContainter tagIds;
			QReadWriteLock tagIdsLock;
		};

		MPtr<Members> m;
};

}
}
}

#endif
