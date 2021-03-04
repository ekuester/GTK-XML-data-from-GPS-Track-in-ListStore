/* 
 * File: tablewindow.h
 * Author: Erich Küster, Krefeld/Germany
 *
 * created on October 11, 2018
 */

#ifndef GTKMM_TABLEWINDOW_H
#define GTKMM_TABLEWINDOW_H

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <glibmm/i18n.h>
#include <glibmm/ustring.h>
#include <gtkmm.h>
#include <iomanip>
#include <iostream>
#include <libxml++/libxml++.h>
#include <limits>
#include <locale>
#include <sstream>
#include <string>
#include "trackpoint.h"

class Trackpoint; // Say Trackpoint exists without defining it.

class XMLTableWindow : public Gtk::Window {
public:
    XMLTableWindow(const Glib::RefPtr<Gtk::Application>& app);
    XMLTableWindow(const XMLTableWindow& orig);
    virtual ~XMLTableWindow();

protected:
    std::string choose_xml_file();
    std::vector<Trackpoint*> parse_xml_file(std::string file);
    //Signal handlers for menu
    void on_menu_file_open();
    void on_menu_file_quit();
    void on_menu_help_about();
     //Signal handler for AboutDialog
    void on_about_dialog_response(int response_id);
    //Signal handlers
    void on_button_quit();

    //Seven model columns:
    class ModelColumns : public Gtk::TreeModel::ColumnRecord {
    public:

        ModelColumns() {
            add(m_col_id);
            add(m_lat_number);
            add(m_lon_number);
            add(m_ele_number);
            add(m_time_number);
            add(m_distance_number);
            add(m_speed_number);
        }

        Gtk::TreeModelColumn<guint> m_col_id;
        Gtk::TreeModelColumn<double> m_lat_number;
        Gtk::TreeModelColumn<double> m_lon_number;
        Gtk::TreeModelColumn<double> m_ele_number;
        Gtk::TreeModelColumn<std::time_t> m_time_number;
        Gtk::TreeModelColumn<double> m_distance_number;
        Gtk::TreeModelColumn<double> m_speed_number;
    };
    ModelColumns m_Columns;

    //Child widgets:
    Gtk::Box m_VBox;
    Gtk::ScrolledWindow m_ScrolledWindow;
    Gtk::TreeView m_TreeView;
    Glib::RefPtr<Gtk::ListStore> m_refTreeModel;
    Gtk::AboutDialog m_Dialog;

    Gtk::Toolbar t_Toolbar;
    Gtk::ToolButton t_ToolButtonOpen;
    Gtk::ToolButton t_ToolButtonQuit;
    Gtk::SeparatorToolItem t_ToolItemSpace;
    Gtk::ToolButton t_ToolButtonAbout;

    Gtk::Box m_HBox;
    Gtk::Label m_Label;
    Gtk::Entry m_Text;

    Gtk::ButtonBox m_ButtonBox;
    Gtk::Button m_Button_Quit;

    Gtk::Frame m_StatusFrame;
    unsigned m_ContextId;
    Gtk::Statusbar m_Statusbar;
};

#endif //GTKMM_TABLEWINDOW_H
