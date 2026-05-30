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

#include <QXmlStreamReader>
#include "helperxmlhandler_epubcontent.h"

HelperXmlHandler_EpubContent::HelperXmlHandler_EpubContent()
{
	m_state = STATE_NONE;
}

bool HelperXmlHandler_EpubContent::parse( const QByteArray& data )
{
	QXmlStreamReader xml( data );
	m_state = STATE_NONE;
	m_tagname.clear();

	while ( !xml.atEnd() )
	{
		switch ( xml.readNext() )
		{
		case QXmlStreamReader::StartElement:
		{
			QString localName = xml.name().toString();

			if ( localName == "metadata" )
				m_state = STATE_IN_METADATA;
			else if ( localName == "manifest" )
				m_state = STATE_IN_MANIFEST;
			else if ( localName == "spine" )
				m_state = STATE_IN_SPINE;
			else if ( m_state == STATE_IN_METADATA )
				m_tagname = localName;
			else if ( m_state == STATE_IN_MANIFEST && localName == "item" )
			{
				QXmlStreamAttributes atts = xml.attributes();
				QString id    = atts.value( "id" ).toString();
				QString href  = atts.value( "href" ).toString();
				QString mtype = atts.value( "media-type" ).toString();

				if ( id.isEmpty() || href.isEmpty() || mtype.isEmpty() )
					return false;

				manifest[ id ] = href;

				if ( mtype == "application/x-dtbncx+xml" )
					tocname = href;
			}
			else if ( m_state == STATE_IN_SPINE && localName == "itemref" )
			{
				QString idref = xml.attributes().value( "idref" ).toString();
				if ( idref.isEmpty() )
					return false;
				spine.push_back( idref );
			}
			break;
		}

		case QXmlStreamReader::Characters:
		{
			if ( m_state == STATE_IN_METADATA && !m_tagname.isEmpty() )
			{
				QString text = xml.text().trimmed().toString();
				if ( !text.isEmpty() )
				{
					if ( metadata.contains( m_tagname ) )
					{
						metadata[ m_tagname ].append( "|" );
						metadata[ m_tagname ].append( text );
					}
					else
						metadata[ m_tagname ] = text;
				}
			}
			break;
		}

		case QXmlStreamReader::EndElement:
		{
			QString name = xml.name().toString();
			if ( name == "manifest" || name == "metadata" || name == "spine" )
				m_state = STATE_NONE;
			break;
		}

		default:
			break;
		}
	}

	return !xml.hasError();
}
