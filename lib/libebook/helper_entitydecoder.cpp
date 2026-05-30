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

#include "helper_entitydecoder.h"

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
#include <QStringDecoder>
#else
#include <QTextCodec>
#endif


HelperEntityDecoder::HelperEntityDecoder(const QString& encodingName)
{
	changeEncoding( encodingName );
}

void HelperEntityDecoder::changeEncoding(const QString& encodingName)
{
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
	QStringDecoder decoder = encodingName.isEmpty()
		? QStringDecoder(QStringConverter::Latin1)
		: QStringDecoder(encodingName.toLatin1().constData());
	auto encodeWith = [&](const char* s) -> QString {
		return decoder.isValid() ? decoder(QByteArray(s)) : QString::fromLatin1(s);
	};
#else
	QTextCodec* encoder = encodingName.isEmpty()
		? nullptr
		: QTextCodec::codecForName(encodingName.toUtf8());
	auto encodeWith = [encoder](const char* s) -> QString {
		return encoder ? encoder->toUnicode(s) : QString::fromLatin1(s);
	};
#endif

	// Set up m_entityDecodeMap characters according to current textCodec
	m_entityDecodeMap.clear();

	m_entityDecodeMap["AElig"]	= encodeWith("\306"); // capital AE diphthong (ligature)
	m_entityDecodeMap["Aacute"]	= encodeWith("\301"); // capital A, acute accent
	m_entityDecodeMap["Acirc"]	= encodeWith("\302"); // capital A, circumflex accent
	m_entityDecodeMap["Agrave"]	= encodeWith("\300"); // capital A, grave accent
	m_entityDecodeMap["Aring"]	= encodeWith("\305"); // capital A, ring
	m_entityDecodeMap["Atilde"]	= encodeWith("\303"); // capital A, tilde
	m_entityDecodeMap["Auml"]	= encodeWith("\304"); // capital A, dieresis or umlaut mark
	m_entityDecodeMap["Ccedil"]	= encodeWith("\307"); // capital C, cedilla
	m_entityDecodeMap["Dstrok"]	= encodeWith("\320"); // whatever
	m_entityDecodeMap["ETH"]	= encodeWith("\320"); // capital Eth, Icelandic
	m_entityDecodeMap["Eacute"]	= encodeWith("\311"); // capital E, acute accent
	m_entityDecodeMap["Ecirc"]	= encodeWith("\312"); // capital E, circumflex accent
	m_entityDecodeMap["Egrave"]	= encodeWith("\310"); // capital E, grave accent
	m_entityDecodeMap["Euml"]	= encodeWith("\313"); // capital E, dieresis or umlaut mark
	m_entityDecodeMap["Iacute"]	= encodeWith("\315"); // capital I, acute accent
	m_entityDecodeMap["Icirc"]	= encodeWith("\316"); // capital I, circumflex accent
	m_entityDecodeMap["Igrave"]	= encodeWith("\314"); // capital I, grave accent
	m_entityDecodeMap["Iuml"]	= encodeWith("\317"); // capital I, dieresis or umlaut mark
	m_entityDecodeMap["Ntilde"]	= encodeWith("\321"); // capital N, tilde
	m_entityDecodeMap["Oacute"]	= encodeWith("\323"); // capital O, acute accent
	m_entityDecodeMap["Ocirc"]	= encodeWith("\324"); // capital O, circumflex accent
	m_entityDecodeMap["Ograve"]	= encodeWith("\322"); // capital O, grave accent
	m_entityDecodeMap["Oslash"]	= encodeWith("\330"); // capital O, slash
	m_entityDecodeMap["Otilde"]	= encodeWith("\325"); // capital O, tilde
	m_entityDecodeMap["Ouml"]	= encodeWith("\326"); // capital O, dieresis or umlaut mark
	m_entityDecodeMap["THORN"]	= encodeWith("\336"); // capital THORN, Icelandic
	m_entityDecodeMap["Uacute"]	= encodeWith("\332"); // capital U, acute accent
	m_entityDecodeMap["Ucirc"]	= encodeWith("\333"); // capital U, circumflex accent
	m_entityDecodeMap["Ugrave"]	= encodeWith("\331"); // capital U, grave accent
	m_entityDecodeMap["Uuml"]	= encodeWith("\334"); // capital U, dieresis or umlaut mark
	m_entityDecodeMap["Yacute"]	= encodeWith("\335"); // capital Y, acute accent
	m_entityDecodeMap["OElig"]	= encodeWith("\338"); // capital Y, acute accent
	m_entityDecodeMap["oelig"]	= encodeWith("\339"); // capital Y, acute accent

	m_entityDecodeMap["aacute"]	= encodeWith("\341"); // small a, acute accent
	m_entityDecodeMap["acirc"]	= encodeWith("\342"); // small a, circumflex accent
	m_entityDecodeMap["aelig"]	= encodeWith("\346"); // small ae diphthong (ligature)
	m_entityDecodeMap["agrave"]	= encodeWith("\340"); // small a, grave accent
	m_entityDecodeMap["aring"]	= encodeWith("\345"); // small a, ring
	m_entityDecodeMap["atilde"]	= encodeWith("\343"); // small a, tilde
	m_entityDecodeMap["auml"]	= encodeWith("\344"); // small a, dieresis or umlaut mark
	m_entityDecodeMap["ccedil"]	= encodeWith("\347"); // small c, cedilla
	m_entityDecodeMap["eacute"]	= encodeWith("\351"); // small e, acute accent
	m_entityDecodeMap["ecirc"]	= encodeWith("\352"); // small e, circumflex accent
	m_entityDecodeMap["Scaron"]	= encodeWith("\352"); // small e, circumflex accent
	m_entityDecodeMap["egrave"]	= encodeWith("\350"); // small e, grave accent
	m_entityDecodeMap["eth"]	= encodeWith("\360"); // small eth, Icelandic
	m_entityDecodeMap["euml"]	= encodeWith("\353"); // small e, dieresis or umlaut mark
	m_entityDecodeMap["iacute"]	= encodeWith("\355"); // small i, acute accent
	m_entityDecodeMap["icirc"]	= encodeWith("\356"); // small i, circumflex accent
	m_entityDecodeMap["igrave"]	= encodeWith("\354"); // small i, grave accent
	m_entityDecodeMap["iuml"]	= encodeWith("\357"); // small i, dieresis or umlaut mark
	m_entityDecodeMap["ntilde"]	= encodeWith("\361"); // small n, tilde
	m_entityDecodeMap["oacute"]	= encodeWith("\363"); // small o, acute accent
	m_entityDecodeMap["ocirc"]	= encodeWith("\364"); // small o, circumflex accent
	m_entityDecodeMap["ograve"]	= encodeWith("\362"); // small o, grave accent
	m_entityDecodeMap["oslash"]	= encodeWith("\370"); // small o, slash
	m_entityDecodeMap["otilde"]	= encodeWith("\365"); // small o, tilde
	m_entityDecodeMap["ouml"]	= encodeWith("\366"); // small o, dieresis or umlaut mark
	m_entityDecodeMap["szlig"]	= encodeWith("\337"); // small sharp s, German (sz ligature)
	m_entityDecodeMap["thorn"]	= encodeWith("\376"); // small thorn, Icelandic
	m_entityDecodeMap["uacute"]	= encodeWith("\372"); // small u, acute accent
	m_entityDecodeMap["ucirc"]	= encodeWith("\373"); // small u, circumflex accent
	m_entityDecodeMap["ugrave"]	= encodeWith("\371"); // small u, grave accent
	m_entityDecodeMap["uuml"]	= encodeWith("\374"); // small u, dieresis or umlaut mark
	m_entityDecodeMap["yacute"]	= encodeWith("\375"); // small y, acute accent
	m_entityDecodeMap["yuml"]	= encodeWith("\377"); // small y, dieresis or umlaut mark

	m_entityDecodeMap["iexcl"]	= encodeWith("\241");
	m_entityDecodeMap["cent"]	= encodeWith("\242");
	m_entityDecodeMap["pound"]	= encodeWith("\243");
	m_entityDecodeMap["curren"]	= encodeWith("\244");
	m_entityDecodeMap["yen"]	= encodeWith("\245");
	m_entityDecodeMap["brvbar"]	= encodeWith("\246");
	m_entityDecodeMap["sect"]	= encodeWith("\247");
	m_entityDecodeMap["uml"]	= encodeWith("\250");
	m_entityDecodeMap["ordf"]	= encodeWith("\252");
	m_entityDecodeMap["laquo"]	= encodeWith("\253");
	m_entityDecodeMap["not"]	= encodeWith("\254");
	m_entityDecodeMap["shy"]	= encodeWith("\255");
	m_entityDecodeMap["macr"]	= encodeWith("\257");
	m_entityDecodeMap["deg"]	= encodeWith("\260");
	m_entityDecodeMap["plusmn"]	= encodeWith("\261");
	m_entityDecodeMap["sup1"]	= encodeWith("\271");
	m_entityDecodeMap["sup2"]	= encodeWith("\262");
	m_entityDecodeMap["sup3"]	= encodeWith("\263");
	m_entityDecodeMap["acute"]	= encodeWith("\264");
	m_entityDecodeMap["micro"]	= encodeWith("\265");
	m_entityDecodeMap["para"]	= encodeWith("\266");
	m_entityDecodeMap["middot"]	= encodeWith("\267");
	m_entityDecodeMap["cedil"]	= encodeWith("\270");
	m_entityDecodeMap["ordm"]	= encodeWith("\272");
	m_entityDecodeMap["raquo"]	= encodeWith("\273");
	m_entityDecodeMap["frac14"]	= encodeWith("\274");
	m_entityDecodeMap["frac12"]	= encodeWith("\275");
	m_entityDecodeMap["frac34"]	= encodeWith("\276");
	m_entityDecodeMap["iquest"]	= encodeWith("\277");
	m_entityDecodeMap["times"]	= encodeWith("\327");
	m_entityDecodeMap["divide"]	= encodeWith("\367");

	m_entityDecodeMap["copy"]	= encodeWith("\251"); // copyright sign
	m_entityDecodeMap["reg"]	= encodeWith("\256"); // registered sign
	m_entityDecodeMap["nbsp"]	= encodeWith("\240"); // non breaking space

	m_entityDecodeMap["fnof"]	= QChar((unsigned short) 402);

	m_entityDecodeMap["Delta"]	= QChar((unsigned short) 916);
	m_entityDecodeMap["Pi"]	= QChar((unsigned short) 928);
	m_entityDecodeMap["Sigma"]	= QChar((unsigned short) 931);

	m_entityDecodeMap["beta"]	= QChar((unsigned short) 946);
	m_entityDecodeMap["gamma"]	= QChar((unsigned short) 947);
	m_entityDecodeMap["delta"]	= QChar((unsigned short) 948);
	m_entityDecodeMap["eta"]	= QChar((unsigned short) 951);
	m_entityDecodeMap["theta"]	= QChar((unsigned short) 952);
	m_entityDecodeMap["lambda"]	= QChar((unsigned short) 955);
	m_entityDecodeMap["mu"]	= QChar((unsigned short) 956);
	m_entityDecodeMap["nu"]	= QChar((unsigned short) 957);
	m_entityDecodeMap["pi"]	= QChar((unsigned short) 960);
	m_entityDecodeMap["rho"]	= QChar((unsigned short) 961);

	m_entityDecodeMap["lsquo"]	= QChar((unsigned short) 8216);
	m_entityDecodeMap["rsquo"]	= QChar((unsigned short) 8217);
	m_entityDecodeMap["rdquo"]	= QChar((unsigned short) 8221);
	m_entityDecodeMap["bdquo"]	= QChar((unsigned short) 8222);
	m_entityDecodeMap["trade"]  = QChar((unsigned short) 8482);
	m_entityDecodeMap["ldquo"]  = QChar((unsigned short) 8220);
	m_entityDecodeMap["ndash"]  = QChar((unsigned short) 8211);
	m_entityDecodeMap["mdash"]  = QChar((unsigned short) 8212);
	m_entityDecodeMap["bull"]  = QChar((unsigned short) 8226);
	m_entityDecodeMap["hellip"]  = QChar((unsigned short) 8230);
	m_entityDecodeMap["emsp"]  = QChar((unsigned short) 8195);
	m_entityDecodeMap["rarr"]  = QChar((unsigned short) 8594);
	m_entityDecodeMap["rArr"]  = QChar((unsigned short) 8658);
	m_entityDecodeMap["crarr"]  = QChar((unsigned short) 8629);
	m_entityDecodeMap["le"]  = QChar((unsigned short) 8804);
	m_entityDecodeMap["ge"]  = QChar((unsigned short) 8805);
	m_entityDecodeMap["lte"]  = QChar((unsigned short) 8804); // wrong, but used somewhere
	m_entityDecodeMap["gte"]  = QChar((unsigned short) 8805); // wrong, but used somewhere
	m_entityDecodeMap["dagger"]  = QChar((unsigned short) 8224);
	m_entityDecodeMap["Dagger"]  = QChar((unsigned short) 8225);
	m_entityDecodeMap["euro"]  = QChar((unsigned short) 8364);
	m_entityDecodeMap["asymp"]  = QChar((unsigned short) 8776);
	m_entityDecodeMap["isin"]  = QChar((unsigned short) 8712);
	m_entityDecodeMap["notin"]  = QChar((unsigned short) 8713);
	m_entityDecodeMap["prod"]  = QChar((unsigned short) 8719);
	m_entityDecodeMap["ne"]  = QChar((unsigned short) 8800);

	m_entityDecodeMap["amp"]	= "&";	// ampersand
	m_entityDecodeMap["gt"] = ">";	// greater than
	m_entityDecodeMap["lt"] = "<"; 	// less than
	m_entityDecodeMap["quot"] = "\""; // double quote
	m_entityDecodeMap["apos"] = "'"; 	// single quote
	m_entityDecodeMap["frasl"]  = "/";
	m_entityDecodeMap["minus"]  = "-";
	m_entityDecodeMap["oplus"] = "+";
	m_entityDecodeMap["Prime"] = "\"";
}


QString HelperEntityDecoder::decode( const QString &entity ) const
{
	// If entity is an ASCII code like &#12349; - just decode it
	if ( entity.isEmpty() )
	{
		return "";
	}
	else if ( entity[0] == '#' )
	{
		bool valid;
		unsigned int ascode = entity.mid(1).toUInt( &valid );

		if ( !valid )
		{
			qWarning ( "HelperEntityDecoder::decode: could not decode HTML entity '%s'", qPrintable( entity ) );
			return QString();
		}

		return (QString) (QChar( ascode ));
	}
	else
	{
		QMap<QString, QString>::const_iterator it = m_entityDecodeMap.find( entity );

		if ( it == m_entityDecodeMap.end() )
		{
			qWarning ("HelperEntityDecoder::decode: could not decode HTML entity '%s'", qPrintable( entity ));
			return "";
		}

		return *it;
	}
}
