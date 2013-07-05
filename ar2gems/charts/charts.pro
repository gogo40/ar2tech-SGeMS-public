TEMPLATE = lib

debug:DEFINES += _DEBUG
DEPENDPATH += .
INCLUDEPATH += .

HEADERS += categorical_histogram_creator.h \
           common.h \
           categorical_histogram_model_item.h \
           continuous_histogram_creator.h \
           categorical_histogram_proxy_model.h \
           histogram_chart_model.h \
           chart_base.h \
           histogram_item_tree_view.h \
           chart_categorical_histogram.h \
           histogram_model_item.h \
           chart_continuous_histogram.h \
           histogram_proxy_model.h \
           chart_creator.h \
           histogram_style_delegate.h \
           chart_dialog.h \
           library_charts_init.h \
           chart_display_control.h \
           region_weight_delegate.h \
           chart_distribution.h \
           scatter_plot_creator.h \
           chart_mdi_area.h \
           scatter_plot_item_tree_view.h \
           chart_model_item.h \
           scatter_plot_model_item.h \
           chart_option_controls.h \
           scatter_plot_point_style_delegate.h \
           chart_scatter_plot.h \
           scatter_plot_proxy_model.h \
           log_data_chart.h \
           log_data_chart_creator.h \
           chart_base_display_controls.h

SOURCES += categorical_histogram_creator.cpp \
           categorical_histogram_model_item.cpp \
           continuous_histogram_creator.cpp \
           categorical_histogram_proxy_model.cpp \
           histogram_chart_model.cpp \
           chart_base.cpp \
           histogram_item_tree_view.cpp \
           chart_categorical_histogram.cpp \
           histogram_model_item.cpp \
           chart_continuous_histogram.cpp \
           histogram_proxy_model.cpp \
           histogram_style_delegate.cpp \
           chart_dialog.cpp \
           library_charts_init.cpp \
           chart_display_control.cpp \
           region_weight_delegate.cpp \
           chart_distribution.cpp \
           scatter_plot_creator.cpp \
           chart_mdi_area.cpp \
           scatter_plot_item_tree_view.cpp \
           scatter_plot_model_item.cpp \
           chart_option_controls.cpp \
           scatter_plot_point_style_delegate.cpp \
           chart_scatter_plot.cpp \
           scatter_plot_proxy_model.cpp \
           log_data_chart.cpp \
           log_data_chart_creator.cpp \
           chart_base_display_controls.cpp

FORMS += chart_display_control.ui

TARGET = ar2gems_charts

QT += xml
QT += opengl
CONFIG += plugin
INCLUDEPATH += $(QTDIR)/tools/designer/interfaces
INCLUDEPATH += /usr/local/include/
contains( TEMPLATE, lib ) {
    DESTDIR = $$GSTLAPPLI_HOME/lib/$$CUR_PLATFORM
    OBJECTS_DIR = $$GSTLAPPLI_HOME/lib/$$CUR_PLATFORM/obj/gui
}
contains( TEMPLATE, app ) {
    DESTDIR += $$GSTLAPPLI_HOME/bin/$$CUR_PLATFORM
    OBJECTS_DIR = $$GSTLAPPLI_HOME/bin/$$CUR_PLATFORM/obj/gui
}
include( $$GSTLAPPLI_HOME/config.qmake )
exists( MMakefile ):include( MMakefile )
