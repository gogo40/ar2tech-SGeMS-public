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
** This file is part of the "grid" module of the Geostatistical Earth
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

#ifndef __GSTLAPPLI_GRID_PROPERTY_COPIER_H__
#define __GSTLAPPLI_GRID_PROPERTY_COPIER_H__


#include <grid/common.h>
#include <grid/grid_property.h>
#include <utils/named_interface.h> 
#include <utils/manager.h>
#include <utils/gstl_types.h>
 
#include <vector>
#include <utility>
#include <string>

class Geostat_grid; 
class Cartesian_grid;
class Point_set; 



/** A Property_copier allows to copy a property from a geostat_grid
* to another one. 
* Its behavior is controlled by 4 parameters:
* - from_scratch: if false, and if the Property_copier has already transfered
*   properties between the same two grids, it capitalize on the previous 
*   computations to speed up the transfer. from_scratch is true by default.
* - overwrite: if true, the current values of the client property can be 
*   overwritten. default: false.
* - mark_as_hard: should a transfered value be flagged as hard data. 
*   default: false.   
* - undo_enabled: keep track of what is being done, so that the property 
*   transfer can be undone. default: false.
*/
class GRID_DECL Property_copier : public Named_interface {
public:
  Property_copier();
  virtual ~Property_copier() {}

  virtual bool copy( const Geostat_grid* server, 
                     const Grid_continuous_property* server_prop,
                     Geostat_grid* client, Grid_continuous_property* client_prop ) = 0;

  virtual bool undo_copy() = 0;

  bool starts_from_scratch() const { return from_scratch_; }
  void starts_from_scratch( bool on ) { from_scratch_ = on; }

  bool does_overwrite() const { return overwrite_; }
  void does_overwrite( bool on ) { overwrite_ = on; }
  
  bool marks_as_hard() const { return mark_as_hard_; }
  void marks_as_hard( bool on ) { mark_as_hard_ = on; }

  bool is_undo_enabled() const { return undo_enabled_; }
  void set_undo_enabled( bool on ) { undo_enabled_ = on; }

  void copy_categorical_definition(const Grid_continuous_property* server_prop,
                                   Grid_continuous_property* client_prop);

protected:

  bool from_scratch_;
  bool overwrite_;
  bool mark_as_hard_;
  bool undo_enabled_;
};



//=====================================

class GRID_DECL Property_copier_factory {
public:
  static SmartPtr<Property_copier> get_copier( const Geostat_grid* server, 
                                               const Geostat_grid* client );
  
  static bool add_method( const std::string& server_type, 
                          const std::string& client_type,
                          CallBackType method );

private:
  static std::string create_type_name( const std::string& server_type, 
                                       const std::string& client_type);

};

//TL modified 
class GRID_DECL Mask_to_mask_copier : public Property_copier 
{
public:
	static Named_interface* create_new_interface( std::string& ) {
		return new Mask_to_mask_copier;
	}

	Mask_to_mask_copier();
	
	virtual bool copy( const Geostat_grid* server, 
		const Grid_continuous_property* server_prop,
		Geostat_grid* client, 
		Grid_continuous_property* client_prop );

	virtual bool undo_copy();
protected:
	const Geostat_grid* server_;
	const Geostat_grid* client_;
	const Grid_continuous_property* server_prop_;

	std::vector< std::pair<GsTLInt,GsTLInt> > last_assignement_; 

	Grid_continuous_property* client_property_;
	std::vector< std::pair< GsTLInt, Grid_continuous_property::property_type > > backup_;
    bool unset_harddata_flag_;

};

class GRID_DECL Pset_to_mask_copier : public Property_copier 
{
public:
  static Named_interface* create_new_interface( std::string& ) {
    return new Pset_to_mask_copier;
  }

  Pset_to_mask_copier();

  virtual bool copy( const Geostat_grid* server, 
                     const Grid_continuous_property* server_prop,
                     Geostat_grid* client, 
                     Grid_continuous_property* client_prop );

  virtual bool undo_copy();


protected:
  const Geostat_grid* server_;
  const Geostat_grid* client_;
  const Grid_continuous_property* server_prop_;
  Grid_continuous_property* client_property_;

  //Allow to keep track which node-id was assigned where
  // useful for the undo
  std::map<int,int> index_client_to_source_;
  std::map<int,float> original_client_value_;

};

