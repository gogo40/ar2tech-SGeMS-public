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
** Author: Alexandre Boucher
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

#ifndef __GSTLAPPLI_GRID_REGION_H__ 
#define __GSTLAPPLI_GRID_REGION_H__ 
 
#include <grid/common.h>
#include <utils/gstl_types.h> 
#include <utils/gstl_messages.h> 
#include <utils/gstl_object_item.h>
 
#include <string> 
#include <fstream> 
#include <vector>



/** A Grid_region contains 3 types of information: 
 *    \li one flag to indicate if the node contains a data value 
 *    \li a data value 
 *    \li one flag to indicate if the data value is a "hard data" 
 */ 
class GRID_DECL Grid_region : public GsTL_object_item{
 
 public: 
  typedef bool region_type; 
  typedef std::vector<region_type> region;

  typedef std::vector<region_type>::iterator iterator;
  typedef std::vector<region_type>::const_iterator const_iterator;
 
 public: 
  Grid_region( GsTLInt size, std::string name, 
    region_type default_value = false ):name_(name) {
      accessor_.assign(size,default_value);
  }
  ~Grid_region(){}; 
     
// Direct acces to the region
  inline std::vector<region_type>& data();
  inline const std::vector<region_type>& data() const; 

  /** Tells whether the ith element of the region array is informed,
  * ie contains a value.
  */
  inline bool is_inside_region( GsTLInt i ) const ;

  /** Changes the value of the ith element to \a val.
  */
  inline void set_region_value( region_type val, GsTLInt id );


  /** Returns the total number of values in the region array
  */
  inline GsTLInt size() const {return accessor_.size();} 

  /** Returns the total number of active values in the region array
  */
  inline GsTLInt active_size() const {
    region::const_iterator it = accessor_.begin();
    int n_active = 0;
    for( ; it != accessor_.end(); ++it) {
      if(*it) n_active++;
    }
    return n_active;
  }
 
  /** Returns the name of the region
  */
  inline std::string name() const { return name_; } 
  inline void rename( const std::string& new_name ) { name_ = new_name; } 


  iterator begin( ) { return accessor_.begin(); } 
  iterator end() { return accessor_.end(); } 
  const_iterator begin() const { return accessor_.begin(); }
  const_iterator end() const { return accessor_.end(); }



  // GsTL_object_item implementation
    virtual QString item_type() const{return "Region";}
    virtual QString item_name() const{return name_.c_str();}
    virtual GsTL_object_item *child(int row){return 0;};
    virtual int childCount() const {return 0;};
    virtual int columnCount() const {return 2;};
    virtual QVariant item_data(int column) const{
    	if(column == 0) return QString(name_.c_str());
    	else if (column == 1) return item_type();

    	else return QVariant();
    }


 protected: 
  std::string name_; 
  region accessor_;

   
 private: 
  Grid_region( const Grid_region& rhs ); 
  Grid_region& operator = ( const Grid_region& rhs ); 

 
}; 
 
inline bool Grid_region::is_inside_region( GsTLInt i ) const {
  if( i<0 || i >= accessor_.size() ) return false;
  return accessor_[i];
} 

/** Changes the value of the ith element to \a val.
*/
inline void Grid_region::set_region_value( region_type val, GsTLInt id ){
  appli_assert(id>=0 && id<accessor_.size());
  accessor_[id] = val;
}

inline 
std::vector<Grid_region::region_type>& Grid_region::data() {
  return accessor_;
} 

inline 
const std::vector<Grid_region::region_type>& Grid_region::data() const{
  return accessor_;
} 

#endif
