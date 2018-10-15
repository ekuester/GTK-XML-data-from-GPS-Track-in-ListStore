/* 
 * File: tablewindow.cpp
 * Author: Erich Küster, Krefeld/Germany
 *
 * created on October 11, 2018
 */

#include "xmltablewindow.h"
#include "about.xpm"

using namespace std;
using namespace xmlpp;

const Glib::ustring app_title = "Gtk+: XML Application - XML TableView from GPX-Tracker";

XMLTableWindow::XMLTableWindow(const Glib::RefPtr<Gtk::Application>& app)
: m_VBox(Gtk::ORIENTATION_VERTICAL),
  t_Toolbar(),
  t_ToolButtonOpen(Gtk::Stock::OPEN),
  t_ToolButtonQuit(Gtk::Stock::QUIT),
  t_ToolItemSpace(),
  t_ToolButtonAbout(Gtk::Stock::ABOUT),
  m_HBox(Gtk::ORIENTATION_HORIZONTAL),
  m_Label(),
  m_Text(),
  m_Button_Quit("Quit"),
  m_StatusFrame(),
  m_Statusbar(),
  m_Dialog() {
    m_ContextId = m_Statusbar.get_context_id(app_title);
    set_title(app_title);
    set_border_width(5);
    set_default_size(640, 640);
    add(m_VBox);

    t_Toolbar.set_toolbar_style(Gtk::TOOLBAR_ICONS);
    t_ToolButtonOpen.set_tooltip_text("XML Datei öffnen");
    t_ToolButtonOpen.signal_clicked().connect(sigc::mem_fun(*this,
        &XMLTableWindow::on_menu_file_open));
    t_ToolButtonQuit.set_tooltip_text("Verlassen");
    t_ToolButtonQuit.signal_clicked().connect(sigc::mem_fun(*this,
        &XMLTableWindow::on_menu_file_quit));
    t_ToolButtonAbout.set_tooltip_text("Über das Programm");
    t_ToolButtonAbout.signal_clicked().connect(sigc::mem_fun(*this,
        &XMLTableWindow::on_menu_help_about));
    t_Toolbar.append(t_ToolButtonOpen);
    t_Toolbar.append(t_ToolButtonQuit);
    t_Toolbar.append(t_ToolItemSpace);
    t_Toolbar.append(t_ToolButtonAbout);
    m_VBox.pack_start(t_Toolbar, Gtk::PACK_SHRINK);

    //Add the TreeView, inside a ScrolledWindow, with the button underneath:
    m_ScrolledWindow.add(m_TreeView);

    //Only show the scrollbars when they are necessary:
    m_ScrolledWindow.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);

    m_Label.set_markup("<b>Total distance:</b>");
    m_Label.set_vexpand(false);
    m_Label.set_hexpand(false);
    m_Label.set_halign(Gtk::ALIGN_START);
    m_Text.set_vexpand(false);
    m_Text.set_hexpand(false);
    m_Text.set_halign(Gtk::ALIGN_END);
    //m_Text.set_width_chars(11);
    m_VBox.pack_start(m_ScrolledWindow);
    m_VBox.pack_start(m_HBox, Gtk::PACK_SHRINK);
    // Label, followed by TextEntry from the left of horizontal row
    m_HBox.pack_start(m_Label, Gtk::PACK_SHRINK, 16);
    m_HBox.pack_start(m_Text, Gtk::PACK_SHRINK);
    // ButtonBox to the end of horizontal row
    m_HBox.pack_end(m_ButtonBox, Gtk::PACK_SHRINK);
    m_HBox.set_border_width(8);

    m_ButtonBox.pack_start(m_Button_Quit, Gtk::PACK_SHRINK);
    m_ButtonBox.set_border_width(2);
    m_ButtonBox.set_layout(Gtk::BUTTONBOX_END);
    m_Button_Quit.signal_clicked().connect(sigc::mem_fun(*this,
            &XMLTableWindow::on_button_quit));

    //Create the Tree model:
    m_refTreeModel = Gtk::ListStore::create(m_Columns);
    m_TreeView.set_model(m_refTreeModel);

    //Add the TreeView's view columns:
    //This number will be shown with the default numeric formatting.
    m_TreeView.append_column("ID", m_Columns.m_col_id);
    // 13 digits plus decimal point
    m_TreeView.append_column_numeric("latitude", m_Columns.m_lat_number, "%10.4f");
    m_TreeView.append_column_numeric("longitude", m_Columns.m_lon_number, "%10.4f");
    // 11 digits plus decimal point
    m_TreeView.append_column_numeric("elevation", m_Columns.m_ele_number, "%9.3f");
    m_TreeView.append_column_numeric("time [sec]", m_Columns.m_time_number, "%d");
    m_TreeView.append_column_numeric("distance", m_Columns.m_distance_number, "%9.3f");
    m_TreeView.append_column_numeric("speed [km/h]", m_Columns.m_speed_number, "%9.3f");
