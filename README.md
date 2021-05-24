# Simulating a Double Pendulum

For the last few projects I have done, I have used raylib quite a bit. This is in order to sort of prepare myself for OpenGL. Since this project's core is more based around physics, the math isn't that hard to implement. This is going to be a way of me improving my knowledge of more abstract concepts in graphical programming, rather than implementing physics into code.

## Physics

To get the boring stuff out of the way first, the movement of a double pendulum is governed by these two equations

$$
\theta_1'' = \frac{-g(2m_1 + m_2) sin \theta_1 - m_2gsin(\theta_1 - 2\theta_2) - 2sin(\theta_1 - \theta_2)m_2(\theta_2'^2L_2 + \theta_1'^2L_1cos(\theta_1 - \theta_2))}{L_1(2m_1 + m_2 - m_2 cos(2\theta_1 - 2\theta_2))}
$$
$$
\theta_2'' = \frac{2sin(\theta_1 - \theta_2)(\theta_1'^2L_1(m_1+m_2) + g(m_1 + m_2)cos \theta_1 + \theta_2'^2L_2m_2cos(\theta_1 - \theta_2))}{L_2(2m_1 + m_2 - m_2 cos(2\theta_1 - 2\theta_2))}
$$

where $\theta$ is the angle of the bearing on each rod, meaning that $\theta'$ is the first time derivative and $\theta''$ is the second time derivative.

The given equations are used to calculate the angular accelerations of the masses as a function of the angular velocities, masses and lengths of the rods.

These 2 equations were derived using the Lagrangian method or purely with the Newtonian physics way, both of which would lead to the same result, however one being less laborious than the other _(Lagrangian_ ;)_)_...

## Documentation

TODO

## Build Instructions

TODO

## Contribution

Please feel free to submit a pull request, I promise to review your request in a period of 48 hours as long as the project is marked active.