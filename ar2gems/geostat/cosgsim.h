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
** This file is part of the "geostat" module of the Geostatistical Earth
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
**********************************************************************/

#ifndef __GSTLAPPLI_GEOSTAT_ALGO_COSGSIM_H__ 
#define __GSTLAPPLI_GEOSTAT_ALGO_COSGSIM_H__ 
 
 
#include <geostat/common.h>
#include <geostat/geostat_algo.h> 
#include <geostat/utilities.h> 
#include <grid/neighborhood.h> 
 
#include <GsTL/utils/smartptr.h> 
#include <GsTL/geometry/covariance.h> 
#include <GsTL/kriging/covariance_set.h> 
#include <GsTL/cdf/non_param_cdf.h> 
#include <GsTL/kriging/cokriging_combiner.h> 
#include <GsTL/kriging/cokriging_constraints.h> 
#include <grid/grid_region_temp_selector.h> 
#include <string> 
 

class Geostat_grid;
class Neighborhood; 
class Parameters_handler; 
class Error_messages_handler; 
//class Grid_initializer; 
class Property_copier;


class GEOSTAT_DECL Cosgsim : public Geostat_algo { 
 public: 
  Cosgsim(); 
  ~Cosgsim(); 
   
  virtual bool initialize( const Parameters_handler* parameters, 
			   Error_messages_handler* errors ); 
  virtual int execute( GsTL_project* proj=0 ); 
  virtual std::string name() const { return "cosgsim"; } 
 
 public: 
  static Named_interface* create_new_interface( std::string& ); 
 
 
 protected: 
  typedef Geostat_grid::location_type Location; 
  typedef Covariance_set< Covariance<Location> > CovarianceSet; 
 
  typedef GsTL_neighborhood< SmartPtr<Neighborhood> > NeighborhoodHandle; 
  typedef std::vector< NeighborhoodHandle >::const_iterator NeighIterator; 
  typedef std::vector<double>::const_iterator WeightIterator; 
  typedef CoKriging_combiner< WeightIterator, NeighIterator > CoKrigingCombiner; 
  typedef CoKriging_constraints< NeighIterator, Geovalue > KrigingConstraints;

  
 protected: 
  Geostat_grid* simul_grid_; 
  MultiRealization_property* multireal_property_; 
   
  Geostat_grid* prim_harddata_grid_;  
  Geostat_grid* sec_harddata_grid_;
  Grid_continuous_property* primary_variable_;
  Grid_continuous_property* secondary_variable_;
  GsTLGridPropertyGroup* secondary_variable_group_;

  //Grid_initializer* initializer_; 
  SmartPtr<Property_copier> property_copier_;

  std::vector< NeighborhoodHandle > neighborhood_vector_; 
 
  long int seed_; 
  int nb_of_realizations_; 
 
  CovarianceSet* covar_; 
  CoKrigingCombiner* combiner_; 
  KrigingConstraints* kconstraints_; 
 
  bool transform_primary_variable_; 
  bool transform_secondary_variable_; 
  //geostat_utils::NonParametricCdfType original_cdf_;
  SmartPtr<Continuous_distribution> original_cdf_;
  SmartPtr<Continuous_distribution> sec_distribution_;
  Neighborhood* variance_record_neighborhood_;
  
  bool clean_primary_var_, clean_secondary_var_;

  Temporary_gridRegion_Selector grid_region_;
  Temporary_gridRegion_Selector prim_hd_grid_region_;
  Temporary_gridRegion_Selector sec_hd_grid_region_;

 protected:

  void clean( Grid_continuous_property* prop = 0 ); 
}; 
 
 
 
 
 
 
 
#endif 
