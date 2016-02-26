// A simple example of using the Ceres minimizer.
//
// Minimize 0.5 (10 - x)^2 using jacobian matrix computed using
// automatic differentiation.
#include <stdio.h>
#include <sstream>

#include "ceres/ceres.h"
#include "glog/logging.h"

#ifdef EMSCRIPTEN

#include "emscripten/emscripten.h"
#include "emscripten/bind.h"

using namespace emscripten;

#endif

using ceres::AutoDiffCostFunction;
using ceres::CostFunction;
using ceres::Problem;
using ceres::Solver;
using ceres::Solve;

using namespace std;


struct Point2D {
  double x;
  double y;
  Point2D() {}
  Point2D(double x_, double y_) : x(x_), y(y_) {}
};


struct CostFunctor {
  double* goal_pose;
  CostFunctor(double* g) : goal_pose(g) {}
  template <typename T> bool operator()(const T* const current_pose, T* residual) const {
    // Objective function: residual = 50^2 - ((x - x_)^2 + (y - y_)^2)
    residual[0] = T(10000.0) - (T(goal_pose[0]) - current_pose[0]) * (T(goal_pose[0]) - current_pose[0]) - (T(goal_pose[1]) - current_pose[1]) * (T(goal_pose[1]) - current_pose[1]);
    return true;
  }
};


class AvoiderSolver {
  
private:
  
  double current_pose_[2];
  double goal_pose_[2];
  Problem problem_; 
  
public:
  
  AvoiderSolver() {
    current_pose_[0] = 0;
    current_pose_[1] = 0;
    goal_pose_[0] = 0;
    goal_pose_[1] = 0;
    buildProblem();
  }
  
  Point2D getCurrentPose() const {
    Point2D p;
    p.x = current_pose_[0];
    p.y = current_pose_[1];
    return p;
  }
  void setCurrentPose(Point2D p) {
    current_pose_[0] = p.x;
    current_pose_[1] = p.y;
  }
  
  Point2D getGoalPose() const {
    Point2D p;
    p.x = goal_pose_[0];
    p.y = goal_pose_[1];
    return p;
  }
  void setGoalPose(Point2D p) {
    goal_pose_[0] = p.x;
    goal_pose_[1] = p.y;
  }
  
  void buildProblem() {
    CostFunction* cost_function =
        new AutoDiffCostFunction<CostFunctor, 1, 2>(new CostFunctor(goal_pose_));
    problem_.AddResidualBlock(cost_function, NULL, current_pose_);
  }
  
  void stepSolve(int step_limit) {
    // Run the solver!
    Solver::Options options;
    options.max_num_iterations = step_limit;
    options.logging_type = ceres::SILENT;
    options.minimizer_type = ceres::LINE_SEARCH;
    Solver::Summary summary;
    Solve(options, &problem_, &summary);
  }
  
  void timeSolve(double time_limit) {
    // Run the solver!
    Solver::Options options;
    options.max_solver_time_in_seconds = time_limit;
    options.logging_type = ceres::SILENT;
    options.minimizer_type = ceres::LINE_SEARCH;
    Solver::Summary summary;
    Solve(options, &problem_, &summary);
  }
};

/*
class RenderingCallback : public IterationCallback {
 public:
  explicit RenderingCallback(double* x)
      : x_(x) {}

  ~RenderingCallback() {}

  CallbackReturnType operator()(const IterationSummary& summary) {
    ostringstream strs;
    strs << "Module.print('x = " << *x_ << "')";
    emscripten_run_script(strs.str().c_str());
    cout << "Iteration " << summary.iteration << endl;
    return SOLVER_CONTINUE;
  }

 private:
  const double* x_;
};
*/

#ifdef EMSCRIPTEN

EMSCRIPTEN_BINDINGS() {
    value_array<Point2D>("Point2D")
        .element(&Point2D::x)
        .element(&Point2D::y)
        ;

    class_<AvoiderSolver>("AvoiderSolver")
        .constructor<>()
        .function("stepSolve", &AvoiderSolver::stepSolve)
        .function("timeSolve", &AvoiderSolver::timeSolve)
        .property("goal_pose", &AvoiderSolver::getGoalPose, &AvoiderSolver::setGoalPose)
        .property("current_pose", &AvoiderSolver::getCurrentPose, &AvoiderSolver::setCurrentPose)
        ;
}

#else

int main(int argc, char** argv) {
  AvoiderSolver solver;
  solver.setGoalPose(Point2D(30,100));
  solver.stepSolve(10);
  Point2D final_pose = solver.getCurrentPose();
  cout << "final_pose.x = " << final_pose.x << ", " << "final_pose.y = " << final_pose.y << "\n";
  return 0;
}

#endif