/*
class GRID_DECL Property_copier_factory {
public:    
  static Property_copier_factory_impl* instance(); 
 
 
private: 
  static Property_copier_factory_impl* instance_; 
 
  Property_copier_factory(); 
  Property_copier_factory(const Property_copier_factory&); 
  Property_copier_factory& operator=(const Property_copier_factory&); 
   
};
*/

//=====================================

class GRID_DECL Pset_to_cgrid_copier : public Property_copier {
public:
  static Named_interface* create_new_interface( std::string& ) {
    return new Pset_to_cgrid_copier;
  }

  Pset_to_cgrid_copier();

  virtual bool copy( const Geostat_grid* server, 
                     const Grid_continuous_property* server_prop,
                     Geostat_grid* client, 
                     Grid_continuous_property* client_prop );

  virtual bool undo_copy();


protected:
  const Geostat_grid* server_;
  const Geostat_grid* client_;
  const Grid_continuous_property* server_prop_;

  std::vector< std::pair<GsTLInt,GsTLInt> > last_assignement_; 

  Grid_continuous_property* client_property_;
  std::vector< std::pair< GsTLInt, Grid_continuous_property::property_type > > backup_;
  bool unset_harddata_flag_;

};



//=====================================

class GRID_DECL Cgrid_to_cgrid_copier : public Property_copier {
public:
  static Named_interface* create_new_interface( std::string& ) {
    return new Cgrid_to_cgrid_copier;
  }

  Cgrid_to_cgrid_copier();

  virtual bool copy( const Geostat_grid* server, 
                     const Grid_continuous_property* server_prop,
                     Geostat_grid* client, 
                     Grid_continuous_property* client_prop );

  virtual bool undo_copy();


protected:
  bool are_identical_grids( const Cartesian_grid* grid1, 
                            const Cartesian_grid* grid2 );

protected:
  const Geostat_grid* server_;
  const Geostat_grid* client_;
  const Grid_continuous_property* server_prop_;

  std::vector< std::pair<GsTLInt,GsTLInt> > last_assignement_; 

  Grid_continuous_property* client_property_;
  std::vector< std::pair< GsTLInt, Grid_continuous_property::property_type > > backup_;
  bool unset_harddata_flag_;

};


/*=====================================
This is a quick implementation, it only allows to copy on
the same grid, and do not implement the undo function.
*/

class GRID_DECL Pset_to_pset_copier : public Property_copier {
public:
  static Named_interface* create_new_interface( std::string& ) {
    return new Pset_to_pset_copier;
  }

  Pset_to_pset_copier();

  virtual bool copy( const Geostat_grid* server, 
                     const Grid_continuous_property* server_prop,
                     Geostat_grid* client, 
                     Grid_continuous_property* client_prop );

  virtual bool undo_copy(){return false;}


protected:
  bool are_identical_grids( const Point_set* grid1, 
			const Point_set* grid2 ) {
		  return grid1 == grid2; }

protected:
  const Geostat_grid* server_;
  const Geostat_grid* client_;
  const Grid_continuous_property* server_prop_;

  std::vector< std::pair<GsTLInt,GsTLInt> > last_assignement_; 

  Grid_continuous_property* client_property_;
  std::vector< std::pair< GsTLInt, Grid_continuous_property::property_type > > backup_;
  bool unset_harddata_flag_;

};



class GRID_DECL Rgrid_to_pset_copier : public Property_copier {
public:
  static Named_interface* create_new_interface( std::string& ) {
    return new Rgrid_to_pset_copier;
  }

  Rgrid_to_pset_copier(){}

  virtual bool copy( const Geostat_grid* server, 
                     const Grid_continuous_property* server_prop,
                     Geostat_grid* client, 
                     Grid_continuous_property* client_prop );

  virtual bool undo_copy(){return false;}


protected:


};


class GRID_DECL Pset_to_structured_grid_copier : public Property_copier {
public:
  static Named_interface* create_new_interface( std::string& ) {
    return new Pset_to_structured_grid_copier;
  }

  Pset_to_structured_grid_copier(){}

  virtual bool copy( const Geostat_grid* server, 
                     const Grid_continuous_property* server_prop,
                     Geostat_grid* client, 
                     Grid_continuous_property* client_prop );

  virtual bool undo_copy();


private :
  const Geostat_grid* server_;
  const Geostat_grid* client_;
  const Grid_continuous_property* server_prop_;
  Grid_continuous_property* client_property_;

  //Allow to keep track which node-id was assigned where
  // useful for the undo
  std::map<int,int> index_client_to_source_;
  std::map<int,float> original_client_value_;

};

#endif
