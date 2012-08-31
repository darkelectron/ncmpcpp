/***************************************************************************
 *   Copyright (C) 2008-2012 by Andrzej Rybczak                            *
 *   electricityispower@gmail.com                                          *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.              *
 ***************************************************************************/

#ifndef _TAG_EDITOR_H
#define _TAG_EDITOR_H

#include "config.h"

#ifdef HAVE_TAGLIB_H

#include <list>

// taglib headers
#include "xiphcomment.h"
#include "fileref.h"
#include "tag.h"

#include "mpdpp.h"
#include "mutable_song.h"
#include "regex_filter.h"
#include "screen.h"

class TagEditor : public Screen<Window>, public Filterable
{
	public:
		TagEditor() : FParser(0), FParserHelper(0), FParserLegend(0), FParserPreview(0), itsBrowsedDir("/") { }
		
		virtual void Resize();
		virtual void SwitchTo();
		
		virtual std::basic_string<my_char_t> Title();
		
		virtual void Refresh();
		virtual void Update();
		
		virtual void EnterPressed();
		virtual void SpacePressed();
		virtual void MouseButtonPressed(MEVENT);
		virtual bool isTabbable() { return true; }
		
		virtual MPD::Song *CurrentSong();
		virtual MPD::Song *GetSong(size_t pos) { return w == Tags ? &Tags->at(pos).value() : 0; }
		
		virtual bool allowsSelection() { return w == Tags; }
		virtual void ReverseSelection() { Tags->ReverseSelection(); }
		virtual void GetSelectedSongs(MPD::SongList &);
		
		virtual std::string currentFilter();
		virtual void applyFilter(const std::string &filter);
		
		virtual List *GetList();
		
		virtual bool isMergable() { return true; }
		
		bool isNextColumnAvailable();
		bool NextColumn();
		bool isPrevColumnAvailable();
		bool PrevColumn();
		
		void LocateSong(const MPD::Song &s);
		
		Menu<string_pair> *LeftColumn;
		Menu<string_pair> *Albums;
		Menu<string_pair> *Dirs;
		Menu<std::string> *TagTypes;
		Menu<MPD::MutableSong> *Tags;
		
		/// NOTICE: this string is always in utf8, no need to convert it
		const std::string &CurrentDir() { return itsBrowsedDir; }
		
		static void ReadTags(MPD::MutableSong &);
		static bool WriteTags(MPD::MutableSong &);
		
	protected:
		virtual void Init();
		virtual bool isLockable() { return true; }
		
	private:
		void SetDimensions(size_t, size_t);
		
		std::vector<MPD::MutableSong *> EditedSongs;
		Menu<std::string> *FParserDialog;
		Menu<std::string> *FParser;
		Scrollpad *FParserHelper;
		Scrollpad *FParserLegend;
		Scrollpad *FParserPreview;
		bool FParserUsePreview;
		
		static std::string CapitalizeFirstLetters(const std::string &);
		static void CapitalizeFirstLetters(MPD::MutableSong &);
		static void LowerAllLetters(MPD::MutableSong &);
		static void GetTagList(TagLib::StringList &, const MPD::MutableSong &, MPD::Song::GetFunction);
		static void WriteXiphComments(const MPD::MutableSong &, TagLib::Ogg::XiphComment *);
		
		static void GetPatternList();
		static void SavePatternList();
		static MPD::MutableSong::SetFunction IntoSetFunction(char);
		static std::string GenerateFilename(const MPD::MutableSong &, const std::string &);
		static std::string ParseFilename(MPD::MutableSong &, std::string, bool);
		
		static std::string TagToString(const MPD::MutableSong &);
		
		std::string itsBrowsedDir;
		std::string itsHighlightedDir;
		
		static std::string PatternsFile;
		static std::list<std::string> Patterns;
		
		static size_t MiddleColumnWidth;
		static size_t LeftColumnStartX;
		static size_t LeftColumnWidth;
		static size_t MiddleColumnStartX;
		static size_t RightColumnWidth;
		static size_t RightColumnStartX;
		
		static size_t FParserDialogWidth;
		static size_t FParserDialogHeight;
		static size_t FParserWidth;
		static size_t FParserWidthOne;
		static size_t FParserWidthTwo;
		static size_t FParserHeight;
};

extern TagEditor *myTagEditor;

#endif

#endif

