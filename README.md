(This Readme was cobbled together from the [project's Sourceforge page](https://sourceforge.net/projects/rezilla/))

Rezilla is a resource editor for the Macintosh (OSX). It is designed to facilitate the edition and manipulation of resources stored in the data fork or in the resource fork of a file.

[Version 1.1 of Rezilla has just been released. It is a major upgrade which introduces many new features and bug fixes:](https://sourceforge.net/p/rezilla/news/2006/11/rezilla-11-released/)

New features

* new plugin architecture to support the addition of third party editors

* new image editor (implemented as a plugin) to display and manipulate image resources. It supports the following image formats: JPEG, TIFF, GIF, PNG, BMP.

* new 'icns' editor to manage icon suite resources. You can create, modify, redraw, delete, etc. any of the bitmaps included in an 'icns' resource suite. Possibility of importing from or exporting to a ".icns" image data file. Possibility of exploding or imploding the contents of an 'icns'.

* introduced resource pickers for displaying graphically and easily manipulating all the resources of a particular type. Pickers have been
defined for the following types: 'TEXT', 'MENU', 'STR#', 'MBAR', 'RID#', 'Mcmd', 'RidL', 'cicn', 'ICON', 'SICN', 'icns', 'PICT', 'PAT ', 'ppat', 'PAT#', 'ICN#', 'icl4', 'icl8', 'icm#', 'icm4', 'icm8', 'ics#', 'ics4', 'ics8', 'CURS', 'crsr'

* new Plugins command in the File menu to get info about the plugins and rearrange their order

* possibility of importing/exporting an entire resource map from/to XML

* new Import command in the File menu to import data in some resource editors

* XML export now correctly escapes the standard entities and writes in utf-8 encoding

* new WCOL and LCOL tags in the Template editor for RGB colors stored on 2 or 4 bytes respectively

* improved Unique ID algorithm: it now returns the first available value (above the current one) when calculating a unique ID rather than
a random number

* aliases are now followed for templates located in Application Support folders

* improved edition of resource ID tags (RSID) in the Template editor. A dynamic popup offers the currently available choices.

* added new templates for the Templates editor (there are now more than 400 templates)

* improved clipboard handling of hexadecimal data strings

* Tab key navigation through the fields of the Template editor's windows

* in the Template editor, the "+" key simulates a click on the Plus Button

* extended AppleScript terminology to support plugins and pickers

* more sample AppleScript scripts to demonstrate the new commands

* many interface improvements...

* many bug fixes...

Bug fixes

* fixed a bug when a resource type string has less than 4 chars

* fixed a bug with the Minus and Plus button messages when edting a fixed length list in the Template editor

* fixed a bug when ending a nested keyed section

* fixed an issue with Hxxx unfilled template fields

* fixed a crash when pasting on an already existing resource which is the only one of its type

* fixed a bug in the template editor when double-saving a resource containing a modified items list in some complicated circumstances

* fixed some keyboard shortcuts in the Template editor to prevent modifying the number of items in a fixed count list

* fixed an issue in the Recent Items menu with filenames containing metacharacters

* fixed an issue when retreiving the value of an LB31 tag in the Template editor

* fixed a bug where the Windows menu is not updated correctly after a click in the contents area of a plugin window

* correctly update the window title of Icon editor when switching from one family member to the other. Update the Windows menu accordingly.

* fixed issue with 8 bit masks inside icns resources: color map is now a table of gray shades

* fixed bug in copy/paste of partial selection in the icon editor canvas

* fix issue when double-clicking a resource file on non-writable media
