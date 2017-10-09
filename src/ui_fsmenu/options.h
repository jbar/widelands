/*
 * Copyright (C) 2002-2017 by the Widelands Development Team
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 */

#ifndef WL_UI_FSMENU_OPTIONS_H
#define WL_UI_FSMENU_OPTIONS_H

#include <cstring>
#include <memory>
#include <string>
#include <vector>

#include "ui_basic/box.h"
#include "ui_basic/button.h"
#include "ui_basic/checkbox.h"
#include "ui_basic/dropdown.h"
#include "ui_basic/multilinetextarea.h"
#include "ui_basic/spinbox.h"
#include "ui_basic/tabpanel.h"
#include "ui_basic/textarea.h"
#include "ui_fsmenu/base.h"

class FullscreenMenuOptions;
class Section;

class OptionsCtrl {
public:
	struct OptionsStruct {

		// Interface options
		int32_t xres;
		int32_t yres;
		bool fullscreen;
		bool inputgrab;
		uint32_t maxfps;

		// Windows options
		bool snap_win_overlap_only;
		bool dock_windows_to_edges;
		int32_t panel_snap_distance;
		int32_t border_snap_distance;
		bool animate_map_panning;

		// Sound options
		bool music;
		bool fx;
		bool message_sound;

		// Saving options
		int32_t autosave;          // autosave interval in minutes
		int32_t rolling_autosave;  // number of file to use for rolling autosave
		bool zip;
		bool write_syncstreams;

		// Game options
		bool auto_roadbuild_mode;
		bool show_warea;
		bool transparent_chat;
		bool single_watchwin;

		// Language options
		std::string language;

		// Last tab for reloading the options menu
		uint32_t active_tab;
	};

	explicit OptionsCtrl(Section&);
	void handle_menu();
	OptionsCtrl::OptionsStruct options_struct(uint32_t active_tab);
	void save_options();

private:
	Section& opt_section_;
	std::unique_ptr<FullscreenMenuOptions> opt_dialog_;
};

/**
 * Fullscreen Optionsmenu. A modal optionsmenu
 */

class FullscreenMenuOptions : public FullscreenMenuBase {
public:
	explicit FullscreenMenuOptions(OptionsCtrl::OptionsStruct opt);
	OptionsCtrl::OptionsStruct get_values();

private:
	void layout() override;

	// Fills the language selection list
	void add_languages_to_list(const std::string& current_locale);
	void update_language_stats(bool include_system_lang);

	// Saves the options and reloads the active tab
	void clicked_apply();

	const uint32_t padding_;
	uint32_t butw_;
	uint32_t buth_;
	uint32_t hmargin_;
	uint32_t tab_panel_y_;

	UI::Textarea title_;
	UI::Box button_box_;
	UI::Button cancel_, apply_, ok_;

	// UI elements
	UI::TabPanel tabs_;
	UI::Box box_interface_;
	UI::Box box_interface_left_;
	UI::Box box_windows_;
	UI::Box box_sound_;
	UI::Box box_saving_;
	UI::Box box_game_;

	// Interface options
	UI::Dropdown<std::string> language_dropdown_;
	UI::Dropdown<uintptr_t> resolution_dropdown_;
	UI::Checkbox fullscreen_;
	UI::Checkbox inputgrab_;
	UI::SpinBox sb_maxfps_;
	UI::MultilineTextarea translation_info_;

	// Windows options
	UI::Checkbox snap_win_overlap_only_;
	UI::Checkbox dock_windows_to_edges_;
	UI::Checkbox animate_map_panning_;
	UI::SpinBox sb_dis_panel_;
	UI::SpinBox sb_dis_border_;

	// Sound options
	UI::Checkbox music_;
	UI::Checkbox fx_;
	UI::Checkbox message_sound_;

	// Saving options
	UI::SpinBox sb_autosave_;
	UI::SpinBox sb_rolling_autosave_;
	UI::Checkbox zip_;
	UI::Checkbox write_syncstreams_;

	// Game options
	UI::Checkbox auto_roadbuild_mode_;
	UI::Checkbox show_workarea_preview_;
	UI::Checkbox transparent_chat_;
	UI::Checkbox single_watchwin_;

	OptionsCtrl::OptionsStruct os_;

	class ScreenResolution {
	public:
		int32_t xres;
		int32_t yres;
		int32_t depth;
	};

	/// All supported screen resolutions.
	std::vector<ScreenResolution> resolutions_;

	// Data model for the entries in the language selection list.
	struct LanguageEntry {
		LanguageEntry(const std::string& init_localename,
		              const std::string& init_descname,
		              const std::string& init_sortname)
		   : localename(init_localename), descname(init_descname), sortname(init_sortname) {
		}
		LanguageEntry() : LanguageEntry("", "", "") {
		}

		bool operator<(const LanguageEntry& other) const {
			return sortname < other.sortname;
		}

		std::string localename;  // ISO code for the locale
		std::string descname;    // Native language name
		std::string sortname;    // ASCII Language name used for sorting
	};
	std::map<std::string, LanguageEntry> language_entries_;
};

#endif  // end of include guard: WL_UI_FSMENU_OPTIONS_H
