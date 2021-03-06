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

#ifndef __GSTLAPPLI_GEOSTAT_SISIM_H__ 
#define __GSTLAPPLI_GEOSTAT_SISIM_H__ 
 
#include <geostat/common.h>
#include <geostat/geostat_algo.h> 
#include <grid/geostat_grid.h> 
#include <grid/neighborhood.h> 
#include <grid/property_copier.h>

#include <GsTL/geometry/covariance.h> 
#include <GsTL/cdf_estimator/indicator_cdf_estimator.h> 
#include <GsTL/cdf_estimator/soft_indicator_cdf_estimator.h>
#include <GsTL/utils/smartptr.h> 
#include <grid/grid_region_temp_selector.h>  
#include <string> 
#include <vector> 
 
 
//class Grid_initializer; 
template<class T> class Non_parametric_cdf; 

class Progress_notifier;


 
 
class GEOSTAT_DECL Sisim : public Geostat_algo { 
 public: 
  Sisim(); 
  ~Sisim(); 
   
  virtual bool initialize( const Parameters_handler* parameters, 
			   Error_messages_handler* errors ); 
  virtual int execute( GsTL_project* proj=0 ); 
  virtual std::string name() const { return "sisim"; } 
 
 public: 
  static Named_interface* create_new_interface( std::string& ); 
 
 
 protected: 
  typedef Geostat_grid::location_type Location; 
  typedef std::vector<double>::const_iterator weight_iterator; 
 
  Geostat_grid* simul_grid_; 
  MultiRealization_property* multireal_property_; 
   
  long int seed_; 
  int nb_of_realizations_; 
  bool is_categorical_;
 
  Geostat_grid* harddata_grid_;   
  Grid_continuous_property* harddata_property_; 
  //Grid_initializer* initializer_; 
  SmartPtr<Property_copier> property_copier_;

  bool is_data_coded_;
  Geostat_grid* coded_grid_;
  

  Non_parametric_cdf<float>* ccdf_; 
  Non_parametric_cdf<float>* marginal_; 
    
  bool do_median_ik_; 
 
  typedef std::vector< Covariance<Location> > CovarianceVector; 
  typedef std::vector< Covariance<Location> >::const_iterator CovarianceIterator; 
  CovarianceVector covar_vector_; 
 
  // For median IK   
  SmartPtr<Neighborhood> neighborhood_; 
  
  // For full IK 
  typedef GsTL_neighborhood< SmartPtr<Neighborhood> > NeighborhoodHandle; 
  std::vector< NeighborhoodHandle > neighborhoods_vector_; 
   
  typedef Indicator_cdf_estimator< CovarianceIterator, 
                                   Indicator<double> > CdfEstimator; 
  typedef Soft_indicator_cdf_estimator< CovarianceIterator, 
                                   Indicator<double> > CdfSoftEstimator;
  //CdfEstimator* cdf_estimator_;
  CdfSoftEstimator* cdf_estimator_;//cdf_soft_estimator_;
 
  Temporary_gridRegion_Selector grid_region_;
  Temporary_gridRegion_Selector hd_grid_region_;
  Temporary_gridRegion_Selector coded_grid_region_;

 protected: 
  int median_ik( Progress_notifier* progress_notifier ); 
  int full_ik( Progress_notifier* progress_notifier ); 
}; 
 
 
#endif 
