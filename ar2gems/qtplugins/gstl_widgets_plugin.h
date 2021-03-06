/* -----------------------------------------------------------------------------
** Copyright (c) 2012 Advanced Resources and Risk Technology, LLC
** All rights reserved.
**
** This file is part of Advanced Resources and Risk Technology, LLC (AR2TECH) 
** version of the open source software sgems.  It is a derivative work by 
** AR2TECH (THE LICENSOR) based on the x-free license granted in the original 
** version of the software (see notice below) and now sublicensed such that it 
** cannot be distributed or modified without the explicit and written permission 
** of AR2TECH.
**
** Only AR2TECH can modify, alter or revoke the licensing terms for this 
** file/software.
**
** This file cannot be modified or distributed without the explicit and written 
** consent of AR2TECH.
**
** Contact Dr. Alex Boucher (aboucher@ar2tech.com) for any questions regarding
** the licensing of this file/software
**
** The open-source version of sgems can be downloaded at 
** sourceforge.net/projects/sgems.
** ----------------------------------------------------------------------------*/



/**********************************************************************
** Author: Nicolas Remy
** Copyright (C) 2002-2004 The Board of Trustees of the Leland Stanford Junior
**   University
** All rights reserved.
**
** This file is part of the "extra" module of the Geostatistical Earth
** Modeling Software (GEMS)
**
** This file may be distributed and/or modified under the terms of the 
** license defined by the Stanford Center for Reservoir Forecasting and 
** appearing in the file LICENSE.XFREE included in the packaging of this file.
**
** This file may be distributed and/or modified under the terms of the
** GNU General Public License version 2 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
** See http://www.gnu.org/copyleft/gpl.html for GPL licensing information.
**
** Contact the Stanford Center for Reservoir Forecasting, Stanford University
** if any conditions of this licensing are not clear to you.
**
Modified A. Boucher
**********************************************************************/

#ifndef __GSTLAPPLI_EXTRA_GSTL_WIDGETS_PLUGIN_H__
#define __GSTLAPPLI_EXTRA_GSTL_WIDGETS_PLUGIN_H__

#include <qtplugins/common.h>
#include <QtDesigner/QDesignerContainerExtension>
#include <QtDesigner/QDesignerCustomWidgetInterface>
#include <QtCore/qplugin.h>
#include <QtGui/QIcon>
#include <qtplugins/selectors.h>
#include <qtplugins/filechooser.h>
#include <qtplugins/variogram_input.h>
#include <qtplugins/kriging_type_selector.h>
#include <qtplugins/gstl_table.h>
#include <qtplugins/ellipsoid_input.h>
#include <qtplugins/non_param_cdf_input.h>
#include <qtplugins/neighborhood_filter_input.h>
#include <qtplugins/categorical_selectors.h>
#include <qtplugins/weight_property_selector.h>
#include <qtplugins/group_selectors.h>
#include <QDesignerCustomWidgetCollectionInterface>
//Added by qt3to4:
#include <QPixmap>

class QDesignerFormEditorInterface;


static const char* variogram_pixmap[] = {
"32 32 3 1",
". c None",
"a c #c00000",
"# c #ff0000",
"................................",
"................................",
"................................",
"........................#.......",
".....................####.......",
".##................#####........",
".####.............#####.........",
"..#####..........####...........",
"....####........####............",
".....####......###..............",
"......####....###...............",
".......####..###................",
".........######......a.......a..",
".........#####......aa.......aa.",
".........####.......a.........a.",
"........######.....aa..aa.....a.",
".......###..###....a...aa.....aa",
"......###....###...a...aa......a",
".....###.....###...a...aa......a",
".....###......###.aa...aa......a",
".....##.......###.a....aaaaaa..a",
"....###.......###.a....aaaaaa..a",
"....###.......###.a....aa..aa..a",
"....###......###..a....aa..aa..a",
"....###.....####...a...aa..aa..a",
"....###.....###....aa..aa..aa.aa",
".....#########......a.........a.",
".....#######........aa.......aa.",
"......#####..........aa......a..",
"......................a......a..",
"................................",
"................................"};

static const char *GridSelector_pixmap[] = {
    "22 22 8 1",
    "  c Gray100",
    ". c Gray97",
    "X c #4f504f",
    "o c #00007f",
    "O c Gray0",
    "+ c none",
    "@ c Gray0",
    "# c Gray0",
    "++++++++++++++++++++++",
    "++++++++++++++++++++++",
    "++++++++++++++++++++++",
    "++++++++++++++++++++++",
    "+OOOOOOOOOOOOOOOOOOOO+",
    "OOXXXXXXXXXXXXXXXXXXOO",
    "OXX.          OO OO  O",
    "OX.      oo     O    O",
    "OX.      oo     O   .O",
    "OX  ooo  oooo   O    O",
    "OX    oo oo oo  O    O",
    "OX  oooo oo oo  O    O",
    "OX oo oo oo oo  O    O",
    "OX oo oo oo oo  O    O",
    "OX  oooo oooo   O    O",
    "OX            OO OO  O",
    "OO..................OO",
    "+OOOOOOOOOOOOOOOOOOOO+",
    "++++++++++++++++++++++",
    "++++++++++++++++++++++",
    "++++++++++++++++++++++",
    "++++++++++++++++++++++"
};

class GsTL_Widgets_plugin: public QObject, public QDesignerCustomWidgetCollectionInterface
 {
     Q_OBJECT
     Q_INTERFACES(QDesignerCustomWidgetCollectionInterface)

 public:
     GsTL_Widgets_plugin(QObject *parent = 0);
     virtual QList<QDesignerCustomWidgetInterface*> customWidgets() const;

 private:
     QList<QDesignerCustomWidgetInterface*> widgets;
 };


