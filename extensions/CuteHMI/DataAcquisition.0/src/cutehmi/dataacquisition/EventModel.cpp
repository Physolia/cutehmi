#include <cutehmi/dataacquisition/EventModel.hpp>

namespace cutehmi {
namespace dataacquisition {

EventModel::EventModel(QObject * parent):
	Parent(parent),
	m(new Members{
	{},
	{},
	{},
	{},
	{},
	{},
	{}})
{
	connect(this, & EventModel::schemaChanged, this, & EventModel::onSchemaChanged);
	connect(& m->dbCollective, & internal::EventCollective::selected, this, & EventModel::onSelected);
	connect(& m->dbCollective, & internal::EventCollective::busyChanged, this, & EventModel::confirmUpdateFinished);
	connect(& m->dbCollective, & internal::EventCollective::errored, this, & EventModel::broke);
	connect(& m->dbCollective, & internal::EventCollective::busyChanged, this, & EventModel::busyChanged);
}

QStringList EventModel::tags() const
{
	return m->tags;
}

void EventModel::setTags(const QStringList & tags)
{
	if (m->tags != tags) {
		m->tags = tags;
		emit tagsChanged();
	}
}

QDateTime EventModel::begin() const
{
	return m->begin;
}

QDateTime EventModel::end() const
{
	return m->end;
}

QDateTime EventModel::from() const
{
	return m->from;
}

void EventModel::setFrom(const QDateTime & from)
{
	if (m->from != from) {
		m->from = from;
		emit fromChanged();
	}
}

QDateTime EventModel::to() const
{
	return m->to;
}

void EventModel::setTo(const QDateTime & to)
{
	if (m->to != to) {
		m->to = to;
		emit toChanged();
	}
}

bool EventModel::busy() const
{
	return m->dbCollective.busy();
}

QVariant EventModel::data(const QModelIndex & index, int role) const
{
	if (!index.isValid())
		return QVariant();

	if (role == TAG_ROLE)
		return m->columnValues.tagName.at(index.row());

	if (role == VALUE_ROLE)
		return m->columnValues.value.at(index.row());

	if (role == TIME_ROLE)
		return m->columnValues.time.at(index.row());

	return QVariant();
}

QHash<int, QByteArray> EventModel::roleNames() const
{
	QHash<int, QByteArray> result = Parent::roleNames();
	result[TAG_ROLE] = "tag";
	result[VALUE_ROLE] = "value";
	result[TIME_ROLE] = "time";
	return result;
}

int EventModel::rowCount(const QModelIndex & parent) const
{
	if (parent.isValid())
		return 0;

	return m->columnValues.length();
}

void EventModel::requestUpdate()
{
	m->dbCollective.select(tags(), from(), to());
}

void EventModel::confirmUpdateFinished()
{
	if (!m->dbCollective.busy())
		emit updateFinished();
}

void EventModel::setBegin(const QDateTime & begin)
{
	if (m->begin != begin) {
		m->begin = begin;
		emit beginChanged();
	}
}

void EventModel::setEnd(const QDateTime & end)
{
	if (m->end != end) {
		m->end = end;
		emit endChanged();
	}
}

void EventModel::onSchemaChanged()
{
	m->dbCollective.setSchema(schema());
}

void EventModel::onSelected(internal::EventCollective::ColumnValues columnValues, QDateTime minTime, QDateTime maxTime)
{
	setBegin(minTime);
	setEnd(maxTime);

	internal::ModelMixin<EventModel>::onSelected(columnValues);
}

}
}

//(c)C: Copyright © 2020, Michał Policht <michal@policht.pl>. All rights reserved.
//(c)C: This file is a part of CuteHMI.
//(c)C: CuteHMI is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//(c)C: CuteHMI is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
//(c)C: You should have received a copy of the GNU Lesser General Public License along with CuteHMI.  If not, see <https://www.gnu.org/licenses/>.
