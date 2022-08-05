#ifndef H_EXTENSIONS_CUTEHMI_2_INCLUDE_CUTEHMI_NOTIFIER_HPP
#define H_EXTENSIONS_CUTEHMI_2_INCLUDE_CUTEHMI_NOTIFIER_HPP

#include "internal/common.hpp"
#include "NotificationListModel.hpp"
#include "Singleton.hpp"

#include <QObject>
#include <QMutexLocker>
#include <QQmlEngine>

#include <limits>

namespace cutehmi {

/**
 * %Notifier.
 */
class CUTEHMI_API Notifier:
	public QObject,
	public Singleton<Notifier>
{
		Q_OBJECT
		//<CuteHMI.Workarounds.Qt5Compatibility-4.workaround target="Qt" cause="Qt5.15-QML_SINGLETON">
#if (QT_VERSION >= QT_VERSION_CHECK(6, 0, 0))
		QML_NAMED_ELEMENT(Notifier)
		QML_UNCREATABLE("Notifier is a singleton")
		QML_SINGLETON
#endif
		//</CuteHMI.Workarounds.Qt5Compatibility-4.workaround>

		friend class Singleton<Notifier>;

	public:
		Q_PROPERTY(cutehmi::NotificationListModel * model READ model CONSTANT)

		Q_PROPERTY(int maxNotifications READ maxNotifications WRITE setMaxNotifications NOTIFY maxNotificationsChanged)

		NotificationListModel * model() const;

		/**
		 * Create intance.
		 * @param qmlEngine QML engine instance.
		 * @param jsEngine JavaScript engine instance.
		 * @return instance.
		 *
		 * @note this method is used by QQmlEngine when class is annotated with QML_SINGLETON macro.
		 */
		static Notifier * create(QQmlEngine * qmlEngine, QJSEngine * jsEngine);

		int maxNotifications() const;

		void setMaxNotifications(int maxNotifications);

	public slots:
		/**
		 * Add notification.
		 * @param notification_l notification to add. Parameter will be used locally by this function.
		 * It's passed by a pointer instead of a reference for easier integration with QML.
		 *
		 * @threadsafe
		 */
		void add(cutehmi::Notification * notification_l);

		void clear();

	signals:
		void maxNotificationsChanged();

		void notificationAdded();

	protected:
		explicit Notifier(QObject * parent = nullptr);

	private:
		struct Members
		{
			std::unique_ptr<NotificationListModel> model {new NotificationListModel};
			QMutex modelMutex {};
			int maxNotifications {std::numeric_limits<int>::max()};
		};

		MPtr<Members> m;
};

}

#endif

//(c)C: Copyright © 2019-2022, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: SPDX-License-Identifier: LGPL-3.0-or-later OR MIT
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
//(c)C: Additionally, this file is licensed under terms of MIT license as expressed below.
//(c)C: Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//(c)C: The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//(c)C: THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