/*
    //Display a progress bar instead of a decimal number:
    auto cell = Gtk::manage(new Gtk::CellRendererProgress);
    int cols_count = m_TreeView.append_column("Some percentage", *cell);
    auto pColumn = m_TreeView.get_column(cols_count - 1);
    if(pColumn)
    {
        pColumn->add_attribute(cell->property_value(), m_Columns.m_col_percentage);
    }
*/
    //Make all the columns reorderable and resizable:
    //This is not necessary, but it's nice to show the feature.
    //You can use TreeView::set_column_drag_function() to more
    //finely control column drag and drop.
    for (guint i = 0; i < 7; i++) {
        auto column = m_TreeView.get_column(i);
        column->set_reorderable();
        column->set_resizable(true);
    }

    m_StatusFrame.add(m_Statusbar);
    m_VBox.pack_start(m_StatusFrame, Gtk::PACK_SHRINK);
    m_ContextId = m_Statusbar.push("Bereit", m_ContextId);

    m_Dialog.set_transient_for(*this);
    m_Dialog.set_logo(Gdk::Pixbuf::create_from_xpm_data(about));
    m_Dialog.set_program_name(app_title);
    m_Dialog.set_version("Version 1.2.5");
    m_Dialog.set_copyright("Copyright © 2018 Erich Küster. All rights reserved.");
    m_Dialog.set_comments("Gtk+: XML Application - Read XML data from GPX-Track into TableView");
    std::ifstream licenseFile("LICENSE");
    std::stringstream licenseStream;
    licenseStream << licenseFile.rdbuf();
    m_Dialog.set_license(licenseStream.str());
    std::ifstream commentsFile("COMMENTS");
    std::stringstream commentsStream;
    commentsStream << commentsFile.rdbuf();
    m_Dialog.set_comments(commentsStream.str());

    m_Dialog.set_website("http://www.gtkmm.org");
    m_Dialog.set_website_label("gtkmm Website - C++ Interfaces for GTK+ and GNOME");

    std::vector<Glib::ustring> list_authors;
    list_authors.push_back("Erich Küster, Krefeld/Germany");
    m_Dialog.set_authors(list_authors);

    m_Dialog.signal_response().connect(
        sigc::mem_fun(*this, &XMLTableWindow::on_about_dialog_response));

    show_all_children();
//    }
}

XMLTableWindow::~XMLTableWindow() {
}

string XMLTableWindow::choose_xml_file() {
    // File Open Dialog
    Gtk::FileChooserDialog dialog("Please choose a file",
            Gtk::FileChooserAction::FILE_CHOOSER_ACTION_OPEN);
    dialog.set_transient_for(*this);

    //Add response buttons the the dialog:
    dialog.add_button("_Cancel", Gtk::ResponseType::RESPONSE_CANCEL);
    dialog.add_button("_Open", Gtk::ResponseType::RESPONSE_OK);

    //Add filters, so that only certain file types can be selected:
/*
    auto filter_text = Gtk::FileFilter::create();
    filter_text->set_name("Text files");
    filter_text->add_mime_type("text/plain");
    dialog.add_filter(filter_text);
*/
    auto filter_xml = Gtk::FileFilter::create();
    filter_xml->set_name("XML files");
    filter_xml->add_mime_type("text/gpx");
    filter_xml->add_mime_type("text/xml");
    dialog.add_filter(filter_xml);

    auto filter_any = Gtk::FileFilter::create();
    filter_any->set_name("Any files");
    filter_any->add_pattern("*");
    dialog.add_filter(filter_any);

    //Show the dialog and wait for a user response:
    int result = dialog.run();

    //Handle the response:
    switch (result) {
        case Gtk::ResponseType::RESPONSE_OK:
        {
            //Notice that this is a std::string, not a Glib::ustring
            return dialog.get_filename();
        }
        case Gtk::ResponseType::RESPONSE_CANCEL:
        {
            m_ContextId = m_Statusbar.push("Keine Datei ausgewählt...", m_ContextId);
            break;
        }
        default:
        {
            m_ContextId = m_Statusbar.push("Antwort bei Dateiauswahl so nicht erwartet,,,", m_ContextId);
            break;
        }
    }
    return string();
}

void XMLTableWindow::on_menu_file_open() {
    string filename = choose_xml_file();
    if (!filename.empty()) {
        if (m_refTreeModel->children().size() > 0) {
            // liststore was in use before
            m_refTreeModel->clear();
        }
        double totalDistance = 0.0;
        vector<Trackpoint*> trackpointItems = parse_xml_file(filename);
        stringstream itemStream;
        itemStream << trackpointItems.size() << " Spurpunkte";
        m_ContextId = m_Statusbar.push(itemStream.str(), m_ContextId);
        // iterate over all trackpoint objects
        for (vector<Trackpoint*>::iterator tp = trackpointItems.begin(); tp != trackpointItems.end(); ++tp) {
            // fill the TreeView's model
            Gtk::TreeModel::Row row = *(m_refTreeModel->append());
            row[m_Columns.m_col_id] = (*tp)->point;
      
            row[m_Columns.m_lat_number] = (*tp)->latitude;
            row[m_Columns.m_lon_number] = (*tp)->longitude;
            row[m_Columns.m_ele_number] = (*tp)->elevation;
            row[m_Columns.m_time_number] = (*tp)->time;
            row[m_Columns.m_distance_number] = (*tp)->distance;
            totalDistance += (*tp)->distance;
            row[m_Columns.m_speed_number] = (*tp)->speed;
        }
        std::stringstream totalStream;
        // change to german locale to obtain decimal comma
        totalStream.imbue(std::locale("de_DE"));
        totalStream << std::fixed << std::setprecision(4) << std::setw(16)
            << totalDistance << " km";
        m_Text.set_text(totalStream.str());
    }
}

