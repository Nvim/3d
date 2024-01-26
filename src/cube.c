#include "../include/header.h"

void init_cube() {

  // South:
  cubeMesh[0].p[0] = (vec3){0.0f, 0.0f, 0.0f};
  cubeMesh[0].p[1] = (vec3){0.0f, 1.0f, 0.0f};
  cubeMesh[0].p[2] = (vec3){1.0f, 1.0f, 0.0f};
  cubeMesh[1].p[0] = (vec3){0.0f, 0.0f, 0.0f};
  cubeMesh[1].p[1] = (vec3){1.0f, 1.0f, 0.0f};
  cubeMesh[1].p[2] = (vec3){1.0f, 0.0f, 0.0f};

  // East:
  cubeMesh[2].p[0] = (vec3){1.0f, 0.0f, 0.0f};
  cubeMesh[2].p[1] = (vec3){1.0f, 1.0f, 0.0f};
  cubeMesh[2].p[2] = (vec3){1.0f, 1.0f, 1.0f};
  cubeMesh[3].p[0] = (vec3){1.0f, 0.0f, 0.0f};
  cubeMesh[3].p[1] = (vec3){1.0f, 1.0f, 1.0f};
  cubeMesh[3].p[2] = (vec3){1.0f, 0.0f, 1.0f};

  // North
  cubeMesh[4].p[0] = (vec3){1.0f, 0.0f, 1.0f};
  cubeMesh[4].p[1] = (vec3){1.0f, 0.0f, 1.0f};
  cubeMesh[4].p[2] = (vec3){1.0f, 1.0f, 1.0f};
  cubeMesh[5].p[0] = (vec3){1.0f, 0.0f, 1.0f};
  cubeMesh[5].p[1] = (vec3){0.0f, 1.0f, 1.0f};
  cubeMesh[5].p[2] = (vec3){0.0f, 0.0f, 1.0f};

  // West:
  cubeMesh[6].p[0] = (vec3){0.0f, 0.0f, 1.0f};
  cubeMesh[6].p[1] = (vec3){0.0f, 1.0f, 1.0f};
  cubeMesh[6].p[2] = (vec3){0.0f, 1.0f, 0.0f};
  cubeMesh[7].p[0] = (vec3){0.0f, 0.0f, 1.0f};
  cubeMesh[7].p[1] = (vec3){0.0f, 1.0f, 0.0f};
  cubeMesh[7].p[2] = (vec3){0.0f, 0.0f, 0.0f};

  // Top:
  cubeMesh[8].p[0] = (vec3){0.0f, 1.0f, 0.0f};
  cubeMesh[8].p[1] = (vec3){0.0f, 1.0f, 1.0f};
  cubeMesh[8].p[2] = (vec3){1.0f, 1.0f, 1.0f};
  cubeMesh[9].p[0] = (vec3){0.0f, 1.0f, 0.0f};
  cubeMesh[9].p[1] = (vec3){1.0f, 1.0f, 1.0f};
  cubeMesh[9].p[2] = (vec3){1.0f, 1.0f, 0.0f};

  // Bottom:
  cubeMesh[10].p[0] = (vec3){1.0f, 0.0f, 1.0f};
  cubeMesh[10].p[2] = (vec3){0.0f, 0.0f, 1.0f};
  cubeMesh[10].p[2] = (vec3){0.0f, 0.0f, 0.0f};
  cubeMesh[11].p[0] = (vec3){1.0f, 0.0f, 1.0f};
  cubeMesh[11].p[2] = (vec3){0.0f, 0.0f, 0.0f};
  cubeMesh[11].p[2] = (vec3){1.0f, 0.0f, 0.0f};
}