class GridSelectorPlugin : public QObject, public QDesignerCustomWidgetInterface
{
  Q_OBJECT
  Q_INTERFACES(QDesignerCustomWidgetInterface)
    
public:
  GridSelectorPlugin(QObject * o) : QObject(o) { _initialized = false; }
  
  bool isContainer() const { return false; }
  
  void initialize(QDesignerFormEditorInterface *)
  {
    if (_initialized)
      return;
    _initialized = true;
  }

  bool isInitialized () const { return _initialized; }

  QWidget * createWidget(QWidget * parent)
  {
    return new GridSelectorBasic(parent);
  }

  QString name() const { return QLatin1String("GridSelectorBasic"); }

  QString group() const { return QLatin1String("GsTLWidget"); }

  QIcon icon() const {     return QIcon( QPixmap( GridSelector_pixmap ) ); }

  QString toolTip() const { return QLatin1String("GridSelectorBasic widget"); }

  QString whatsThis() const {
    return "Widget for selecting a grid object among all the objects currently loaded";
  }

  QString includeFile() const { return "GsTLAppli/extra/qtplugins/selectors.h"; }
  
private:
  bool _initialized;
  
};

class PropertySelectorPlugin : public QObject, public QDesignerCustomWidgetInterface
{
  Q_OBJECT
  Q_INTERFACES(QDesignerCustomWidgetInterface)
    
public:
  PropertySelectorPlugin(QObject * o) : QObject(o) { _initialized = false; }
  
  bool isContainer() const { return false; }
  
  void initialize(QDesignerFormEditorInterface *)
  {
    if (_initialized)
      return;
    _initialized = true;
  }

  bool isInitialized () const { return _initialized; }

  QWidget * createWidget(QWidget * parent)
  {
    return new PropertySelectorNoRegion(parent);
  }

  QString name() const { return QLatin1String("PropertySelectorNoRegion"); }

  QString group() const { return QLatin1String("GsTLWidget"); }

  QIcon icon() const {     return QIcon( QPixmap( GridSelector_pixmap ) ); }

  QString toolTip() const { return QLatin1String("PropertySelectorNoRegion widget"); }

  QString whatsThis() const {
    return "Widget for selecting a property of a grid object";
  }

  QString includeFile() const { return "GsTLAppli/extra/qtplugins/selectors.h"; }
  
private:
  bool _initialized;
  
};


class HardDataKrigingPropertySelectorPlugin : public QObject, public QDesignerCustomWidgetInterface
{
  Q_OBJECT
  Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
  HardDataKrigingPropertySelectorPlugin(QObject * o) : QObject(o) { _initialized = false; }

  bool isContainer() const { return false; }

  void initialize(QDesignerFormEditorInterface *)
  {
    if (_initialized)
      return;
    _initialized = true;
  }

  bool isInitialized () const { return _initialized; }

  QWidget * createWidget(QWidget * parent)
  {
    return new HardDataKrigingPropertySelector(parent);
  }

  QString name() const { return QLatin1String("HardDataKrigingPropertySelector"); }

  QString group() const { return QLatin1String("GsTLWidget"); }

  QIcon icon() const {     return QIcon( QPixmap( GridSelector_pixmap ) ); }

  QString toolTip() const { return QLatin1String("HardDataKrigingPropertySelector widget"); }

  QString whatsThis() const {
    return "Widget for selecting a hard data property of a grid object.  Provide field to enter a LVM or external drifts";
  }

  QString includeFile() const { return "GsTLAppli/extra/qtplugins/kriging_type_selector.h"; }

private:
  bool _initialized;

};



class SinglePropertySelectorPlugin : public QObject, public QDesignerCustomWidgetInterface
{
  Q_OBJECT
  Q_INTERFACES(QDesignerCustomWidgetInterface)
    
public:
  SinglePropertySelectorPlugin(QObject * o) : QObject(o) { _initialized = false; }
  
  bool isContainer() const { return false; }
  
  void initialize(QDesignerFormEditorInterface *)
  {
    if (_initialized)
      return;
    _initialized = true;
  }

  bool isInitialized () const { return _initialized; }

  QWidget * createWidget(QWidget * parent)
  {
    return new SinglePropertySelector(parent);
  }

  QString name() const { return QLatin1String("SinglePropertySelector"); }

  QString group() const { return QLatin1String("GsTLWidget"); }

  QIcon icon() const {     return QIcon( QPixmap( GridSelector_pixmap ) ); }

  QString toolTip() const { return QLatin1String("SinglePropertySelector widget"); }

  QString whatsThis() const {
    return "Widget for selecting a single property of a grid object";
  }

  QString includeFile() const { return "GsTLAppli/extra/qtplugins/selectors.h"; }
  
private:
  bool _initialized;
  
};


class MultiPropertySelectorPlugin : public QObject, public QDesignerCustomWidgetInterface
{
  Q_OBJECT
  Q_INTERFACES(QDesignerCustomWidgetInterface)
    
public:
  MultiPropertySelectorPlugin(QObject * o) : QObject(o) { _initialized = false; }
  
  bool isContainer() const { return false; }
  
  void initialize(QDesignerFormEditorInterface *)
  {
    if (_initialized)
      return;
    _initialized = true;
  }

  bool isInitialized () const { return _initialized; }

  QWidget * createWidget(QWidget * parent)
  {
    return new MultiPropertySelector(parent);
  }

  QString name() const { return QLatin1String("MultiPropertySelector"); }

  QString group() const { return QLatin1String("GsTLWidget"); }

  QIcon icon() const {     return QIcon( QPixmap( GridSelector_pixmap ) ); }

  QString toolTip() const { return QLatin1String("MultiPropertySelector widget"); }

  QString whatsThis() const {
    return "Widget for selecting multiple properties of a grid object";
  }

