#include "CtrlObjective.h"

//===========================================================================

void getForceControlCoeffs(arr& f_des, arr& u_bias, arr& KfL, arr& J_ft, const rai::Configuration& world);
void fwdSimulateControlLaw(arr& Kp, arr& Kd, arr& u0, rai::Configuration& world);

//===========================================================================

/// implements a number of basic equations given a set of control tasks
struct TaskControlMethods {
  arr Hmetric;           ///< defines the metric in q-space (or qddot-space)
  boolA lockJoints;

  TaskControlMethods(const arr& _Hmetric);

  CtrlObjective* addPDTask(CtrlObjectiveL& tasks, const char* name, double decayTime, double dampingRatio, ptr<Feature> map);

//  void updateCtrlObjectives(double tau, const rai::Configuration& world);
//  void resetCtrlObjectivesState();

  void lockJointGroup(const char* groupname, rai::Configuration& world, bool lockThem=true);

  double getIKCosts(CtrlObjectiveL& tasks, const arr& q=NoArr, const arr& q0=NoArr, arr& g=NoArr, arr& H=NoArr);
  arr inverseKinematics(CtrlObjectiveL& tasks, arr& qdot, const arr& P_compliance, const arr& nullRef=NoArr, double* cost=nullptr);
  arr inverseKinematics_hierarchical(CtrlObjectiveL& tasks);
  arr getComplianceProjection(CtrlObjectiveL& tasks);
  arr operationalSpaceControl(CtrlObjectiveL& tasks);
  arr calcOptimalControlProjected(CtrlObjectiveL& tasks, arr& Kp, arr& Kd, arr& u0, const arr& q, const arr& qdot, const arr& M, const arr& F); ///< returns the linearized control law
  arr getDesiredLinAccLaw(CtrlObjectiveL& tasks, arr& Kp, arr& Kd, arr& u0, const arr& q, const arr& qdot); ///< returns the linearized control law
  arr getDesiredConstraintForces(CtrlObjectiveL& tasks); ///< J^T lambda^*
  void calcForceControl(CtrlObjectiveL& tasks, arr& K_ft, arr& J_ft_inv, arr& fRef, double& gamma, const rai::Configuration& world); ///< returns the force controller coefficients
  void reportCurrentState(CtrlObjectiveL& tasks);
};