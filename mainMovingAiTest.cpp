//#define DEBUG 1 // TODO activate DEBUG in PlannerSettings.h

#include "base/PlannerSettings.h"

#include "metrics/PathLengthMetric.h"

#include "planners/OMPLPlanner.hpp"
#include "planners/chomp/Chomp.h"
#include "planners/sbpl/SbplPlanner.h"
#include "planners/thetastar/ThetaStar.h"

#include "utils/ScenarioLoader.h"

#include "gui/PathEvaluation.h"
#if QT_SUPPORT
#include "gui/QtVisualizer.h"
#endif

#include "PostSmoothing.h"

namespace og = ompl::geometric;

void printStats(const PathStatistics &stats) {
  std::cout << stats.planner << std::endl;
  std::cout << "\tPath length:   \t" << stats.pathLength << std::endl;
  std::cout << "\tMax curvature: \t" << stats.curvature << std::endl;
}

int main(int argc, char **argv) {
  settings.environment = Environment::createRandomCorridor(
      50, 50, 3,
      30,  // 1540486476); //1540445576); //1502484532); //1502407983);
      // //1502323408); //1502316103); //1502231684); //1502227898);
      // //1501893283); //1501892155);//1501089540); //1501089410
      // );//1500660612);// 1500551721);// 1500550472);
      (unsigned int)(time(nullptr) + 123));

  settings.steer.steering_type = Steering::STEER_TYPE_LINEAR;
  //    settings.CarTurningRadius = 1.5;
  settings.steer.initializeSteering();
  PathEvaluation::initialize();

#if QT_SUPPORT
  QtVisualizer::initialize();
#endif

  //    std::vector<Rectangle> obstacles;
  //    obstacles.emplace_back(Rectangle(10, 0, 15, 14));
  //    obstacles.emplace_back(Rectangle(26, 10, 31, 25));
  //    settings.environment =
  //    Environment::createFromObstacles(obstacles, 40, 25);
  //    settings.environment->setStart(Point(5, 3));
  //    settings.environment->setGoal(Point(36, 22));
  //    settings.environment = Environment::createRandom(50, 50, 0.1,
  //    1542671305);

  Log::instantiateRun();

  // create ScenarioLoader object

  if (argc < 2) {
    OMPL_ERROR(
        "Missing Parameter. Enter .scen file name after execute command.");
    return 1;
  }

  const std::string scene_name = argv[1];

  ScenarioLoader scenarioLoader;
  scenarioLoader.load(scene_name);

  unsigned int counter = 0;
  for (auto &scenario : scenarioLoader.scenarios()) {
    // create environment
    settings.environment =
        Environment::createFromMovingAiScenario(scenario);
#if QT_SUPPORT
    QtVisualizer::visualize(settings.environment, 0);
#endif
    PathStatistics thetaStarStats, rrtStarStats, gripsStats,
        smoothThetaStarStats, sbplStats, chompStats;

    std::vector<Point> gripsPath;
    std::vector<GNode> gripsTrajectory;

    auto info =
        nlohmann::json({{"plans", {}},
                        {"environment", settings.environment->asJSON()},
                        {"optimalDistance", scenario.optimal_length}});

    //        ChompPlanner chompPlanner;
    //        if (chompPlanner.run()) {
    //            std::vector<Point> path = chompPlanner.solutionPath();
    //            chompStats = PathEvaluation::evaluate(path, "CHOMP",
    //            Qt::darkCyan);
    //        }
    //        info["plans"]["chomp"] = {
    //                {"curvature", chompStats.curvature},
    //                {"pathLength", chompStats.pathLength},
    //                {"steps", std::nan("N/A")},
    //                {"time", chompPlanner.planningTime()},
    //                {"meanClearingDistance", chompStats.meanClearingDistance},
    //                {"medianClearingDistance",
    //                chompStats.medianClearingDistance},
    //                {"minClearingDistance", chompStats.minClearingDistance},
    //                {"maxClearingDistance", chompStats.maxClearingDistance},
    //                {"path", chompPlanner.solution().empty() ?
    //                Log::serializePath({}) :
    //                Log::serializePath(chompPlanner.solutionPath())},
    //                {"trajectory",
    //                Log::serializeTrajectory(chompPlanner.solution())}
    //        };

            auto *thetaStar = new ThetaStar;
            if (thetaStar->run()) {
//                std::vector<Point> path = thetaStar->solutionPath();
                thetaStarStats = PathEvaluation::evaluate(thetaStar->solution(), "Theta*");

//                std::vector<GNode> trajectory =
//                thetaStar->solution(); gripsTrajectory = trajectory;
//                PostSmoothing::smooth(gripsTrajectory, path);
//                gripsPath =
//                PlannerUtils::toSteeredTrajectoryPoints(gripsTrajectory);
//                gripsStats = PathEvaluation::evaluate(gripsPath, "GRIPS",
//                Qt::red);
            } else {
                OMPL_ERROR("Theta* couldn't find a solution.");
            }
            info["plans"]["thetaStar"] = {
                    {"curvature", thetaStarStats.curvature},
                    {"pathLength", thetaStarStats.pathLength},
                    {"steps", thetaStar->steps()},
                    {"time", thetaStar->planningTime()},
                    {"meanClearingDistance",
                    thetaStarStats.meanClearingDistance},
                    {"medianClearingDistance",
                    thetaStarStats.medianClearingDistance},
                    {"minClearingDistance",
                    thetaStarStats.minClearingDistance},
                    {"maxClearingDistance",
                    thetaStarStats.maxClearingDistance},
                    {"path", Log::serializePath(thetaStar->solutionPath())},
                    {"trajectory",
                    Log::serializeTrajectory(thetaStar->solution())}
            };
    //        info["plans"]["grips"] = {
    //                {"curvature", gripsStats.curvature},
    //                {"pathLength", gripsStats.pathLength},
    //                {"steps", thetaStar->steps()},
    //                {"time", PostSmoothing::smoothingTime +
    //                thetaStar->planningTime()},
    //                {"meanClearingDistance", gripsStats.meanClearingDistance},
    //                {"medianClearingDistance",
    //                gripsStats.medianClearingDistance},
    //                {"minClearingDistance", gripsStats.minClearingDistance},
    //                {"maxClearingDistance", gripsStats.maxClearingDistance},
    //                {"path", Log::serializePath(gripsPath)},
    //                {"trajectory", Log::serializeTrajectory(gripsTrajectory)}
    //        };
    //        delete thetaStar;
    //
//            auto *rrtStar = new RRTstarPlanner;
//            if (rrtStar->run()) {
//                rrtStarStats = PathEvaluation::evaluate(rrtStar->solution(), "RRT*");
//#if QT_SUPPORT
//                rrtStarStats.color = Qt::red;
//#endif
//            } else {
//                OMPL_ERROR("RRT* couldn't find a solution.");
//            }
//            info["plans"]["rrtStar"] = {
//                    {"curvature", rrtStarStats.curvature},
//                    {"pathLength", rrtStarStats.pathLength},
//                    {"steps", std::nan("N/A")},
//                    {"time", rrtStar->planningTime()},
//                    {"meanClearingDistance",
//                    rrtStarStats.meanClearingDistance},
//                    {"medianClearingDistance",
//                    rrtStarStats.medianClearingDistance},
//                    {"minClearingDistance", rrtStarStats.minClearingDistance},
//                    {"maxClearingDistance", rrtStarStats.maxClearingDistance},
//                    {"path", Log::serializePath(rrtStar->solutionPath())},
//                    {"trajectory",
//                    Log::serializeTrajectory(rrtStar->solution())}
//            };
//            delete rrtStar;

    auto *sbplPlanner = new SbplPlanner(SbplPlanner::SbplType::SBPL_ARASTAR);
    if (sbplPlanner->run()) {
      sbplStats =
          PathEvaluation::evaluate(sbplPlanner->solution(), "SBPL (ANA*)");
#if QT_SUPPORT
      sbplStats.color = Qt::darkGreen;
#endif
    }
    info["plans"]["sbpl"] = {
        {"curvature", sbplStats.curvature},
        {"pathLength", sbplStats.pathLength},
        {"steps", std::nan("N/A")},
        {"time", sbplPlanner->planningTime()},
        {"meanClearingDistance", sbplStats.meanClearingDistance},
        {"medianClearingDistance", sbplStats.medianClearingDistance},
        {"minClearingDistance", sbplStats.minClearingDistance},
        {"maxClearingDistance", sbplStats.maxClearingDistance},
        {"path", Log::serializePath(sbplPlanner->solutionPath())},
        {"trajectory", Log::serializeTrajectory(sbplPlanner->solution())}};
    delete sbplPlanner;

    //        printStats(thetaStarStats);
    //        std::cout << "\tSteps:\t\t\t" << thetaStar->steps() << std::endl;
    //        std::cout << "\tTime:\t\t\t" << thetaStar->planningTime() <<
    //        std::endl; printStats(gripsStats); std::cout << "\tSteps:\t\t\t"
    //        << thetaStar->steps() << std::endl; std::cout << "\tTime:\t\t\t"
    //        << PostSmoothing::smoothingTime + thetaStar->planningTime() <<
    //        std::endl; printStats(smoothThetaStarStats); std::cout <<
    //        "\tSteps:\t\t\t" << smoothThetaStar->steps() << std::endl;
    //        std::cout << "\tTime:\t\t\t" << smoothThetaStar->planningTime() <<
    //        std::endl;
    //
    Log::log(info);

    if (++counter > 10)
        break;
  }

  Log::save();

#if DEBUG
  QtVisualizer::show();
  return QtVisualizer::exec();
#else
  return EXIT_SUCCESS;
#endif
}