  QString includeFile() const { return "GsTLAppli/extra/qtplugins/selectors.h"; }
  
private:
  bool _initialized;
  
};


class SinglePropertyGroupSelectorPlugin : public QObject, public QDesignerCustomWidgetInterface
{
  Q_OBJECT
  Q_INTERFACES(QDesignerCustomWidgetInterface)
    
public:
  SinglePropertyGroupSelectorPlugin(QObject * o) : QObject(o) { _initialized = false; }
  
  bool isContainer() const { return false; }
  
  void initialize(QDesignerFormEditorInterface *)
  {
    if (_initialized)
      return;
    _initialized = true;
  }

  bool isInitialized () const { return _initialized; }

  QWidget * createWidget(QWidget * parent)
  {
    return new SinglePropertyGroupSelector(parent);
  }

  QString name() const { return QLatin1String("SinglePropertyGroupSelector"); }

  QString group() const { return QLatin1String("GsTLWidget"); }

  QIcon icon() const {     return QIcon( QPixmap( GridSelector_pixmap ) ); }

  QString toolTip() const { return QLatin1String("SinglePropertyGroupSelector widget"); }

  QString whatsThis() const {
    return "Widget for selecting a group property of a grid object";
  }

  QString includeFile() const { return "GsTLAppli/extra/qtplugins/group_selectors.h"; }
  
private:
  bool _initialized;
  
};


class MultiPropertyGroupSelectorPlugin : public QObject, public QDesignerCustomWidgetInterface
{
  Q_OBJECT
  Q_INTERFACES(QDesignerCustomWidgetInterface)
    
public:
  MultiPropertyGroupSelectorPlugin(QObject * o) : QObject(o) { _initialized = false; }
  
  bool isContainer() const { return false; }
  
  void initialize(QDesignerFormEditorInterface *)
  {
    if (_initialized)
      return;
    _initialized = true;
  }

  bool isInitialized () const { return _initialized; }

  QWidget * createWidget(QWidget * parent)
  {
    return new MultiPropertyGroupSelector(parent);
  }

  QString name() const { return QLatin1String("MultiPropertyGroupSelector"); }

  QString group() const { return QLatin1String("GsTLWidget"); }

  QIcon icon() const {     return QIcon( QPixmap( GridSelector_pixmap ) ); }

  QString toolTip() const { return QLatin1String("MultiPropertyGroupSelector widget"); }

  QString whatsThis() const {
    return "Widget for selecting multiple properties of a grid object";
  }

  QString includeFile() const { return "GsTLAppli/extra/qtplugins/group_selectors.h"; }
  
private:
  bool _initialized;
  
};


class OrderedPropertySelectorPlugin : public QObject, public QDesignerCustomWidgetInterface
{
  Q_OBJECT
  Q_INTERFACES(QDesignerCustomWidgetInterface)
    
public:
  OrderedPropertySelectorPlugin(QObject * o) : QObject(o) { _initialized = false; }
  
  bool isContainer() const { return false; }
  
  void initialize(QDesignerFormEditorInterface *)
  {
    if (_initialized)
      return;
    _initialized = true;
  }

  bool isInitialized () const { return _initialized; }

  QWidget * createWidget(QWidget * parent)
  {
    return new OrderedPropertySelector(parent);
  }

  QString name() const { return QLatin1String("OrderedPropertySelector"); }

  QString group() const { return QLatin1String("GsTLWidget"); }

  QIcon icon() const {     return QIcon( QPixmap( GridSelector_pixmap ) ); }

  QString toolTip() const { return QLatin1String("OrderedPropertySelector widget"); }

  QString whatsThis() const {
    return "Widget for selecting multiple properties of a grid object and ordering them";
  }

  QString includeFile() const { return "GsTLAppli/extra/qtplugins/selectors.h"; }
  
private:
  bool _initialized;
  
};

class GsTLTablePlugin : public QObject, public QDesignerCustomWidgetInterface
{
  Q_OBJECT
  Q_INTERFACES(QDesignerCustomWidgetInterface)
    
public:
  GsTLTablePlugin(QObject * o) : QObject(o) { _initialized = false; }
  
  bool isContainer() const { return false; }
  
  void initialize(QDesignerFormEditorInterface *)
  {
    if (_initialized)
      return;
    _initialized = true;
  }

  bool isInitialized () const { return _initialized; }

  QWidget * createWidget(QWidget * parent)
  {
    return new GsTLTable(parent);
  }

  QString name() const { return QLatin1String("GsTLTable"); }

  QString group() const { return QLatin1String("GsTLWidget"); }

  QIcon icon() const {     return QIcon( QPixmap( GridSelector_pixmap ) ); }

  QString toolTip() const { return QLatin1String("GsTLTable widget"); }

  QString whatsThis() const {
    return "Table widget with copy/paste support";
  }

  QString includeFile() const { return "GsTLAppli/extra/qtplugins/gstl_table.h"; }
  
private:
  bool _initialized;
  
};

class FileChooserPlugin : public QObject, public QDesignerCustomWidgetInterface
{
  Q_OBJECT
  Q_INTERFACES(QDesignerCustomWidgetInterface)
    
public:
  FileChooserPlugin(QObject * o) : QObject(o) { _initialized = false; }
  
  bool isContainer() const { return false; }
  
  void initialize(QDesignerFormEditorInterface *)
  {
    if (_initialized)
      return;
    _initialized = true;
  }

  bool isInitialized () const { return _initialized; }

  QWidget * createWidget(QWidget * parent)
  {
    return new FileChooser(parent);
  }

  QString name() const { return QLatin1String("FileChooser"); }

  QString group() const { return QLatin1String("GsTLWidget"); }

  QIcon icon() const {     return QIcon( QPixmap( GridSelector_pixmap ) ); }

