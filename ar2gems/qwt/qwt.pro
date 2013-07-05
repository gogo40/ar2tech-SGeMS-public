# -*- mode: sh -*- ###########################
# Qwt Widget Library
# Copyright (C) 1997   Josef Wilgen
# Copyright (C) 2002   Uwe Rathmann
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the Qwt License, Version 1.0
##############################################

# qmake project file for building the qwt libraries

include( qwtconfig.pri )

TARGET            = GsTLAppli_qwt
TEMPLATE          = lib

CONFIG += plugin


HEADERS += \
    qwt.h \
    qwt_abstract_scale_draw.h \
    qwt_array.h \
    qwt_color_map.h \
    qwt_double_interval.h \
    qwt_double_rect.h \
    qwt_dyngrid_layout.h \
    qwt_global.h \
    qwt_layout_metrics.h \
    qwt_math.h \
    qwt_paint_buffer.h \
    qwt_painter.h \
    qwt_panner.h \
    qwt_picker.h \
    qwt_picker_machine.h \
    qwt_polygon.h \
    qwt_rect.h \
    qwt_round_scale_draw.h \
    qwt_scale_div.h \
    qwt_scale_draw.h \
    qwt_scale_engine.h \
    qwt_scale_map.h \
    qwt_spline.h \
    qwt_symbol.h \
    qwt_text_engine.h \
    qwt_text_label.h \
    qwt_text.h \
    qwt_valuelist.h

SOURCES += \
    qwt_abstract_scale_draw.cpp \
    qwt_color_map.cpp \
    qwt_double_interval.cpp \
    qwt_double_rect.cpp \
    qwt_dyngrid_layout.cpp \
    qwt_layout_metrics.cpp \
    qwt_math.cpp \
    qwt_paint_buffer.cpp \
    qwt_panner.cpp \
    qwt_painter.cpp \
    qwt_picker.cpp \
    qwt_rect.cpp \
    qwt_round_scale_draw.cpp \
    qwt_scale_div.cpp \
    qwt_scale_draw.cpp \
    qwt_scale_map.cpp \
    qwt_spline.cpp \
    qwt_text_engine.cpp \
    qwt_text_label.cpp \
    qwt_text.cpp \
    qwt_event_pattern.cpp \
    qwt_picker_machine.cpp \
    qwt_scale_engine.cpp \
    qwt_symbol.cpp


contains(CONFIG, QwtPlot) {

    HEADERS += \
        qwt_curve_fitter.h \
        qwt_data.h \
        qwt_event_pattern.h \
        qwt_interval_data.h \
        qwt_legend.h \
        qwt_legend_item.h \
        qwt_plot.h \
        qwt_plot_curve.h \
        qwt_plot_dict.h \
        qwt_plot_grid.h \
        qwt_plot_item.h \
        qwt_plot_layout.h \
        qwt_plot_marker.h \
        qwt_plot_printfilter.h \
        qwt_plot_rasteritem.h \
        qwt_plot_spectrogram.h \
        qwt_plot_canvas.h \
        qwt_plot_panner.h \
        qwt_plot_picker.h \
        qwt_plot_zoomer.h \
        qwt_plot_magnifier.h \
        qwt_raster_data.h \
        qwt_scale_widget.h

    SOURCES += \
        qwt_curve_fitter.cpp \
        qwt_data.cpp \
        qwt_interval_data.cpp \
        qwt_legend.cpp \
        qwt_legend_item.cpp \
        qwt_plot.cpp \
        qwt_plot_print.cpp \
        qwt_plot_xml.cpp \
        qwt_plot_axis.cpp \
        qwt_plot_curve.cpp \
        qwt_plot_dict.cpp \
        qwt_plot_grid.cpp \
        qwt_plot_item.cpp \
        qwt_plot_spectrogram.cpp \
        qwt_plot_marker.cpp \
        qwt_plot_layout.cpp \
        qwt_plot_printfilter.cpp \
        qwt_plot_canvas.cpp \
        qwt_plot_panner.cpp \
        qwt_plot_rasteritem.cpp \
        qwt_plot_picker.cpp \
        qwt_plot_zoomer.cpp \
        qwt_plot_magnifier.cpp \
        qwt_raster_data.cpp \
        qwt_scale_widget.cpp
}


contains( TEMPLATE, lib ) {
    DESTDIR = $$GSTLAPPLI_HOME/lib/$$CUR_PLATFORM
    OBJECTS_DIR = $$GSTLAPPLI_HOME/lib/$$CUR_PLATFORM/obj/
}
contains( TEMPLATE, app ) {
    DESTDIR += $$GSTLAPPLI_HOME/bin/$$CUR_PLATFORM
    OBJECTS_DIR = $$GSTLAPPLI_HOME/bin/$$CUR_PLATFORM/obj/
}

include( $$GSTLAPPLI_HOME/config.qmake )

exists( MMakefile ) {
    include( MMakefile )
}
