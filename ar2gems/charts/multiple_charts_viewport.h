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



#ifndef __MULTIPLE_CHARTS_VIEWPORT__
#define __MULTIPLE_CHARTS_VIEWPORT__

#include <charts/common.h>

#include <vector>

namespace charts {

  struct viewport{
  public:
    viewport(double _xmin, double _ymin, double _xmax, double _ymax) : xmin(_xmin), ymin(_ymin), xmax(_xmax), ymax(_ymax){}

    double xmin;
    double ymin;
    double xmax;
    double ymax;

  };

}

std::vector<charts::viewport> CHARTS_DECL get_charts_viewport(int number_of_charts);


#endif