  QString toolTip() const { return QLatin1String("FileChooser widget"); }

  QString whatsThis() const {
    return "Widget for selecting a file";
  }

  QString includeFile() const { return "GsTLAppli/extra/qtplugins/filechooser.h"; }
  
private:
  bool _initialized;
  
};

class VariogramInputPlugin : public QObject, public QDesignerCustomWidgetInterface
{
  Q_OBJECT
  Q_INTERFACES(QDesignerCustomWidgetInterface)
    
public:
  VariogramInputPlugin(QObject * o) : QObject(o) { _initialized = false; }
  
  bool isContainer() const { return false; }
  
  void initialize(QDesignerFormEditorInterface *)
  {
    if (_initialized)
      return;
    _initialized = true;
  }

  bool isInitialized () const { return _initialized; }

  QWidget * createWidget(QWidget * parent)
  {
    return new VariogramInput(parent);
  }

  QString name() const { return QLatin1String("VariogramInput"); }

  QString group() const { return QLatin1String("GsTLWidget"); }

  QIcon icon() const {     return QIcon( QPixmap( variogram_pixmap ) ); }

  QString toolTip() const { return QLatin1String("VariogramInput widget"); }

  QString whatsThis() const {
    return "Widget for inputing a variogram";
  }

  QString includeFile() const { return "GsTLAppli/extra/qtplugins/variogram_input.h"; }
  
private:
  bool _initialized;
  
};

class KrigingTypeSelectorPlugin : public QObject, public QDesignerCustomWidgetInterface
{
  Q_OBJECT
  Q_INTERFACES(QDesignerCustomWidgetInterface)
    
public:
  KrigingTypeSelectorPlugin(QObject * o) : QObject(o) { _initialized = false; }
  
  bool isContainer() const { return false; }
  
  void initialize(QDesignerFormEditorInterface *)
  {
    if (_initialized)
      return;
    _initialized = true;
  }

  bool isInitialized () const { return _initialized; }

  QWidget * createWidget(QWidget * parent)
  {
    return new KrigingTypeSelector(parent);
  }

  QString name() const { return QLatin1String("KrigingTypeSelector"); }

  QString group() const { return QLatin1String("GsTLWidget"); }

  QIcon icon() const {     return QIcon( QPixmap( GridSelector_pixmap ) ); }

  QString toolTip() const { return QLatin1String("KrigingTypeSelector widget"); }

  QString whatsThis() const {
    return "Widget for choose a kriging type and input the corresponding parameters";
  }

  QString includeFile() const { return "GsTLAppli/extra/qtplugins/kriging_type_selector.h"; }
  
private:
  bool _initialized;
  
};

class GsTLButtonGroupPlugin : public QObject, public QDesignerCustomWidgetInterface
{
  Q_OBJECT
  Q_INTERFACES(QDesignerCustomWidgetInterface)
    
public:
  GsTLButtonGroupPlugin(QObject * o) : QObject(o) { _initialized = false; }
  
  bool isContainer() const { return false; }
  
  void initialize(QDesignerFormEditorInterface *)
  {
    if (_initialized)
      return;
    _initialized = true;
  }

  bool isInitialized () const { return _initialized; }

  QWidget * createWidget(QWidget * parent)
  {
    return new GsTLButtonGroup(parent);
  }

  QString name() const { return QLatin1String("GsTLButtonGroup"); }

  QString group() const { return QLatin1String("GsTLWidget"); }

  QIcon icon() const {     return QIcon( QPixmap( GridSelector_pixmap ) ); }

  QString toolTip() const { return QLatin1String("GsTLButtonGroup widget"); }

  QString whatsThis() const {
    return "Widget to group other widgets";
  }

  QString includeFile() const { return "GsTLAppli/extra/qtplugins/selectors.h"; }
  
private:
  bool _initialized;
  
};


class CloneGroupBoxPlugin : public QObject, public QDesignerCustomWidgetInterface
{
  Q_OBJECT
  Q_INTERFACES(QDesignerCustomWidgetInterface)
    
public:
  CloneGroupBoxPlugin(QObject * o) : QObject(o) { _initialized = false; }
  
  bool isContainer() const { return false; }
  
  void initialize(QDesignerFormEditorInterface *)
  {
    if (_initialized)
      return;
    _initialized = true;
  }

  bool isInitialized () const { return _initialized; }

  QWidget * createWidget(QWidget * parent)
  {
    return new CloneGroupBox(parent);
  }

  QString name() const { return QLatin1String("CloneGroupBox"); }

  QString group() const { return QLatin1String("GsTLWidget"); }

  QIcon icon() const {     return QIcon( QPixmap( GridSelector_pixmap ) ); }

  QString toolTip() const { return QLatin1String("CloneGroupBox widget"); }

  QString whatsThis() const {
    return "CloneGroupBox widgets";
  }

  QString includeFile() const { return "GsTLAppli/extra/qtplugins/selectors.h"; }
  
private:
  bool _initialized;
  
};


class GsTLGroupBoxPlugin : public QObject, public QDesignerCustomWidgetInterface
{
  Q_OBJECT
  Q_INTERFACES(QDesignerCustomWidgetInterface)
    
public:
  GsTLGroupBoxPlugin(QObject * o) : QObject(o) { _initialized = false; }
  
  bool isContainer() const { return false; }
  
  void initialize(QDesignerFormEditorInterface *)
  {
    if (_initialized)
      return;
    _initialized = true;
  }

  bool isInitialized () const { return _initialized; }

  QWidget * createWidget(QWidget * parent)
  {
    return new GsTLGroupBox(parent);
  }

  QString name() const { return QLatin1String("GsTLGroupBox"); }

  QString group() const { return QLatin1String("GsTLWidget"); }

  QIcon icon() const {     return QIcon( QPixmap( GridSelector_pixmap ) ); }

