TEMPLATE = lib
DEPENDPATH += . \
    grid_model
INCLUDEPATH += . \
    grid_model

HEADERS += log_data_grid.h \
           common.h \
           maskedgridcursor.h \
           library_grid_init.h \
           mgrid_neighborhood.h \
           cartesian_grid.h \
           combined_neighborhood.h \
           cross_variog_computer.h \
           geostat_grid.h \
           geovalue.h \
           grid_property.h \
           grid_categorical_property.h \
           grid_weight_property.h \
           grid_property_set.h \
           grid_property_manager.h \
           grid_region.h \
           grid_region_manager.h \
           grid_region_temp_selector.h \
           grid_topology.h \
           gval_iterator.h \
           gstl_kdtree2.h \
           neighborhood.h \
           point_set.h \
           point_set_neighborhood.h \
           property_copier.h \
           reduced_grid.h \
           rgrid.h \
           rgrid_geometry.h \
           rgrid_gval_accessor.h \
           rgrid_iterator.h \
           rgrid_neighborhood.h \
           search_filters.h \
           sgrid_cursor.h \
           strati_grid.h \
           superblock.h \
           distribution_utilities.h \
           grid_downscaler.h \
           structured_grid.h \
           coordinate_mapper.h \
           property_transformer.h \
           grid_filter.h \
           utilities.h

SOURCES += log_data_grid.cpp \
           library_grid_init.cpp \
           mgrid_neighborhood.cpp \
           cartesian_grid.cpp \
           combined_neighborhood.cpp \
           cross_variog_computer.cpp \
           geostat_grid.cpp \
           geovalue.cpp \
           grid_property.cpp \
           grid_categorical_property.cpp \
           grid_property_set.cpp \
           grid_property_manager.cpp \
           grid_region_manager.cpp \
           gstl_kdtree2.cpp \
           neighborhood.cpp \
           point_set.cpp \
           point_set_neighborhood.cpp \
           property_copier.cpp \
           reduced_grid.cpp \
           rgrid.cpp \
           rgrid_geometry.cpp \
           rgrid_gval_accessor.cpp \
           rgrid_neighborhood.cpp \
           superblock.cpp \
           distribution_utilities.cpp \
           grid_weigth_property.cpp \
           grid_downscaler.cpp \
           structured_grid.cpp \
           coordinate_mapper.cpp \
           property_transformer.cpp \
           grid_filter.cpp \
           utilities.cpp

TARGET = ar2gems_grid

QT += xml
CONFIG += plugin

INCLUDEPATH += $(QTDIR)/tools/designer/interfaces
contains( TEMPLATE, lib ) {
    DESTDIR = $$GSTLAPPLI_HOME/lib/$$CUR_PLATFORM
    OBJECTS_DIR = $$GSTLAPPLI_HOME/lib/$$CUR_PLATFORM/obj/grid
}
contains( TEMPLATE, app ) {
    DESTDIR += $$GSTLAPPLI_HOME/bin/$$CUR_PLATFORM
    OBJECTS_DIR = $$GSTLAPPLI_HOME/bin/$$CUR_PLATFORM/obj/grid
}
include( $$GSTLAPPLI_HOME/config.qmake )
exists( MMakefile ):include( MMakefile )
