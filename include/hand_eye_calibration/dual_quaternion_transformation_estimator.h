 
 /******************************************************************************
*
* Author:
* Stefan Isler, islerstefan@bluewin.ch, ETH Zürich 2014
*
*
* Class to estimate the transformation from a robot link (hand) to a camera 
* sensor frame (eye) [Hand-Eye-Calibration] using the method described in
* "Hand-Eye Calibration Using Dual Quaternions" by Konstantinos Daniilidis.
* It features a simple command line interface, the estimated transformations
* are printed to the command line as well.
* 
* subscribes:	- /hec/eye_position [geometry_msgs/Pose]: transformation grid->camera [rotation R_CG, position of origin of G in C
* 		- /hec/hand_position [geometry_msgs/Pose]: transformation hand->base  [rotation R_BH, position of origin of H in B
* 
* 
* Released under the GNU Lesser General Public License v3 (LGPLv3), see www.gnu.org
*
******************************************************************************/
 
 
/* Copyright (c) 2014, 2015, Stefan Isler, islerstefan@bluewin.ch
*
This file is part of hand_eye_calibration, a ROS package for hand eye calibration,

hand_eye_calibration is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
hand_eye_calibration is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU Lesser General Public License for more details.
You should have received a copy of the GNU Lesser General Public License
along with hand_eye_calibration. If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include <iostream>

#include "hand_eye_calibration/transformation_estimation_method.h"


class DaniilidisDualQuaternionEstimation:public TransformationEstimator::EstimationMethod
{
public:
  class DaniilidisNewPtrConstructor;
  
  /** Returns the name of the method */
  virtual std::string estimationMethod();
  
  /** calculates the transformation estimate
   * @param _pose_data data on which the estimation will be calculated
   * @param _suppressWarnings whether warnings are displayed or not
   * @return EstimationData with estimated transformation but without error estimates
   */
  virtual TransformationEstimator::EstimationData calculateTransformation( std::vector<TransformationEstimator::PoseData>& _pose_data, bool _suppressWarnings=false );
  
  /** alias function to calculate the transformation estimate
   * @param _pose_data data on which the estimation will be calculated
   * @param _suppressWarnings whether warnings are displayed or not
   * @throws std::runtime_error If the given pose_data is insufficient for hand-eye estimation
   * @return EstimationData without error estimates
   */
  virtual TransformationEstimator::EstimationData operator()( std::vector<TransformationEstimator::PoseData>& _pose_data, bool _suppressWarnings=false );
  
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW
private:
  static std::string g_method_name_;
};

extern DaniilidisDualQuaternionEstimation::DaniilidisNewPtrConstructor daniilidis_1998; // convenience object for new object

class DaniilidisDualQuaternionEstimation::DaniilidisNewPtrConstructor
{
public:
  operator boost::shared_ptr<TransformationEstimator::EstimationMethod>()
  {
    return boost::shared_ptr<TransformationEstimator::EstimationMethod>( new DaniilidisDualQuaternionEstimation() );
  }
};