  QString toolTip() const { return QLatin1String("GsTLGroupBox widget"); }

  QString whatsThis() const {
    return "Widget to group other widgets";
  }

  QString includeFile() const { return "GsTLAppli/extra/qtplugins/selectors.h"; }
  
private:
  bool _initialized;
  
};

class TrendComponentsPlugin : public QObject, public QDesignerCustomWidgetInterface
{
  Q_OBJECT
  Q_INTERFACES(QDesignerCustomWidgetInterface)
    
public:
  TrendComponentsPlugin(QObject * o) : QObject(o) { _initialized = false; }
  
  bool isContainer() const { return false; }
  
  void initialize(QDesignerFormEditorInterface *)
  {
    if (_initialized)
      return;
    _initialized = true;
  }

  bool isInitialized () const { return _initialized; }

  QWidget * createWidget(QWidget * parent)
  {
    return new TrendComponents(parent);
  }

  QString name() const { return QLatin1String("TrendComponents"); }

  QString group() const { return QLatin1String("GsTLWidget"); }

  QIcon icon() const {     return QIcon( QPixmap( GridSelector_pixmap ) ); }

  QString toolTip() const { return QLatin1String("TrendComponents widget"); }

  QString whatsThis() const {
    return "Trend components";
  }

  QString includeFile() const { return "GsTLAppli/extra/qtplugins/kriging_type_selector.h"; }
  
private:
  bool _initialized;
  
};


class Drift_componentsPlugin : public QObject, public QDesignerCustomWidgetInterface
{
  Q_OBJECT
  Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
  Drift_componentsPlugin(QObject * o) : QObject(o) { _initialized = false; }

  bool isContainer() const { return false; }

  void initialize(QDesignerFormEditorInterface *)
  {
    if (_initialized)
      return;
    _initialized = true;
  }

  bool isInitialized () const { return _initialized; }

  QWidget * createWidget(QWidget * parent)
  {
    return new Drift_components(parent);
  }

  QString name() const { return QLatin1String("Drift_components"); }

  QString group() const { return QLatin1String("GsTLWidget"); }

  QIcon icon() const {     return QIcon( QPixmap( GridSelector_pixmap ) ); }

  QString toolTip() const { return QLatin1String("Drift_components widget"); }

  QString whatsThis() const {
    return "Widget for selecting a hard data property of a grid object.  Provide field to enter a LVM or external drifts";
  }

  QString includeFile() const { return "GsTLAppli/extra/qtplugins/kriging_type_selector.h"; }

private:
  bool _initialized;

};


class EllipsoidInputPlugin : public QObject, public QDesignerCustomWidgetInterface
{
  Q_OBJECT
  Q_INTERFACES(QDesignerCustomWidgetInterface)
    
public:
  EllipsoidInputPlugin(QObject * o) : QObject(o) { _initialized = false; }
  
  bool isContainer() const { return false; }
  
  void initialize(QDesignerFormEditorInterface *)
  {
    if (_initialized)
      return;
    _initialized = true;
  }

  bool isInitialized () const { return _initialized; }

  QWidget * createWidget(QWidget * parent)
  {
    return new EllipsoidInput(parent);
  }

  QString name() const { return QLatin1String("EllipsoidInput"); }

  QString group() const { return QLatin1String("GsTLWidget"); }

  QIcon icon() const {     return QIcon( QPixmap( GridSelector_pixmap ) ); }

  QString toolTip() const { return QLatin1String("EllipsoidInput widget"); }

  QString whatsThis() const {
    return "widget for defining a 3D Ellipsoid";
  }

  QString includeFile() const { return "GsTLAppli/extra/qtplugins/ellipsoid_input.h"; }
  
private:
  bool _initialized;
  
};
class UpperTailCdfInputPlugin : public QObject, public QDesignerCustomWidgetInterface
{
  Q_OBJECT
  Q_INTERFACES(QDesignerCustomWidgetInterface)
    
public:
  UpperTailCdfInputPlugin(QObject * o) : QObject(o) { _initialized = false; }
  
  bool isContainer() const { return false; }
  
  void initialize(QDesignerFormEditorInterface *)
  {
    if (_initialized)
      return;
    _initialized = true;
  }

  bool isInitialized () const { return _initialized; }

  QWidget * createWidget(QWidget * parent)
  {
    return new UpperTailCdfInput(parent);
  }

  QString name() const { return QLatin1String("UpperTailCdfInput"); }

  QString group() const { return QLatin1String("GsTLWidget"); }

  QIcon icon() const {     return QIcon( QPixmap( GridSelector_pixmap ) ); }

  QString toolTip() const { return QLatin1String("UpperTailCdfInput widget"); }

  QString whatsThis() const {
    return "Widget for upper tail extrapolation";
  }

  QString includeFile() const { return "GsTLAppli/extra/qtplugins/non_param_cdf_input.h"; }
  
private:
  bool _initialized;
  
};

class LowerTailCdfInputPlugin : public QObject, public QDesignerCustomWidgetInterface
{
  Q_OBJECT
  Q_INTERFACES(QDesignerCustomWidgetInterface)
    
public:
  LowerTailCdfInputPlugin(QObject * o) : QObject(o) { _initialized = false; }
  
  bool isContainer() const { return false; }
  
  void initialize(QDesignerFormEditorInterface *)
  {
    if (_initialized)
      return;
    _initialized = true;
  }

  bool isInitialized () const { return _initialized; }

  QWidget * createWidget(QWidget * parent)
  {
    return new LowerTailCdfInput(parent);
  }

  QString name() const { return QLatin1String("LowerTailCdfInput"); }

  QString group() const { return QLatin1String("GsTLWidget"); }

  QIcon icon() const {     return QIcon( QPixmap( GridSelector_pixmap ) ); }

