#include "multi_grid_path.h"


Multi_grid_path::iterator
Multi_grid_path::begin() const
{
  return Multi_grid_path::iterator( grid_, prop_, 
	                  		       0, grid_path_.size(),  
		                           TabularMapIndex(&grid_path_) );
}

Multi_grid_path::iterator
Multi_grid_path::end() const
{
  return Multi_grid_path::iterator( grid_, prop_, 
	                  		       grid_path_.size(), grid_path_.size(),  
		                           TabularMapIndex(&grid_path_) );
}

GsTLInt 
Multi_grid_path::size() const
{
  return grid_path_.size();
}

GsTLInt 
Multi_grid_path::node_id( GsTLInt _path_index ) const
{
  return cursor_->node_id( grid_path_[_path_index] );
}

Geovalue 
Multi_grid_path::geovalue( GsTLInt _path_index ) const
{
  GsTLInt node_id = cursor_->node_id( grid_path_[_path_index] );
  return Geovalue(grid_, prop_, node_id);
}

void 
Multi_grid_path::multigrid_level_is(GsTLInt _multigrid_level)
{
  multigrid_level_ = _multigrid_level;
  cursor_->set_multigrid_level(multigrid_level_);

  // init random path for this multigrid_level
  grid_path_.clear();
  grid_path_.resize( cursor_->max_index() );
  for( int i = 0; i < int( grid_path_.size() ); i++ ) 
    grid_path_[i] = i;

  STL_generator gen;
  std::random_shuffle( grid_path_.begin(), grid_path_.end(), gen );
}

Multi_grid_path::Multi_grid_path(RGrid * _grid, Grid_continuous_property * _prop)
{
  if ( !_grid || !_prop ) return;
  this->grid_ = _grid;
  this->prop_ = _prop;
  this->cursor_ = new SGrid_cursor( *grid_->cursor() );
  multigrid_level_ = 1; // initially
  cursor_->set_multigrid_level(multigrid_level_);

  // init random path
  grid_path_.resize( cursor_->max_index() );
  for( int i = 0; i < int( grid_path_.size() ); i++ ) 
    grid_path_[i] = i;

  STL_generator gen;
  std::random_shuffle( grid_path_.begin(), grid_path_.end(), gen );
}

Multi_grid_path::~Multi_grid_path(void)
{
  this->grid_ = NULL;
  this->prop_ = NULL;
  delete this->cursor_;
}