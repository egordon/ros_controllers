/*********************************************************************
 * Software License Agreement (BSD License)
 *
 *  Copyright (c) 2008, Willow Garage, Inc.
 *  Copyright (c) 2012, hiDOF, Inc.
 *  Copyright (c) 2013, PAL Robotics, S.L.
 *  Copyright (c) 2014, Fraunhofer IPA
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of the Willow Garage nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *********************************************************************/

#include <position_controllers/joint_group_position_controller.h>
#include <pluginlib/class_list_macros.hpp>

template <class T>
void forward_command_controller::ForwardJointGroupCommandController<T>::starting(const ros::Time& time)
{
  // Start controller with current joint positions
  std::vector<double> & commands = *commands_buffer_.readFromRT();
  for(unsigned int i=0; i<joints_.size(); i++)
  {
    commands[i]=joints_[i].getPosition();
    default_commands_[i] = commands[i];
  }
}

template <class T>
void forward_command_controller::ForwardJointGroupCommandController<T>::updateDefaultCommand()
{
  // Set default to current position
  for(unsigned int i=0; i<joints_.size(); i++)
  {
    default_commands_[i] = joints_[i].getPosition();
  }
}

template <class T>
void forward_command_controller::ForwardJointGroupCommandController<T>::goalCB(GoalHandle gh)
{
  // Set as position command
  setGoal(gh, gh.getGoal()->command.positions);
}

PLUGINLIB_EXPORT_CLASS(position_controllers::JointGroupPositionController,controller_interface::ControllerBase)