  QString toolTip() const { return QLatin1String("LowerTailCdfInput widget"); }

  QString whatsThis() const {
    return "Widget for lower tail extrapolation";
  }

  QString includeFile() const { return "GsTLAppli/extra/qtplugins/non_param_cdf_input.h"; }
  
private:
  bool _initialized;
  
};

class NonParamCdfInputPlugin : public QObject, public QDesignerCustomWidgetInterface
{
  Q_OBJECT
  Q_INTERFACES(QDesignerCustomWidgetInterface)
    
public:
  NonParamCdfInputPlugin(QObject * o) : QObject(o) { _initialized = false; }
  
  bool isContainer() const { return false; }
  
  void initialize(QDesignerFormEditorInterface *)
  {
    if (_initialized)
      return;
    _initialized = true;
  }

  bool isInitialized () const { return _initialized; }

  QWidget * createWidget(QWidget * parent)
  {
    return new NonParamCdfInput(parent);
  }

  QString name() const { return QLatin1String("NonParamCdfInput"); }

  QString group() const { return QLatin1String("GsTLWidget"); }

  QIcon icon() const {     return QIcon( QPixmap( GridSelector_pixmap ) ); }

  QString toolTip() const { return QLatin1String("NonParamCdfInput widget"); }

  QString whatsThis() const {
    return "Widgets for defining a non parametric distribution";
  }

  QString includeFile() const { return "GsTLAppli/extra/qtplugins/non_param_cdf_input.h"; }
  
private:
  bool _initialized;
  
};




class SingleRegionSelectorPlugin : public QObject, public QDesignerCustomWidgetInterface
{
  Q_OBJECT
  Q_INTERFACES(QDesignerCustomWidgetInterface)
    
public:
  SingleRegionSelectorPlugin(QObject * o) : QObject(o) { _initialized = false; }
  
  bool isContainer() const { return false; }
  
  void initialize(QDesignerFormEditorInterface *)
  {
    if (_initialized)
      return;
    _initialized = true;
  }

  bool isInitialized () const { return _initialized; }

  QWidget * createWidget(QWidget * parent)
  {
    return new SingleRegionSelector(parent);
  }

  QString name() const { return QLatin1String("SingleRegionSelector"); }

  QString group() const { return QLatin1String("GsTLWidget"); }

  QIcon icon() const {     return QIcon( QPixmap( GridSelector_pixmap ) ); }

  QString toolTip() const { return QLatin1String("SingleRegionSelector widget"); }

  QString whatsThis() const {
    return "Widget for selecting a single region of a grid object";
  }

  QString includeFile() const { return "GsTLAppli/extra/qtplugins/selectors.h"; }
  
private:
  bool _initialized;
  
};



class GridRegionSelectorPlugin : public QObject, public QDesignerCustomWidgetInterface
{
  Q_OBJECT
  Q_INTERFACES(QDesignerCustomWidgetInterface)
    
public:
  GridRegionSelectorPlugin(QObject * o) : QObject(o) { _initialized = false; }
  
  bool isContainer() const { return false; }
  
  void initialize(QDesignerFormEditorInterface *)
  {
    if (_initialized)
      return;
    _initialized = true;
  }

  bool isInitialized () const { return _initialized; }

  QWidget * createWidget(QWidget * parent)
  {
    return new GridSelector(parent);
  }

  QString name() const { return QLatin1String("GridSelector"); }

  QString group() const { return QLatin1String("GsTLWidget"); }

  QIcon icon() const {     return QIcon( QPixmap( GridSelector_pixmap ) ); }

  QString toolTip() const { return QLatin1String("GridSelector widget"); }

  QString whatsThis() const {
    return "Widget for selecting a grid object with a region";
  }

  QString includeFile() const { return "GsTLAppli/extra/qtplugins/selectors.h"; }
  
private:
  bool _initialized;
  
};




class MultiRegionSelectorPlugin : public QObject, public QDesignerCustomWidgetInterface
{
  Q_OBJECT
  Q_INTERFACES(QDesignerCustomWidgetInterface)
    
public:
  MultiRegionSelectorPlugin(QObject * o) : QObject(o) { _initialized = false; }
  
  bool isContainer() const { return false; }
  
  void initialize(QDesignerFormEditorInterface *)
  {
    if (_initialized)
      return;
    _initialized = true;
  }

  bool isInitialized () const { return _initialized; }

  QWidget * createWidget(QWidget * parent)
  {
    return new MultiRegionSelector(parent);
  }

  QString name() const { return QLatin1String("MultiRegionSelector"); }

  QString group() const { return QLatin1String("GsTLWidget"); }

  QIcon icon() const {     return QIcon( QPixmap( GridSelector_pixmap ) ); }

  QString toolTip() const { return QLatin1String("MultiRegionSelector widget"); }

  QString whatsThis() const {
    return "Widget for selecting multiple regions of a grid object";
  }

  QString includeFile() const { return "GsTLAppli/extra/qtplugins/selectors.h"; }
  
private:
  bool _initialized;
  
};



class OctanSearchPlugin : public QObject, public QDesignerCustomWidgetInterface
{
  Q_OBJECT
  Q_INTERFACES(QDesignerCustomWidgetInterface)
    
public:
  OctanSearchPlugin(QObject * o) : QObject(o) { _initialized = false; }
  
  bool isContainer() const { return false; }
  
  void initialize(QDesignerFormEditorInterface *)
  {
    if (_initialized)
      return;
    _initialized = true;
  }

  bool isInitialized () const { return _initialized; }

  QWidget * createWidget(QWidget * parent)
  {
    return new OctantSearchInput(parent);
  }

  QString name() const { return QLatin1String("OctantSearchInput"); }

  QString group() const { return QLatin1String("GsTLWidget"); }

