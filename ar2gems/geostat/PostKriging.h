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
** Author: Alexndre Boucher
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
#ifndef __GSTLAPPLI_GEOSTAT_PLUGIN_POSTKRIGING_H__
#define __GSTLAPPLI_GEOSTAT_PLUGIN_POSTKRIGING_H__


#include <geostat/geostat_algo.h>
#include <GsTL/utils/smartptr.h>
#include <grid/point_set.h>
#include <grid/rgrid.h>
#include <grid/neighborhood.h>
#include <math/gstlpoint.h>

#include <geostat/parameters_handler.h>
#include <utils/error_messages_handler.h>
#include <GsTL/cdf/cdf_basics.h>
#include <GsTL/cdf/non_param_cdf.h>
#include <GsTL/cdf/gaussian_cdf.h>

class Geostat_grid;
class GsTL_project;
//class Cdf;

typedef std::vector< Grid_continuous_property* > prop_vecT;

class  PostKriging : public Geostat_algo {
 public:
  static Named_interface* create_new_interface(std::string&);

 public:
	 PostKriging();
	virtual bool initialize( const Parameters_handler* parameters,
			   Error_messages_handler* errors );

  /** Runs the algorithm. 
   * @return 0 if the run was successful
   */
  
	virtual int execute( GsTL_project* proj=0);
  /** Tells the name of the algorithm
   */
	virtual std::string name() const { return "PostKriging"; }
   
  private:

	Geostat_grid* grid_;
	prop_vecT props;
	std::vector< float > thresholds_;

	Cdf<float>* cdf_;
	Non_param_cdf<>* non_param_cdf_;
	Gaussian_cdf* gaussian_cdf_;

	bool is_non_param_cdf_;
	bool mean_;
	bool iqr_;
	bool cond_var_;
	bool prob_above_;
	bool prob_below_;
	bool quantile_;

	Grid_continuous_property*  mean_prop_;
	Grid_continuous_property*  iqr_prop_;
	Grid_continuous_property*  cond_var_prop_;
	std::vector<Grid_continuous_property*>  quantile_props_;
	std::vector<Grid_continuous_property*>  prob_above_props_;
	std::vector<Grid_continuous_property*>  prob_below_props_;

	std::vector<float> quantile_vals_;
	std::vector<float> prob_above_vals_;
	std::vector<float> prob_below_vals_;

	void initialize_operation(std::vector<Grid_continuous_property*>& props, std::vector<float>& vals,
		Error_messages_handler* errors, const Parameters_handler* parameters, std::string base_name);

	void initialize_operation(Grid_continuous_property*& props,Error_messages_handler* errors, 
		const Parameters_handler* parameters, std::string base_name);

  void check_input_string(Error_messages_handler* errors, 
    const Parameters_handler* parameters, std::string input);

  void check_input_string(Error_messages_handler* errors, 
    const Parameters_handler* parameters, std::string input,float min, float max );

};

#endif

