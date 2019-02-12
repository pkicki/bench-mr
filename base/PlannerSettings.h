#pragma once

#include <chomp/Chomp.h>
#include <ompl/base/spaces/ReedsSheppStateSpace.h>

#include "Environment.h"

#include "steer_functions/Steering.h"


//#define DEBUG 1
#define STATS

namespace chomp {
enum ChompInitialization { STRAIGHT_LINE, THETA_STAR, THETA_STAR_X_CLEARING };
}

struct PlannerSettings {
 public:
  static Environment *environment;

  static int numberEdges;

  static double stateEqualityTolerance;


  static ompl::base::StateSpacePtr stateSpace;
  static ompl::base::SpaceInformationPtr spaceInfo;
  static ompl::base::OptimizationObjectivePtr objective;

  // HC/CC steer function settings
  static double ccKappa;
  static double ccSigma;

  /**
   * Distance between states sampled using the steer function for collision
   * detection, rendering and evaluation.
   */
  static double samplingResolution;

  static Steering::SteeringType steeringType;
  static void initializeSteering();

  static double CarTurningRadius;
  static double LinearSteeringDelta;

  static constexpr double PlanningTime{15.0};

  static bool VisualizeSmoothing1;
  static bool VisualizeSmoothing2;
  static bool VisualizeSmoothing3;
  static bool VisualizeSmoothing4;

  // GRIPS settings

  /*
   * Minimum distance to be maintained between two consecutive nodes.
   */
  static double gripsMinNodeDistance;
  /*
   * Gradient descent rate.
   */
  static double gripsEta;
  /*
   * Discount factor for gradient descent rate.
   */
  static double gripsEtaDiscount;

  /**
   * Number of gradient descent rounds.
   */
  static unsigned int gripsGradientDescentRounds;
  /**
   * Maximum number of pruning rounds after which the algorithm
   * should terminate.
   */
  static unsigned int gripsMaxPruningRounds;

  /**
   * Whether to estimate the orientation of the start and goal states for
   * planners that need them (e.g. SBPL).
   */
  static bool estimateTheta;

  // Smooth Theta* settings
  static bool gradientDescentOpenNodes;
  static bool annealedGradientDescentOpenNodes;
  static bool gradientDescentCurrent;
  static bool gradientDescentSuccessors;
  static double gradientDescentEta;
  static double gradientDescentEtaDiscount;
  static unsigned int gradientDescentRounds;
  static bool averageAngles;

  // SBPL settings
  static bool
      sbplSearchUntilFirstSolution;  // search until it finds a solution?
                                     // (even if allotted time is over)
  static double
      sbplInitialSolutionEps;  // >1, ignored by planners that don't have notion
                               // of eps, 1 means optimal search
  static double sbplFordwardVelocity;         // in meters/sec
  static double sbplTimeToTurn45DegsInPlace;  // in sec
  static char *sbplMotionPrimitiveFilename;
  // Tolerances are most likely ignored by SPBL at the moment
  static double sbplGoalToleranceX;
  static double sbplGoalToleranceY;
  static double sbplGoalToleranceTheta;
  static double
      sbplResolution;  // XXX Important: resolution must match resolution in
                       // motion primitive definition file
  static double sbplScaling;  // scale environment to accommodate extents of
                              // SBPL's motion primitives
  static unsigned int
      sbplNumThetaDirs;  // XXX Important: number of theta directions must match
                         // resolution in motion primitive definition file

  // CHOMP settings
  static unsigned int chompNodes;
  static double chompAlpha;
  static float chompEpsilon;  // obstacle importance
  static double chompGamma;
  static double chompErrorTolerance;
  static unsigned int chompMaxIterations;  // global == local iterations
  static chomp::ChompObjectiveType chompObjectiveType;
  static chomp::ChompInitialization chompInitialization;
};