  QIcon icon() const {     return QIcon( QPixmap( GridSelector_pixmap ) ); }

  QString toolTip() const { return QLatin1String("OctantSearchInput widget"); }

  QString whatsThis() const {
    return "widget for octant search parameters";
  }

  QString includeFile() const { return "GsTLAppli/extra/qtplugins/neighborhood_filter_input.h"; }
  
private:
  bool _initialized;
  
};



class AdvancedSearchPlugin : public QObject, public QDesignerCustomWidgetInterface
{
  Q_OBJECT
  Q_INTERFACES(QDesignerCustomWidgetInterface)
    
public:
  AdvancedSearchPlugin(QObject * o) : QObject(o) { _initialized = false; }
  
  bool isContainer() const { return false; }
  
  void initialize(QDesignerFormEditorInterface *)
  {
    if (_initialized)
      return;
    _initialized = true;
  }

  bool isInitialized () const { return _initialized; }

  QWidget * createWidget(QWidget * parent)
  {
    return new AdvancedNeighborhoodInput(parent);
  }

  QString name() const { return QLatin1String("AdvancedNeighborhoodInput"); }

  QString group() const { return QLatin1String("GsTLWidget"); }

  QIcon icon() const {     return QIcon( QPixmap( GridSelector_pixmap ) ); }

  QString toolTip() const { return QLatin1String("AdvancedNeighborhoodInput widget"); }

  QString whatsThis() const {
    return "widget for advanced search parameters";
  }

  QString includeFile() const { return "GsTLAppli/extra/qtplugins/neighborhood_filter_input.h"; }
  
private:
  bool _initialized;
  
};




class PropertyRegionSelectorPlugin : public QObject, public QDesignerCustomWidgetInterface
{
  Q_OBJECT
  Q_INTERFACES(QDesignerCustomWidgetInterface)
    
public:
  PropertyRegionSelectorPlugin(QObject * o) : QObject(o) { _initialized = false; }
  
  bool isContainer() const { return false; }
  
  void initialize(QDesignerFormEditorInterface *)
  {
    if (_initialized)
      return;
    _initialized = true;
  }

  bool isInitialized () const { return _initialized; }

  QWidget * createWidget(QWidget * parent)
  {
    return new PropertySelector(parent);
  }

  QString name() const { return QLatin1String("PropertySelector"); }

  QString group() const { return QLatin1String("GsTLWidget"); }

  QIcon icon() const {     return QIcon( QPixmap( GridSelector_pixmap ) ); }

  QString toolTip() const { return QLatin1String("PropertyRegionSelector widget"); }

  QString whatsThis() const {
    return "Widget for selecting a property of a grid object";
  }

  QString includeFile() const { return "GsTLAppli/extra/qtplugins/selectors.h"; }
  
private:
  bool _initialized;
  
};



class SingleCategoricalPropertySelectorPlugin : public QObject, public QDesignerCustomWidgetInterface
{
  Q_OBJECT
  Q_INTERFACES(QDesignerCustomWidgetInterface)
    
public:
  SingleCategoricalPropertySelectorPlugin(QObject * o) : QObject(o) { _initialized = false; }
  
  bool isContainer() const { return false; }
  
  void initialize(QDesignerFormEditorInterface *)
  {
    if (_initialized)
      return;
    _initialized = true;
  }

  bool isInitialized () const { return _initialized; }

  QWidget * createWidget(QWidget * parent)
  {
    return new SingleCategoricalPropertySelector(parent);
  }

  QString name() const { return QLatin1String("SingleCategoricalPropertySelector"); }

  QString group() const { return QLatin1String("GsTLWidget"); }

  QIcon icon() const {     return QIcon( QPixmap( GridSelector_pixmap ) ); }

  QString toolTip() const { return QLatin1String("SingleCategoricalPropertySelector widget"); }

  QString whatsThis() const {
    return "Widget for selecting a single categorical property of a grid object";
  }

  QString includeFile() const { return "GsTLAppli/extra/qtplugins/categorical_selectors.h"; }
  
private:
  bool _initialized;
  
};

class MultiCategoricalPropertySelectorPlugin : public QObject, public QDesignerCustomWidgetInterface
{
  Q_OBJECT
  Q_INTERFACES(QDesignerCustomWidgetInterface)
    
public:
  MultiCategoricalPropertySelectorPlugin(QObject * o) : QObject(o) { _initialized = false; }
  
  bool isContainer() const { return false; }
  
  void initialize(QDesignerFormEditorInterface *)
  {
    if (_initialized)
      return;
    _initialized = true;
  }

  bool isInitialized () const { return _initialized; }

  QWidget * createWidget(QWidget * parent)
  {
    return new MultiCategoricalPropertySelector(parent);
  }

  QString name() const { return QLatin1String("MultiCategoricalPropertySelector"); }

  QString group() const { return QLatin1String("GsTLWidget"); }

  QIcon icon() const {     return QIcon( QPixmap( GridSelector_pixmap ) ); }

  QString toolTip() const { return QLatin1String("MultiCategoricalPropertySelector widget"); }

  QString whatsThis() const {
    return "Widget for selecting multiple categroical properties of a grid object";
  }

  QString includeFile() const { return "GsTLAppli/extra/qtplugins/categorical_selectors.h"; }
  
private:
  bool _initialized;
  
};

class OrderedCategoricalPropertySelectorPlugin : public QObject, public QDesignerCustomWidgetInterface
{
  Q_OBJECT
  Q_INTERFACES(QDesignerCustomWidgetInterface)
    
public:
  OrderedCategoricalPropertySelectorPlugin(QObject * o) : QObject(o) { _initialized = false; }
  
  bool isContainer() const { return false; }
  
  void initialize(QDesignerFormEditorInterface *)
  {
    if (_initialized)
      return;
    _initialized = true;
  }

