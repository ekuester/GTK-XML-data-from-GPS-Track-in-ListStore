# GTK-XML-data-from-GPS-Track-TreeView-with-ListStore

Read XML data from a GPX file und display the GPS trackpoints in a meaningful table.</br>
Calculates the total distance of the track by the Haversine formula for the great circle.</br>
(C++ / Linux / Gnome / GTK / gtkmm / XML data / GPS track)

This program is written in C++ with use of gtkmm wrapper for Gnome GTK environment of Linux. My development environment in the moment is Netbeans IDE 8.2 under Fedora 28 Cinnamon. An alternative compilation is easily possible, if you execute the added shell script in a terminal as command line:

$ sh ./GTKXMLTableView.sh

Since I switched from macOS to Fedora Linux (for what reasons ever) I had to change my programming language. For "simplicity" I choose C++ and to my pleasure found its "way to think" very similar to Swift and Objective-C. In some aspects I found C++ in combination with GTK easier compared to Swift ... Furthermore with the gtkmm wrapper you have an excellent tool for developing own programs.

I wrote this program to become familiar with the C++ language, especially the GTK-API under the gtkmm wrapper and to get a feeling how to display different widgets on the screen. For reading of XML files I use the libxml++ 3.0 library, which integrates itself trouble-free into the C++ environment via the pkgconfig method. Take the whole as example for handling treeviews on liststore base and reading of xml files under GTK+.

During trips by foot, bicycle or car I record the covered distance on my Apple iPhone or iPad with the excellent App <b>myTracks</b> by Dirk Stichling. Find more informations at <br/>
&nbsp; <https://www.mytracks4mac.info/index.php/en/> (english)</br>
&nbsp; <https://www.mytracks4mac.info/index.php/de/> (german)</br>
The obtained GPX files are extracted from the backup files made by iTunes under macOS or Windows and then transferred to my personal computer for dealing with further. To read in the file correctly into the program, you must do some changes:
 - delete the namespace prefix inside the data file and make a backup</br>
&nbsp; `$ sed -e 's/mytracks://g' -i.backup gpxtrack-0.gpx`
 - delete the attributes of the gpx node (complex regular expression code for sed)</br>
&nbsp; `$ sed -e ':a;N;$!ba;s|\(.*<gpx\).*\(<trk>.*\)|\1>\2|' -i gpxtrack-0.gpx`</br>
&nbsp; the prefix `:a;N;$!ba;` is for adding of eventually existing linefeeds to the pattern space
 
Usage: The program is mostly self explaining. On the toolbar at top of the window you will find buttons for opening a xml file, leaving the program and getting info about. After opening a xml file the contained track points are displayed in a table together with the calculated speed between two points. The total covered distance is shown at the bottom of the window. Erasing and/or inserting additional points should not be difficult to implant just as storing of the modified file.

Simplified example of a xml file with GPS track data:<br/>
```
<?xml version="1.0" encoding="UTF-8"?>
<gpx>
  <trk>
    <name>2012-11-14 09:57:20</name>
    <extensions>
      <area showArea="no" areaDistance="0.000000"/>
      <directionArrows showDirectionArrows="yes"/>
      <sync syncPhotosOniPhone="no"/>
      <timezone offset="60"/>
    </extensions>
    <trkseg>
      <trkpt lat="51.30887235519598" lon="6.595192467799964">
        <ele>29.93182373046875</ele>
        <time>2012-11-14T09:17:41Z</time>
        <extensions>
          <speed>15.88389816914975</speed>
          <length>0.008501878652107393</length>
        </extensions>
      </trkpt>
      <trkpt lat="51.30883484617929" lon="6.59517176449913">
        <ele>30.09716796875</ele>
        <time>2012-11-14T09:17:42Z</time>
        <extensions>
          <speed>15.86182185803758</speed>
          <length>0.00441219393587493</length>
        </extensions>
      </trkpt>
   </trkseg>
  </trk>
</gpx>
```

Disclaimer: Use the program for what purpose you like, but hold in mind, that I will not be responsible for any harm it will cause to your hard- or software. It was your decision to use this piece of software.

