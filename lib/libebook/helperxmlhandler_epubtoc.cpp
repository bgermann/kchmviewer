/*
 *  Kchmviewer - a CHM and EPUB file viewer with broad language support
 *  Copyright (C) 2004-2014 George Yunaev, gyunaev@ulduzsoft.com
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <QtDebug>
#include <QXmlStreamReader>
#include "helperxmlhandler_epubtoc.h"

HelperXmlHandler_EpubTOC::HelperXmlHandler_EpubTOC(EBook_EPUB *epub)
{
	m_epub = epub;
	m_inNavMap = false;
	m_inText = false;
	m_indent = 0;
}

bool HelperXmlHandler_EpubTOC::parse( const QByteArray& data )
{
	QXmlStreamReader xml( data );

	while ( !xml.atEnd() )
	{
		switch ( xml.readNext() )
		{
		case QXmlStreamReader::StartElement:
		{
			QString localName = xml.name().toString();

			if ( localName == "navMap" )
			{
				m_inNavMap = true;
			}
			else if ( m_inNavMap )
			{
				if ( localName == "navPoint" )
					m_indent++;
				else if ( localName == "text" )
					m_inText = true;
				else if ( localName == "content" )
				{
					QString src = xml.attributes().value( "src" ).toString();
					if ( src.isEmpty() )
						return false;
					m_lastId = src;
					checkNewTocEntry();
				}
			}
			break;
		}

		case QXmlStreamReader::Characters:
			if ( m_inText )
				m_lastTitle = xml.text().toString();
			checkNewTocEntry();
			break;

		case QXmlStreamReader::EndElement:
		{
			QString localName = xml.name().toString();
			if ( localName == "navMap" )
				m_inNavMap = false;
			else if ( localName == "navPoint" )
				m_indent--;
			else if ( localName == "text" )
				m_inText = false;
			break;
		}

		default:
			break;
		}
	}

	return !xml.hasError();
}

void HelperXmlHandler_EpubTOC::checkNewTocEntry()
{
	if ( !m_lastId.isEmpty() && !m_lastTitle.isEmpty() )
	{
		EBookTocEntry entry;
		entry.name = m_lastTitle;
		entry.url = m_epub->pathToUrl( m_lastId );
		entry.iconid = EBookTocEntry::IMAGE_AUTO;
		entry.indent = m_indent - 1;

		entries.push_back( entry );

		//qDebug() << "TOC entry: " << m_lastId << " :" << m_lastTitle << " :" << m_indent - 1;

		m_lastId.clear();
		m_lastTitle.clear();
	}
}