  bool isInitialized () const { return _initialized; }

  QWidget * createWidget(QWidget * parent)
  {
    return new OrderedCategoricalPropertySelector(parent);
  }

  QString name() const { return QLatin1String("OrderedCategoricalPropertySelector"); }

  QString group() const { return QLatin1String("GsTLWidget"); }

  QIcon icon() const {     return QIcon( QPixmap( GridSelector_pixmap ) ); }

  QString toolTip() const { return QLatin1String("OrderedCategoricalPropertySelector widget"); }

  QString whatsThis() const {
    return "Widget for selecting multiple categorical properties of a grid object and ordering them";
  }

  QString includeFile() const { return "GsTLAppli/extra/qtplugins/categorical_selectors.h"; }
  
private:
  bool _initialized;
  
};



class CategoricalDefinitionSelectorPlugin : public QObject, public QDesignerCustomWidgetInterface
{
  Q_OBJECT
  Q_INTERFACES(QDesignerCustomWidgetInterface)
    
public:
  CategoricalDefinitionSelectorPlugin(QObject * o) : QObject(o) { _initialized = false; }

  bool isContainer() const { return false; }
 
  void initialize(QDesignerFormEditorInterface *)
  {
    if (_initialized)
      return;
    _initialized = true;
  }

  bool isInitialized () const { return _initialized; }

  QWidget * createWidget(QWidget * parent)
  {
    return new CategoricalDefinitionSelector(parent);
  }

  QString name() const { return QLatin1String("CategoricalDefinitionSelector"); }

  QString group() const { return QLatin1String("GsTLWidget"); }

  QIcon icon() const {     return QIcon( QPixmap( GridSelector_pixmap ) ); }

  QString toolTip() const { return QLatin1String("CategoricalDefinitionSelector widget"); }

  QString whatsThis() const {
    return "Widget for selecting a categorical definitions";
  }

  QString includeFile() const { return "GsTLAppli/extra/qtplugins/categorical_selectors.h"; }
  
private:
  bool _initialized;
  
};




class MultiCategoricalDefinitionSelectorPlugin : public QObject, public QDesignerCustomWidgetInterface
{
  Q_OBJECT
  Q_INTERFACES(QDesignerCustomWidgetInterface)
    
public:
  MultiCategoricalDefinitionSelectorPlugin(QObject * o) : QObject(o) { _initialized = false; }

  bool isContainer() const { return false; }
 
  void initialize(QDesignerFormEditorInterface *)
  {
    if (_initialized)
      return;
    _initialized = true;
  }

  bool isInitialized () const { return _initialized; }

  QWidget * createWidget(QWidget * parent)
  {
    return new MultiCategoricalDefinitionSelector(parent);
  }

  QString name() const { return QLatin1String("MultiCategoricalDefinitionSelector"); }

  QString group() const { return QLatin1String("GsTLWidget"); }

  QIcon icon() const {     return QIcon( QPixmap( GridSelector_pixmap ) ); }

  QString toolTip() const { return QLatin1String("MultiCategoricalDefinitionSelector widget"); }

  QString whatsThis() const {
    return "Widget for selecting multiple categorical definitions";
  }

  QString includeFile() const { return "GsTLAppli/extra/qtplugins/categorical_selectors.h"; }
  
private:
  bool _initialized;
  
};



class CategoricalDefinitionViewerPlugin : public QObject, public QDesignerCustomWidgetInterface
{
  Q_OBJECT
  Q_INTERFACES(QDesignerCustomWidgetInterface)
    
public:
  CategoricalDefinitionViewerPlugin(QObject * o) : QObject(o) { _initialized = false; }

  bool isContainer() const { return false; }
 
  void initialize(QDesignerFormEditorInterface *)
  {
    if (_initialized)
      return;
    _initialized = true;
  }

  bool isInitialized () const { return _initialized; }

  QWidget * createWidget(QWidget * parent)
  {
    return new CategoricalDefinitionViewer(parent);
  }

  QString name() const { return QLatin1String("CategoricalDefinitionViewer"); }

  QString group() const { return QLatin1String("GsTLWidget"); }

  QIcon icon() const {     return QIcon( QPixmap( GridSelector_pixmap ) ); }

  QString toolTip() const { return QLatin1String("CategoricalDefinitionViewer widget"); }

  QString whatsThis() const {
    return "Widget for selecting multiple categorical definitions";
  }

  QString includeFile() const { return "GsTLAppli/extra/qtplugins/categorical_selectors.h"; }
  
private:
  bool _initialized;
  
};




class SingleWeightPropertySelectorPlugin : public QObject, public QDesignerCustomWidgetInterface
{
  Q_OBJECT
  Q_INTERFACES(QDesignerCustomWidgetInterface)
    
public:
  SingleWeightPropertySelectorPlugin(QObject * o) : QObject(o) { _initialized = false; }
  
  bool isContainer() const { return false; }
  
  void initialize(QDesignerFormEditorInterface *)
  {
    if (_initialized)
      return;
    _initialized = true;
  }

  bool isInitialized () const { return _initialized; }

  QWidget * createWidget(QWidget * parent)
  {
    return new SingleWeightPropertySelector(parent);
  }

  QString name() const { return QLatin1String("SingleWeightPropertySelector"); }

  QString group() const { return QLatin1String("GsTLWidget"); }

  QIcon icon() const {     return QIcon( QPixmap( GridSelector_pixmap ) ); }

  QString toolTip() const { return QLatin1String("SingleWeightPropertySelector widget"); }

  QString whatsThis() const {
    return "Widget for selecting a single weight property of a grid object";
  }

  QString includeFile() const { return "GsTLAppli/extra/qtplugins/weight_property_selectors.h"; }
  
private:
  bool _initialized;
  
};


#endif
