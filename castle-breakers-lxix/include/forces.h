#ifndef __FORCES_H__
#define __FORCES_H__

#include "scene.h"

typedef struct {
  int type;
  int hits;
  int max_health;
} block_data;

/**
 * A function called when a collision occurs.
 * @param body1 the first body passed to create_collision()
 * @param body2 the second body passed to create_collision()
 * @param axis a unit vector pointing from body1 towards body2
 *   that defines the direction the two bodies are colliding in
 * @param aux the auxiliary value passed to create_collision()
 */
typedef void (*CollisionHandler)
    (Body *body1, Body *body2, Vector axis, void *aux);

/**
 * Adds a Newtonian gravitational force between two bodies in a scene.
 * See https://en.wikipedia.org/wiki/Newton%27s_law_of_universal_gravitation#Vector_form.
 * The force should not be applied when the bodies are very close,
 * because its magnitude blows up as the distance between the bodies goes to 0.
 *
 * @param scene the scene containing the bodies
 * @param G the gravitational proportionality constant
 * @param body1 the first body
 * @param body2 the second body
 */
void create_newtonian_gravity(Scene *scene, double G, Body *body1, Body *body2);

/**
 * Adds a Hooke's-Law spring force between two bodies in a scene.
 * See https://en.wikipedia.org/wiki/Hooke%27s_law.
 *
 * @param scene the scene containing the bodies
 * @param k the Hooke's constant for the spring
 * @param body1 the first body
 * @param body2 the second body
 */
void create_spring(Scene *scene, double k, Body *body1, Body *body2);

/**
 * Adds a drag force on a body proportional to its velocity.
 * The force points opposite the body's velocity.
 *
 * @param scene the scene containing the bodies
 * @param gamma the proportionality constant between force and velocity
 *   (higher gamma means more drag)
 * @param body the body to slow down
 */
void create_drag(Scene *scene, double gamma, Body *body);

/**
 * Adds a drag force on a cannon ball proportional to its velocity.
 * The force points opposite the body's velocity in the x direction only.
 *
 * @param scene the scene containing the bodies
 * @param gamma the proportionality constant between force and velocity
 *   (higher gamma means more drag)
 * @param body the body to slow down
 */

void create_drag_force_cannon(Scene *scene, double g, Body *body);
/**
 * Adds a constant gravitational acceleration on a body of magnitude
 * g that points downwards
 *
 * @param scene the scene containing the bodies
 * @param g the acceleration of gravity
 * @param body the body to apply gravity to
 */
void create_flat_earth(Scene *scene, double g, Body *body);

/**
 * Adds a ForceCreator to a scene that flags two bodies for removal
 * if they ever collide
 *
 * @param scene the scene containing the bodies
 * @param body1 the first body
 * @param body2 the second body
 */
void create_destructive_collision(Scene *scene, Body *body1, Body *body2);

/**
 * Adds a ForceCreator to a scene that calls a given CollisionHandler
 * each time two bodies collide.
 * This generalizes create_destructive_collision() from last week,
 * allowing different things to happen when bodies collide.
 * The handler is passed the bodies, the collision axis, and an auxiliary value.
 * It should only be called once while the bodies are still colliding.
 *
 * @param scene the scene containing the bodies
 * @param body1 the first body
 * @param body2 the second body
 * @param handler a function to call whenever the bodies collide
 * @param aux an auxiliary value to pass to the handler
 * @param freer if non-NULL, a function to call in order to free aux
 */
void create_collision(
    Scene *scene,
    Body *body1,
    Body *body2,
    CollisionHandler handler,
    void *aux,
    FreeFunc freer
);

/**
 * Adds a ForceCreator to a scene that applies impulses
 * to resolve collisions between two bodies in the scene.
 * This should be represented as an on-collision callback
 * registered with create_collision().
 *
 * You may remember from project01 that you should avoid applying impulses
 * multiple times while the bodies are still colliding.
 * You should also have a special case that allows either body1 or body2
 * to have mass INFINITY, as this is useful for simulating walls.
 *
 * @param scene the scene containing the bodies
 * @param elasticity the "coefficient of restitution" of the collision;
 * 0 is a perfectly inelastic collision and 1 is a perfectly elastic collision
 * @param body1 the first body
 * @param body2 the second body
 */
void create_physics_collision(
    Scene *scene, double elasticity, Body *body1, Body *body2
);


#endif // #ifndef __FORCES_H__
