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




#ifndef __GSTLAPPLI_CLUSTERING_FROM_CENTROID_H__ 
#define __GSTLAPPLI_CLUSTERING_FROM_CENTROID_H__ 
 
#include <grid/grid_property.h>
#include <grid/grid_region.h>
#include <grid/geostat_grid.h>
#include <geostat/common.h>
#include <geostat/geostat_algo.h> 
#include <geostat/utilities.h> 
#include <geostat/parameters_handler.h>
#include <utils/error_messages_handler.h>
#include <actions/action.h>

/*  Need to move the algorithm_action from Action to Geostat
class GEOSTAT_DECL Clustering_from_centroids_action : public Action { 

 public: 
  static Named_interface* create_new_interface( std::string& );

public:
  Clustering_from_centroids_action(void);
  virtual ~Clustering_from_centroids_action(void);

  virtual bool init( const Parameters_handler* parameters, 
			   Error_messages_handler* errors ); 
  virtual int execute( GsTL_project* proj=0 ); 
  virtual std::string name() const { return "ClusterFromCentroids"; } 

protected :

};
*/
class GEOSTAT_DECL Clustering_from_centroids : public Geostat_algo { 

 public: 
  static Named_interface* create_new_interface( std::string& );

public:
  Clustering_from_centroids(void);
  virtual ~Clustering_from_centroids(void);

  virtual bool initialize( const Parameters_handler* parameters, 
			   Error_messages_handler* errors ); 
  virtual int execute( GsTL_project* proj=0 ); 
  virtual std::string name() const { return "ClusteringFromCentroids"; } 

protected :

  std::string infile_name_;
  std::string clusters_prop_name_;
  std::vector<const Grid_continuous_property*> props_;
  const Grid_region* region_;
  Geostat_grid* grid_;
  std::vector<std::vector<float> > centroids_;

};

#endif
