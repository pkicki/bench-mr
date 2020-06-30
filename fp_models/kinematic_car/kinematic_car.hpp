#ifndef _KINEMATIC_CAR_
#define _KINEMATIC_CAR_

#include <ompl/base/spaces/SE2StateSpace.h>
#include <ompl/control/ODESolver.h>
#include <ompl/control/SpaceInformation.h>
#include <ompl/control/spaces/RealVectorControlSpace.h>

namespace oc = ompl::control;
namespace ob = ompl::base;

namespace KinematicCar {
// as in
// https://ompl.kavrakilab.org/RigidBodyPlanningWithODESolverAndControls_8cpp_source.html
void kinematicCarODE(const oc::ODESolver::StateType& q,
                     const oc::Control* control,
                     oc::ODESolver::StateType& qdot) {
  double* u = control->as<oc::RealVectorControlSpace::ControlType>()->values;
  double heading = q[2];
  double car_length = 0.5;
  qdot.resize(q.size(), 0);

  // Dynamics
  qdot[0] = u[0] * cos(heading);
  qdot[1] = u[0] * sin(heading);
  qdot[2] = u[0] * tan(u[1]) / car_length;
}

// as in
// https://ompl.kavrakilab.org/RigidBodyPlanningWithODESolverAndControls_8cpp_source.html
void kinematicCarPostIntegration(const ob::State* /*state*/,
                                 const oc::Control* /*control*/,
                                 const double /*duration*/, ob::State* result) {
  // Normalize orientation between 0 and 2*pi
  ob::SO2StateSpace SO2;
  SO2.enforceBounds(result->as<ob::SE2StateSpace::StateType>()
                        ->as<ob::SO2StateSpace::StateType>(1));
}

}  // namespace KinematicCar
#endif /* _KINEMATIC_CAR_ */