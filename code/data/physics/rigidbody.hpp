#ifndef RIGIDBODY_INCLUDED_52FD6DE0_2B99_45F3_93DB_E55B1FA97275
#define RIGIDBODY_INCLUDED_52FD6DE0_2B99_45F3_93DB_E55B1FA97275


#include "motion_state.hpp"
#include <btBulletDynamicsCommon.h>
#include <memory>


namespace Physics {

/*!
  Bullet has a you allocate you destroy policy.
  We are just holing on to these so we can clean up memory.
*/
struct Rigidbody
{
  std::unique_ptr<Motion_state>       motion_state;
  std::unique_ptr<btRigidBody>        rigidbody;
  std::unique_ptr<btCollisionShape>   shape;
};


/*!
  Apply force to a rigidbody.
*/
void
rigidbody_apply_local_force(Rigidbody *rb, const float force[3]);


/*!
  Apply torque to a rigidbody
*/
void
rigidbody_apply_local_torque(Rigidbody *rb, const float torque[3]);


} // ns


#endif // inc guard