void XMLTableWindow::on_menu_file_quit() {
    hide();
}

void XMLTableWindow::on_menu_help_about() {
    m_Dialog.show();
    //bring it to the front, in case it was already shown:
    m_Dialog.present();    
}

void XMLTableWindow::on_about_dialog_response(int response_id) {
    switch (response_id) {
        case Gtk::RESPONSE_CLOSE:
        case Gtk::RESPONSE_CANCEL:
        case Gtk::RESPONSE_DELETE_EVENT:
            m_Dialog.hide();
            break;
        default:
            m_ContextId = m_Statusbar.push("Antwort so nicht erwartet...", m_ContextId);
            break;
    }
}

void XMLTableWindow::on_button_quit() {
    hide();
}

vector<Trackpoint*> XMLTableWindow::parse_xml_file(std::string file) {
    guint points = 1;
    double totalDistance = 0.0;
    double trackDistance = 0.0;
    // intialize track point array
    vector<Trackpoint*> trackpointItems;
    // Parse the file
    DomParser parser;
    parser.parse_file(file);
    Document* document = parser.get_document();
    Element* root_node = document->get_root_node();
    // Xpath query: find special elements
    Element::NodeSet nodes(root_node->find("/gpx/trk/trkseg/trkpt"));
    // read recorded track points
    for (Element::NodeSet::iterator i = nodes.begin(); i != nodes.end(); ++i) {
        Trackpoint* trackpoint = new Trackpoint();
        Element* element = dynamic_cast<Element*> (*i);
        Element::AttributeList attributes = element->get_attributes();
        for (Element::AttributeList::iterator a = attributes.begin(); a != attributes.end(); ++a) {
            Attribute* attribute = dynamic_cast<Attribute*> (*a);
            if (attribute->get_name() == "lat") {
                stringstream(attribute->get_value()) >> trackpoint->latitude;
            }
            if (attribute->get_name() == "lon") {
                stringstream(attribute->get_value()) >> trackpoint->longitude;
            }
//            cout << "attribute: " << attribute->get_name() << " = " << attribute->get_value() << endl;
        }
        trackpoint->point = points;
        // obtain text content from childs by iteration
        Node* child = element->get_first_child();
        while (child) {
            // test for TextNode
            const auto text = dynamic_cast<const TextNode*> (child);
            // better ignoring the indenting
            bool content_exists = !(text && text->is_white_space());
            if (content_exists) {
                Element* elem = dynamic_cast<Element*> (child);
                if (elem->has_child_text()) {
                    if (elem->get_name() == "ele") {
                        stringstream(elem->get_first_child_text()->get_content()) >> trackpoint->elevation;
                    }
                    if (elem->get_name() == "time") {
                        stringstream dateTime(elem->get_first_child_text()->get_content());
                        tm tm = {};
                        dateTime >> std::get_time(&tm, "%Y-%m-%dT%H:%M:%SZ");
                        trackpoint->time = mktime(&tm);
                        trackpoint->timeReading = elem->get_first_child_text()->get_content();
                    }
                }
            }
            // you must know in advance which childs to extract
            if (child->get_name() == "extensions") {
                Node* ch = child->get_first_child();
                while (ch) {
                    if (ch->get_name() == "speed") {
                        Element* el = dynamic_cast<Element*> (ch);
//                      cout << "speed: " << el->get_first_child_text()->get_content() << endl;
                    }
                    if (ch->get_name() == "length") {
                        Element* el = dynamic_cast<Element*> (ch);
                        double dist = 0.0;
                        stringstream(el->get_first_child_text()->get_content()) >> dist;
                        trackDistance += dist;
//                      cout << "length: " << el->get_first_child_text()->get_content() << endl;
                    }
                    ch = ch->get_next_sibling();
                }
            }
            child = child->get_next_sibling();
        }
        if (points > 1) {
            // get last object
            Trackpoint* previous = trackpointItems.back();
            trackpoint->distanceByHaversine(previous);
            totalDistance += trackpoint->distance;
            double elapsedTime = difftime(trackpoint->time, previous->time);
            double coveredDistance = trackpoint->distance;
            trackpoint->speed = trackpoint->distance / elapsedTime * 3600.0;
        }
        trackpointItems.push_back(trackpoint);
        points += 1;
    }
    cout << "total distance: " << totalDistance << endl;
    cout << "mytracks distance: " << trackDistance << endl;
    return trackpointItems;
}
